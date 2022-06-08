/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:26:16 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/08 21:03:58 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_addpipe(void)  //Fonction pour l'ajout du maillon pipe dans la liste chainée
{
	printf("%s\n", "pipe added");
}

void	ft_parsing2(char *str, t_list *cmd_table, t_data *data, int end) //Fonction secondaire (deuxieme découpage)
{
	str[end] = '\0';       //Selectionne la commande en coupant au Pipe
	printf("%s\n", str);

	data->dquote = data->dquote; //-Werror content
	cmd_table->cmd = "o"; //-Werror content
}

int	ft_parsing(char *str, t_list *cmd_table, t_data *data) //Fonction principale du parsing (premier découpage)
{
	int	start;
	int	i;

	data->squote = 0;
	data->dquote = 0;
	i = 0;
	start = 0;
	if (str[0] == '|')
		return (1);
	while (str[i])
	{
		if (str[i] == '"' && data->dquote == 0) //switch single quote
		{
			if (data->squote == 0)
				data->squote = 1;
			else
				data->squote = 0;
		}
		if (str[i] == '\'' && data->squote == 0) //switch double quote
		{
			if (data->dquote == 0)
				data->dquote = 1;
			else
				data->dquote = 0;
		}
		if (str[i] == '|' && data->squote == 0 && data->dquote == 0)  //Detection du pipe
		{
			ft_parsing2(&str[start], cmd_table, data, i);
			ft_addpipe();
			start = i + 1;
		}
		i++;
	}
	if (data->squote == 1 || data->dquote == 1)
		return (2);
	ft_parsing2(&str[start], cmd_table, data, i);  //Envoie la derniere commande
	return (0);
}

void	parserror(int nbr) //Fonction pour les erreurs de parsing
{
	if (nbr == 1)
	{
		write(2, "syntax error near unexpected token `|'", 39);
		exit(0);
	}
	if (nbr == 2)
	{
		write(2, "Error quote not closed", 23);
		exit(0);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	*str;
	t_list	cmd_table;
	t_data	data;

	i = 0;
	//printf("%d\n", argc);
	int poulpe;
	poulpe = argc; //-Werror content
	//printf("NAME = %s\n", argv[0]);
	argv[0] = argv[0]; //-Werror content
	while (env[i])
	{
		//printf("%d- %s\n", i, env[i]);
		i++;
	}
	while (1)
	{
		str = readline("test> ");
		printf("INITIAL STRING = %s\n", str);
		parserror(ft_parsing(str, &cmd_table, &data));
	}
	return (0);
}
