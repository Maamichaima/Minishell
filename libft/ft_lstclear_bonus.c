/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:06:30 by cmaami            #+#    #+#             */
/*   Updated: 2023/11/19 17:02:08 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*l;

	if (lst != NULL && del)
	{
		while ((*lst) != NULL)
		{
			l = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = l;
		}
	}
	lst = NULL;
}
// int main (int c, char **v)
// {
//     int i;
//     i = 1;
//     t_list *l;
//     t_list *ll = NULL;
//     while (i < c)
//     {
//         l = ft_lstnew (ft_strdup(v[i]));
//         ft_lstadd_front(&ll,l);
//         i++;
// 	}
// 	ft_lstclear(&ll, del);
// 	printf ("%p",ll);
// }
