/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:19:43 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/23 12:10:11 by dbouron          ###   ########lyon.fr   */
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
	while (cmd_list)
	{
		i = 0;
		while (cmd_list->cmd[i])
		{
			if (cmd_list->cmd[i] == '$')
				ft_replace_var_env(&cmd_list, i, data);
			i++;
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}

/*	Replace environment variables by their value
	in each element of the cmd_list */
int	ft_replace_var_env(t_cmd_list **cmd_list, int pos, t_data *data)
{
	int			len;
	t_env_list	*env_list;

	len = 0;
	env_list = data->env_table;
	if (ft_isalnum(cmd_list->cmd[pos + 1]) == 1)
	{
		if (cmd_list->cmd[pos + 1] == '0') //if $0, display shell
			cmd_list->cmd = ft_replace_word(cmd_list->cmd, pos, 2, "minishell");
		else
		{
			while (ft_isalnum(cmd_list->cmd[pos + 1]) == 1)
				len++;
			//search if variable exists in env_list
			if (exists) //	if it exists, print its value
				cmd_list->cmd = ft_replace_word(cmd_list->cmd, pos, len, );
			else //	if doesn't exist, print nothing
				cmd_list->cmd = ft_replace_word(cmd_list->cmd, pos, len, "");
		}
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

void	ft_search_var_env_in_list()
{
	
}
