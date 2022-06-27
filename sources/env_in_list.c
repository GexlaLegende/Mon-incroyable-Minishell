/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_in_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:19:50 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/27 10:18:33 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	ft_sort_list(t_data *data)
{
	int			i;
	t_env_list	*current;
	t_env_list	*p_petit;

	i = 0;
	data->env_table_sorted = NULL;
	current = data->env_table;
	p_petit = current;
	while (current->next)
	{
		if (current->name[i] == current->next->name[i])
			while (current->name[i] && current->next->name[i] \
				&& current->name[i] == current->next->name[i])
				i++;
		if (current->name[i] > current->next->name[i])
			p_petit = current->next;
		current = current->next;
	}
}
