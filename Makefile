SRC = main.c lst.c get_token.c valide_syntax.c cmd_path.c create_tree.c env.c set_env.c\
      redirection.c execution.c execve.c builtins.c builtins_utils.c quotes.c execute_builtins.c\
      sort_export.c count_cmd.c expand.c
OBJ = ${SRC:.c=.o}

FLAGS = -Wall -Wextra -Werror -fsanitize=address
LDFLAGS = -lreadline
NAME = minishell
LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a
CC = cc

all: ${NAME}

${NAME}: ${OBJ} $(LIBFT)
	@$(CC) -o ${NAME} ${OBJ} ${LIBFT} ${LDFLAGS} ${FLAGS}
	@echo "everything is successfully completed"

clean:
	@${RM} ${OBJ}
	@make -s clean -C $(LIBFT_DIR)
	@echo "clean"

fclean: clean
	@make -s fclean -C $(LIBFT_DIR)
	@${RM} ${NAME}
	@echo "fclean"

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

re: fclean all