# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isb3 <isb3@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 11:33:14 by adesille          #+#    #+#              #
#    Updated: 2024/07/13 07:06:50 by isb3             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## ARGUMENTS ########################

NAME = philo
CFLAGS += -Wall -Wextra -MP -MD -g3 -I. -pthread
CC = cc 

DEFAULT = \033[0;39m
BLUE = \033[0;34m
GREEN = \033[0;32m
RED = \033[31;1m
WHITE = \033[0;37m

######################## SOURCES ########################

SRCS = main.c ./srcs/utils.c \
	./srcs/memory_manager.c ./srcs/memory_manager_utils.c

DEPFILES = $(SRCS:%c=$(OBJ_DIR)/%.o)
OBJ_DIR = .obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

######################## UTILS ########################

GREEN = \033[0;92m
CURRENT_DATE	:= $(shell date +"%Y-%m-%d %H:%M")

VALGRIND = valgrind -s --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all --suppressions=valgrind.supp --quiet ./minishell

######################## RULES ########################

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@if [ ! -d .obj/srcs ]; then \
	    echo "$(WHITE)\nCompiling Philosophers files...$(DEFAULT)"; \
	fi
	@$(CC) $(CFLAGS) -c $< -o $@

val :
	@$(VALGRIND)

clean :
	@rm -rf $(OBJ_DIR) $(DEPFILES)
	@echo "$(BLUE)\nEvery files are cleaned$(DEFAULT)"

fclean : clean
	@rm -f $(NAME)

re : fclean all

git:
	@git add . > /dev/null 2>&1
	@git commit -m "$(CURRENT_DATE)" > /dev/null 2>&1
	@git push > /dev/null 2>&1
	@echo "$(GREEN)┌(メ▼▼)┘ GIT UPDATE └(▼▼メ)┐ $(DEF_COLOR)"

-include $(DEPFILES)

.PHONY : all clean fclean re val git