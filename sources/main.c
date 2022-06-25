/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:26:16 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/25 15:39:50 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	str_is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != 9)
			return (1);
		i++;
	}
	return (0);
}

/* void	handler(int sigtype)
{
	if (sigtype == SIGINT)
		//ah oui
	else if (sigtype == SIGQUIT)
		//ah oui
} */

//struct sigaction	action;

//action.sa_handler = handler;
//action.sa_flags = SA_RESTART;
//sigaction(SIGINT, &action, NULL); // ctrl-C
//sigaction(SIGUSR2, &action, NULL); // ctrl-D = EOF = special = chiant
//sigaction(SIGQUIT, &action, NULL); // ctrl-backslash
int	main(int argc, char **argv, char **env)
{
	t_data				data;

	if (argc != 1 || !(argv[0]))
		exit (0);
	data.paths = recup_path(env, &data);
	while (1)
	{
		data.cmd_table = ft_lstnew(NULL, NULL, NULL);
		data.here_doc_nbr = 0;
		data.main_str = readline("Minishell $> ");
		if (str_is_empty(data.main_str) != 0)
			add_history(data.main_str);
		data.main_error = parserror(ft_lexer(data.main_str, &data));
		if (data.main_error == 0)
		{
			data.cmd_table = data.cmd_table->next;
			parserror(ft_env_var(&data, env));
			exekerror(ft_execution(&data, env));
		}
		if (data.main_error != -1)
			ft_lstclear(&data.cmd_table);
		ft_env_lstclear(&data.env_table);
	}
	return (0);
}

//rl_clear_history();
//aff_list_env(&data);
//afflistchaine(&data);
//rl_clear_history();    //Ne fonctionne pas
//str = readline("Minishell \033[31m❯\033[33m❯\033[32m❯\033[00m ");
