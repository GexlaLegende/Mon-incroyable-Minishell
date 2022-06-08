/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:26:16 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/08 15:32:20 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	*str;

	i = 0;
	printf("%d\n", argc);
	printf("NAME = %s\n", argv[0]);
	while (env[i])
	{
		printf("%d- %s\n", i, env[i]);
		i++;
	}
	while (1)
	{
		str = readline("test> ");
		printf("%s\n", str);
	}
	return (0);
}
