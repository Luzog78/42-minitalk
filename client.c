/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 06:30:36 by ysabik            #+#    #+#             */
/*   Updated: 2023/11/17 09:06:31 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

int	ft_printf(const char *format, ...);
int	ft_uatoi(const char *str);

int	received;

static void	action(int sig)
{
	(void) sig;
	received = 1;
}

static void	send(int pid, const char *str)
{
	int				sent;
	unsigned char	curr;

	while(*str)
	{
		curr = *str;
		sent = 0;
		while (sent < 8)
		{
			if (curr & (1 << (7 - sent)))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			sent++;
			usleep(100);
		}
		str++;
	}
	sent = 0;
	while (sent < 8)
	{
		kill(pid, SIGUSR1);
		sent++;
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	
	if (argc < 3)
		return (1);
	pid = ft_uatoi(argv[1]);
	signal(SIGUSR1, action);
	send(pid, argv[2]);
	while (!received)
		pause();
	return (0);
}
