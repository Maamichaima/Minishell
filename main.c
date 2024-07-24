/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:26:03 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/24 13:10:19 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*set_signal_flag(void)
{
	static int	sig_flag = 0;

	return (&sig_flag);
}

void	start_minishell(t_token *head, t_env **v)
{
	t_ast	*root;
	t_token	*t;

	t = is_valid_token(head);
	if (t && check_herdoc(head, *v))
		error_syntax(*v);
	else if (t)
		error_syntax(*v);
	else if (head)
	{
		root = parse_pipe(head);
		init_ast(root, *v);
		if (execut_all_here_doc(root, *v) == 1)
			executer_tree(root, root, v);
		close_(root);
		wait_(root, *v);
	}
}

void	control_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (!(*set_signal_flag()))
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	write_err(char *av)
{
	write(2, "bash_42: ", 10);
	write(2, av, ft_strlen(av));
	write(2, ": No such file or directory\n", 29);
	exit (127);
}

int	main(int c, char **av, char **env)
{
	char	*input;
	t_token	*head;
	t_env	*v;

	if (c > 1)
		write_err(av[1]);
	v = get_env_lst(env);
	signal_handler();
	while (1)
	{
		input = readline("42_bash_$ ");
		*set_signal_flag() = 1;
		if (!input)
			ctl_d(v);
		if (*input)
			add_history(input);
		head = NULL;
		lst_token(input, &head);
		start_minishell(head, &v);
		ft_malloc(0, 'f');
		*set_signal_flag() = 0;
		signal(SIGQUIT, SIG_IGN);
		free(input);
	}
	return (0);
}
