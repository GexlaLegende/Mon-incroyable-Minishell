/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 07:06:56 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/26 21:34:21 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	bin_unset(char **arg, t_data *data)
{
	int			i;
	int			j;
	char		*name;
	t_env_list	*save_p_next;
	t_env_list	*p_env_name;
	
	j = 0;
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
				p_env_name = ft_search_preenv(data, name);
				if (!p_env_name)
					return ;
				else
				{
					save_p_next = p_env_name->next;
					p_env_name->next = p_env_name->next->next;
					save_p_next->next = NULL;
					ft_env_lstclear(&save_p_next);
				}
			}
			else
			{
				while (arg[j][i] && arg[j][i] != ' ')
					i++;
				name = ft_substr(arg[j], 0, i);
				printf("minishell: unset: `%s': not a valid identifier\n", name);
			}
			if (arg[j][i])
				i++;
		}
		j++;
	}
}

t_env_list	*ft_search_preenv(t_data *data, char *name)
{
	t_env_list	*current_elmt;

	current_elmt = data->env_table;
	while (current_elmt->next)
	{
		if (ft_strncmp(name, current_elmt->next->name) == 0)
			return (current_elmt);
		current_elmt = current_elmt->next;
	}
	return (NULL);
}