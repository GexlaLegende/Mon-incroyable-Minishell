/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:44:13 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/15 15:21:19 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Renvoie le dernier élément de la liste. */
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

/* Alloue (avec malloc(3)) et renvoie un nouvel
élément. La variable membre ’cmd’ est
initialisée à l’aide de la valeur du paramètre ’cmd’.  FONCTION FINIT*/
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
