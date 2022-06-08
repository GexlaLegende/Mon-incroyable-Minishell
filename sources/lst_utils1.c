/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:14:37 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/08 15:38:05 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Ajoute l’élément ’new’ à la fin de la liste. */
void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*begin;
	t_list	*newelm;

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

/* Ajoute l’élément ’new’ au début de la liste. */
void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst != NULL && new != NULL)
	{
		new->next = *alst;
		*alst = new;
	}
}

/* Supprime et libère la mémoire de l’élément passé en
paramètre, et de tous les éléments qui suivent, à
l’aide de ’del’ et de free(3) */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nexto;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		nexto = (*lst)->next;
		ft_lstdelone(*lst, (*del));
		(*lst) = nexto;
	}
}

/* Libère la mémoire de l’élément passé en argument en
utilisant la fonction ’del’ puis avec free(3). */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		if (del)
			del(lst->content);
		free(lst);
	}
}

/* Compte le nombre d’éléments de la liste. */
int	ft_lstsize(t_list *lst)
{
	int		nbr;
	t_list	*begin;

	nbr = 0;
	begin = lst;
	while (begin)
	{
		nbr++;
		begin = begin->next;
	}
	return (nbr);
}
