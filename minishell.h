/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:55:55 by maamichaima       #+#    #+#             */
/*   Updated: 2024/05/20 23:48:57 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

typedef	enum{
	token_num,
	token_symbole,
	token_word
}	token_type;

typedef struct s_data
{
	token_type *type;
	char *data;
} t_data;


typedef struct s_token
{
	t_data token;
	struct s_token *left;
	struct s_token *right;
}	t_token;

#endif