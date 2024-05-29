/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:55:55 by maamichaima       #+#    #+#             */
/*   Updated: 2024/05/28 22:46:51 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# define READLINE_LIBRARY
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <string.h>
# include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

typedef enum
{
	token_pipe,
	token_red_input,
	token_red_output,
	token_herd,
	token_apend,
	token_or,
	token_and,
	token_back_ope,
	token_left_par,
	token_right_par,
	token_word,
	token_cmd
}					token_type;

typedef struct s_cmd
{
	int				infile;
	int				outfile;
	char			**args;
	char			*path;
	pid_t			pid;
}					t_cmd;

typedef struct s_env
{
	char			*value;
	char			*key;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*token;
	token_type		type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_str
{
	char			*str;
	token_type		type;
	struct s_str	*next;
}					t_str;

typedef struct s_ast
{
	token_type		type;
	t_str			*args;
	t_str			*red;
	t_cmd			cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

t_token				*ft_lstnew(char *content);
t_token				*ft_lstlast(t_token *lst);
void				ft_lstadd_back(t_token **lst, t_token *new);
int					is_symbol(char c);
char				*get_next_token(char *s);
int					is_redirectien(token_type type);
int					is_valid_token(t_token *lst);
int					is_valid_word(char *s);
t_ast				*parse_pipe(t_token *lst);
t_str				*jbdi_red(t_token *lst);
t_str				*jbdi_cmd(t_token *lst);
t_ast				*parse_and_or(t_token *lst);
char				**list_to_table(t_str *str);
int					ft_strcmp(char *s1, char *s2);
size_t				ft_strlen(const char *s);
int					outfile(t_str *red);
int					infile(t_str *red);
char				**ft_split(char const *s, char *c);
void   				initialize_cmd(t_ast *node, t_env *env);
t_env				*get_env_lst(char **env);
void    			init_ast(t_ast *root,t_env *env);
char				*correct_path(char **path, char *v);
char				**get_paths(t_env *env);
void    			executer_tree(t_ast *root, t_ast *const_root, t_env *env);
char				*ft_strjoin(char const *s1, char const *s2);
char				**list_to_table_env(t_env *str);
void				close_(t_ast *root);
int					check_redin(t_str *red);
int					check_redout(t_str *red);
int					check_redherdoc(t_str *red);
void 				execut_all_here_doc(t_ast *root);

#endif
