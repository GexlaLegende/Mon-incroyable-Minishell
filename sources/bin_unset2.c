/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unset2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:06:44 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/30 13:58:36 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	bin_pwd(t_data *data)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	data->last_error = 0;
	return (0);
}
