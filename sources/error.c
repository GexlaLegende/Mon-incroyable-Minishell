/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:23:31 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/23 14:38:03 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parserror(int nbr) //Fonction pour les erreurs de parsing
{
	if (nbr == 1)
	{
		write(2, "syntax error near unexpected token `|'\n", 40);
		return (1);
	}
	if (nbr == 2)
	{
		write(2, "Error quote not closed\n", 24);
		exit(0);
	}
	if (nbr == 3)
	{
		write(2, "Syntax error\n", 14);
		exit(0);
	}
	if (nbr == -2)
	{
		write(2, "Syntax error after >\n", 22);
		exit(0);
	}
}

void	exekerror(int nbr) //Fonction pour les erreurs d'execution (0 == good)
{
	if (nbr == 2)
	{
		write(2, "Command not found\n", 19);
		exit(0);
	}
	if (nbr == 3) // - /!\ IN CHILD PROCESS
	{
		write(2, "Error with redirections\n", 25);
		exit(0);
	}
	if (nbr == 4) // - /!\ IN CHILD PROCESS
	{
		write(2, "No command after pipe\n", 23);
		exit(0);
	}
}