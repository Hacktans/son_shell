
#include "minishell.h"

void    ft_env(char **cmds, t_list *mini)
{
    int i = 0;
    char *er;
    if(cmds[1] != NULL)
    {   
        er = cmds[1];
        printf("env: %s: No such file or directory\n", er);
        mini->exit_code = 1;
        return;
    }
    while(mini->env[i])
    {
        printf("%s\n", mini->env[i]);
        i++;
    }
}