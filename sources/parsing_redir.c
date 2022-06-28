/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:18:34 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/28 21:35:31 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	here_doc_fct(t_data *data, char *str)
{
	char	*file;
	int		fd;
	char	*str2;

	str2 = NULL;
	file = ft_strjoin_c("/tmp/.here_doc", (char)(data->here_doc_nbr + 97));
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(file);
	while (1)
	{
		str2 = readline("> ");
		//if (data->is_quote == 0)
		str2 = ft_search_and_change_env_var(data, str2);
		if (str_diff(str, str2) == 0)
			break ;
		write(fd, str2, ft_strlen(str2));
		write(fd, "\n", 1);
		free(str2);
	}
	free(str2);
}

int	redir_parsing2(t_data *data, char *str)
{
	data->rdj = data->rdi;
	if (str[data->rdj] == '>' && str[data->rdj + 1] == '>')
	{
		data->redir_type[data->r_tabl] = 1;
		data->rdj++;
	}
	else if (str[data->rdj] == '>')
		data->redir_type[data->r_tabl] = 2;
	else if (str[data->rdj] == '<' && str[data->rdj + 1] == '<')
	{
		data->redir_type[data->r_tabl] = 3;
		data->rdj++;
	}
	else if (str[data->rdj] == '<')
		data->redir_type[data->r_tabl] = 4;
	data->rdj++;
	while (str[data->rdj] == ' ')
		data->rdj++;
	return (0);
}

int	ft_is_chr(char c, t_data *data)
{
	if ((c == 33 || c == 35 || c == 42 || c == 40 || c == 41
			|| c == 59 || c == 47 || c == 63 || c == 124)
		&& data->squote == 0 && data->dquote == 0)
		return (1);
	return (0);
}

int	redir_parsing(char *str, t_data *data)
{
	data->rd_error = redir_parsing2(data, str);
	if (data->rd_error != 0)
		return (data->rd_error);
	while (str[data->rdj])
	{
		quotes_switch(data, str, data->rdj);
		if ((str[data->rdj] == ' ' || str[data->rdj] == '<' || str[data->rdj]
				== '>') && data->squote == 0 && data->dquote == 0)
			break ;
		if (ft_is_chr(str[data->rdj], data) == 1)
			return (-2);
		data->redir_file[data->r_tabl]
			= ft_strmjoin(data->redir_file[data->r_tabl], str[data->rdj]);
		data->rdj++;
	}
	if (!(data->redir_file[data->r_tabl]))
		return (-2);
	data->redir_file = rm_quote(data->redir_file, data);
	if (str[data->rdi] == '<' && str[data->rdi + 1] == '<')
		here_doc_fct(data, data->redir_file[data->r_tabl]);
	data->r_tabl = data->r_tabl + 1;
	while (str[data->rdj] == ' ')
		data->rdj++;
	return (data->rdj - data->rdi);
}

//ERREUR >< ET CAS <> <-- A NE PAS GERERreturn (2)
int	count_redir(char *str, t_data *data)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		quotes_switch(data, str, i);
		if ((str[i] == '>' || str[i] == '<') && data->squote == 0
			&& data->dquote == 0)
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
	}
	return (count);
}
