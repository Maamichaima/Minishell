/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:56:59 by cmaami            #+#    #+#             */
/*   Updated: 2024/07/06 23:40:30 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_del_quotes(char *del)
{
	int	i;

	i = 0;
	while (del[i])
	{
		if (del[i] == '\'' || del[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int	open_here_doc(char *del, t_env *env)
{
	char	*tmp;
	char	*del_;
	int		pipe_fd[2];
	pid_t	pid;

	pipe(pipe_fd);
	del_ = ft_malloc(sizeof(char) * ft_strlen(del + 1), 'a');
	ft_strcpy(del_, del);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			tmp = readline("> ");
			if (!tmp || ft_strcmp(tmp, ignor(del_)) == 0)
			{
				// free(tmp);
				break ;
			}
			if (check_del_quotes(del) == 1)
			{
				write(pipe_fd[1], tmp, ft_strlen(tmp));
				write(pipe_fd[1], "\n", 1);
			}
			else
			{
				write(pipe_fd[1], expand(tmp, env, 'h'), ft_strlen(expand(tmp,
							env, 'h')));
				write(pipe_fd[1], "\n", 1);
			}
		}
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		exit(0);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

void	outfile(t_str *red)
{
	while (red)
	{
		if (red->type == token_apend)
		{
			red->fd = open(ignor(red->str), O_CREAT | O_APPEND | O_WRONLY,
					0644);
			if (red->fd == -1)
			{
				perror(red->str);
				exit(1);
			}
		}
		else if (red->type == token_red_output)
		{
			red->fd = open(ignor(red->str), O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (red->fd == -1)
			{
				perror(red->str);
				exit(1);
			}
		}
		red = red->next;
	}
}

void	infile(t_str *red)
{
	while (red)
	{
		if (red->type == token_red_input)
		{
			red->fd = open(ignor(red->str), O_RDONLY, 0644);
			if (red->fd == -1)
			{
				perror(red->str);
				exit(1);
			}
		}
		red = red->next;
	}
}
