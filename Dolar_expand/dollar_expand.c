#include "minishell.h"

int		pass_env(char *str, int i)
{
	if(str[i + 1] == '{')
		i += 2;
	else
		i += 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && str[i] != '$')
		i++;
	if(str[i] == '}')
		i++;
	return (i);
}

char	*take_env(char *str, int i, t_list *mini)
{
	char *tmp;
	int j = 0;
	char *value;
	int len = 0;

	len = pass_env(str, i);
	tmp = malloc(sizeof(char) * len + 1);
	if (!tmp)
		return NULL;
	if(str[i + 1] == '{')
		i += 2;
	else
		i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') && str[i] != '"' && str[i] != '}')
		tmp[j++] = str[i++];
	tmp[j] = '\0';
	value = ft_getenv(tmp, mini->env);
	free(tmp);
	if (!value)
		return ft_strdup("");
	return ft_strdup(value);
}

void 	*special_dlr(char *str, int i, t_list *mini)
{
	int pid;
	char *str_pid;
	if(str[i + 1] == '$')
	{
		pid = getpid();
		str_pid = ft_itoa(pid);
		return(str_pid);
	}
	else 
	{
		str_pid = ft_itoa(mini->exit_code);
		return(str_pid);
	}
}

static int handle_special_dollar(char *str, int i, char *tmp, int j, t_list *mini)
{
	char *tmp2;
	int k = 0;

	if (str[i + 1] == '$' || str[i + 1] == '?')
	{
		tmp2 = special_dlr(str, i, mini);
		while (tmp2[k])
			tmp[j++] = tmp2[k++];
		free(tmp2);
		return j;
	}
	return -1;
}

static int handle_env_expansion(char *str, int i, char *tmp, int j, t_list *mini)
{
	char *tmp2;
	int k = 0;

	tmp2 = take_env(str, i, mini);
	while (tmp2[k])
		tmp[j++] = tmp2[k++];
	free(tmp2);
	return j;
}

static int should_skip_char(char *str, int i)
{
	if (str[i] == '{' && str[i + 1] == '$')
		return 1;
	return 0;
}

static char *process_dollar_string(char *str, char *tmp, t_list *mini)
{
	int i = 0;
	int j = 0;
	int new_j;

	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != ' ')
		{
			new_j = handle_special_dollar(str, i, tmp, j, mini);
			if (new_j != -1)
			{
				j = new_j;
				i += 2;
				continue;
			}
			j = handle_env_expansion(str, i, tmp, j, mini);
			i = pass_env(str, i);
			continue;
		}
		if (should_skip_char(str, i))
		{
			i++;
			continue;
		}
		tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	return tmp;
}

char *exp_dollar(char *str, int quote, t_list *mini)
{
	int k;
	char *tmp;

	k = total_len_with_mini(str, mini);
	tmp = malloc(sizeof(char) * k);
	if (!tmp)
		return NULL;
	if (if_has_dollar(str) == 0 || quote == 1)
		return (str);
	tmp = process_dollar_string(str, tmp, mini);
	return tmp;
}
