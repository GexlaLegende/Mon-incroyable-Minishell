/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:51:48 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/30 13:14:07 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	forward_redir(t_data *data, int i)
{
	int	file;

	file = 0;
	if (data->cmd_table->redir_type[i] == 1)
	{
		file = open(data->cmd_table->redir_file[i],
				O_CREAT | O_RDWR | O_APPEND, 0644);
		if (file < 0)
			return (-1);
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	if (data->cmd_table->redir_type[i] == 2)
	{
		file = open(data->cmd_table->redir_file[i],
				O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (file < 0)
			return (-1);
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	return (0);
}

int	backward_redir(t_data *data, int i, int nbr)
{
	int		file;
	char	*here_doc_file;
	char	*str2;

	file = 0;
	if (data->cmd_table->redir_type[i] == 3)
	{
		str2 = NULL;
		here_doc_file = ft_strjoin_c("/tmp/.here_doc", (char)(nbr + 97));
		file = open(here_doc_file, O_RDONLY);
		if (file < 0)
			return (-1);
		dup2(file, STDIN_FILENO);
		close(file);
		free(here_doc_file);
	}
	if (data->cmd_table->redir_type[i] == 4)
	{
		file = open(data->cmd_table->redir_file[i], O_RDONLY);
		if (file < 0)
			return (-1);
		dup2(file, STDIN_FILENO);
		close(file);
	}
	return (0);
}

// 1 - >> 2 - > 3 - << 4 - <
int	cmd_redir(t_data *data, char **env, int nbr)
{
	int		i;

	i = 0;
	while (data->cmd_table->redir_type[i] != 0)
	{
		if (forward_redir(data, i) == -1)
			return (-1);
		if (backward_redir(data, i, nbr) == -1)
			return (-1);
		i++;
	}
	if (data->is_built_in == 0)
	{
		if (data->cmd_table->cmd[0] == '\0')
			exit (0);
		execve(data->arg_tabl[0], data->arg_tabl, env);
	}
	return (0);
}

int	exec_cmds(t_data *data, char **env)
{
	char	*hd_file;

	data->error_getcmd = exec_cmds_second(data, env);
	if (data->error_getcmd != 0)
		return (data->error_getcmd);
	exec_cmds_two(data);
	while (data->exec_i++ < data->lst_nbr)
		wait_loop(data);
	data->exec_i = 0;
	while (data->exec_i < data->lst_nbr)
	{
		hd_file = ft_strjoin_c("/tmp/.here_doc", (char)(data->exec_i + 97));
		if (access(hd_file, F_OK) == 0)
			unlink(hd_file);
		free(hd_file);
		data->exec_i++;
	}
	data->free_i = -1;
	while (++data->free_i <= data->lst_nbr)
		free(data->fds[data->free_i]);
	free(data->fds);
	return (0);
}

//FONCTION PRINCIPALE DE L'EXECUTION
int	ft_execution(t_data *data, char **env)
{
	t_cmd_list	*last;

	last = ft_lstlast(data->cmd_table);
	data->lst_nbr = ft_lstsize(data->cmd_table);
	data->stdin_save = dup(1);
	data->stdout_save = dup(0);
	data->is_pipe = 0;
	data->is_built_in = 0;
	if (data->lst_nbr == 1)
		return (exec_one_cmd(data, env));
	if (data->lst_nbr > 1)
	{
		data->is_pipe = 1;
		if (last->cmd[0] == '\0')
			return (4);
		data->lst_nbr = (data->lst_nbr / 2) + 1;
		return (exec_cmds(data, env));
	}
	return (0);
}
