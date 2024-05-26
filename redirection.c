/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:56:59 by cmaami            #+#    #+#             */
/*   Updated: 2024/05/26 14:57:09 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int here_doc(char *del)
// {
//     char *tmp;
//     int pipe_fd[2];

//     while(1)
//     {
//         write(1, ">", 1);
//         tmp = readline("");                                                                                                                                                                                                                                                                      );
//         if (!tmp || ft_strcmp(tmp, del) == 0)
// 			break ;
//         write();
//     }
// }

int outfile(t_str *red)
{
    int fd;

    while(red)
    {
        if(red->type == token_apend)
        {
            fd = open(red->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
            if(fd == -1)
            {
                perror(red->str);
                exit(1);
            }
        }
        else if(red->type == token_red_output)
        {
            fd = open(red->str,  O_CREAT | O_TRUNC | O_WRONLY, 0644);
            if(fd == -1)
            {
                perror(red->str);
                exit(1);
            }
        }
        red = red->next;
    }
    return (fd);
}

int infile(t_str *red)
{
    int fd;

    while(red)
    {
        if(red->type == token_herd)
        {
            fd = here_doc(red->str);
        }
    }
    return fd;
}
