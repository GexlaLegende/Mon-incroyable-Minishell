/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exekONE.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:51:48 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/24 15:51:11 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cmd_redir(t_data *data, char **env, int nbr)
{
	int		i;
	int		file;
	char	*here_doc_file;

	i = 0;
	file = 0;
	while (data->cmd_table->redir_type[i] != 0)
	{
		if (data->cmd_table->redir_type[i] == 1) // >>
		{
			file = open(data->cmd_table->redir_file[i], O_CREAT | O_RDWR | O_APPEND, 0644);
			if (file < 0)
				return (-1);
			dup2(file, STDOUT_FILENO);
			close(file);
		}
		if (data->cmd_table->redir_type[i] == 2) // >
		{
			file = open(data->cmd_table->redir_file[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (file < 0)
				return (-1);
			dup2(file, STDOUT_FILENO);
			close(file);
		}
		if (data->cmd_table->redir_type[i] == 3) // <<
		{
			char	*str2;

			str2 = NULL;
			here_doc_file = ft_strjoin_c("/tmp/.here_doc", (char)(nbr + 97));
			file = open(here_doc_file, O_RDONLY);
			if (file < 0)
				return (-1);
			dup2(file, STDIN_FILENO);
			close(file);
		}
		if (data->cmd_table->redir_type[i] == 4) // <
		{
			file = open(data->cmd_table->redir_file[i], O_RDONLY);
			if (file < 0)
				return (-1);
			dup2(file, STDIN_FILENO);
			close(file);
		}
		i++;
	}
	execve(data->arg_tabl[0], data->arg_tabl, env);
	return (0);
}

int	exec_cmds(t_data *data, char **env)
{
	int		fds[data->lst_nbr][2];
	int		i;
	int		pid;
	int		j;
	int		status;
	char	*hd_file;

	i = 0;
	while (i < data->lst_nbr - 1)
	{
		pipe(fds[i]);                                           //A CHECK ERROR
		i++;
	}
	i = 0;
	while (i < data->lst_nbr)  //MAIN WHILE
	{
		data->arg_tabl = get_cmd(data);
		if (put_path(data) == 2) // JOIN LE PATH ET LA CMD
			return (2);
		j = 0;
		pid = fork();
		if (pid == 0)
		{
			if (i != data->lst_nbr - 1)  //IF NOT LAST CMD
				dup2(fds[i][1], STDOUT_FILENO);
			if (i != 0)  //IF NOT FIRST CMD
				dup2(fds[i - 1][0], STDIN_FILENO);
			while (j < data->lst_nbr - 1)
			{
				close(fds[j][0]);
				close(fds[j][1]);                                           //A CHECK ERROR
				j++;
			}
			if (cmd_redir(data, env, i) != 0)
				return (3);
		}
		if (data->cmd_table->next)
			data->cmd_table = data->cmd_table->next;
		if (data->cmd_table->next)
			data->cmd_table = data->cmd_table->next;
		i++;
	}
	i = 0;
	while (i < data->lst_nbr - 1)
	{
		close(fds[i][0]);
		close(fds[i][1]);                                           //A CHECK ERROR
		i++;
	}
	i = 0;
	while (i++ < data->lst_nbr)
		wait(&status);
	i = 0;
	while (i < data->lst_nbr)
	{
		hd_file = ft_strjoin_c("/tmp/.here_doc", (char)(i + 97));	
		if (access(hd_file, F_OK) == 0)
			unlink(hd_file);
		free(hd_file);
		i++;
	}
	return (0);
}

int	ft_execution(t_data *data, char **env) //FONCTION PRINCIPALE DE L'EXECUTION
{
	t_cmd_list	*last;

	last = ft_lstlast(data->cmd_table);
	data->lst_nbr = ft_lstsize(data->cmd_table);
	if (data->lst_nbr == 1)
		return (exec_one_cmd(data, env));
	if (data->lst_nbr > 1)
	{
		if (last->cmd[0] == '\0')
			return (4);
		data->lst_nbr = (data->lst_nbr / 2) + 1;
		return (exec_cmds(data, env));
	}
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

// ls >a -a > b -l
