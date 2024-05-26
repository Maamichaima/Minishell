SRC = main.c lst.c get_token.c valide_syntax.c create_tree.c env.c redirection.c
OBJ = ${SRC:.c=.o}

LDFLAGS = -lreadline
NAME = minishell

all: ${NAME}

${NAME}: ${OBJ}
	cc -o ${NAME} ${OBJ} ${LDFLAGS} -fsanitize=address -g

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all
