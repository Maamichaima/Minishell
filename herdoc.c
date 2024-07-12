#include "minishell.h"

void	fd_here_doc(t_str *red, t_env *env)
{
	int	status;

	while (red)
	{
		if (red->type == token_herd)
		{
			red->fd = open_here_doc(red->str, env);
			wait(&status);
			if (status)
				break ;
		}
		red = red->next;
	}
}

void	execut_all_here_doc(t_ast *root, t_env *env)
{
	t_str	*r;

	if (root->type == token_cmd)
		fd_here_doc(root->red, env);
	else
	{
		execut_all_here_doc(root->left, env);
		execut_all_here_doc(root->right, env);
	}
}

int	get_last_fd(t_str *red, char c)
{
	int	f;

	while (red)
	{
		if (c == 'o' && (red->type == token_apend
				|| red->type == token_red_output))
			f = red->fd;
		if (c == 'i' && (red->type == token_herd
				|| red->type == token_red_input))
			f = red->fd;
		red = red->next;
	}
	return (f);
}

void	init_infile_outfile(t_str *red, t_ast *node)
{
	if (check_redout(red))
	{
		outfile(red);
		node->cmd.outfile = get_last_fd(red, 'o');
	}
	if (check_redin(red))
	{
		infile(red);
		node->cmd.infile = get_last_fd(red, 'i');
	}
}
void	ft_quit_signal(int sig)
{
	(void)sig;
	write(1, "Quit", 5);
}