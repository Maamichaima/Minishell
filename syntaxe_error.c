
#include "minishell.h"

int check_pipe(t_token *head)
{
   
    if(head->type == token_pipe)
        return(0);
    t_token *tmp = head->next;
    while(head)
    {
        if(head->type == token_pipe)
       { 
            if( head->next && head->prev->type == token_word && ( head->next->type == token_word || head->next->type == token_red_output || head->next->type == token_expand))
              { printf("%s %d\n",head->next->token ,head->next->type);
                head = head->next;}
            else
                 return(0);
       }
        else
            head = head->next;
    }
}
 int check_string(t_token *head)
 {
    int i;
    int count;
    int a;
    while(head)
    {
        i = 0;
        count = 0;
        if(head->type == token_word)
        {
            while(head->token[i])
            {
               
                if(head->token[i] ==  '\'' || head->token[i] == '\"')
                {
                    a = i;
                    count++;
                }
                i++;
            }
            if((count % 2 == 0))
                head = head->next;
            else
                return(0);
        }
        else 
            head = head->next;
    }
    return(1);
}