/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:26:16 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/27 09:48:25 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	str_is_empty(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] != ' ' && str[i] != 9)
				return (1);
			i++;
		}
	}
	return (0);
}

void	handler(int sigtype)
{
	if (sigtype == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data				data;
	struct sigaction	action;
	struct sigaction	action2;

	action.sa_handler = handler;
	action.sa_flags = SA_RESTART;
	action2.sa_handler = SIG_IGN;
	action2.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL); // ctrl-C
	sigaction(SIGQUIT, &action2, NULL); // ctrl-backslash
	if (argc != 1 || !(argv[0]))
		exit (0);
	data.paths = recup_path(env, &data);
	parserror(ft_put_env_in_lst(&data, env));
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
			parserror(ft_env_var(&data));
			exekerror(ft_execution(&data, env));
		}
		if (data.main_error != -1)
			ft_lstclear(&data.cmd_table);
	}
	ft_env_lstclear(&data.env_table);
	rl_clear_history();
	return (0);
}

//aff_list_env(&data);
//afflistchaine(&data);
//rl_clear_history();    //Ne fonctionne pas
//str = readline("Minishell \033[31m❯\033[33m❯\033[32m❯\033[00m ");
