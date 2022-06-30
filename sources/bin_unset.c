/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 07:06:56 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/30 10:49:39 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	bin_unset(char **arg, t_data *data)
{
	data->last_error = 0;
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

	name = ft_substr(arg[data->f], 0, data->e);
	if (ft_strncmp(name, data->env_table->name) == 0 && data->env_table->next)
	{
		ft_clear_first_elmt(data);
		free(name);
	}
	else
		ft_clear_elmt(data, name);
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

void	ft_clear_first_elmt(t_data *data)
{
	t_env_list	*save_p;

	save_p = data->env_table;
	data->env_table = data->env_table->next;
	save_p->next = NULL;
	ft_env_lstclear(&save_p);
}

void	ft_clear_elmt(t_data *data, char *name)
{
	t_env_list	*p_env_name;
	t_env_list	*save_p_next;

	p_env_name = ft_search_preenv(data, name);
	if (!p_env_name)
	{
		free(name);
		return ;
	}
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
	free(name);
}

void	ft_name_error(char **arg, t_data *data)
{
	char	*name;

	while (arg[data->f][data->e] && arg[data->f][data->e] != ' ')
		data->e++;
	name = ft_substr(arg[data->f], 0, data->e);
	printf("minishell: unset: `%s': not a valid identifier\n", name);
	data->last_error = 1;
	free(name);
}
