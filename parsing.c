#include "minishell.h"

int cmd_chk(char *cmd, char **paths) 
{
	if (!cmd || !paths) return 0;

	int i = 0;
	while (paths[i])
	{
		char *path = ft_strjoin(paths[i], "/");
		char *full_path = ft_strjoin(path, cmd);
		free(path);

		if (access(full_path, X_OK) == 0) 
		{
			free(full_path);
			return 1;
		}
		free(full_path);
		i++;
	}
	return 0;
}

int ft_lstsize(t_token *tokens)
{
	int i;
	t_token *tmp;
	tmp = tokens;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return(i);
}

void parse_command(t_cmd **cmd, t_token **tokens, t_list *mini) 
{
	int cmd_len = 0, redir_len = 0;
	t_token *tmp = *tokens;

	while (tmp && strcmp(tmp->type, "pipe") != 0)
	{
		if (!strcmp(tmp->type, "word"))
			cmd_len++;
		else if (!strcmp(tmp->type, "rdr"))
			redir_len += 2;
		tmp = tmp->next;
	}
	(*cmd)->command = ft_calloc(cmd_len + 1, sizeof(char *));
	if(redir_len != 0)
		(*cmd)->redirections = ft_calloc(redir_len + 1, sizeof(char *));
	int i = 0, j = 0;
	while (*tokens && strcmp((*tokens)->type, "pipe") != 0) 
	{
		if (!strcmp((*tokens)->type, "word")) 
		{
			if(if_has_dollar((*tokens)->value) && !strcmp((*tokens)->type, "word"))
				(*tokens)->value = exp_dollar((*tokens)->value, (*tokens)->quote_num, mini);
			if(ft_strcmp((*tokens)->value, "") != 0)
				(*cmd)->command[i++] = ft_strdup((*tokens)->value);
			(*cmd)->quote_num = (*tokens)->quote_num;
			(*tokens) = (*tokens)->next;
		}
		else if (!strcmp((*tokens)->type, "rdr")) 
		{
			(*cmd)->redirections[j++] = ft_strdup((*tokens)->value);  // ">", "<", vb.
			(*tokens) = (*tokens)->next;
			(*cmd)->redirections[j++] = ft_strdup((*tokens)->value);  // dosya adı
			(*tokens) = (*tokens)->next;
		}
	}
}

void	ft_join_quotes(t_token *tokens)
{
	t_token	*tmp = tokens;
	t_token *next;

	while (tmp)
	{
		if (tmp->quote_num == 2)
		{
			while (tmp->next && tmp->next->quote_num == 2)
			{
				next = tmp->next;
				tmp->value = ft_strjoin(tmp->value, next->value);
				tmp->next = next->next;
				free(next->value);
				free(next);
			}
		}
		tmp = tmp->next;
	}
}

t_cmd *ft_parsing(t_token *tokens, t_list *mini) 
{
	(void)mini;
	t_cmd *head = NULL;
	t_cmd **tail = &head;

	if(ft_strcmp(tokens->value, "echo") != 0)
		ft_join_quotes(tokens);
	while (tokens)
	{
		t_cmd *cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd) return NULL;
		
		// Her komut için ayrı fd structure oluştur
		t_fd *fds = malloc(sizeof(t_fd));
		if (!fds) 
		{
			free(cmd);
			return NULL;
		}
		// fd'leri sıfırla
		fds->stdin = 0;
		fds->stdout = 0;
		fds->stderr = 0;
		cmd->fd = fds;
		
		parse_command(&cmd, &tokens, mini);
		
		*tail = cmd;
		tail = &cmd->next;
		
		if (tokens && !strcmp(tokens->type, "pipe"))
			tokens = tokens->next;
	}
	
	return head;
}