/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:26:16 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/30 14:47:56 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handler(int sigtype)
{
	if (sigtype == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	handler2(int sigtype)
{
	if (sigtype == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (sigtype == SIGQUIT)
	{
		printf("Quit: 3\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	main_fonction_two(t_data *data)
{
	data->paths = recup_path(data);
	data->cmd_table = ft_lstnew(NULL, NULL, NULL);
	data->here_doc_nbr = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	setup_term(0);
	data->main_str = readline("Minishell $> ");
	setup_term(1);
	if (!data->main_str)
		bin_exit(data, 0);
	if (str_is_empty(data->main_str) != 0)
		add_history(data->main_str);
	data->main_error = parserror(ft_lexer(data->main_str, data), data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc != 1 || !(argv[0]))
		exit (0);
	parserror(ft_put_env_in_lst(&data, env), &data);
	data.env_table_sorted = NULL;
	data.last_error = 0;
	while (1)
	{
		main_fonction_two(&data);
		if (data.main_error == 0)
		{
			data.cmd_table_temp = data.cmd_table;
			data.cmd_table = data.cmd_table->next;
			signal(SIGINT, handler2);
			signal(SIGQUIT, handler2);
			parserror(ft_env_var(&data), &data);
			exekerror(ft_execution(&data, env), &data);
		}
		ft_free_all(&data);
		if (data.main_error != -1)
			ft_lstclear(&data.cmd_table_temp);
		else
			free(data.cmd_table);
	}
}

//aff_list_env(&data);
//afflistchaine(&data);
//rl_clear_history();    //Ne fonctionne pas
//str = readline("Minishell \033[31m❯\033[33m❯\033[32m❯\033[00m ");
