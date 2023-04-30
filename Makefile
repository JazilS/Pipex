# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsabound <jsabound@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 18:16:16 by jsabound          #+#    #+#              #
#    Updated: 2023/04/30 19:24:42 by jsabound         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		= ./srcs
BONUS_DIR	= ./srcs_bonus
SRCS		=	main.c\
				forks.c\
				free.c\
				parsing.c\
				pipex.c
BONUS_SRCS	=	main_bonus.c\
				forks_bonus.c\
				free_bonus.c\
				parsing_bonus.c\
				pipex_bonus.c\
				here_doc.c

OBJS			=	$(addprefix $(SRC_DIR)/, $(SRCS:%.c=%.o))
BONUS_OBJS		=	$(addprefix $(BONUS_DIR)/, $(BONUS_SRCS:%.c=%.o))
NAME			=	pipex
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -g3
RM				=	rm -f

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	$(OBJS)
	cd libft && make
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) libft/libft.a

all:		${NAME}

clean:	
	cd libft && make fclean
	${RM} ${OBJS} ${BONUS_OBJS}

bonus:		$(BONUS_OBJS)
	cd libft && make 
	$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJS) libft/libft.a 
	
fclean:		clean
		${RM} ${NAME}

re:			fclean all

.PHONY: 	all clean fclean re