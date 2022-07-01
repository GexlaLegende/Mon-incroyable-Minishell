/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 07:06:38 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/30 23:51:40 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return(1);
	return (0);
}

void	bin_exit(t_data *data, int is_pipe)
{
	if (data->nbr_save > 1)
		printf("exit: too many arguments\n");
	if (data->nbr_save > 1)
		if (is_pipe == 1)
			exit(1);
	if (!(data->nbr_save > 1))
	{
		if (is_pipe == 0)
			printf("exit");
		ft_env_lstclear(&data->env_table);
		ft_env_lstclear(&data->env_table_sorted);
		rl_clear_history();
		if (data->nbr_save == 1)
		{
			if (is_number(data->arg_tabl[1]) == 0 || ft_atoi(data->arg_tabl[1]) == -2)
			{
				printf(" numeric argument required\n");
				exit(255);
			}
			exit(ft_atoi((data->arg_tabl[1])) % 256);
		}
		printf("\n");
		exit(EXIT_SUCCESS);
	}
}
