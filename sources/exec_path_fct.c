/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_fct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:22:41 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/30 13:14:11 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// NORME -- {OK}

//RETOURNE UN TABLEAU DE PATHS  -  [OK] - 25 lines //path_return
char	**recup_path(t_data *data)
{
	int		i;
	char	*str;
	char	**tabl;

	str = ft_found_path(data, "PATH");
	i = -1;
	data->nbr = 0;
	while (str[++i])
		if (str[i] == ':')
			data->nbr = data->nbr + 1;
	data->path_nbr = data->nbr;
	tabl = malloc(sizeof(char *) * (data->nbr + 2));
	tabl[data->nbr + 1] = NULL;
	while (i-- > 0)
	{
		if (str[i] == ':')
		{
			tabl[data->nbr] = ft_malloc_str(&str[i + 1]);
			str[i] = '\0';
			data->nbr = data->nbr - 1;
		}
	}
	tabl[data->nbr] = ft_malloc_str(str);
	free(str);
	return (tabl);
}

void	wait_loop(t_data *data)
{
	int	error_code;
	int	status;

	status = wait(&data->last_error);
	while (status != -1)
	{
		if (WIFEXITED(data->last_error))
		{
			error_code = WEXITSTATUS(data->last_error);
		}
		else if (WIFSIGNALED(data->last_error))
		{
			error_code = WTERMSIG(data->last_error) + 128;
		}
		status = wait(&data->last_error);
	}
	data->last_error = error_code;
}

char	*safe_malloc(void)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		exit(EXIT_FAILURE);
	return (str);
}

//FONCTION QUI JOIN LE PATH ET LA COMMANDE  -  [OK] - 22 lines
int	put_path(t_data *data)
{
	char	*full_path;

	data->ppi = -1;
	if (access(data->arg_tabl[0], X_OK) == 0)
		return (0);
	full_path = safe_malloc();
	full_path[0] = '\0';
	while (access(full_path, X_OK) == -1 && data->ppi < data->path_nbr)
	{
		data->ppi++;
		full_path[0] = '\0';
		free(full_path);
		full_path = ft_1ststrjoin(data->paths[data->ppi], data->arg_tabl[0]);
	}
	data->ppi = 0;
	if (access(full_path, X_OK) == 0)
	{
		free(data->arg_tabl[0]);
		data->arg_tabl[0] = ft_malloc_str(full_path);
		free(full_path);
		return (0);
	}
	else
		free(full_path);
	return (2);
}
