#include "minishell.h"

int count_cmd(t_ast *root)
{
    int count;
    count = 0;

    if(root && root->type == token_cmd)
        count++;
    else
    {
         count += count_cmd(root->left); 
         count += count_cmd(root->right);
    }
   
    return(count);
}