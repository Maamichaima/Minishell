/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:46:15 by cmaami            #+#    #+#             */
/*   Updated: 2023/11/17 19:40:54 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*l;
	t_list	*final;
	void	*v;

	final = NULL;
	if (!f || !del)
		return (NULL);
	while (lst)
	{
		v = f(lst->content);
		l = ft_lstnew(v);
		if (!l)
		{
			ft_lstclear(&final, del);
			free(v);
			return (NULL);
		}
		ft_lstadd_back(&final, l);
		lst = lst->next;
	}
	return (final);
}
// int main (int c, char **v)
// {
//     int i;
//     i = 1;
//     t_list *l;
// 	t_list *ff;
//     t_list *ll = NULL;
//     while (i < c)
//     {
//         l = ft_lstnew (v[i]);
//         ft_lstadd_front(&ll,l);
//         i++;
// 	}
// 	ff = ft_lstmap(ll, f, del);
// 	i = 1;
// 	while (i < c)
// 	{
// 		printf ("%s\n", (char *)ff->content);
// 		i++;
// 		ff = ff->next;
// 	}
// }
