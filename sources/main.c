/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:26:16 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/16 15:41:11 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	afflistchaine(t_data *data)  //POUR PRINT TOUTE LA LISTE CHAINER PUIS VERIF
{
	int			nbr;
	t_cmd_list	*begin;

	nbr = 0;
	begin = data->cmd_table;
	begin = begin->next;
	dprintf(2, "\033[33mLISTE CHAINE CMD--------------\033[00m\n");
	while (begin)
	{
		nbr++;
		printf("Maillon %d ----------------------\n", nbr);
		printf("Command - %s\n", begin->cmd);
		if (begin->redir_type)
			printf("Type 1 - %d \n", begin->redir_type[0]);
		if (begin->redir_file)
			printf("File 1 - %s\n", begin->redir_file[0]);
		if (begin->redir_type[0] != 5 && begin->redir_type[0] != 0)
		{
			if (begin->redir_type)
				printf("Type 2 - %d \n", begin->redir_type[1]);
			if (begin->redir_file)
				printf("File 2 - %s\n", begin->redir_file[1]);
		}
		begin = begin->next;
	}
	dprintf(2, "\n");
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	*str;
	t_data	data;

	i = 0;
	if (argc)
		if (argv)
			if (env)
				i = 0;
	while (1)
	{
		data.cmd_table = ft_lstnew(NULL, NULL, NULL); // CHANGER A METTRE DANS FONCTION + CLEAR LISTE A CHAKK FOIS
		str = readline("Minishell \033[31m❯\033[33m❯\033[32m❯\033[00m ");
		add_history(str);
		dprintf(2, "\033[33mINITIAL STRING----------------\033[00m\n\t%s\n\n", str);
		parserror(ft_lexer(str, &data));
		afflistchaine(&data);
		dprintf(2, "\033[33mVARIABLES ENV-----------------\033[00m\n");
		parserror(ft_env_var(&data, env));
		dprintf(2, "\n");
		//afflistchaine(&data);
		ft_lstclear(&data.cmd_table);
	}
	//rl_clear_history();    //Ne fonctionne pas
	return (0);
}

// Pour voir tous le env
/* while (env[i])
	{
		//printf("%d- %s\n", i, env[i]);
		i++;
	} */

//ft_lstadd_back(data.cmd_table, ft_lstnew(NULL));
