/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 09:37:41 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/26 11:54:333 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**rm_quote(char **tabl, t_data *data)
{
	char	*str;

	data->i = 0;
	data->j = 0;
	str = NULL;
	data->dquote = 0;
	data->squote = 0;
	while (tabl[data->j])
	{
		data->i = 0;
		str = malloc(sizeof(char) * (ft_strlen(tabl[data->j]) + 1));
		str[ft_strlen(tabl[data->j])] = '\0';
		data->x = 0;
		data->nbr = 0;
		while (tabl[data->j][data->i])
			str = rm_quote2(data, tabl, str);
		str[ft_strlen(tabl[data->j]) - data->nbr] = '\0';
		free(tabl[data->j]);
		tabl[data->j] = str;
		data->j = data->j + 1;
	}
	return (tabl);
}

char	*rm_quote2(t_data *data, char **tabl, char *str)
{
	quotes_switch(data, tabl[data->j], data->i);
	if (tabl[data->j][data->i] == '"' && data->squote == 0)
		data->nbr++;
	else if (tabl[data->j][data->i] == '\'' && data->dquote == 0)
		data->nbr++;
	else
	{
		str[data->x] = tabl[data->j][data->i];
		data->x = data->x + 1;
	}
	data->i = data->i + 1;
	return (str);
}

int	ft_is_builtin(const char *s1)
{
	size_t	i;
	

	i = 0;
	if (ft_strncmp(s1, "pwd") == 0)
		return (0);
	if (ft_strncmp(s1, "env") == 0)
		return (0);
	if (ft_strncmp(s1, "cd") == 0)
		return (0);
	if (ft_strncmp(s1, "echo") == 0)
		return (0);
	if (ft_strncmp(s1, "export") == 0)
		return (0);
	if (ft_strncmp(s1, "unset") == 0)
		return (0);
	if (ft_strncmp(s1, "exit") == 0)
		return (0);
	return (1);
}
