/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:41:08 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/28 18:21:15 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	getcmd_and_pipe(t_data *data, char **env)
{
	if (ft_is_builtin(data->arg_tabl[0]) != 0)
		if (put_path(data) == 2)
			return (2);
	data->j = 0;
	data->pid = fork();
	if (data->pid == 0)
	{
		if (data->exec_i != data->lst_nbr - 1)
			dup2(data->fds[data->exec_i][1], STDOUT_FILENO);
		if (data->exec_i != 0)
			dup2(data->fds[data->exec_i - 1][0], STDIN_FILENO);
		while (data->j < data->lst_nbr - 1)
		{
			close(data->fds[data->j][0]);
			close(data->fds[data->j][1]);
			data->j = data->j + 1;
		}
		if (ft_is_builtin(data->arg_tabl[0]) == 0)
		{
			built_in(data, env, data->bin_nbr);
			data->is_built_in = 0;
			exit (0);
		}
		else
			if (cmd_redir(data, env, data->exec_i) != 0)
				return (3);
	}
	if (data->cmd_table->next)
		data->cmd_table = data->cmd_table->next;
	if (data->cmd_table->next)
		data->cmd_table = data->cmd_table->next;
	data->exec_i++;
	return (0);
}

int	exec_cmds_second(t_data *data, char **env)
{
	data->exec_i = -1;
	data->fds = malloc(sizeof(int *) * (data->lst_nbr + 1));
	while (++data->exec_i <= data->lst_nbr)
		data->fds[data->exec_i] = malloc(sizeof(int) * 2);
	data->exec_i = 0;
	while (data->exec_i < data->lst_nbr - 1)
	{
		pipe(data->fds[data->exec_i]);
		data->exec_i++;
	}
	data->exec_i = 0;
	while (data->exec_i < data->lst_nbr)
	{
		data->arg_tabl = get_cmd(data);
		data->error_getcmd = getcmd_and_pipe(data, env);
		if (data->error_getcmd != 0)
			return (data->error_getcmd);
		data->free_i = 0;
		while (data->free_i <= data->nbr_save + 1)
			free(data->arg_tabl[data->free_i++]);
		free(data->arg_tabl);
	}
	data->exec_i = 0;
	return (0);
}
