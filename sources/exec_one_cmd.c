/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:14:40 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/29 10:11:33 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// NORME -- {OK}

// execve (PATH+cmd | tabl [PATH+cmd][arg1][arg2]... | tabl env)
int	exec_one_cmd(t_data *data, char **env)
{
	int	pid;

	pid = 0;
	data->bin_nbr = 0;
	data->arg_tabl = get_cmd(data);
	if (ft_is_builtin(data->arg_tabl[0]) == 0)
	{
		if (built_in(data, env, data->bin_nbr) != 0)
			return (5);
		return (0);
	}
	if (put_path(data) == 2)
		return (2);
	pid = fork();
	if (pid == 0)
		if (cmd_redir(data, env, 0) != 0)
			return (3);
	waitpid(pid, NULL, 0);
	if (access("/tmp/.here_doca", F_OK) == 0)
		unlink("/tmp/.here_doca");
	pid = 0;
	while (pid <= data->nbr_save + 1)
		free(data->arg_tabl[pid++]);
	free(data->arg_tabl);
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
			tabl[data->nbr] = ft_malloc_str(&str[i + 1]);
			while (str[i] == ' ' && data->squote == 0 && data->dquote == 0)
				i--;
			str[i + 1] = '\0';
			data->nbr--;
		}
		else
			i--;
	}
	tabl[data->nbr] = ft_malloc_str(&str[i]);
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
	i = strlen(str) - 1;
	if (i == -1)
		i = 0;
	if (str[i] == ' ' && data->squote == 0 && data->dquote == 0)
	{
		data->nbr--;
		while (str[i] == ' ' && data->squote == 0 && data->dquote == 0)
			i--;
		str[i + 1] = '\0';
	}
	data->nbr_save = data->nbr;
	tabl = malloc(sizeof(char *) * (data->nbr + 2));
	tabl[data->nbr + 1] = NULL;
	tabl = put_cmd_in_arg(i, data, str, tabl);
	return (tabl);
}
