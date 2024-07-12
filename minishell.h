/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:55:55 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/12 11:31:07 by rraida-          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>

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
	struct s_env	*prev;
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
	int				fd;
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

typedef struct s_garbage
{
	void				*p;
	struct s_garbage 	*next;
} t_garbage;

t_token				*ft_lstnew(char *content);
t_token				*ft_lstlast(t_token *lst);
void				ft_lstadd_back(t_token **lst, t_token *new);
int					is_symbol(char c);
char				*get_next_token(char *s);
int					is_redirectien(token_type type);
t_token				*is_valid_token(t_token *lst);
int					is_valid_word(char *s);
t_ast				*parse_pipe(t_token *lst);
t_str				*jbdi_red(t_token *lst);
t_str				*jbdi_cmd(t_token *lst);
t_ast				*parse_and_or(t_token *lst);
char				**list_to_table(t_str *str);
int					ft_strcmp(char *s1, char *s2);
size_t				ft_strlen(const char *s);
char				*ft_strdup(char *src);
void				outfile(t_str *red);
void				infile(t_str *red);
char				**ft_split(char const *s, char *c);
void				initialize_cmd(t_ast *node, t_env *env);
t_env				*get_env_lst(char **env);
t_env				*ft_lstnew_env(char *key, char *value);
void				ft_lstadd_back_env(t_env **lst, t_env *new);
char				*get_key(char *env);
char				*get_value(char *env);
t_env				*get_env_lst(char **env);
void				init_ast(t_ast *root, t_env *env);
char				*correct_path(char **path, char *v);
char				**get_paths(t_env *env);
void				executer_tree(t_ast *root, t_ast *const_root, t_env **env);
char				*ft_strjoin(char const *s1, char const *s2);
char				**list_to_table_env(t_env *str);
void				close_(t_ast *root);
int					check_redin(t_str *red);
int					check_redout(t_str *red);
int					check_redherdoc(t_str *red);
void				execut_all_here_doc(t_ast *root, t_env *env);
int					open_here_doc(char *del, t_env *env);
int					ft_export(char **args, t_env *env);
int					is_builtin(t_str cmd);
int					ft_cd(char **args, t_env *env);
int					ft_pwd(t_env *env);
int					ft_unset(char **str, t_env **env);
int					ft_env(t_env *env);
int					ft_echo(char **args, t_env *env, int outfile);
int					check_flag(char *flag);
int					ft_exit(char **args);
long				ft_atoi(char *str);
int					ft_isnum(int arg);
int					str_is_num(char *str);
int					execut_bultin(t_ast *root, t_env **env);
char				*ignor(char *str);
char				**table_of_key(t_env *env);
char 				**sort_table(char **str);
char 				*get_value_(char *key, t_env *env);
void 				ft_write_export(char **key, t_env *env);
int 				count_cmd(t_ast *root);
void				init_infile_outfile(t_str *red, t_ast *node);
int 				check_bultins(t_ast *root, t_ast *const_root, t_env **env);
int					ft_isalpha(char c);
char				*ft_strchr(const char *s, int c);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
void 				expand_node(t_ast *root, t_env *env);
char    			*expand(char *str, t_env *env, char c);
int					check_quotes(char *str, int c, char h);
char				*ft_strcpy(char *s1, char *s2);
void 				ignor_args(char **args);
void				ft_lstadd_back_str(t_str **lst, t_str *new);
t_str				*lst_new_str(char *content, token_type type);
void 				*ft_malloc(int size, char c);
char				*ft_itoa(int nbr);
void				ft_bzero(void *s, size_t n);
void				set_content(t_env *env,char *key, char *content);
int					is_builtin(t_str cmd);
t_ast				*lstnew_ast(token_type type, t_str *cmd, t_str *red);
void				ft_quit_signal(int sig);
void				execute_node(t_ast *root, t_ast *const_root, t_env **env);
void				error_syntax(t_token *t);
void				message_error(char *str);
void				copy(char *dst, const char *str);
int					check_equal(char *str, int j);
void 				clear_env(t_env *env);
#endif
