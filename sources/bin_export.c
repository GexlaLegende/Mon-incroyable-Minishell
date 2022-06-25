/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 07:06:53 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/25 15:37:47 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void	bin_export(char **arg, t_data *data)
{
	int			i;
	int			j;
	t_env_list	*begin;
	char		*name;
	char		*value;
	
	if (!arg)
	{
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
	else
	{
		j = 0;
		while (arg[j])
		{
			i = 0;
			while (arg[j][i])
			{
				while (ft_isalnum(arg[j][i]) == 1 || arg[j][i] == '_')
					i++;
				if (arg[j][i] == '=')
				{
					
				}
				else
					printf("bash: export: `%s': not a valid identifier\n", name);
			}
			j++;
		}
	}
} */

/* 	if (cmd export avec arg qui set une nouvelle variable)
		ajoute un element à la liste chaine env */