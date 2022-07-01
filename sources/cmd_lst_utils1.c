/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:14:37 by apercebo          #+#    #+#             */
/*   Updated: 2022/07/01 11:17:13 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstadd_back(t_cmd_list **alst, t_cmd_list *new)
{
	t_cmd_list	*begin;
	t_cmd_list	*newelm;

	begin = *alst;
	if (!alst)
		return ;
	if (*alst == 0)
	{
		*alst = new;
		return ;
	}
	while (begin)
	{
		newelm = begin;
		begin = begin->next;
	}
	newelm->next = new;
}

void	ft_lstadd_front(t_cmd_list **alst, t_cmd_list *new)
{
	if (alst != NULL && new != NULL)
	{
		new->next = *alst;
		*alst = new;
	}
}

void	ft_lstclear(t_cmd_list **lst)
{
	t_cmd_list	*nexto;
	int			i;

	if (!lst)
		return ;
	nexto = (*lst)->next;
	free(*lst);
	(*lst) = nexto;
	while (*lst != NULL)
	{
		i = -1;
		nexto = (*lst)->next;
		free((*lst)->cmd);
		free((*lst)->redir_type);
		while ((*lst)->redir_file[++i])
			free((*lst)->redir_file[i]);
		free((*lst)->redir_file);
		free(*lst);
		(*lst) = nexto;
	}
}

int	ft_lstsize(t_cmd_list *lst)
{
	int			nbr;
	t_cmd_list	*begin;

	nbr = 0;
	begin = lst;
	while (begin)
	{
		nbr++;
		begin = begin->next;
	}
	return (nbr);
}
