/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:01:55 by cmaami            #+#    #+#             */
/*   Updated: 2023/11/17 19:36:43 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*t;

	if (!lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		t = ft_lstlast(*lst);
		t->next = new;
	}
}

// int main (int c, char **v)
// {
//     t_list *l;
//     t_list *ll;
//     int i;
//     i = 1;
//     while (i < c)
//     {
//         l = ft_lstnew (v[i]);
//         ft_lstadd_back(&ll,l);
//         i++;
//     }
//     while (ll)
//     {
//         printf ("%s  ", (char *)ll->content);
//         ll = ll->next;
//     }
// }