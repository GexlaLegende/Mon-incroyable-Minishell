/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:57:43 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/20 16:33:40 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Ajoute l’élément ’new’ à la fin de la liste. */
void	ft_env_lstadd_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*current;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	if (new != NULL)
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	return ;
}

/* Ajoute l’élément ’new’ au début de la liste. */
void	ft_env_lstadd_front(t_env_list **alst, t_env_list *new)
{
	if (alst != NULL && new != NULL)
	{
		new->next = *alst;
		*alst = new;
	}
}

/* Renvoie le dernier élément de la liste. */
t_env_list	*ft_env_lstlast(t_env_list *lst)
{	
	t_env_list	*last;
	t_env_list	*begin;

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

/* Compte le nombre d’éléments de la liste. */
int	ft_env_lstsize(t_env_list *lst)
{
	int			nbr;
	t_env_list	*begin;

	nbr = 0;
	begin = lst;
	while (begin)
	{
		nbr++;
		begin = begin->next;
	}
	return (nbr);
}
