/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_in_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:19:50 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/28 21:09:43 by apercebo         ###   ########.fr       */
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

/* Duplicate and sort env_table */
void	ft_sort_list(t_data *data)
{
	data->env_table_sorted = NULL;
	data->env_table_sorted = ft_dup_list(data->env_table);
	ft_insertion_sort(data);
}

/* Duplicates a list in another one and return it */
t_env_list	*ft_dup_list(t_env_list *list)
{
	t_env_list	*elemt;
	t_env_list	*new_list;
	char		*name;
	char		*value;

	elemt = list;
	new_list = NULL;
	while (elemt)
	{
		name = ft_strdup(elemt->name);
		if (!name)
			return (NULL);
		if (elemt->value != NULL)
		{
			value = ft_strdup(elemt->value);
			if (!value)
				return (NULL);
		}
		else
			value = NULL;
		ft_env_lstadd_back(&new_list, ft_env_lstnew(name, value));
		elemt = elemt->next;
	}
	return (new_list);
}

/* Sort env_list in alphabetical order of names */
void	ft_insertion_sort(t_data *data)
{
	t_env_list	*start;
	t_env_list	*analyse;
	t_env_list	*min;
	char		*tmp_name;
	char		*tmp_value;

	start = data->env_table_sorted;
	while (start->next)
	{
		printf("A\n");
		min = start;
		analyse = start->next;
		while (analyse)
		{
			if (ft_strncmp(min->name, analyse->name) > 0)
				min = analyse;
			analyse = analyse->next;
		}
		tmp_name = start->name;
		tmp_value = start->value;
		start->name = min->name;
		start->value = min->value;
		min->name = tmp_name;
		min->value = tmp_value;
		start = start->next;
	}
}
