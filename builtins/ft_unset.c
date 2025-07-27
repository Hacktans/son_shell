#include "minishell.h"

int ft_unset(char *var_name, t_list *mini)
{
	int i = 0;
	int var_len;
	int removed = 0;

	if (!var_name)
		return (1);
	var_len = ft_strlen(var_name);
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], var_name, var_len) == 0 && mini->env[i][var_len] == '=')
		{
			int j = i;
			while (mini->env[j + 1])
			{
				mini->env[j] = mini->env[j + 1];
				j++;
			}
			mini->env[j] = NULL;
			removed = 1;
			break;
		}
		i++;
	}
	if (!removed)
		return (1);
	return (0);
}