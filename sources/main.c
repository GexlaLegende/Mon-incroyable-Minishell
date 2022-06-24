/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:26:16 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/24 18:28:41 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	afflistchaine(t_data *data)  //POUR PRINT TOUTE LA LISTE CHAINEE PUIS VERIF
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

void	aff_list_env(t_data *data)  //POUR PRINT TOUTE LA LISTE CHAINEE ENV
{
	int			nbr;
	t_env_list	*begin;

	nbr = 0;
	begin = data->env_table;
	//begin = begin->next;
	dprintf(2, "\033[33mLISTE CHAINE ENV--------------\033[00m\n");
	while (begin)
	{
		printf("Maillon %d ----------------------\n", nbr);
		printf("- Name : %s\n", begin->name);
		printf("- Value : %s\n", begin->value);
		begin = begin->next;
		nbr++;
	}
	dprintf(2, "\n");
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	*str;
	t_data	data;
	int		error;

	i = 0;
	if (argc)
		if (argv)
			if (env)
				i = 0;
	data.paths = recup_path(env, &data);
	while (1)
	{
		data.cmd_table = ft_lstnew(NULL, NULL, NULL); // CHANGER A METTRE DANS FONCTION + CLEAR LISTE A CHAKK FOIS
		//dprintf(2, "\033[33mINITIAL STRING----------------\033[00m\n\t%s\n\n", str);
		data.here_doc_nbr = 0;
		str = readline("Minishell $> "); //str = readline("Minishell \033[31m❯\033[33m❯\033[32m❯\033[00m ");
		add_history(str); // Faire une fonction special pour voir si str est composé que d'espaces ou de tab
		error = parserror(ft_lexer(str, &data));
		//afflistchaine(&data);
		if (error == 0)
		{
			data.cmd_table = data.cmd_table->next;
			parserror(ft_env_var(&data, env));
			exekerror(ft_execution(&data, env));
		}
		if (error != -1)
			ft_lstclear(&data.cmd_table);
		ft_env_lstclear(&data.env_table);
	}
	//aff_list_env(&data);
	//afflistchaine(&data);
	//rl_clear_history();    //Ne fonctionne pas
	return (0);
}
