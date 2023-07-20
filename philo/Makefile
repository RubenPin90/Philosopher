# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 16:58:54 by rpinchas          #+#    #+#              #
#    Updated: 2023/07/19 11:35:04 by rpinchas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SETUP
NAME := philo	
CFLAGS := -Werror -Wall -Wextra -pthread
DEBUG := -g
CC := cc

#FILES
SRCDIR := src
SRC_F := main.c \
	init.c \
	utils.c \
	threads.c \
	feast.c \
	feast_utils.c \
	exit.c \
	handle_mutex.c
SRC := 	${addprefix ${SRCDIR}/, ${SRC_F}}
OBJDIR := obj
OBJ_F :=  ${SRC_F:%.c=%.o}
OBJ :=	${addprefix ${OBJDIR}/, ${OBJ_F}}

#COLORS
GREEN := \033[32m
BLUE := \033[34m
YELLOW := \033[33m
RED := \033[31m
RESET := \033[0m

#RULES
all: ${OBJDIR} ${NAME}

${NAME}: ${OBJ}
	@echo "${YELLOW}Compiling...${RESET}"
	${CC} ${CFLAGS} ${DEBUG} ${OBJ} -o $@
	@echo "${GREEN}Code ready to run${RESET}"

${OBJDIR}/%.o: ${SRCDIR}/%.c
	${CC} ${CFLAGS} ${DEBUG} -I. -c $< -o $@

debug1: DEBUG += -fsanitize=address
debug1: fclean all
	@echo "DEBUG: Compiled with ${BLUE}fsanitize=address${RESET}\n\n"

debug2: DEBUG += -fsanitize=thread
debug2: fclean all 
	@echo "DEBUG: Compiled with ${BLUE}fsanitize=thread${RESET}\n\n"

${OBJDIR}: 
	@echo "${BLUE}Making object files...${RESET}"
	@mkdir -p ${OBJDIR}

clean:
	@echo "${GREEN}Removing object files...${RESET}"
	@rm -f ${OBJ}
	@rm -rf ${OBJDIR}
	@echo "${BLUE}DONE!${RESET}"

fclean: clean
	@echo "${GREEN}Removing executables...${RESET}"
	@rm	-rf ${NAME}
	@echo "${BLUE}DONE!${RESET}"

re: fclean all

.PHONY: all clean fclean debug1 debug2 re
