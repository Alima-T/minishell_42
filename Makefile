# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbolsako <tbolsako@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 18:05:01 by aokhapki          #+#    #+#              #
#    Updated: 2025/03/20 19:21:23 by tbolsako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

LIB_DIR     = LIBFT
SRCS        = ${shell find ./srcs -name "*.c"}
OBJS        = $(patsubst %.c,%.o,$(SRCS))

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror # -I$(RDL_DIR)/include
# RDL_DIR		=	/opt/homebrew/opt/readline
RDL			=	-lreadline # -L$(RDL_DIR)/lib

RM			=	rm -f

all:        $(NAME)

$(NAME):	$(OBJS) 
			@echo "\033[0;32m----Compiling project----\033[0m"
			@make -s -C $(LIB_DIR)
			@$(CC) $(CFLAGS) $^ $(LIB_DIR)/libft.a -o $@ $(RDL)
			@echo "\033[0;33mType \033[1;32m./minishell\033[0;33m to go into minishell!\033[0m"


%.o:        %.c
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@make clean -s -C $(LIB_DIR)
			@$(RM) $(OBJS)
			@echo "\033[0;33mCleaned up object files!\033[0m"

fclean:      clean
			@make fclean -s -C $(LIB_DIR)
			@$(RM) $(NAME)
			@echo "\033[0;33mCompletely cleaned the project!\033[0m"

re:          fclean all

.PHONY:      all clean fclean re