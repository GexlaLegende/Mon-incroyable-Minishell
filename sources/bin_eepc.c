/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_eepc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 07:06:46 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/28 10:09:04 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//FONCTION QUI RENVOIE VERS LES FONCTIONS BUILT-IN
int	built_in(t_data *data, char **env, int nbr)// Les arguments sont dans data -> data->arg_tabl (arg_tabl[0] étant le nom de la cmd ex: -> env)
{
	printf("IN BUILT IN\n");
	data->is_built_in = 1;
	cmd_redir(data, env, nbr);
	if (ft_strncmp(data->arg_tabl[0], "pwd") == 0)
		return (bin_pwd());
	if (ft_strncmp(data->arg_tabl[0], "env") == 0)
		bin_env(data);
	if (ft_strncmp(data->arg_tabl[0], "export") == 0)
		bin_export(&data->arg_tabl[1], data);
	if (ft_strncmp(data->arg_tabl[0], "unset") == 0)
		bin_unset(&data->arg_tabl[1], data);
	return (0);
}

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
		if (begin->value != NULL)
		{
			printf("%s", begin->name);
			printf("=%s\n", begin->value);
		}
		begin = begin->next;
		i++;
	}
}

int	bin_pwd()
{
	char cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (0);
}
/* void	bin_cd()
{
	
} */
