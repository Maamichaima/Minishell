/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:05:11 by cmaami            #+#    #+#             */
/*   Updated: 2023/11/17 19:26:05 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		if (*lst == NULL)
		{
			*lst = new;
			return ;
		}
		new->next = *lst;
		*lst = new;
	}
}

// int main (int c, char **v)
// {

//     int i;
//     i = 1;
//     t_list *l;
//     t_list *llll = NULL;
//     while (i < c)
//     {
//         l = ft_lstnew (v[i]);
//         ft_lstadd_front(&llll,l);
//         i++;
//     }
//     while (llll)
//     {
//         t_list *temp = llll;
//         printf ("%s    ",(char *)llll -> content);
//         llll = llll -> next;
//     }
//     //printf ("%d", ft_lstsize(llll));
// }