/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:44:13 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/10 11:13:07 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

/* Alloue (avec malloc(3)) et renvoie un nouvel
élément. La variable membre ’cmd’ est
initialisée à l’aide de la valeur du paramètre ’cmd’.  FONCTION FINIT*/
t_list	*ft_lstnew(char *cmd, int *redir_type, char **redir_file)
{
	t_list	*newelm;

	newelm = (t_list *)malloc(sizeof(t_list));
	if (!newelm)
		return (0);
	newelm->cmd = cmd;
	newelm->redir_type = redir_type;
	newelm->redir_file = redir_file;
	newelm->next = NULL;
	return (newelm);
}
