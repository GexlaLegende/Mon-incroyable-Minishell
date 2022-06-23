/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:19:43 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/23 16:04:54 by dbouron          ###   ########lyon.fr   */
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
	cmd_list = cmd_list->next;
	while (cmd_list)
	{
		i = 0;
		while (cmd_list->cmd[i])
		{
			if (cmd_list->cmd[i] == '$')
				ft_replace_var_env(cmd_list, i, data);
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
	char	*value;

	len = 0;
	dprintf(2, "cmd = %s\npos = %d\n", cmd_list->cmd, pos);
	if (ft_isalnum(cmd_list->cmd[pos + 1]) == 1)
	{
		dprintf(2, "je rentre dans le if alnum\n");
		if (cmd_list->cmd[pos + 1] == '0') //if $0, display shell
		{
			dprintf(2, "je rentre dans le if $0\n");
			cmd_list->cmd = ft_replace_word(cmd_list->cmd, pos, 2, "minishell");
			dprintf(2, "je sors du replace word\n");
		}
		else
		{
			while (ft_isalnum(cmd_list->cmd[pos + 1]) == 1)
				len++;//boucle infinie
			value = ft_search_var_env_in_list(data, cmd_list->cmd, pos, len);//search if variable exists in env_list
			cmd_list->cmd = ft_replace_word(cmd_list->cmd, pos, len, value);
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

/* if variable exists, replace by value, if not, replace by nothing */
char	*ft_search_var_env_in_list(t_data *data, char *cmd, int pos, int len)
{
	t_env_list	*env_list;
	char		*var_name;

	env_list = data->env_table;
	var_name = ft_substr(cmd, pos, len);
	while (env_list)
	{
		if (ft_strncmp(var_name, env_list->name, len) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return ("");
}
