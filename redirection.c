/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:56:59 by cmaami            #+#    #+#             */
/*   Updated: 2024/07/20 00:27:31 by maamichaima      ###   ########.fr       */
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

void	in_the_pipe(char *del, int *p_fd, t_env *env, char *del_)
{
	char	*tmp;
	char	*t;

	t = ignor(del_);
	while (1)
	{
		tmp = readline("> ");
		if (!tmp || ft_strcmp(tmp, t) == 0)
		{
			free(tmp);
			break ;
		}
		if (check_del_quotes(del) == 1)
		{
			write(p_fd[1], tmp, ft_strlen(tmp));
			write(p_fd[1], "\n", 1);
		}
		else
		{
			write(p_fd[1], expand(tmp, env, 'h'), ft_strlen(expand(tmp, env,
						'h')));
			write(p_fd[1], "\n", 1);
		}
		free(tmp);
	}
}

int	open_here_doc(char *del, t_env *env)
{
	char	*del_;
	int		pipe_fd[2];
	pid_t	pid;

	if(pipe(pipe_fd) == -1)
	{
		perror("pipe");
		ft_exit_free(env, 1);
	}
	del_ = ft_malloc(sizeof(char) * (ft_strlen(del) + 1), 'a');
	ft_strcpy(del_, del);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		in_the_pipe(del, pipe_fd, env, del_);\
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		ft_exit_free(env, 0);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	outfile(t_str *red)
{
	while (red)
	{
		if (red->type == token_apend)
		{
			red->fd = open(ignor(red->str), O_CREAT | O_APPEND | O_WRONLY,
					0644);
			if (red->fd == -1)
			{
				write(2,"bash: ",7);
				perror(red->str);
				return(1);
			}
		}
		else if (red->type == token_red_output)
		{
			red->fd = open(ignor(red->str), O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (red->fd == -1)
			{
				write(2,"bash: ",7);
				perror(red->str);
				return(1);
			}
		}
		red = red->next;
	}
	return(0);
}

int	infile(t_str *red)
{
	while (red)
	{
		if (red->type == token_red_input)
		{
			red->fd = open(ignor(red->str), O_RDONLY, 0644);
			if (red->fd == -1)
			{
				write(2,"bash: ",7);
				perror(red->str);
				return(1);
			}
		}
		red = red->next;
	}
	return(0);
}
