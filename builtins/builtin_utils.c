#include "minishell.h"

char	*ft_getenv(char *key, char **env)
{
	int		i;
	int		len = strlen(key);

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char *ft_strcat(char *dest, const char *src)
{
	int i = 0;
	int j = 0;

	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return dest;
}


int ft_envlen(char **env)
{
	int i = 0;
	while (env[i])
		i++;
	return i;
}

int	input_chk(char *inp, t_cmd *input)
{
	int i = 0;
	if(inp[0] >= '0' && inp[0] <= '9')
		return(0);
	while(inp[i])
	{
		if(inp[i] == '-' && input->quote_num != 2)
			return(0);
		if(inp[i] == '=' && inp[i + 1] == '\0')
			return(0);
		i++;
	}
	return(1);
}

int ft_short(char **env)
{
	int i = 0;
	int j;
	char *temp;
	
	if (!env)
		return (1);
		
	while (env[i] && env[i + 1])
	{
		j = i + 1;
		while (env[j])
		{
			if (strcmp(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (0);
}