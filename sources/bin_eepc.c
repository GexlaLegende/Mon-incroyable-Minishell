/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_eepc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
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
	if (ft_strncmp(data->arg_tabl[0], "echo") == 0)
		bin_echo(data);
	if (ft_strncmp(data->arg_tabl[0], "cd") == 0)
		bin_cd(data);
/* 	if (ft_strncmp(data->arg_tabl[0], "exit") == 0)
		bin_echo(exit); */
	i = 0;
	while (i <= data->nbr_save + 1)
		free(data->arg_tabl[i++]);
	free(data->arg_tabl);
	return (0);
}

int	bin_echo(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->echo_n = 0;
	while (data->arg_tabl[++i])
	{
		j = 0;
		if (data->arg_tabl[i][j++] == '-')
			while (data->arg_tabl[i][j] && data->arg_tabl[i][j] == 'n')
				j++;
		if (j != 1 && data->arg_tabl[i][j] == '\0')
			data->echo_n = 1;
		else
		{
			i--;
			j = 0;
			while (data->arg_tabl[++i])
			{
				if (j != 0)
					printf(" ");
				printf("%s", data->arg_tabl[i]);
				j++;
			}
			if (data->echo_n == 0)
				printf("\n");
			return (0);
		}
	}
	return (0);
}

/* Builtin env: display environment variables if there is a value */
void	bin_env(t_data *data)
{
	int			i;
	t_env_list	*begin;

	i = 0;
	begin = data->env_table;
	if (data->arg_tabl[1] == NULL)
	{
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
	else
		printf("env: No such file or directory\n");
}

/* Display the PATH of the current position */
int	bin_pwd(void)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (0);
}

void	bin_cd(t_data *data)
{
	char	cwd[PATH_MAX];

	data->e = 0;
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	chdir("/Volumes/Storage/goinfre/dbouron");
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}
