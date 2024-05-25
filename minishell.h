/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:55:55 by maamichaima       #+#    #+#             */
/*   Updated: 2024/05/25 19:27:09 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# define READLINE_LIBRARY
# include <readline/history.h>
# include <readline/readline.h>
# include <string.h>

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

typedef struct s_env
{
	char  *value;	
	char  *key;
	struct s_env *next;
}				t_env;
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
	t_str			*cmd;
	t_str			*red;
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

#endif
