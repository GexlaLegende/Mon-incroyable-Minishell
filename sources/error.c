/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:23:31 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/20 19:18:21 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Displays errors of parsing */

void	parserror(int nbr)
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
	if (nbr == 3)
	{
		write(2, "Syntax error", 13);
		exit(0);
	}
	if (nbr == -2)
	{
		write(2, "Syntax error after > < >> <<", 21);
		exit(0);
	}
	if (nbr == -3)
	{
		write(2, "Malloc went wrong", 17);
		exit(0);
	}
}
