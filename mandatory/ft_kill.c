/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:47:09 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/04 14:15:49 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	ft_kill(int pid, int sig)
{
	int	ret;
	int	timeout;

	ret = kill(pid, sig);
	if (ret == -1)
	{
		g_received = -1;
	}
	timeout = 10000;
	while (--timeout && !g_received)
		usleep(5);
	if (g_received > 0)
		g_received = 0;
	else if (!g_received)
		g_received = 1;
}
