/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_in_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:19:50 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/27 16:42:48 by dbouron          ###   ########lyon.fr   */
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

void	ft_sort_list(t_data *data)
{
	int	i;

	i = 0;
	data->env_table_sorted = NULL;
	data->env_table_sorted = ft_dup_list(data->env_table);
	ft_display_env(data);//for debugging
	dprintf(2, "Before sort list\n");
	while (ft_list_is_sorted(data->env_table_sorted) != 0)
	{
		while (data->env_table_sorted->next)
		{
			while (data->env_table_sorted->name[i] && data->env_table_sorted->next->name[i] \
				&& data->env_table_sorted->name[i] == data->env_table_sorted->next->name[i])
				i++;
			if (data->env_table_sorted->name[i] > data->env_table_sorted->next->name[i])
			{
				dprintf(2, "Before swap list\nname = %s | name + 1 = %s\n", data->env_table_sorted->name, data->env_table_sorted->next->name);
				ft_swap_elmt_list(data->env_table_sorted, data->env_table_sorted->next);//il me faut un current
				dprintf(2, "Before swap list\nname = %s | name + 1 = %s\n", data->env_table_sorted->name, data->env_table_sorted->next->name);
				dprintf(2, "After swap list\n");
			}
			data->env_table = data->env_table->next;
		}
	}
	ft_display_env(data);//for debugging
	dprintf(2, "After sort list\n");
}

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
		value = ft_strdup(elemt->value);
		ft_env_lstadd_back(&new_list, ft_env_lstnew(name, value));
		elemt = elemt->next;
	}
	return (new_list);
}

void	ft_swap_elmt_list(t_env_list *elt1, t_env_list *elt2)
{
	t_env_list	*tmp;

	tmp = elt1;
	elt1->next = elt2->next;
	elt2->next = elt1;
	elt1 = elt2;
	elt2 = tmp;
}

int	ft_list_is_sorted(t_env_list *list)
{
	int			i;
	t_env_list	*elemt;

	i = 0;
	elemt = list;
	while (elemt)
	{
		while (elemt->name[i] && elemt->next->name[i] \
			&& elemt->name[i] == elemt->next->name[i])
			i++;
		if (elemt->name[i] > elemt->next->name[i])
			return (1);
		elemt = elemt->next;
	}
	return (0);
}

/* 	int			i;
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
	} */