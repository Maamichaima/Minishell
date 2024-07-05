/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:26:03 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/04 23:23:14 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_token(char *ligne, t_token **head)
{
	char	*token;

	while (*ligne != '\0')
	{
		token = get_next_token(ligne);
		if (!token)
			break ;
		ft_lstadd_back(head, ft_lstnew(token));
	}
}

void	print(t_ast *root)
{
	printf("        %d       \n", root->type);
	if (root->left && root->right)
		printf(" %s           %s \n", root->left->cmd.path,
			root->right->cmd.path);
}

void	printf_tree(t_ast *root)
{
	if (!root)
		return ;
	print(root);
	if (root->left && (root->left->type == token_pipe
			|| root->left->type == token_and || root->left->type == token_or))
		printf_tree(root->left);
	if (root->right && (root->right->type == token_pipe
			|| root->right->type == token_and || root->right->type == token_or))
		printf_tree(root->right);
}

void	wait_(t_ast *root,t_env *env)
{
	int status;
	char *str = malloc(256);
	char *tmp;
	if (root->type == token_cmd)
	{
		waitpid(root->cmd.pid, &status, 0);
		tmp = ft_itoa(WEXITSTATUS(status));
		ft_lstadd_back_env(&env,ft_lstnew_env("?",tmp,NULL));
	}
	else
	{
		wait_(root->left,env);
		wait_(root->right,env);
	}
}

void	close_(t_ast *root)
{
	if (root->type == token_cmd)
	{
		if (root->cmd.infile != 0)
			close(root->cmd.infile);
		if (root->cmd.outfile != 1)
			close(root->cmd.outfile);
	}
	else
	{
		close_(root->left);
		close_(root->right);
	}
}

void error_syntax(t_token *t)
{
	if(t)
	{
		if(!is_redirectien(t->type))
		{
			write(2, "bash: syntax error near unexpected token '", 42);
			write(2, t->token, ft_strlen(t->token));
			write(2, "'\n", 2);
		}
		else
			write(2, "bash: syntax error near unexpected token `newline'\n", 52);
	}
}

void control_c(int sig)
{
	(void)sig;
    write(1, "\n", 1);
	rl_replace_line("",0);
	rl_on_new_line();
	rl_redisplay();
}

void signal_handler()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, control_c);
}
int	main(int c, char **av, char **env)
{
	char	*input;
	t_token	*head;
	t_ast	*root;
	t_env	*v;
	t_token *t;
	//int status;

	v = get_env_lst(env);
	t_env *tmp = v;
	while (1)
	{
		signal_handler();
		if(ft_strcmp(get_value_("?",tmp),"130") != 0)
			input = readline("bash$ ");
		if (!input)
		{
			printf("exit\n");
			exit(127);
		}
		if (*input)
			add_history(input);
		head = NULL;
		lst_token(input, &head);
		// t = is_valid_token(head)
		if ((t = is_valid_token(head)))//SGV
			error_syntax(t);
		else if (head)
		{
			root = parse_and_or(head);
			init_ast(root, v);
			execut_all_here_doc(root, v);
			executer_tree(root, root, &v);
			close_(root);
			wait_(root,v);
		
		}
		free(input);
		//status = last_status_in tree(root);
	}
	return (0);
}
