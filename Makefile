# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 06:25:02 by ysabik            #+#    #+#              #
#    Updated: 2023/11/17 06:53:40 by ysabik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC					= cc
CFLAGS				= -Werror -Wall -Wextra
INCLUDES			= .
NAME				= minitalk
SERVER_NAME			= server
CLIENT_NAME			= client
SERVER_SRC_FILES	= server.c
CLIENT_SRC_FILES	= client.c
SERVER_OBJ_FILES	= $(SERVER_SRC_FILES:.c=.o)
CLIENT_OBJ_FILES	= $(CLIENT_SRC_FILES:.c=.o)

FT_PRINTF_DIR		= ./ft_printf
FT_PRINTF_LIB		= $(FT_PRINTF_DIR)/libftprintf.a
FT_PRINTF_FLAGS		= -I $(FT_PRINTF_DIR) -L $(FT_PRINTF_DIR) -lftprintf
FT_PRINTF_MAKE		= make -C $(FT_PRINTF_DIR)

all : $(NAME)

$(NAME) : $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME) : ft_printf $(SERVER_OBJ_FILES)
	$(CC) $(CFLAGS) -o $(SERVER_NAME) $(SERVER_OBJ_FILES) \
		-I $(INCLUDES) $(FT_PRINTF_FLAGS)

$(CLIENT_NAME) : ft_printf $(CLIENT_OBJ_FILES)
	$(CC) $(CFLAGS) -o $(CLIENT_NAME) $(CLIENT_OBJ_FILES) \
		-I $(INCLUDES) $(FT_PRINTF_FLAGS)

bonus : all

ft_printf :
	$(FT_PRINTF_MAKE)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES) $(FT_PRINTF_FLAGS)

clean :
	$(FT_PRINTF_MAKE) clean
	rm -rf $(SERVER_OBJ_FILES) $(CLIENT_OBJ_FILES)

fclean : clean
	$(FT_PRINTF_MAKE) fclean
	rm -rf $(SERVER_NAME) $(CLIENT_NAME)

re : fclean all

.PHONY : all bonus ft_printf clean fclean re
