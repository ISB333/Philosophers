# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adesille <adesille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 11:33:14 by adesille          #+#    #+#              #
#    Updated: 2024/09/30 09:46:57 by adesille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## ARGUMENTS ########################

NAME = philo
CFLAGS += -Wall -Wextra -MP -MD -g3 -I.
CC = cc 

DEFAULT = \033[0;39m
BLUE = \033[0;34m
GREEN = \033[0;32m
RED = \033[31;1m
WHITE = \033[0;37m

######################## SOURCES ########################

SRCS = ./srcs/main.c ./srcs/init_n_manage.c ./srcs/activities.c ./srcs/verification.c

UTILS =./srcs/utils/utils.c \
	./srcs/utils/memory_manager.c ./srcs/utils/memory_manager_utils.c

DEPFILES = $(SRCS:%c=$(OBJ_DIR)/%.o) \
		$(UTILS:%c=$(OBJ_DIR)/%.o)
OBJ_DIR = .obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o) \
		$(UTILS:%.c=$(OBJ_DIR)/%.o)

######################## RULES ########################

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@if [ ! -d .obj/srcs ]; then \
	    echo "$(WHITE)\nCompiling Philosophers files...$(DEFAULT)"; \
	fi
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJ_DIR) $(DEPFILES)
	@echo "$(BLUE)\nEvery files are cleaned$(DEFAULT)"

fclean : clean
	@rm -f $(NAME)

re : fclean all

-include $(DEPFILES)

.PHONY : all clean fclean re val git