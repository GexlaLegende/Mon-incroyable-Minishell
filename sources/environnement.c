/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environnement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:19:43 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/15 14:58:30 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env_var(t_data *data, char **env)
{
	int	i;

	i = 0;
	(void)data;
	while (env[i])
		printf("%s\n", env[i++]);
	return (0);
}


int	main(int argc, char **argv, char **env)
{
	t_data	data;

	dprintf(2, "\033[33mARGC------------------------\033[00m\n\t%d\n\n\033[33mARGV[0]---------------------\033[00m\n\t%s\n\n\033[33mVARIABLES ENV---------------\033[00m\n", argc, argv[0]);
	ft_env_var(&data, env);
	dprintf(2, "\n");
	return (0);
}
