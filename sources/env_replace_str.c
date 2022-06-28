/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:05:39 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/28 16:40:00 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/minishell.h>

/*	Search and replace environment variables by their value in str of here_doc*/
char	*ft_search_and_change_env_var(t_data *data, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) == 1 \
			|| str[i + 1] == '_') && data->squote == 0)
		{
			str = ft_change_var_env(str, i, data);
			if (i > 0)
				i--;
		}
		i++;
	}
	return (str);
}

/*	Replace environment variables by their value in str of here_doc */
char	*ft_change_var_env(char *str, int pos, t_data *data)
{
	int		len;
	int		i;
	char	*value;

	len = 0;
	i = pos;
	if (str[pos + 1] == '0')
		str = ft_replace_word(str, pos, 2, "minishell");
	else
	{
		while (ft_isalnum(str[i + 1]) == 1 \
			|| str[i + 1] == '_')
		{
			len++;
			i++;
		}
		value = ft_is_var_env(data, str, pos, len);
		str = ft_replace_word(str, pos, len + 1, value);
	}
	return (str);
}
