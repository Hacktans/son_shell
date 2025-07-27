#include "minishell.h"

void    ft_echo(t_cmd *cmds, char *input) 
{
    int i = 1;
    int j = 0;
    int spc = spc_chk(input);
    int newline = 1;
    char **strngs = cmds->command;
    
    while (strngs[i] && ft_strncmp("-n", strngs[i], 2) == 0)
    {
        newline = 0;
        i++;
    }
    while (strngs[i])
    {
        j = 0;
        while (strngs[i][j])
        {
            write(1, &strngs[i][j], 1);
            j++;
        }
        if (strngs[i + 1] && strngs[i][0] != '\0' && spc != 0)
            write(1, " ", 1);
        i++;
    }
    if (newline)
        write(1, "\n", 1);
}