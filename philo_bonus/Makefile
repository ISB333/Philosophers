# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adesille <adesille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 11:33:14 by adesille          #+#    #+#              #
#    Updated: 2024/10/03 14:27:04 by adesille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## ARGUMENTS ########################

NAME = philo_bonus
CFLAGS += -Wall -Wextra -Werror -MP -MD -g3 -I. 
CC = cc 

DEFAULT = \033[0;39m
BLUE = \033[0;34m
GREEN = \033[0;32m
RED = \033[31;1m
WHITE = \033[0;37m

######################## SOURCES ########################

SRCS = ./srcs_bonus/philo_bonus.c ./srcs_bonus/philo_bonus_utils.c ./srcs_bonus/init.c \
		./srcs_bonus/activities.c ./srcs_bonus/verification.c

UTILS =./srcs_bonus/utils/utils.c \
	./srcs_bonus/utils/memory_manager.c ./srcs_bonus/utils/memory_manager_utils.c

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