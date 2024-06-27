/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:26:50 by cmaami            #+#    #+#             */
/*   Updated: 2024/06/09 16:26:54 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_ast *root)
{
	int	count;

	count = 0;
	if (root && root->type == token_cmd)
		count++;
	else
	{
		count += count_cmd(root->left);
		count += count_cmd(root->right);
	}
	return (count);
}
