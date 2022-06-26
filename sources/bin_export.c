/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 07:06:53 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/26 21:41:48 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	bin_export(char **arg, t_data *data)
{
	int			i;
	int			j;
	char		*name;
	char		*value;
	t_env_list	*p_env_name;

	j = 0;
	if (!arg[j])
	{
		ft_display_env(data);
		return ;
	}
	while (arg[j])
	{
		i = 0;
		while (arg[j][i])
		{
			while (ft_isalnum(arg[j][i]) == 1 || arg[j][i] == '_')
				i++;
			if ((arg[j][i] == '=' || arg[j][i] == '\0') && i > 0)
			{
				name = ft_substr(arg[j], 0, i);
				if (arg[j][i] == '=')
				{
					value = ft_substr(arg[j], i + 1, ft_strlen(arg[j]) - (i + 1));
					i = ft_strlen(arg[j]);
				}
				else
					value = "";
				p_env_name = ft_search_env(data, name);
				if (!p_env_name)
					ft_env_lstadd_back(&data->env_table, \
						ft_env_lstnew(name, value));
				else
					p_env_name->value = ft_strdup(value);
			}
			else
			{
				while (arg[j][i] && arg[j][i] != ' ')
					i++;
				name = ft_substr(arg[j], 0, i);
				printf("minishell: export: `%s': not a valid identifier\n", name);
			}
			if (arg[j][i])
				i++;
		}
		j++;
	}
}

void	ft_display_env(t_data *data)
{
	t_env_list	*begin;

	//trier par ordre alphabetique
	begin = data->env_table;
	while (begin)
	{
		printf("declare -x %s", begin->name);
		//checker si affiche un truc quand il n'a pas de value
		if (begin->value)//marche pas
			printf("=\"%s\"\n", begin->value);
		begin = begin->next;
	}
}

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
