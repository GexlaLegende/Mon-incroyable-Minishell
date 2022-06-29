/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 07:06:56 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/29 11:31:48 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	bin_unset(char **arg, t_data *data)
{
	data->f = 0;
	while (arg[data->f])
	{
		data->e = 0;
		while (arg[data->f][data->e])
		{
			while (ft_isalnum(arg[data->f][data->e]) == 1 \
				|| arg[data->f][data->e] == '_')
				data->e++;
			if (arg[data->f][data->e] == '\0')
				ft_remove_env_var(arg, data);
			else
				ft_name_error(arg, data);
			if (arg[data->f][data->e])
				data->e++;
		}
		data->f++;
	}
}

t_env_list	*ft_search_preenv(t_data *data, char *name)
{
	t_env_list	*current_elmt;

	current_elmt = data->env_table;
	if (current_elmt && !current_elmt->next)
		if (ft_strncmp(name, current_elmt->name) == 0)
			return (current_elmt);
	while (current_elmt && current_elmt->next)
	{
		if (ft_strncmp(name, current_elmt->next->name) == 0)
			return (current_elmt);
		current_elmt = current_elmt->next;
	}
	return (NULL);
}

void	ft_remove_env_var(char **arg, t_data *data)
{
	char		*name;
	t_env_list	*p_env_name;
	t_env_list	*save_p_next;

	name = ft_substr(arg[data->f], 0, data->e);
	p_env_name = ft_search_preenv(data, name);
	if (!p_env_name)
		return ;
	else if (!p_env_name->next)
	{
		free(p_env_name->name);
		free(p_env_name->value);
		data->env_table = NULL;
		free(p_env_name);
	}
	else
	{
		save_p_next = p_env_name->next;
		p_env_name->next = p_env_name->next->next;
		save_p_next->next = NULL;
		ft_env_lstclear(&save_p_next);
	}
}

void	ft_name_error(char **arg, t_data *data)
{
	char	*name;

	while (arg[data->f][data->e] && arg[data->f][data->e] != ' ')
		data->e++;
	name = ft_substr(arg[data->f], 0, data->e);
	printf("minishell: unset: `%s': not a valid identifier\n", name);
	free(name);
}
