/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:14:40 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/23 14:34:21 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_one_cmd(t_data *data, char **env) // execve (PATH+cmd | tabl [PATH+cmd][arg1][arg2]... | tabl env)
{
	int	pid;

	pid = 0;
	if (data->cmd_table->cmd[0] == '\0')
		return (2);
	data->arg_tabl = get_cmd(data);
	if (put_path(data) == 2) // JOIN LE PATH ET LA CMD
		return(2);
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

int	get_argnbr(char *str, t_data *data) //Return le nombre d'arguments via les espaces - [OK] - 20 lines
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

char	**get_cmd(t_data *data) //Retourne un tableau avec la commande puis les args - [OK] - 29 lines [X] --
{
	char	*str;
	char	**tabl;
	int		i;
	int		nbr;

	str = data->cmd_table->cmd;
	nbr = get_argnbr(str, data);
	i = ft_strlen(str) - 1;
	if (i == -1)
		i = 0;
	if (str[i] == ' ' && data->squote == 0 && data->dquote == 0)
	{
		nbr--;
		while (str[i] == ' ' && data->squote == 0 && data->dquote == 0)
			i--;
		str[i + 1] = '\0';
	}
	tabl = malloc(sizeof(char *) * (nbr + 2));
	tabl[nbr + 1] = NULL;
	while (i > 0)
	{
		quotes_switch(data, str, i);
		if (str[i] == ' ' && data->squote == 0 && data->dquote == 0)
		{
			tabl[nbr] = malloc(sizeof(char) * ft_strlen(&str[i + 1]));
			tabl[nbr] = &str[i + 1];
			tabl[nbr][ft_strlen(tabl[nbr])] = '\0';
			while (str[i] == ' ' && data->squote == 0 && data->dquote == 0)
				i--;
			str[i + 1] = '\0';
			nbr--;
		}
		else
			i--;
	}
	tabl[nbr] = malloc(sizeof(char) * ft_strlen(&str[i])); // PAS SUR !
	tabl[nbr] = &str[i];
	tabl[nbr][ft_strlen(tabl[nbr])] = '\0';
	tabl = rm_quote(tabl, data);
	return (tabl);
}

char	**rm_quote(char **tabl, t_data *data)
{
	int		i;
	int		j;
	int		x;
	char	*str;
	int		nbr;

	i = 0;
	j = 0;
	str = NULL;
	data->dquote = 0;
	data->squote = 0;
	while (tabl[j])
	{
		i = 0;
		str = malloc(sizeof(char) * (ft_strlen(tabl[j]) + 1));
		str[ft_strlen(tabl[j])] = '\0';
		x = 0;
		nbr = 0;
		while (tabl[j][i])
		{
			
			quotes_switch(data, tabl[j], i);
			/* if ((tabl[j][i] == '"' && data->squote == 0) || (tabl[j][i] == '\'' && data->dquote == 0))
				nbr++; */
			if (tabl[j][i] == '"' && data->squote == 0)
				nbr++;
			else if (tabl[j][i] == '\'' && data->dquote == 0)
				nbr++;
			else
			{
				str[x] = tabl[j][i];
				x++;
			}
			i++;
		}
		str[ft_strlen(tabl[j]) - nbr] = '\0';
		tabl[j] = str;
		j++;
	}
	return (tabl);
}
