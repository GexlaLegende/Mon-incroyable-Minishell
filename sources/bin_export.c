/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 07:06:53 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/29 17:47:49 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	bin_export(char **arg, t_data *data)
{
	data->f = 0;
	if (!arg[data->f])
	{
		ft_sort_list(data);
		ft_display_env(data->env_table_sorted);
		return ;
	}
	while (arg[data->f])
	{
		data->e = 0;
		while (arg[data->f][data->e])
		{
			while (ft_isalnum(arg[data->f][data->e]) == 1 \
				|| arg[data->f][data->e] == '_')
				data->e++;
			if ((arg[data->f][data->e] == '=' || arg[data->f][data->e] == '\0') \
				&& data->e > 0)
				ft_correct_env_name(arg, data);
			else
				ft_wrong_env_name(arg, data);
			if (arg[data->f][data->e])
				data->e++;
		}
		data->f++;
	}
}

/* Display a list */
void	ft_display_env(t_env_list *list)
{
	t_env_list	*begin;

	begin = list;
	while (begin)
	{
		printf("declare -x %s", begin->name);
		if (begin->value)
			printf("=\"%s\"\n", begin->value);
		else
			printf("\n");
		begin = begin->next;
	}
}

/*	Search a environment variable in env_table by name 
	and return a pointer to the element of the list */
t_env_list	*ft_search_env(t_data *data, char *name)
{
	t_env_list	*current_elmt;

	current_elmt = data->env_table;
	while (current_elmt)
	{
		if (ft_strncmp(name, current_elmt->name) == 0)
			return (current_elmt);
		current_elmt = current_elmt->next;
	}
	return (NULL);
}

void	ft_correct_env_name(char **arg, t_data *data)
{
	char		*name;
	char		*value;
	t_env_list	*p_env_name;

	name = ft_substr(arg[data->f], 0, data->e);
	if (arg[data->f][data->e] == '=' && arg[data->f][data->e + 1])
	{
		value = ft_substr(arg[data->f], data->e + 1, \
			ft_strlen(arg[data->f]) - (data->e + 1));
		data->e = ft_strlen(arg[data->f]);
	}
	else
		value = NULL;
	p_env_name = ft_search_env(data, name);
	if (!p_env_name)
	{
		ft_env_lstadd_back(&data->env_table, \
			ft_env_lstnew(name, value));
	}
	else
	{
		free(p_env_name->value);
		free(name);
		p_env_name->value = ft_strdup(value);
		free(value);
	}
}

void	ft_wrong_env_name(char **arg, t_data *data)
{
	char	*name;

	while (arg[data->f][data->e] && arg[data->f][data->e] != ' ')
		data->e++;
	name = ft_substr(arg[data->f], 0, data->e);
	printf("minishell: export: `%s': not a valid identifier\n", name);
	free(name);
}
