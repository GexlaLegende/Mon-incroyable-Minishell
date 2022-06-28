/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_eepc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 07:06:46 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/28 10:38:35 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*	Choose the appropriate builtin function 
	Arguments are in data -> data->arg_tabl
	(arg_tabl[0] is the name of cmd - ex: env) */
int	built_in(t_data *data, char **env, int nbr)
{
	int	i;

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
	i = 0;
	while (i <= data->nbr_save + 1)
		free(data->arg_tabl[i++]);
	free(data->arg_tabl);
	return (0);
}

/* void	bin_echo()
{
	
} */

/* Builtin env: display environment variables if there is a value */
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

/* Display the PATH of the current position */
int	bin_pwd(void)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (0);
}

/* void	bin_cd()
{
	
} */
