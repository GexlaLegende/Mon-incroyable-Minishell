/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:58:48 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/15 17:11:48 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Alloue (avec malloc(3)) et renvoie un nouvel
élément. La variable membre ’cmd’ est
initialisée à l’aide de la valeur du paramètre ’cmd’.  FONCTION FINIT*/
t_env_list	*ft_lstnew(char *name, char *value)
{
	t_env_list	*newelm;

	newelm = (t_env_list *)malloc(sizeof(t_env_list));
	if (!newelm)
		return (0);
	newelm->name = name;
	newelm->value = value;
	newelm->next = NULL;
	return (newelm);
}

/* Supprime et libère la mémoire de l’élément passé en
paramètre, et de tous les éléments qui suivent */
void	ft_lstclear(t_env_list **lst)
{
	t_env_list	*nexto;
	int			i;

	if (!lst)
		return ;
	nexto = (*lst)->next;
	free(*lst);
	(*lst) = nexto;
	while (*lst != NULL)
	{
		i = 0;
		nexto = (*lst)->next;
		free((*lst)->name);
		free((*lst)->value);
		free(*lst);
		(*lst) = nexto;
	}
}
