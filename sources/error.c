/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:23:31 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/30 12:13:36 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Fonction pour les erreurs de parsing
int	parserror(int nbr, t_data *data)
{
	if (nbr == 1)
	{
		write(2, "syntax error near unexpected token `|'\n", 40);
		data->last_error = 258;
		return (-1);
	}
	if (nbr == 2)
	{
		write(2, "Error quote not closed\n", 24);
		data->last_error = 1;
		return (-1);
	}
	if (nbr == 3)
	{
		write(2, "Syntax error\n", 14);
		data->last_error = 258;
		return (-1);
	}
	if (nbr == -2)
	{
		write(2, "Syntax error after > < >> <<", 21);
		data->last_error = 258;
		return (1);
	}
	if (nbr == -3)
		write(2, "Malloc went wrong", 17);
	if (nbr == -3)
		exit(0);
	return (0);
}

//Fonction pour les erreurs d'execution (0 == good)
void	exekerror(int nbr, t_data *data)
{
	int	i;

	i = 0;
	(void)data;
	if (nbr == 2)
	{
		while (i <= data->nbr_save + 1)
			free(data->arg_tabl[i++]);
		free(data->arg_tabl);
		data->last_error = 127;
		write(2, "Command not found\n", 19);
		if (data->is_pipe == 1)
			exit(127);
	}
	if (nbr == 3)
	{
		write(2, "Error with redirections\n", 25);
		data->last_error = 1;
	}	
	if (nbr == 4)
	{
		write(2, "No command after pipe\n", 23);
		data->last_error = 1;
	}
}
