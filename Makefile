# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 18:05:01 by aokhapki          #+#    #+#              #
#    Updated: 2024/12/20 18:34:11 by tbolsako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME        = minishell

LIB_DIR     = LIBFT
SRCS        = ${shell find ./srcs -name "*.c"}
OBJS        = $(patsubst %.c,%.o,$(SRCS))

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

INCLUDES	= -I./include -I./LIBFT

all:        $(NAME)

$(NAME):    $(OBJS) $(LIB_DIR)/libft.a
			@echo "\033[0;34m---- Compiling Minishell Project ----\033[0m"
			@make -C $(LIB_DIR) || { echo "Failed to build libft"; exit 1; }
			@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIB_DIR)/libft.a -o $(NAME) -lreadline
			@echo "\033[0;32mMinishell is ready to run!\033[0m"

%.o:        %.c
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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