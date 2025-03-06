# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aokhapki <aokhapki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 18:05:01 by aokhapki          #+#    #+#              #
#    Updated: 2025/03/06 18:36:02 by aokhapki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

LIB_DIR     = LIBFT
SRCS        = ${shell find ./srcs -name "*.c"}
OBJS        = $(patsubst %.c,%.o,$(SRCS))

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -I$(RDL_DIR)/include
RDL_DIR		=	/opt/homebrew/opt/readline
RDL			=	-lreadline -L$(RDL_DIR)/lib

RM			=	rm -f

all:        $(NAME)

$(NAME):	$(OBJS) 
			@echo "\033[0;32m----Compiling project----\033[0m"
			@make -C $(LIB_DIR)
			@$(CC) $(CFLAGS) $(OBJS) $(LIB_DIR)/libft.a -o $(NAME) $(RDL)
			@echo "\033[0;33mType \033[1;32m./minishell\033[0;33m to go into minishell!\033[0m"


%.o:        %.c
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@make clean -C $(LIB_DIR)
			@$(RM) $(OBJS)
			@echo "\033[0;33mCleaned up object files!\033[0m"

fclean:      clean
			@make fclean -C $(LIB_DIR)
			@$(RM) $(NAME)
			@echo "\033[0;33mCompletely cleaned the project!\033[0m"

re:          fclean all

.PHONY:      all clean fclean re