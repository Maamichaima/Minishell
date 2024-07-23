SRC = main.c lst.c get_token.c valide_syntax.c cmd_path.c create_tree.c env.c set_env.c\
      redirection.c execution.c pre_execution.c builtins_utils.c quotes.c execute_builtins.c\
      sort_export.c count_cmd.c expand.c ft_malloc.c builtins_cd.c builtins_exit.c\
	  builtins_pwd.c builtins_echo.c builtins_unset.c builtins_export.c builtins_env.c\
	  utils_0.c lst_str.c herdoc.c utils_1.c expand_utils.c set_env_utils.c valide_syntax_utils.c\
	  signal.c wait_close.c
OBJ = ${SRC:.c=.o}

CFLAGS = -g3 #-fsanitize=address  #-Wall -Wextra -Werror 
LDFLAGS = -lreadline
NAME = minishell
LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a
CC = cc -g

all: ${NAME}

${NAME}: ${OBJ} $(LIBFT)
	@$(CC) -o ${NAME} ${OBJ} ${LIBFT} ${LDFLAGS} ${CFLAGS}
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
