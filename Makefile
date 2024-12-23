# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 18:05:01 by aokhapki          #+#    #+#              #
#    Updated: 2024/12/23 12:51:16 by aokhapki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME        = minishell

LIB_DIR     = LIBFT
SRCS        = ${shell find ./srcs -name "*.c"}
OBJS        = $(patsubst %.c,%.o,$(SRCS))

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

all:        $(NAME)

$(NAME):    $(OBJS)
			@echo "\033[0;34m---- Compiling Minishell Project ----\033[0m"
			@make -C $(LIB_DIR) || { echo "Failed to build libft"; exit 1; }
			@$(CC) $(CFLAGS) $(OBJS) $(LIB_DIR)/libft.a -o $(NAME) -lreadline
			@echo "\033[0;32mMinishell is ready to run!\033[0m"

%.o:        %.c
			@$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)

clean:
			@make clean -C $(LIB_DIR)
			@$(RM) $(OBJS)
			@echo "\033[0;33mCleaned up object files!\033[0m"

fclean:      clean
			@make fclean -C $(LIB_DIR)
			@$(RM) $(NAME)
			"\033[0;33mCompletely cleaned the project!\033[0m"

re:          fclean all

.PHONY:      all clean fclean re