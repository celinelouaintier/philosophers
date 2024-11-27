.SILENT:

NAME	= philo

SRCS 	= main.c utils.c threads.c init.c states.c
SRCS_DIR = srcs/
SRC 	= ${addprefix ${SRCS_DIR}, ${SRCS}}
OBJS 	= ${SRC:.c=.o}

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -I./includes


%.o: %.c
					@echo "\033[34mCompiling $<..."
					$(CC) $(CFLAGS) -c $< -o $@

all: 		${NAME}

${NAME}:	${OBJS}
					$(CC) $(CFLAGS) ${OBJS} -o ${NAME}
					@echo "\033[32mPhilo Compiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

clean:
					rm -f ${OBJS}

fclean: 	clean
					rm -f ${NAME}
					@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"

re:			fclean all

.PHONY: all clean fclean re re_bonus bonus party