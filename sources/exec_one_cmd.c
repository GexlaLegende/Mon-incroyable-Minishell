/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:14:40 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/25 09:57:26 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// NORME -- {OK}

// execve (PATH+cmd | tabl [PATH+cmd][arg1][arg2]... | tabl env)
int	exec_one_cmd(t_data *data, char **env)
{
	int	pid;

	pid = 0;
	data->arg_tabl = get_cmd(data);
	if (put_path(data) == 2)
		return (2);
	pid = fork();
	if (pid == 0)
	{
		if (cmd_redir(data, env, 0) != 0)
			return (3);
	}
	waitpid(pid, NULL, 0);
	if (access("/tmp/.here_doca", F_OK) == 0)
		unlink("/tmp/.here_doca");
	return (0);
}

//Return le nombre d'arguments via les espaces - [OK] - 20 lines
int	get_argnbr(char *str, t_data *data)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	data->squote = 0;
	data->dquote = 0;
	while (str[i])
	{
		quotes_switch(data, str, i);
		if (str[i] == ' ' && data->squote == 0 && data->dquote == 0)
		{
			nbr++;
			while (str[i] == ' ' && data->squote == 0 && data->dquote == 0)
				i++;
		}
		else
			i++;
	}
	return (nbr);
}

char	**put_cmd_in_arg(int i, t_data *data, char *str, char **tabl)
{
	while (i > 0)
	{
		quotes_switch(data, str, i);
		if (str[i] == ' ' && data->squote == 0 && data->dquote == 0)
		{
			tabl[data->nbr] = malloc(sizeof(char) * ft_strlen(&str[i + 1]));
			tabl[data->nbr] = &str[i + 1];
			tabl[data->nbr][ft_strlen(tabl[data->nbr])] = '\0';
			while (str[i] == ' ' && data->squote == 0 && data->dquote == 0)
				i--;
			str[i + 1] = '\0';
			data->nbr--;
		}
		else
			i--;
	}
	tabl[data->nbr] = malloc(sizeof(char) * ft_strlen(&str[i]));
	tabl[data->nbr] = &str[i];
	tabl[data->nbr][ft_strlen(tabl[data->nbr])] = '\0';
	tabl = rm_quote(tabl, data);
	return (tabl);
}

//Retourne un tableau avec la commande puis les args - [OK] - 29 lines [X] --
char	**get_cmd(t_data *data)
{
	char	*str;
	char	**tabl;
	int		i;

	str = data->cmd_table->cmd;
	data->nbr = get_argnbr(str, data);
	i = ft_strlen(str) - 1;
	if (i == -1)
		i = 0;
	if (str[i] == ' ' && data->squote == 0 && data->dquote == 0)
	{
		data->nbr--;
		while (str[i] == ' ' && data->squote == 0 && data->dquote == 0)
			i--;
		str[i + 1] = '\0';
	}
	tabl = malloc(sizeof(char *) * (data->nbr + 2));
	tabl[data->nbr + 1] = NULL;
	tabl = put_cmd_in_arg(i, data, str, tabl);
	return (tabl);
}
