/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 06:30:36 by ysabik            #+#    #+#             */
/*   Updated: 2023/11/17 09:02:20 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

int	ft_printf(const char *format, ...);

/**
 * An int is 4*4 bits long,
 * A char is only 1*4 bits long.
 * ==> `data` will use the first 3*8 bits to store the amount of received bits
 * ==> `data` will use the last 1*8 bits to store the received bit
 * 
 * --> 0000 0000  0000 0000  0000 0000  1111 1111 <--
 *    |    Amount of received bits    ||  Char   |
*/
unsigned int	data;

static void	action(int sig, siginfo_t *info, void *context)
{
	unsigned int	tmp;

	(void) context;
	if (info->si_pid == 0)
		return ;
	tmp = data % 256;
	tmp <<= 1;
	if (sig == SIGUSR2)
		tmp += 1;
	data = (data >> 8) + 1;
	if (data >= 8)
	{
		if (tmp)
			write(1, &(char){ tmp }, 1);
		else
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR1);
		}
		data = 0;
	}
	else
		data = (data << 8) + tmp;
}

int	main(void)
{
	struct sigaction	sa;

	data = 0;
	ft_printf("PID: %d\n", getpid());
	sa.sa_sigaction = &action;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
