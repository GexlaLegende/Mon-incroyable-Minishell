/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:23:31 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/10 10:23:58 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parserror(int nbr) //Fonction pour les erreurs de parsing
{
	if (nbr == 1)
	{
		write(2, "syntax error near unexpected token `|'", 39);
		exit(0);
	}
	if (nbr == 2)
	{
		write(2, "Error quote not closed", 23);
		exit(0);
	}
}
