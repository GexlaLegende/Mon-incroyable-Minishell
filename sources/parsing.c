/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:25:13 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/10 20:57:05 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parsing(char *str, t_data *data) //Fonction principale du parsing (premier découpage)
{
	int	start;
	int	i;
	int error;

	data->squote = 0;
	data->dquote = 0;
	data->r_tabl = 0;
	i = 0;
	start = 0;
	if (str[0] == '|')
		return (1);
	while (str[i])
	{
		quotes_switch(data, str, i);
		if (str[i] == '|' && data->squote == 0 && data->dquote == 0)  //Detection du pipe
		{
			printf("MESSAGE DERREUR\n");
			error = ft_parsing2(&str[start], data, i);
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
	error = ft_parsing2(&str[start], data, i);  //Envoie la derniere commande
	if (error != 0)
		return (error);
	return (0);
}

void	ft_addpipe(t_data *data)							//Fonction pour l'ajout du maillon pipe dans la liste chainée
{
	int		*redir_type;
	char	**redir_file;

	printf("%s\n", "pipe added");			//TODO erreur si || double pipes
	redir_type = (int *)malloc(sizeof(int) * 2);
	redir_file = malloc(sizeof(char *) * 2);
	ft_lstadd_back(&data->cmd_table, ft_lstnew(NULL, redir_type, redir_file));
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

int	ft_parsing2(char *str, t_data *data, int end) //Fonction secondaire (deuxieme découpage)
{
	int		i;
	int		skip;
	char	*command;
	int		*redir_type;
	char	**redir_file;
	int		sizeoftabl;

	i = 0;
	str[end] = '\0';								//Selectionne la commande en coupant au Pipe
	command = NULL;
	sizeoftabl = count_redir(str, data);
	if (sizeoftabl == -1)
		return (3);
	redir_type = (int *)malloc(sizeof(int) * (sizeoftabl + 1));
	redir_file = malloc(sizeof(char *) * (sizeoftabl + 1));
	while (i < sizeoftabl)
	{
		redir_type[i] = 0;
		redir_file[i] = NULL;
		i++;
	}
	i = 0;
	while (str[i])
	{
		quotes_switch(data, str, i);
		if ((str[i] == '>' || str[i] == '<') && data->squote == 0 && data->dquote == 0)  //TODO SIMPLIFIER SKIP EN UTILISANT LADDRESSE DE I
		{
			skip = redir_parsing(str, i, data, &redir_type, &redir_file);
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
	ft_lstadd_back(&data->cmd_table, ft_lstnew(command, redir_type, redir_file));
	return (0);
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
		if ((str[j] == ' ' || str[j] == '<' || str[j] == '<') && data->squote == 0 && data->dquote == 0)
			break ;
		(*redir_file)[data->r_tabl] = ft_strmjoin((*redir_file)[data->r_tabl], str[j]);
		j++;
	}
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
// LA FONCTION ADD PIPE
// FAIRE FONCTIONNER LE PARSING APRES LES PIPES
// METTRE LES LISTES CHAINEES DANS LA BOUCLE READLINE + CLEAR LES ANCIENNES LISTES CHAINEES
// FONCTION D"ERREUR A MACHINER
// LES SEGFAULTS


// GERER LES NOM DE FICHIER APRES LES REDIR KI COMMENCE PAR UN CHAR SPE EX : |, &, %.....