/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 06:30:36 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/04 12:07:24 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

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
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (!g_received)
			pause();
		g_received = 0;
		sent++;
	}
}

static void	send(int pid, const char *str)
{
	int				sent;
	unsigned char	curr;

	ft_send_size(pid, str);
	while (*str)
	{
		curr = *str;
		sent = 0;
		while (sent < 8)
		{
			if (curr & (1 << (7 - sent)))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			while (!g_received)
				pause();
			g_received = 0;
			sent++;
		}
		str++;
	}
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
		write(1, "Usage: ./client [PID] [MESSAGE]\n", 31);
		return (1);
	}
	pid = ft_uatoi(argv[1]);
	if (pid <= 0)
	{
		write(1, "Invalid PID\n", 12);
		return (1);
	}
	signal(SIGUSR1, action);
	send(pid, argv[2]);
	return (0);
}
