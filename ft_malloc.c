/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:41:03 by cmaami            #+#    #+#             */
/*   Updated: 2024/07/17 15:42:40 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_garbage	*ft_lstnew_garbage(void *content)
{
	t_garbage	*l;

	if (!content)
		return (NULL);
	l = malloc(sizeof(t_garbage));
	if (!l)
		return (NULL);
	l->p = content;
	l->next = NULL;
	return (l);
}

t_garbage	*ft_lstlast_garbage(t_garbage *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_garbage(t_garbage **lst, t_garbage *new)
{
	t_garbage	*t;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		t = ft_lstlast_garbage(*lst);
		t->next = new;
	}
}

void	*ft_malloc(int size, char c)
{
	static t_garbage	*head;
	t_garbage			*tmp;
	void				*ptr;

	if (c == 'f')
	{
		while (head)
		{
			tmp = head;
			head = head->next;
			if(tmp->p)
				free(tmp->p);
			if(tmp)
				free(tmp);
		}
		head = NULL;
		return (NULL);
	}
	else
	{
		ptr = malloc(size);
		ft_bzero(ptr, size);
		ft_lstadd_back_garbage(&head, ft_lstnew_garbage(ptr));
	}
	return (ptr);
}

void	clear_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}
