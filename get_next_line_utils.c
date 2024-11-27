/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:39:49 by akumari           #+#    #+#             */
/*   Updated: 2024/11/27 12:29:31 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Write a function that returns a line read from a
file descriptor*/
#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	new_str = NULL;
	if (new_str)
		return (new_str);
	new_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*cpy_str;
	size_t	i;

	cpy_str = (char *)malloc(ft_strlen(src) + 1);
	if (cpy_str == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		cpy_str[i] = src[i];
		i++;
	}
	cpy_str[i] = '\0';
	return (cpy_str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*new_str;
	unsigned int	s_len;
	size_t			substr_len;
	size_t			i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len < s_len - start)
		substr_len = len;
	else
		substr_len = s_len - start;
	new_str = (char *)malloc(substr_len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < substr_len)
	{
		new_str[i] = s[i + start];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
