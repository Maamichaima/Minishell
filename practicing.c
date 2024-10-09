#include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <sys/wait.h>
int     peek_index(char **av ,char *sep)
{
    int i;
    i = 0;
    while(av[i])
    {
      if(!strcmp(av[i], sep))
            return(i);
        i++;
    }
    return(-1);
}
int count_args(char **av)
{
    int i = 0;
    while(av[i])
        i++;
    
    return(i);
}
void    builtin_cd(char **av)
{
    if(count_args(av) != 1)
        write(2,"error: cd: bad arguments \n",27);
    else
    {
        if(chdir(av[1]) == -1)
        {
            write(2,"error: cd: cannot change directory to",38);
            write(2,av[0],strlen(av[0]));
            write(2,"\n",1);
            exit(1);
        }
    }
    
}
void    execute(char **av,char **env)
{
    int pid;
    int status;
     if(!strcmp(av[0],"cd"))
            builtin_cd(&av[1]);
    pid = fork();
    if (!pid)
    {
       
        execve(av[0],av,env);
        write(2,"error: cannot execute ",23);
        write(2,av[0],strlen(av[0]));
        write(2,"\n",1);
        exit(1);
            
    }
    waitpid(pid,&status,0);
}
void lookfor_pipe(char **av,char **env)
{
    int index;
    int wstatus;
    int pid[2];
    int fdpipe[2];
    if(av == NULL || av[0] == NULL)
        return;
    index = peek_index(av,"|");
    if(index != -1)
    {
        av[index] = NULL;
        if (pipe(fdpipe) == -1)
		{
			//print2("error: fatal\n");
			exit(1);
		}
        pid[0] = fork();
        if (pid[0] == -1)
		{
			//print2("error: fatal\n");
			exit(1);
		}
        if(!pid[0])
        {   
            close(fdpipe[0]);
            dup2(fdpipe[1],1);
            close(fdpipe[1]);
            execute(av,env);
            exit(0);
        }
                
        pid[1] = fork();
        if (pid[1] == -1)
		{
			//print2("error: fatal\n");
			exit(1);
		}
        if(!pid[1])
        {   
                close(fdpipe[1]);
                dup2(fdpipe[0],0);
                close(fdpipe[0]);
                lookfor_pipe(&av[index + 1], env);
                exit(0);
        }

        close(fdpipe[0]);
        close(fdpipe[1]);
        waitpid(pid[0],&wstatus,0);
        waitpid(pid[1],&wstatus,0);
    }
    else
        execute(av,env);

}
void    lookfor_cmd_seperator(char **av,char **env)
{
    int index;
    if(av == NULL || av[0] == NULL)
        return;
    index = peek_index(av,";");
    if(index != -1)
    {
        av[index] = NULL;
        lookfor_pipe(av,env);
        lookfor_cmd_seperator(&av[index + 1],env);
        
    }
    else
        lookfor_pipe(av,env);

}


int main(int ac, char **av,char **env)
{
    if(ac > 1)
        lookfor_cmd_seperator(&av[1],env);
    return(0);
}