/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_fct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:22:41 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/18 18:55:22 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*recupathline(char **env) //RETOURNE LA LIGNE DES PATHS  -  [OK] - 15 lines
{
	int	i;
	char	*str;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && env[i][3] == 'H' && env[i][4] == '=')
		{
			str = malloc(sizeof(char) * (ft_strlen(env[i]) - 4));
			str = &env[i][5];
			str[ft_strlen(env[i]) - 5] = '\0';
		}
		i++;
	}
	return (str);
}

char	**recup_path(char **env, t_data *data) //RETOURNE UN TABLEAU DE PATHS  -  [OK] - 25 lines //path_return
{
	int	i;
	char	*str;
	char	**tabl;
	int	nbr;

	str = recupathline(env);
	i = -1;
	nbr = 0;
	while (str[++i])
		if (str[i] == ':')
			nbr++;
	data->path_nbr = nbr;
	tabl = malloc(sizeof(char *) * (nbr + 2));
	while (i-- > 0)
		if (str[i] == ':')
		{
			tabl[nbr] = malloc(sizeof(char) * ft_strlen(&str[i + 1]));
			tabl[nbr] = &str[i + 1];
			tabl[nbr][ft_strlen(tabl[nbr])] = '\0';
			str[i] = '\0';
			nbr--;
		}
	tabl[nbr] = &str[i];
	tabl[nbr][ft_strlen(tabl[nbr])] = '\0';
	return (tabl);
}

int	put_path(t_data *data)  //FONCTION QUI JOIN LE PATH ET LA COMMANDE 
{
	char	*full_path;
	int		i;

	i = -1;
	full_path = malloc(sizeof(char) * 2);
	full_path[0] = '\0';
	while(access(full_path, X_OK) == -1 && i < data->path_nbr)
	{
		i++;
		full_path[0] = '\0';
		free(full_path);
		full_path = ft_1ststrjoin(data->paths[i], data->arg_tabl[0]);
	}
	if (access(full_path, X_OK) == 0)
	{
		free(data->arg_tabl[0]);
		data->arg_tabl[0] = malloc(sizeof(char) * (ft_strlen(full_path) + 1));
		data->arg_tabl[0] = full_path;
		return (0);
	}
	else
		return (2);
}
