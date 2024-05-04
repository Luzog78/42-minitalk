# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 06:25:02 by ysabik            #+#    #+#              #
#    Updated: 2024/05/04 10:54:55 by ysabik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC					= gcc
CFLAGS				= -Werror -Wall -Wextra
INCLUDES			= .
NAME				= minitalk
SERVER_NAME			= server
CLIENT_NAME			= client
SERVER_SRC_FILES	= server.c
CLIENT_SRC_FILES	= client.c
SERVER_OBJ_FILES	= $(SERVER_SRC_FILES:.c=.o)
CLIENT_OBJ_FILES	= $(CLIENT_SRC_FILES:.c=.o)

all : $(NAME)

$(NAME) : $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME) : $(SERVER_OBJ_FILES)
	$(CC) $(CFLAGS) -o $(SERVER_NAME) $(SERVER_OBJ_FILES) -I $(INCLUDES)

$(CLIENT_NAME) : $(CLIENT_OBJ_FILES)
	$(CC) $(CFLAGS) -o $(CLIENT_NAME) $(CLIENT_OBJ_FILES) -I $(INCLUDES)

bonus : all

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

clean :
	rm -rf $(SERVER_OBJ_FILES) $(CLIENT_OBJ_FILES)

fclean : clean
	rm -rf $(SERVER_NAME) $(CLIENT_NAME)

re : fclean all

.PHONY : all bonus clean fclean re
