SRC = main.c lst.c get_token.c valide_syntax.c cmd_path.c split.c create_tree.c env.c set_env.c\
 redirection.c execution.c execve.c builtins.c builtins_utils.c quotes.c execute_builtins.c count_cmd.c
OBJ = ${SRC:.c=.o}

LDFLAGS = -lreadline
NAME = minishell

all: ${NAME}

${NAME}: ${OBJ}
	cc -o ${NAME} ${OBJ} ${LDFLAGS} #-fsanitize=address -g

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all
