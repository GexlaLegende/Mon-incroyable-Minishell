/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:44:13 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/08 20:53:24 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Itère sur la liste 'lst' et applique la fonction
’f’ au contenu chaque élément. */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*begin;

	begin = lst;
	while (begin && f)
	{
		(*f)(begin->cmd);
		begin = begin->next;
	}
}

/* Renvoie le dernier élément de la liste. */
t_list	*ft_lstlast(t_list *lst)
{	
	t_list	*last;
	t_list	*begin;

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

/* Itère sur la liste ’lst’ et applique la fonction
’f ’au contenu de chaque élément. Crée une nouvelle
liste résultant des applications successives de ’f’. */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin;
	t_list	*newlst;
	t_list	*new;

	begin = lst;
	if (!lst)
		return (0);
	newlst = ft_lstnew(f(begin->cmd));
	begin = begin->next;
	while (begin)
	{
		new = ft_lstnew(f(begin->cmd));
		if (!new)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, new);
		begin = begin->next;
	}
	return (newlst);
}

/* Alloue (avec malloc(3)) et renvoie un nouvel
élément. La variable membre ’cmd’ est
initialisée à l’aide de la valeur du paramètre ’cmd’. */
t_list	*ft_lstnew(void *cmd)
{
	t_list	*newelm;

	newelm = (t_list *)malloc(sizeof(t_list));
	if (!newelm)
		return (0);
	newelm->cmd = cmd;
	newelm->next = NULL;
	return (newelm);
}
