/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:26:16 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/28 17:34:49 by dbouron          ###   ########lyon.fr   */
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
			data.cmd_table_temp = data.cmd_table;
			data.cmd_table = data.cmd_table->next;
			parserror(ft_env_var(&data));
			exekerror(ft_execution(&data, env));
		}
		free(data.main_str);
		if (data.main_error != -1)
			ft_lstclear(&data.cmd_table_temp);
		else
			free(data.cmd_table);
	}
	ft_env_lstclear(&data.env_table);
	ft_env_lstclear(&data.env_table_sorted);
	rl_clear_history();
	return (0);
}

//aff_list_env(&data);
//afflistchaine(&data);
//rl_clear_history();    //Ne fonctionne pas
//str = readline("Minishell \033[31m❯\033[33m❯\033[32m❯\033[00m ");

/* printf("%p\n", data.cmd_table->cmd);
		printf("%p\n", &data.cmd_table->redir_type[0]);
		printf("%p\n", &data.cmd_table->redir_type[1]);
		printf("%p\n", data.arg_tabl);
		printf("%p\n", data.arg_tabl[0]);
		printf("%p\n", data.arg_tabl[1]);
		printf("%p\n", data.arg_tabl[2]);
		printf("%p\n", data.paths);
		printf("%p\n", data.paths[0]);
		printf("%p\n", data.paths[1]);
		printf("%p\n", data.paths[2]);
		printf("%p\n", data.paths[3]);
		printf("%p\n", data.paths[4]);
		printf("%p\n", data.paths[5]);
		printf("%p\n", data.paths[6]);
		printf("%p\n", data.paths[7]);
		printf("%p\n", data.paths[8]);
		printf("%p\n", data.paths[9]); */
		/* while (data.env_table->next->next)
		{
			printf("%p\n", data.env_table);
			data.env_table = data.env_table->next;
		}
		printf("%p\n", data.env_table->name);
		printf("%p\n", data.env_table->value);
		printf("%p\n", data.env_table->next); */
		//sleep(20);
		/* printf("%p\n", data.main_str);
		printf("%p\n", data.cmd_table);
		printf("%p\n", data.env_table);
		printf("%p\n", &data.squote);
		printf("%p\n", &data.dquote);
		printf("%p\n", &data.r_tabl);
		printf("%p\n", data.paths);
		printf("%p\n", data.arg_tabl);
		printf("%p\n", &data.path_nbr);
		printf("%p\n", &data.here_doc_nbr);
		printf("%p\n", &data.lst_nbr);
		printf("%p\n", &data.nbr);
		printf("%p\n", &data.i);
		printf("%p\n", &data.li);
		printf("%p\n", &data.ly);
		printf("%p\n", &data.j);
		printf("%p\n", &data.rdj);
		printf("%p\n", &data.x);
		printf("%p\n", &data.exec_i);
		printf("%p\n", &data.lexer_error);
		printf("%p\n", &data.lexer_start);
		printf("%p\n", &data.error_getcmd);
		printf("%p\n", &data.main_error);
		printf("%p\n", &data.fds);
		printf("%p\n", &data.pid);
		printf("%p\n", &data.rdi);
		printf("%p\n", &data.pskip);
		printf("%p\n", data.pcommand);
		printf("%p\n", data.redir_type);
		printf("%p\n", data.redir_file);
		printf("%p\n", &data.tabl_s);
		printf("%p\n", &data.parser_error);
		printf("%p\n", &data.rd_error);
		printf("%p\n", &data.is_built_in);
		printf("%p\n", &data.bin_nbr);
		printf("%p\n", &data.bin_inpipe);
		printf("%p\n", &data.nbr_save); */
