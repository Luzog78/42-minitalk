# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 06:25:02 by ysabik            #+#    #+#              #
#    Updated: 2024/05/04 14:44:05 by ysabik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC					= gcc
CFLAGS				= -Werror -Wall -Wextra
INCLUDES			= includes
NAME				= minitalk

SERVER_NAME			= server
CLIENT_NAME			= client

SERVER_SRC_FILES	= mandatory/server.c
CLIENT_SRC_FILES	= mandatory/client.c mandatory/ft_kill.c

# When I pushed, I copied the files,
#  put the copies in a 'bonus' folder,
#  and replaced the '.c' by '_bonus.c'.
B_SERVER_SRC_FILES	= mandatory/server.c 
B_CLIENT_SRC_FILES	= mandatory/client.c mandatory/ft_kill.c


# **************************************************************************** #


ifeq ($(filter bonus, $(MAKECMDGOALS)), bonus)
	SERVER_OBJ_FILES	= $(B_SERVER_SRC_FILES:.c=.o)
	CLIENT_OBJ_FILES	= $(B_CLIENT_SRC_FILES:.c=.o)
else
	SERVER_OBJ_FILES	= $(SERVER_SRC_FILES:.c=.o)
	CLIENT_OBJ_FILES	= $(CLIENT_SRC_FILES:.c=.o)
endif


# **************************************************************************** #


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
	rm -rf $(SERVER_SRC_FILES:.c=.o) $(CLIENT_SRC_FILES:.c=.o)
	rm -rf $(B_SERVER_SRC_FILES:.c=.o) $(B_CLIENT_SRC_FILES:.c=.o)


fclean : clean
	rm -rf $(SERVER_NAME) $(CLIENT_NAME)


re : fclean all


.PHONY : all bonus clean fclean re
