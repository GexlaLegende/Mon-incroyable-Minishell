/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 07:06:38 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/28 19:07:50 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	bin_exit(t_data *data, int is_pipe)
{
	if (is_pipe == 0)
		printf("exit\n");
	ft_env_lstclear(&data->env_table);
	ft_env_lstclear(&data->env_table_sorted);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
