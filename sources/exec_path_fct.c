/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_fct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:22:41 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/27 08:33:28 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// NORME -- {OK}

//RETOURNE LA LIGNE DES PATHS  -  [OK] - 15 lines
char	*recupathline(char **env)
{
	int		i;
	char	*str;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' &&
				env[i][3] == 'H' && env[i][4] == '=')
		{
			//str = malloc(sizeof(char) * (ft_strlen(env[i]) - 4));
			str = &env[i][5];
			str[ft_strlen(env[i]) - 5] = '\0';
		}
		i++;
	}
	return (str);
}

//RETOURNE UN TABLEAU DE PATHS  -  [OK] - 25 lines //path_return
char	**recup_path(char **env, t_data *data)
{
	int		i;
	char	*str;
	char	**tabl;

	str = recupathline(env);
	i = -1;
	data->nbr = 0;
	while (str[++i])
		if (str[i] == ':')
			data->nbr = data->nbr + 1;
	data->path_nbr = data->nbr;
	tabl = malloc(sizeof(char *) * (data->nbr + 2));
	while (i-- > 0)
	{
		if (str[i] == ':')
		{
			tabl[data->nbr] = ft_malloc_str(&str[i + 1]);
			str[i] = '\0';
			data->nbr = data->nbr - 1;
		}
	}
	tabl[data->nbr] = ft_malloc_str(&str[i]);
	return (tabl);
}

//FONCTION QUI JOIN LE PATH ET LA COMMANDE  -  [OK] - 22 lines
int	put_path(t_data *data)
{
	char	*full_path;
	int		i;

	i = -1;
	if (access(data->arg_tabl[0], X_OK) == 0)
		return (0);
	full_path = malloc(sizeof(char) * 2);
	full_path[0] = '\0';
	while (access(full_path, X_OK) == -1 && i < data->path_nbr)
	{
		i++;
		full_path[0] = '\0';
		free(full_path);
		full_path = ft_1ststrjoin(data->paths[i], data->arg_tabl[0]);
	}
	free(data->arg_tabl[0]);
	if (access(full_path, X_OK) == 0)
	{
		data->arg_tabl[0] = full_path;
		return (0);
	}
	else
		return (2);
}
