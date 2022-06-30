/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:19:43 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/30 15:49:26 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env_var(t_data *data)
{
	int	error;

	error = 0;
	error = ft_search_and_replace_env_var(data);
	if (error != 0)
		return (error);
	return (0);
}

void	ft_init_quotes(t_data *data)
{
	data->squote = 0;
	data->dquote = 0;
}

/*	Search and replace environment variables by their value
	in each element of the cmd_list */
int	ft_search_and_replace_env_var(t_data *data)
{
	int			i;
	t_cmd_list	*cmd_list;

	cmd_list = data->cmd_table;
	ft_init_quotes(data);
	while (cmd_list)
	{
		i = 0;
		while (cmd_list->cmd[i])
		{
			quotes_switch(data, cmd_list->cmd, i);
			if (cmd_list->cmd[i] == '$' && (ft_isalnum(cmd_list->cmd[i + 1]) \
				== 1 || cmd_list->cmd[i + 1] == '_' || cmd_list->cmd[i + 1] \
				== '?') && data->squote == 0)
			{
				ft_replace_var_env(cmd_list, i, data);
				if (i > 0)
					i--;
			}
			if (cmd_list->cmd[i])
				i++;
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}

/*	Replace environment variables by their value
	in each element of the cmd_list */
void	ft_replace_var_env(t_cmd_list *cmd_list, int pos, t_data *data)
{
	int		len;
	int		i;
	char	*value;
	char	*str;

	len = -1;
	i = pos;
	if (cmd_list->cmd[pos + 1] == '0')
		cmd_list->cmd = ft_replace_word(cmd_list->cmd, pos, 2, "minishell");
	else if (cmd_list->cmd[pos + 1] == '?')
	{
		str = ft_itoa(data->last_error);
		cmd_list->cmd = ft_replace_word(cmd_list->cmd, pos, 2, str);
		free(str);
	}
	else
	{
		while (ft_isalnum(cmd_list->cmd[i + 1]) == 1 \
			|| cmd_list->cmd[i + 1] == '_')
			if (len++)
				i++;
		value = ft_is_var_env(data, cmd_list->cmd, pos, len);
		cmd_list->cmd = ft_replace_word(cmd_list->cmd, pos, len + 1, value);
	}
}

/* if variable exists, replace by value, if not, replace by nothing */
char	*ft_is_var_env(t_data *data, char *cmd, int pos, int len)
{
	t_env_list	*env_list;
	char		*var_name;

	env_list = data->env_table;
	var_name = ft_substr(cmd, pos + 1, len);
	while (env_list)
	{
		if (ft_strncmp(var_name, env_list->name) == 0)
		{
			free(var_name);
			return (env_list->value);
		}
		env_list = env_list->next;
	}
	free(var_name);
	return (NULL);
}
