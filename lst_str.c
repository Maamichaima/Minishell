#include "minishell.h"

t_ast	*lstnew_ast(token_type type, t_str *cmd, t_str *red)
{
	t_ast	*l;

	l = ft_malloc(sizeof(t_ast), 'a');
	if (!l)
		return (NULL);
	l->type = type;
	l->args = cmd;
	l->red = red;
	l->right = NULL;
	l->left = NULL;
	l->cmd.infile = 0;
	l->cmd.outfile = 1;
	return (l);
}

t_str	*lst_new_str(char *content, token_type type)
{
	t_str	*l;

	l = ft_malloc(sizeof(t_str), 'a');
	if (!l)
		return (NULL);
	l->str = content;
	l->type = type;
	l->next = NULL;
	return (l);
}

t_str	*ft_lstlast_str(t_str *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_str(t_str **lst, t_str *new)
{
	t_str	*t;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		t = ft_lstlast_str(*lst);
		t->next = new;
	}
}