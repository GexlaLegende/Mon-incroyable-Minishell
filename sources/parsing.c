/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:25:13 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/25 06:48:07 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lexer(char *str, t_data *data) //Fonction principale du parsing (premier découpage)
{
	int		start;
	int		i;
	int		error;
	int		y;

	data->squote = 0;
	data->dquote = 0;
	data->r_tabl = 0;
	i = 0;
	start = 0;
	y = 0;
	while (str[y] && (str[y] == ' ' || str[y] == '\n'))
		y++;
	if (str[y] == '|')
		return (1);
	while (str[i])
	{
		y = i;
		quotes_switch(data, str, i);
		if (str[i] == '|' && data->squote == 0 && data->dquote == 0) //Detection du pipe
		{
			y++;
			while (str[y] && (str[y] == ' ' || str[y] == '\n'))
				y++;
			if (str[y] == '|')
				return (3);
			error = ft_parser(&str[start], data, i - start);
			if (error != 0)
				return (error);
			ft_addpipe(data);
			start = i + 1;
			data->r_tabl = 0;
		}
		i++;
	}
	if (data->squote == 1 || data->dquote == 1)
		return (2);
	error = ft_parser(&str[start], data, i - start); //Envoie la derniere commande
	if (error != 0)
		return (error);
	return (0);
}

void	ft_addpipe(t_data *data)						//Fonction pour l'ajout du maillon pipe dans la liste chainée
{
	char	*str;
	int		*redir_type;
	char	**redir_file;

	//printf("%s\n", "pipe added");			//TODO erreur si || double pipes
	redir_type = (int *)malloc(sizeof(int) * 2);
	redir_file = malloc(sizeof(char *) * 2);
	str = malloc(sizeof(char) * 2);
	redir_type[0] = 5;
	redir_file[0] = NULL;
	str[0] = '|';
	str[1] = '\0';
	ft_lstadd_back(&data->cmd_table, ft_lstnew(str, redir_type, redir_file));
}

void	quotes_switch(t_data *data, char *str, int i)
{
	if (str[i] == '\'' && data->dquote == 0) //switch single quote
	{
		if (data->squote == 0)
			data->squote = 1;
		else
			data->squote = 0;
	}
	if (str[i] == '"' && data->squote == 0) //switch double quote
	{
		if (data->dquote == 0)
			data->dquote = 1;
		else
			data->dquote = 0;
	}
}

int	ft_parser(char *str, t_data *data, int end) //Fonction secondaire (deuxieme découpage)
{
	int		i;
	int		skip;
	char	*command;
	int		*redir_type;
	char	**redir_file;
	int		sizeoftabl;

	i = 0;
	if (str[end])
		str[end] = '\0';								//Selectionne la commande en coupant au Pipe
	command = NULL;
	sizeoftabl = count_redir(str, data);
	if (sizeoftabl == -1)
		return (3);
	redir_type = (int *)malloc(sizeof(int) * (sizeoftabl + 1));
	redir_file = malloc(sizeof(char *) * (sizeoftabl + 1));
	while (i < sizeoftabl + 1)
	{
		redir_type[i] = 0;
		redir_file[i] = NULL;
		i++;
	}
	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		quotes_switch(data, str, i);
		if ((str[i] == '>' || str[i] == '<') && data->squote == 0 && data->dquote == 0)  //TODO SIMPLIFIER SKIP EN UTILISANT LADDRESSE DE I
		{
			skip = redir_parsing(str, i, data, &redir_type, &redir_file);
			if (skip < 0)
				return (skip);
			i = i + skip;
		}
		else
		{
			command = ft_strmjoin(command, str[i]);
			if (str[i] == ' ' && data->squote == 0 && data->dquote == 0)
				while (str[i] == ' ' && data->squote == 0 && data->dquote == 0)
					i++;
			else
				i++;
		}
	}
	command = ft_strmjoin(command, '\0');
	ft_lstadd_back(&data->cmd_table, ft_lstnew(command, redir_type, redir_file));
	data->here_doc_nbr = data->here_doc_nbr + 1;
	return (0);
}

void	here_doc_fct(t_data *data, char *str)
{
	char	*file;
	int		fd;
	char	*str2;

	str2 = NULL;
	file = ft_strjoin_c("/tmp/.here_doc", (char)(data->here_doc_nbr + 97));
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		str2 = readline("> ");
		if (str_diff(str, str2) == 0)
			break ;
		write(fd, str2, ft_strlen(str2));
		write(fd, "\n", 1);
	}
}

int	redir_parsing(char *str, int i, t_data *data, int **redir_type, char ***redir_file)
{
	int	j;

	j = i;
	if (str[j] == '>' && str[j + 1] == '>')
	{
		(*redir_type)[data->r_tabl] = 1;
		j++;
	}
	else if (str[j] == '>')
		(*redir_type)[data->r_tabl] = 2;
	else if (str[j] == '<' && str[j + 1] == '<')
	{
		(*redir_type)[data->r_tabl] = 3;
		j++;
	}
	else if (str[j] == '<')
		(*redir_type)[data->r_tabl] = 4;
	j++;
	while (str[j] == ' ')
		j++;
	while (str[j])
	{
		quotes_switch(data, str, j);
		//printf("QUOTE D-S -- |%d|%d|\n", data->dquote, data->squote);
		if ((str[j] == ' ' || str[j] == '<' || str[j] == '>') && data->squote == 0 && data->dquote == 0)
			break ;
		if ((str[j] == 33 || str[j] == 35 || str[j] == 42 || str[j] == 40
				|| str[j] == 41 || str[j] == 59 || str[j] == 47 || str[j] == 63
				|| str[j] == 124) && data->squote == 0 && data->dquote == 0)
			return (-2);
		(*redir_file)[data->r_tabl] = ft_strmjoin((*redir_file)[data->r_tabl], str[j]);
		//printf("STR -- ||%s||\n", (*redir_file)[data->r_tabl]);
		j++;
	}
	if (!((*redir_file)[data->r_tabl]))
		return (-2);
	(*redir_file) = rm_quote((*redir_file), data);
	if (str[i] == '<' && str[i + 1] == '<')
		here_doc_fct(data, (*redir_file)[data->r_tabl]);
	data->r_tabl = data->r_tabl + 1;
	while (str[j] == ' ')
		j++;
	return (j - i);
}

int	count_redir(char *str, t_data *data)  //ERREUR >< ET CAS <> <-- A NE PAS GERER
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		quotes_switch(data, str, i);
		if ((str[i] == '>' || str[i] == '<') && data->squote == 0 && data->dquote == 0)
		{
			if (str[i] == '>' && str[i + 1] == '>')
				i++;
			if (str[i] == '<' && str[i + 1] == '<')
				i++;
			if (str[i] == '>' && str[i + 1] == '<')
				return (-1);
			if (str[i] == '<' && str[i + 1] == '>')
				return (-1);
			count++;
			if (str[i + 1] == '>' && str[i + 1] == '<')
				return (-1);
		}
		i++;
	}
	return (count);
}


//TODO
// FONCTION D"ERREUR A MACHINER -- à moitier fait ça mais sa passe crème tkt
// LES SEGFAULTS (à trouver avant de les corriger)


// FAIT | GERER LES NOM DE FICHIER APRES LES REDIR KI COMMENCE PAR UN CHAR SPE EX : |, &, %.....
// FAIT |N'EST PAS AUTORISER : ! # * ( ) ; / ?

//Si $variable non trouvé marche pour heredoc mais pas les autre ?? (ps: oskour)