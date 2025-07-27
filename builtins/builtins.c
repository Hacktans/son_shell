#include "minishell.h"

void    builtin_exe(t_list *mini, t_cmd *cmds)
{
        if(ft_strcmp(cmds->command[0], "exit") == 0)
            return;
        if (ft_strcmp(cmds->command[0], "echo") == 0)
            ft_echo(cmds, mini->input);
        if (ft_strcmp(cmds->command[0], "pwd") == 0)
            ft_pwd(mini);
        if (ft_strcmp(cmds->command[0], "cd") == 0)
            ft_cd(cmds->command, mini);
        if (ft_strcmp(cmds->command[0], "export") == 0)
            ft_exp(cmds, mini);
        if (ft_strcmp(cmds->command[0], "unset") == 0)
            ft_unset(cmds->command[1], mini);
        if (ft_strcmp(cmds->command[0], "env") == 0)
            ft_env(cmds->command, mini);
        if (cmds->redirections)
            retfd(cmds);
}

void    ft_builtins(t_list *mini, t_cmd *cmds)
{
	if(!cmds)
		return;
    int is_builtin = is_builtin_command(cmds);
    if (cmds->next)
		ft_cmds(mini, cmds);
    else if (is_builtin)
    {
        if (cmds->redirections)
		{
            apply_redirections(cmds->redirections, cmds->fd, mini);
			ft_heredoc(cmds->redirections, mini);
		}
        builtin_exe(mini, cmds);
        return;
    }
	else
    	ft_cmds(mini, cmds);
}