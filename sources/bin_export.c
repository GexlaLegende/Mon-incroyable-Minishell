/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 07:06:53 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/26 09:33:52 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void	bin_export(char **arg, t_data *data)
{
	int			i;
	int			j;
	char		*name;
	char		*value;
	t_env_list	*p_env_name;

	if (!arg)
	{
		ft_display_env(data);
		return ;
	}
	j = 0;
	while (arg[j])
	{
		i = 0;
		while (arg[j][i])
		{
			while (ft_isalnum(arg[j][i]) == 1 || arg[j][i] == '_')
				i++;
			if (arg[j][i] == '=' && i > 0)
			{
				name = ft_substr(arg[j], 0, i);
				value = ft_substr(arg[j], i + 1, ft_strlen(arg[j]) - (i + 1));
				p_env_name = ft_search_env(data, name);
				if (!p_env_name)
					ft_env_lstadd_back(&data->env_table, \
						ft_env_lstnew(name, value));
				else
					p_env_name->value = ft_replace_word(p_env_name->value, 0, \
						ft_strlen(value), value);
			}
			else
			{
				while (arg[j][i] && arg[j][i] != ' ')
					i++;
				name = ft_substr(arg[j], 0, i);
				printf("bash: export: `%s': not a valid identifier\n", name);
			}
			if (arg[j][i])
				i++;
		}
		j++;
	}
}

void	ft_display_env(t_data *data)
{
	int			i;
	t_env_list	*begin;

	//trier par ordre alphabetique
	i = 0;
	begin = data->env_table;
	while (begin)
	{
		printf("declare -x %s", begin->name);
		//checker si affiche un truc quand il n'a pas de value
		printf("=%s\n", begin->value);
		begin = begin->next;
		i++;
	}
}

t_env_list	*ft_search_env(t_data *data, char *name)
{
	t_env_list	*current_elmt;

	current_elmt = data->env_table;
	while (current_elmt)
	{
		if (ft_strncmp(name, current_elmt->name, ft_strlen(name)) == 0)
			return (current_elmt);
		current_elmt = current_elmt->next;
	}
	return (NULL);
}
 */