#include "minishell.h"

int ft_unset(char **env, char *var_name)
{
	int i = 0;
	int var_len;
	int removed = 0;

	if (!var_name)
		return (1);
	var_len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, var_len) == 0 && env[i][var_len] == '=')
		{
			int j = i;
			while (env[j + 1])
			{
				env[j] = env[j + 1];
				j++;
			}
			env[j] = NULL;
			removed = 1;
			break;
		}
		i++;
	}
	if (!removed)
		return (1);
	return (0);
}
