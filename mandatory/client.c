/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 06:30:36 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/04 14:24:16 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	g_received = 0;

static void	action(int sig)
{
	(void) sig;
	g_received = 1;
}

static void	ft_send_size(int pid, const char *str)
{
	int	sent;
	int	str_len;

	str_len = 0;
	while (str[str_len])
		str_len++;
	sent = 0;
	while (sent < 32)
	{
		if (str_len & (1 << (31 - sent)))
			ft_kill(pid, SIGUSR2);
		else
			ft_kill(pid, SIGUSR1);
		if (g_received)
			break ;
		sent++;
	}
}

static void	ft_send(int pid, const char *str)
{
	int				sent;
	unsigned char	curr;

	ft_send_size(pid, str);
	while (*str)
	{
		curr = *str;
		sent = 0;
		while (sent < 8 && !g_received)
		{
			if (curr & (1 << (7 - sent)))
				ft_kill(pid, SIGUSR2);
			else
				ft_kill(pid, SIGUSR1);
			sent++;
		}
		str++;
	}
	if (g_received < 0)
		write(2, "Error: Could not send the message\n", 34);
	else if (g_received > 0)
		write(2, "Error: Timout while waiting for acknowledgment\n", 47);
	else
		write(1, "The message was successfully transmitted !\n", 43);
}

static int	ft_uatoi(const char *str)
{
	long long	res;

	res = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		res = res * 10 + *str - '0';
		if (res > 2147483647)
			return (-1);
		str++;
	}
	return ((int) res);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		write(2, "Usage: ./client [PID] [MESSAGE]\n", 32);
		return (1);
	}
	pid = ft_uatoi(argv[1]);
	if (pid <= 0)
	{
		write(2, "Error: Invalid PID\n", 19);
		return (1);
	}
	signal(SIGUSR1, action);
	ft_send(pid, argv[2]);
	return (!!g_received);
}
