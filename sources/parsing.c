/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:25:13 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/25 14:45:38 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_lexer2(t_data *data, char *str)
{
	while (str[data->li])
	{
		data->ly = data->li;
		quotes_switch(data, str, data->li);
		if (str[data->li] == '|' && data->squote == 0 && data->dquote == 0)
		{
			data->ly++;
			while (str[data->ly] && (str[data->ly] == ' '
					|| str[data->ly] == '\n'))
				data->ly++;
			if (str[data->ly] == '|')
				return (3);
			data->lexer_error = ft_parser(&str[data->lexer_start],
					data, data->li - data->lexer_start);
			if (data->lexer_error != 0)
				return (data->lexer_error);
			ft_addpipe(data);
			data->lexer_start = data->li + 1;
			data->r_tabl = 0;
		}
		data->li++;
	}
	return (0);
}

//Fonction principale du parsing (premier découpage)
int	ft_lexer(char *str, t_data *data)
{
	data->squote = 0;
	data->dquote = 0;
	data->r_tabl = 0;
	data->li = 0;
	data->lexer_start = 0;
	data->ly = 0;
	while (str[data->ly] && (str[data->ly] == ' ' || str[data->ly] == '\n'))
		data->ly++;
	if (str[data->ly] == '|')
		return (1);
	data->lexer_error = ft_lexer2(data, str);
	if (data->lexer_error != 0)
		return (data->lexer_error);
	if (data->squote == 1 || data->dquote == 1)
		return (2);
	data->lexer_error = ft_parser(&str[data->lexer_start],
			data, data->li - data->lexer_start);
	if (data->lexer_error != 0)
		return (data->lexer_error);
	return (0);
}

//Fonction pour l'ajout du maillon pipe dans la liste chainée
void	ft_addpipe(t_data *data)
{
	char	*str;
	int		*redir_type;
	char	**redir_file;

	redir_type = (int *)malloc(sizeof(int) * 2);
	redir_file = malloc(sizeof(char *) * 2);
	str = malloc(sizeof(char) * 2);
	redir_type[0] = 5;
	redir_file[0] = NULL;
	str[0] = '|';
	str[1] = '\0';
	ft_lstadd_back(&data->cmd_table, ft_lstnew(str, redir_type, redir_file));
}

int	ft_parser2(t_data *data, char *str)
{
	while (str[data->rdi] == ' ')
		data->rdi++;
	while (str[data->rdi])
	{
		quotes_switch(data, str, data->rdi);
		if ((str[data->rdi] == '>' || str[data->rdi] == '<')
			&& data->squote == 0 && data->dquote == 0)
		{
			data->pskip = redir_parsing(str, data);
			if (data->pskip < 0)
				return (data->pskip);
			data->rdi = data->rdi + data->pskip;
		}
		else
		{
			data->pcommand = ft_strmjoin(data->pcommand, str[data->rdi]);
			if (str[data->rdi] == ' ' && data->squote == 0 && data->dquote == 0)
				while (str[data->rdi] == ' ' && data->squote == 0
					&& data->dquote == 0)
					data->rdi++;
			else
				data->rdi++;
		}
	}
	return (0);
}

//Fonction secondaire (deuxieme découpage)
int	ft_parser(char *str, t_data *data, int end)
{
	data->rdi = 0;
	if (str[end])
		str[end] = '\0';
	data->pcommand = NULL;
	data->tabl_s = count_redir(str, data);
	if (data->tabl_s == -1)
		return (3);
	data->redir_type = (int *)malloc(sizeof(int) * (data->tabl_s + 1));
	data->redir_file = malloc(sizeof(char *) * (data->tabl_s + 1));
	while (data->rdi < data->tabl_s + 1)
	{
		data->redir_type[data->rdi] = 0;
		data->redir_file[data->rdi] = NULL;
		data->rdi++;
	}
	data->rdi = 0;
	data->parser_error = ft_parser2(data, str);
	if (data->parser_error != 0)
		return (data->parser_error);
	data->pcommand = ft_strmjoin(data->pcommand, '\0');
	ft_lstadd_back(&data->cmd_table,
		ft_lstnew(data->pcommand, data->redir_type, data->redir_file));
	data->here_doc_nbr = data->here_doc_nbr + 1;
	return (0);
}

//TODO
// FONCTION D"ERREUR A MACHINER -- à moitier fait ça mais sa passe crème tkt
// LES SEGFAULTS (à trouver avant de les corriger)

// FAIT | GERER LES NOM DE FICHIER APRES LES REDIR KI -
// - COMMENCE PAR UN CHAR SPE EX : |, &, %.....
// FAIT |N'EST PAS AUTORISER : ! # * ( ) ; / ?

//Si $variable non trouvé marche pour heredoc mais pas les autre ?? (ps: oskour)
