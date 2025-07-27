#include "minishell.h"

char	*go_home(char *path, t_list *mini)
{
	path = getenv("HOME");
	if(!path)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		mini->exit_code = 1;
		return(NULL);
	}
	return(path);
}

char	*go_old_pwd(char *path, char *oldpwd, t_list *mini)
{
	oldpwd = getenv("OLDPWD");
	if(!oldpwd)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		mini->exit_code = 1;
		return(NULL);
	}
	path = oldpwd;
	printf("%s\n", path);
	return(path);
}

void	ch_dir(char *new, char *path, char *oldpwd, t_list *mini)
{
	oldpwd = getenv("PWD");
	if (chdir(path) != 0)
    {
        perror("cd");
        mini->exit_code = 1;
        return;
    }
	new = getcwd(NULL , 0);
	if(!new)
	{
		ft_putstr_fd("cd", STDERR_FILENO);
		mini->exit_code = 1;
		return;
	}
	if(oldpwd)
		setenv("OLDPWD", oldpwd, 1);
	setenv("PWD", new, 1);
	mini->exit_code = 0;
}

void	ft_cd(char **args, t_list *mini)
{
	char *oldpwd = NULL;
	char *path = NULL;
	char *new = NULL;

	if(!args[1])
		path = go_home(path, mini);
	else if(args[1][0] == '-' && args[1][1] == '\0')
		path = go_old_pwd(path, oldpwd, mini);
	else if (args[0] && args[1] && args[2])
	{
		mini->exit_code = 0;
		return ;
	}
	else
		path = args[1];
	ch_dir(new, path, oldpwd, mini);
}