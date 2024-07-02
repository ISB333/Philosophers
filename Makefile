# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adesille <adesille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 11:33:14 by adesille          #+#    #+#              #
#    Updated: 2024/07/02 08:47:55 by adesille         ###   ########.fr        #
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

SRCS = main.c

DEPFILES = $(SRCS:%c=$(OBJ_DIR)/%.o)
OFLAGS += -Wall -Wextra -g3 -I.
OBJ_DIR = .obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

######################## LIBRARY ########################

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

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
	@$(CC) $(OFLAGS) -c $< -o $@

$(LIBFT) :
	@if [ ! -f $(LIBFT)/*.o ]; then \
	    echo "$(RED)\nCompiling libft files...$(DEFAULT)\n"; \
	fi
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

val :
	@$(VALGRIND)

clean :
	@rm -rf $(OBJ_DIR) $(DEPFILES)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(BLUE)\nEvery files are cleaned$(DEFAULT)"

fclean : clean
	@rm -f $(NAME)

re : fclean all

-include $(DEPFILES)

.PHONY : all clean fclean re val