/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_in_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:19:50 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/27 22:36:31 by dbouron          ###   ########lyon.fr   */
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



//-------------------------------------------------------------------------------------------------------------------------------------------------
void	ft_sort_list(t_data *data)
{
	t_env_list	*start;
	t_env_list	*analyse;
	t_env_list	*min;
	char		*tmp_name;
	char		*tmp_value;
	
	data->env_table_sorted = NULL;
	data->env_table_sorted = ft_dup_list(data->env_table);
	dprintf(2, "\033[31mDEBUT list DUP------------------------------------------------------------------------------------\033[00m\n");
	ft_display_env(data->env_table_sorted);//for debugging
	dprintf(2, "\033[31mFIN list DUP--------------------------------------------------------------------------------------\033[00m\n");
	dprintf(2, "\033[33mBefore sort list----------------------------------------------------------------------------------\033[00m\n");
	
	start = data->env_table_sorted;
	while (start->next)
	{
		min = start;
		analyse = start->next;
		while (analyse)
		{
			if (ft_strncmp(analyse->name, min->name) > 0)
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
	
	dprintf(2, "\033[32mDEBUT list SORTED----------------------------------------------------------------------------------\033[00m\n");
	ft_display_env(data->env_table_sorted);//for debugging
	dprintf(2, "\033[32mFIN list SORTED------------------------------------------------------------------------------------\033[00m\n");
	dprintf(2, "\033[33mAfter sort list----------------------------------------------------------------------------------\033[00m\n");
}
//-------------------------------------------------------------------------------------------------------------------------------------------------



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

int	ft_list_is_sorted(t_env_list *list)
{
	int			i;
	t_env_list	*elemt;

	i = 0;
	elemt = list;
	while (elemt)
	{
		if (ft_strncmp(elemt->name, elemt->next->name) > 0)
			return (1);
		elemt = elemt->next;
	}
	return (0);
}



/* void Tri_Selection(liste *tete)
{
	liste *p, *q, *min;
	int aide;
	
	p = tete;
	while (p->next != NULL)
	{
		min = p;
		q = p->next;
		while (q != NULL)
		{
			if (q->val < min->val)
			{
				min = q;
			}
			q = q->next;
		}
		aide = p->val;
		p->val = min->val;
		min->val = aide;
		p = p->next;
	}
} */