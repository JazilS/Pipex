# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 18:16:16 by jsabound          #+#    #+#              #
#    Updated: 2023/04/27 19:48:44 by jsabound         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables

NAME		= pipex
INCLUDE		= ./
LIBFT		= libft
SRC_DIR		= srcs/
OBJ_DIR		= objects/
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
RM			= rm -f
SMAKE		= make --no-print-directory

# Colors

END			=	\033[0m
BOLD		=	\033[1m
UNDER		=	\033[4m
REV			=	\033[7m
DEF_COLOR	=	\033[0;39m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
LIGHT_RED	=	\033[0;31m
GREEN		=	\033[0;92m
YELLOW		=	\033[0;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

# Sources

SRC_FILES	=	pipex main parsing free


SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

###

OBJF		=	.cache_exists

all:		$(NAME)

bonus:		all

$(NAME):	$(OBJ)
			@$(SMAKE) -C $(LIBFT)
			@$(CC) $(OBJ) -L $(LIBFT) -lX11 -lXext -lft -lm -o $@
			@echo "$(GREEN)$(BOLD)pipex compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@$(CC) $(CFLAGS) -I $(INCLUDE) -I $(LIBFT)/includes -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -r $(OBJ_DIR)
			@echo "$(BLUE)pipex object files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) $(NAME)
			@$(SMAKE) -C $(LIBFT) fclean
			@echo "$(CYAN)pipex executable files cleaned!$(DEF_COLOR)"

re:			fclean all

.PHONY:		all clean fclean re 