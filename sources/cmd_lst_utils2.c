/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:44:13 by apercebo          #+#    #+#             */
/*   Updated: 2022/07/01 11:17:21 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd_list	*ft_lstlast(t_cmd_list *lst)
{	
	t_cmd_list	*last;
	t_cmd_list	*begin;

	begin = lst;
	if (begin == 0)
		return (0);
	while (begin)
	{
		last = begin;
		begin = begin->next;
	}
	return (last);
}

t_cmd_list	*ft_lstnew(char *cmd, int *redir_type, char **redir_file)
{
	t_cmd_list	*newelm;

	newelm = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!newelm)
		return (0);
	newelm->cmd = cmd;
	newelm->redir_type = redir_type;
	newelm->redir_file = redir_file;
	newelm->next = NULL;
	return (newelm);
}
