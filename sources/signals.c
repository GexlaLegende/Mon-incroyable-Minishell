/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 09:51:37 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/30 19:46:02 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	setup_term(int save)
{
	struct termios			t;
	static int				ifsave;
	static struct termios	saved;

	if (!ifsave)
	{
		tcgetattr(STDOUT_FILENO, &saved);
		ifsave = 1;
	}
	tcgetattr(STDOUT_FILENO, &t);
	t.c_lflag &= ~ECHOCTL;
	t.c_cc[VQUIT] = 0;
	if (save == 1)
		tcsetattr(STDOUT_FILENO, TCSANOW, &saved);
	else
		tcsetattr(STDOUT_FILENO, TCSANOW, &t);
}

int	str_is_empty(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] != ' ' && str[i] != 9)
				return (1);
			i++;
		}
	}
	return (0);
}

void	ft_free_all(t_data *data)
{
	int	i;

	i = -1;
	while (data->paths[++i])
		free(data->paths[i]);
	free(data->paths);
	free(data->main_str);
}

void	exec_cmds_two(t_data *data)
{
	while (data->exec_i < data->lst_nbr - 1)
	{
		close(data->fds[data->exec_i][0]);
		close(data->fds[data->exec_i][1]);
		data->exec_i++;
	}
	data->exec_i = 0;
}
