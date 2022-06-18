/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:26:16 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/18 18:23:48 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	afflistchaine(t_data *data)  //POUR PRINT TOUTE LA LISTE CHAINER PUIS VERIF
{
	int		nbr;
	t_list	*begin;

	nbr = 0;
	begin = data->cmd_table;
	begin = begin->next;
	while (begin)
	{
		nbr++;
		printf("MAILLON %d ------------------------------\n", nbr);
		printf("COMMAND - %s\n", begin->cmd);
		if (begin->redir_type)
			printf("TYPE 1 - %d \n", begin->redir_type[0]);
		if (begin->redir_file)
			printf("FILE 1 - %s\n", begin->redir_file[0]);
		if (begin->redir_type[0] != 5 && begin->redir_type[0] != 0)
		{
			if (begin->redir_type)
				printf("TYPE 2 - %d \n", begin->redir_type[1]);
			if (begin->redir_file)
				printf("FILE 2 - %s\n", begin->redir_file[1]);
		}
		begin = begin->next;
	}
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
	data.paths = recup_path(env, &data);
	while (1)
	{
		data.cmd_table = ft_lstnew(NULL, NULL, NULL); // CHANGER A METTRE DANS FONCTION + CLEAR LISTE A CHAKK FOIS
		str = readline("Minishell $> ");
		add_history(str);
		parserror(ft_parsing(str, &data));
		afflistchaine(&data);
		data.cmd_table = data.cmd_table->next;
		exekerror(ft_execution(&data, env));
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
