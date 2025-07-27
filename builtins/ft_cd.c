#include "minishell.h"

char	**ft_env_set(char **env, const char *key, const char *value)
{
	int		i = 0;
	int		key_len = strlen(key);
	char	*new_var;

	new_var = malloc(strlen(key) + strlen(value) + 2);
	if (!new_var)
		return (env);
	ft_strcpy(new_var, key);
	ft_strcat(new_var, "=");
	ft_strcat(new_var, value);
	while (env[i])
	{
		if (strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
		{
			free(env[i]);
			env[i] = new_var;
			return (env);
		}
		i++;
	}
	return(env);
}

char	*go_home(t_list *mini)
{
	char *home = ft_getenv("HOME", mini->env);
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		mini->exit_code = 1;
		return (NULL);
	}
	return (home);
}

char	*go_old_pwd(t_list *mini)
{
	char *oldpwd = ft_getenv("OLDPWD", mini->env);
	if (!oldpwd)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		mini->exit_code = 1;
		return (NULL);
	}
	printf("%s\n", oldpwd);
	return (oldpwd);
}

void	ch_dir(char *new, char *path, char *oldpwd, t_list *mini)
{
	oldpwd = ft_getenv("PWD", mini->env);
	if (chdir(path) != 0)
	{
		perror("cd");
		mini->exit_code = 1;
		return;
	}
	new = getcwd(NULL, 0);
	if (!new)
	{
		ft_putstr_fd("cd: getcwd failed\n", STDERR_FILENO);
		mini->exit_code = 1;
		return;
	}
	if (oldpwd)
		mini->env = ft_env_set(mini->env, "OLDPWD", oldpwd);
	mini->env = ft_env_set(mini->env, "PWD", new);
	free(new);
	mini->exit_code = 0;
}

void	ft_cd(char **args, t_list *mini)
{
	char *oldpwd = NULL;
	char *path = NULL;
	char *new = NULL;

	if (!args[1])
		path = go_home(mini);
	else if (args[1][0] == '-' && args[1][1] == '\0')
		path = go_old_pwd(mini);
	else if (args[0] && args[1] && args[2])
	{
		mini->exit_code = 0;
		return;
	}
	else
		path = args[1];
	if (path)
		ch_dir(new, path, oldpwd, mini);
}
