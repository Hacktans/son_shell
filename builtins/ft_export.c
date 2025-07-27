#include "minishell.h"

char *ft_strcpy(char *dest, const char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return dest;
}

int only_exp(char **env)
{
	int env_len;
	char **env_copy;
	int j = 0;

	env_len = ft_envlen(env);
	env_copy = malloc(sizeof(char *) * (env_len + 1));
	if (!env_copy)
		return (1);
	while(j < env_len)
	{
		env_copy[j] = ft_strdup(env[j]);
		j++;
	}
	env_copy[env_len] = NULL;
	ft_short(env_copy);
	j = 0;
	while(env_copy[j])
	{
		printf("declare -x %s\n", env_copy[j]);
		free(env_copy[j]);
		j++;
	}
	free(env_copy);
	return (0);
}

int ft_exp(t_cmd *input, t_list *mini)
{
	char **inp = input->command;
	int i = 0;
	int updated = 0;
	char *eq;
	char *to_add;

	if (!inp[1])
	{
		only_exp(mini->env);
		return(0);
	}
	if(inp[2])
		inp[1] = ft_strjoin(inp[1], inp[2]);
	if(!input_chk(inp[1], input))
	{
		print_error(" not a valid identifier\n");
		mini->exit_code = 1;
		return 0;
	}
	eq = ft_strchr(inp[1], '=');
	if (eq)
		to_add = strdup(inp[1]);
	else
	{
		to_add = malloc(strlen(inp[1]) + 2);
		if (!to_add)
			return (1);
		ft_strcpy(to_add, inp[1]);
		to_add[strlen(inp[1])] = '=';
		to_add[strlen(inp[1]) + 1] = '\0';
	}
	while (mini->env[i])
	{
		if (strncmp(mini->env[i], inp[1], eq - inp[1]) == 0 && mini->env[i][eq - inp[1]] == '=')
		{
			free(mini->env[i]);
			mini->env[i] = strdup(inp[1]);
			updated = 1;
			break;
		}
		i++;
	}
	if (!updated)
	{
		int len = ft_envlen(mini->env);
		mini->env[len] = strdup(inp[1]);
		mini->env[len + 1] = NULL;
	}
	return 0;
}