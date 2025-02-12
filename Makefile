# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 15:05:53 by lbenatar          #+#    #+#              #
#    Updated: 2025/02/12 11:36:28 by lbenatar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET  = $(shell printf "\33[0m")
GREEN  = $(shell printf "\33[32m")

SRC	= ./src/fonctions_utils.c \
		./src/fonctions_utils2.c \
		./src/gestion_forks.c \
		./src/liberator.c \
		./src/parsing.c \
		./src/philosophers_life.c \
		./src/ft_atoi.c \
		./src/lone_philo_sad_life.c \

CFLAGS	= -Wall -Wextra -Werror -pthread

# Run 'make re MODE=pretty' for color formatting.
# Run 'make re MODE=debug' for debug formatting.
MODE	= none
ifeq ($(MODE), pretty)
	CFLAGS	+= -D DEBUG_FORMATTING=1
endif
ifeq ($(MODE), debug)
	CFLAGS	+= -D DEBUG_FORMATTING=1 -fsanitize=thread -g
endif

NAME = philosophers.a

NAME_EXE = philo

OBJ	= $(SRC:.c=.o)

.c.o	:
		cc ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME} : ${OBJ}
		ar rc ${NAME} ${OBJ}
		cc ${CFLAGS} ./src/main.c -L. ${NAME} -o ${NAME_EXE}
		@echo "$(GREEN)$(NAME_EXE) successfully created!$(RESET)"

all : ${NAME}

clean :
		@rm -f ${OBJ}
		@rm -rf ./src/*.o
		@echo "$(GREEN)Successfully cleaned!$(RESET)"

fclean : clean
		@rm -f ${NAME}
		@rm -f ${NAME_EXE}
		@echo "$(GREEN)Successfully fcleaned!$(RESET)"

re : fclean all

.PHONY:	all clean fclean re libft
