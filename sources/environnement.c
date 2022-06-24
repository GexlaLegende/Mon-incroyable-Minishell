/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:19:43 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/24 16:23:42 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env_var(t_data *data, char **env)
{
	int	error;

	error = 0;
	error = ft_put_env_in_lst(data, env);
	if (error != 0)
		return (error);
	error = ft_search_and_replace_env_var(data);
	if (error != 0)
		return (error);
	return (0);
}

/*	Puts environment variables from char** to list,
	separated by name and value */
int	ft_put_env_in_lst(t_data *data, char **env)
{
	int		i;
	int		pos;
	char	*name;
	char	*value;

	i = 0;
	data->env_table = NULL;
	while (env[i])
	{
		pos = 0;
		while (env[i][pos] && env[i][pos] != '=')
			pos++;
		name = ft_substr(env[i], 0, pos);
		value = ft_substr(env[i], pos + 1, ft_strlen(env[i]) - (size_t)pos);
		if (!name || !value)
			return (-3);
		ft_env_lstadd_back(&data->env_table, ft_env_lstnew(name, value));
		i++;
	}
	return (0);
}

/*	Search and replace environment variables by their value
	in each element of the cmd_list */
int	ft_search_and_replace_env_var(t_data *data)
{
	int			i;
	t_cmd_list	*cmd_list;

	cmd_list = data->cmd_table;
	data->squote = 0;
	data->dquote = 0;
	//cmd_list = cmd_list->next;
	while (cmd_list)
	{
		i = 0;
		while (cmd_list->cmd[i])
		{
			quotes_switch(data, cmd_list->cmd, i);
			if (cmd_list->cmd[i] == '$' \
				&& (ft_isalnum(cmd_list->cmd[i + 1]) == 1 \
				|| cmd_list->cmd[i + 1] == '_') && data->squote == 0)
			{
				ft_replace_var_env(cmd_list, i, data);
				//dprintf(2, "cmd[i] = %c | i = %d\n", cmd_list->cmd[i], i);
				if (i > 0)
					i--;
				//dprintf(2, "cmd[i] = %c | i = %d\n", cmd_list->cmd[i], i);
			}
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

	len = 0;
	i = pos;
	if (cmd_list->cmd[pos + 1] == '0') //if $0, display shell
		cmd_list->cmd = ft_replace_word(cmd_list->cmd, pos, 2, "minishell");
	else
	{
		while (ft_isalnum(cmd_list->cmd[i + 1]) == 1 \
			|| cmd_list->cmd[i + 1] == '_')
		{
			len++;
			i++;
		}
		value = ft_is_var_env(data, cmd_list->cmd, pos, len);//search if variable exists in env_list
		cmd_list->cmd = ft_replace_word(cmd_list->cmd, pos, len + 1, value);
	}
}

/*
	else if (cmd_list->cmd[i + 1] == '{' || cmd_list->cmd[i + 1] == '(' \
		|| cmd_list->cmd[i + 1] == '\'' || cmd_list->cmd[i + 1] == '"')
	{
		//verify if {('" opened is closed with same quotes system
		//manage single and double quotes (see notion tests)
	}
	else if (cmd_list->cmd[i + 1] == '!' || cmd_list->cmd[i + 1] == '?' \
		|| cmd_list->cmd[i + 1] == '$' || cmd_list->cmd[i + 1] == '@' \
		|| cmd_list->cmd[i + 1] == '*')
	{
		//replace by nothing or special action (see notion)
	}
*/

/* if variable exists, replace by value, if not, replace by nothing */
char	*ft_is_var_env(t_data *data, char *cmd, int pos, int len)
{
	t_env_list	*env_list;
	char		*var_name;

	env_list = data->env_table;
	var_name = ft_substr(cmd, pos + 1, len);
	while (env_list)
	{
		if (ft_strncmp(var_name, env_list->name, len) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return ("");
}
