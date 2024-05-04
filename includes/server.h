/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:00:22 by ysabik            #+#    #+#             */
/*   Updated: 2024/05/04 12:04:55 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

typedef enum e_type
{
	SIZE,
	MESSAGE
}	t_type;

typedef struct s_data
{
	size_t	len;
	size_t	received_chars;
	size_t	received_bits;
	t_type	type;
	char	*message;
	int		client_pid;
}	t_data;

#endif
