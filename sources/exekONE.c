/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exekONE.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:51:48 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/21 09:02:24 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	tabl[nbr] = &str[i];
	tabl[nbr][ft_strlen(tabl[nbr])] = '\0';
	return (tabl);
}

void	exec_cmd_one(t_data *data, char **env)
{
	execve(data->arg_tabl[0], data->arg_tabl, env);
}

int	cmd_redir(t_data *data, char **env)
{
	int	i;
	int	file;

	i = 0;
	file = 0;
	while (data->cmd_table->redir_type[i] != 0)
	{
		if (data->cmd_table->redir_type[i] == 1)
		{
			// DO REDIR '>>'
		}
		if (data->cmd_table->redir_type[i] == 2)
		{
			file = open(data->cmd_table->redir_file[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (file < 0)
				return (-1);
			dup2(file, STDOUT_FILENO);
			close(file);
		}
		if (data->cmd_table->redir_type[i] == 3)
		{
			// DO REDIR '<<'
		}
		if (data->cmd_table->redir_type[i] == 4)
		{
			file = open(data->cmd_table->redir_file[i], O_RDONLY);
			if (file < 0)
				return (-1);
			dup2(file, STDIN_FILENO);
			close(file);
		}
		i++;
	}
	exec_cmd_one(data, env);
	return (0);
}

int	exekonecmd(t_data *data, char **env) // execve (PATH+cmd | tabl [PATH+cmd][arg1][arg2]... | tabl env)
{
	int	pid;

	pid = 0;
	data->arg_tabl = get_cmd(data);
	if (put_path(data) == 2) // JOIN LE PATH ET LA CMD
		return(2);
	pid = fork();
	if (pid == 0)
	{
		if (cmd_redir(data, env) != 0)
			return (3);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	ft_execution(t_data *data, char **env) //FONCTION PRINCIPALE DE L'EXECUTION
{
	while (env)
		break;
	if (ft_lstsize(data->cmd_table) == 1)
		return (exekonecmd(data, env));
	return (0);
}





/* int nombre = -1;
while(tabl[++nombre])
	printf("%d -- %s\n", nombre, tabl[nombre]); */

/* printf("%s\n", tabl[0]);
	printf("%s\n", tabl[1]);
	printf("%s\n", tabl[2]);
	printf("%s\n", tabl[3]);
	printf("%s\n", tabl[4]);
	printf("%s\n", tabl[5]);
	printf("%s\n", tabl[6]);
	printf("%s\n", tabl[7]);
	printf("%s\n", tabl[8]); */
