/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:49:00 by apercebo          #+#    #+#             */
/*   Updated: 2022/06/26 11:43:22 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isalnum(int c)
{
	if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) \
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	else
	{
		while (i < ft_strlen(src) && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s1)
{
	char	*result;

	result = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, sizeof(char) * (ft_strlen(s1) + 1));
	return (result);
}

char	*ft_replace_word(char *str, int start, int len, char *word)
{
	char	*result;
	int		newlen;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	newlen = ft_strlen(str) - len + ft_strlen(word);
	result = malloc(sizeof(char) * (newlen + 1));
	while (str[k])
	{
		if (k == start)
		{
			while (word[j])
				result[i++] = word[j++];
			k = start + len;
		}
		if (str[k] != '\0')
			result[i++] = str[k++];
	}
	result[i] = '\0';
	free(str);
	return (result);
}

int	ft_strncmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
