/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:41:03 by cmaami            #+#    #+#             */
/*   Updated: 2024/07/01 14:41:08 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_garbage *ft_lstnew_garbage(void *content)
{
    t_garbage *l;

    if (!content)
        return (NULL);
    l = malloc(sizeof(t_garbage));
    if (!l)
        return (NULL);
    l->p = content;
    l->next = NULL;
    return (l);
}

t_garbage *ft_lstlast_garbage(t_garbage *lst)
{
    if (lst == NULL)
        return (NULL);
    while (lst->next != NULL)
        lst = lst->next;
    return (lst);
}

void ft_lstadd_back_garbage(t_garbage **lst, t_garbage *new)
{
    t_garbage *t;

    if (!lst || !new)
        return;
    if (*lst == NULL)
        *lst = new;
    else
    {
        t = ft_lstlast_garbage(*lst);
        t->next = new;
    }
}

void *ft_malloc(int size, char c)
{
    static t_garbage *head;
    t_garbage *tmp;
    void *ptr;

    if(c == 'f')
    {
        while(head)
        {
            tmp = head;
            head = head->next;
            free(tmp->p);
            free(tmp);
        }
        head = NULL;
        return NULL;
    }
    else
    {
        ptr = malloc(size);
        ft_lstadd_back_garbage(&head, ft_lstnew_garbage(ptr));
    }
    return ptr;
}

// int main()
// {
//     int *t;
//     int i = 0;

//     t = (int *)ft_malloc(sizeof(int) * 5, 'a');
//     t = (int *)ft_malloc(sizeof(int) * 5, 'a');
//     while (i < 5)
//     {
//         t[i] = i;
//         printf("%d\n", t[i]);
//         i++;
//     }
//     // t = ft_malloc(0, 'f');

//     return 0;
// }
