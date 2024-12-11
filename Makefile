# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomlimon <tomlimon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 13:38:25 by tomlimon          #+#    #+#              #
#    Updated: 2024/12/11 14:33:36 by tomlimon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = ./src/main.c ./src/error.c

LIBFT_SRCS = 

ALL_SRCS = $(SRCS) $(LIBFT_SRCS)

OBJS = $(ALL_SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = 

YELLOW = \033[0;33m
GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo -e "$(YELLOW)Compiling $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo -e "$(GREEN)Compilation successful!$(RESET)"

%.o: %.c
	@echo -e "$(YELLOW)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo -e "$(YELLOW)Cleaning object files...$(RESET)"
	rm -f $(OBJS)

fclean: clean
	@echo -e "$(YELLOW)Removing executable...$(RESET)"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re