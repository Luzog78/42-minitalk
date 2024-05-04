/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 06:30:36 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/04 14:33:18 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	ft_receive_size(t_data *data, int sig)
{
	data->len <<= 1;
	if (sig == SIGUSR2)
		data->len |= 1;
	if (++data->received_bits == 32)
	{
		if (data->len == 0)
			*data = (t_data){0};
		else
		{
			data->type = MESSAGE;
			data->received_chars = 0;
			data->received_bits = 0;
			data->message = malloc(data->len + 1);
			if (data->message == NULL)
				*data = (t_data){0};
			else
				data->message[data->len] = 0;
		}
	}
}

static void	ft_receive_message(t_data *data, int sig)
{
	data->message[data->received_chars] <<= 1;
	if (sig == SIGUSR2)
		data->message[data->received_chars] |= 1;
	if (++data->received_bits == 8)
	{
		if (++data->received_chars == data->len)
		{
			write(1, data->message, data->len);
			write(1, "\n", 1);
			free(data->message);
			*data = (t_data){0};
		}
		else
			data->received_bits = 0;
	}
}

static void	action(int sig, siginfo_t *info, void *context)
{
	static t_data	data = {0};

	(void) context;
	if (info->si_pid == 0)
		return ;
	if (data.client_pid == 0)
		data.client_pid = info->si_pid;
	else if (data.client_pid != info->si_pid)
	{
		data = (t_data){0};
		data.client_pid = info->si_pid;
	}
	if (data.type == SIZE)
		ft_receive_size(&data, sig);
	else
		ft_receive_message(&data, sig);
	kill(info->si_pid, SIGUSR1);
}

static void	ft_put_number(int n)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_put_number(n / 10);
	write(1, &(char){(n % 10) + '0'}, 1);
}

int	main(void)
{
	struct sigaction	sa;

	sa = (struct sigaction){0};
	write(1, "PID: ", 5);
	ft_put_number(getpid());
	write(1, "\n", 1);
	sa.sa_sigaction = &action;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
