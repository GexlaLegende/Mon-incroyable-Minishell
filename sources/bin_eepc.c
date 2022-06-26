/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_eepc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 07:06:46 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/26 10:02:35 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void	bin_echo()
{
	
} */

void	bin_env(t_data *data)
{
	int			i;
	t_env_list	*begin;

	i = 0;
	begin = data->env_table;
	while (begin)
	{
		printf("%s", begin->name);
		//checker si affiche un truc quand il n'a pas de value
		printf("=%s\n", begin->value);
		begin = begin->next;
		i++;
	}
}

/* 
void	bin_pwd()
{
	char cwd[PATH_MAX];
	
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}
void	bin_cd()
{
	
}
 */