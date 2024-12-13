# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 18:05:01 by aokhapki          #+#    #+#              #
#    Updated: 2024/12/13 19:40:37 by aokhapki         ###   ########.fr        #
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

$(NAME):    $(OBJS) include
			@echo "\033[0;34m---- Compiling Minishell Project ----\033[0m"
			@make -C $(LIB_DIR)
			@$(CC) $(CFLAGS) $(OBJS) $(LIB_DIR)/libft.a -o $(NAME)
			@echo "\033[0;32mMinishell is ready to run!\033[0m"

%.o:        %.c
			@$(CC) $(CFLAGS) -c $< -o $@ $(HEADER)

clean:
			@make clean -C $(LIB_DIR)
			@$(RM) $(OBJS)
			@echo "\033[0;31mCleaned up object files!\033[0m"

fclean:      clean
			@make fclean -C $(LIB_DIR)
			@$(RM) $(NAME)
			@echo "\033[0;31mCompletely cleaned the project!\033[0m"

re:          fclean all

.PHONY:      all clean fclean re