/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:26:23 by akumari           #+#    #+#             */
/*   Updated: 2024/12/12 15:22:09 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line_and_update(char **stat_var_ptr, char *line, int i)
{
	char	*stat_var;
	char	*temp;

	stat_var = *stat_var_ptr;
	while (stat_var[i] != '\n' && stat_var[i] != '\0')
		i++;
	if (stat_var[i] == '\n')
	{
		line = ft_substr(stat_var, 0, i + 1);
		if (!line)
			return (free(stat_var), NULL);
		temp = ft_strdup(stat_var + i + 1);
		if (!temp)
			return (free(line), NULL);
		free(stat_var);
		*stat_var_ptr = temp;
	}
	else
	{
		line = ft_strdup(stat_var);
		free(stat_var);
		*stat_var_ptr = NULL;
	}
	return (line);
}

char	*read_and_concat(int fd, char *buffer, char *stat_var)
{
	int		read_line;
	char	*new;

	read_line = 1;
	while (read_line > 0)
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		if (read_line <= 0)
			break ;
		buffer[read_line] = '\0';
		new = stat_var;
		stat_var = ft_strjoin(new, buffer);
		if (!stat_var)
			return (free(new), NULL);
		free(new);
		if (ft_strchr(stat_var, '\n'))
			break ;
	}
	if (read_line == -1 || (read_line == 0 && stat_var && stat_var[0] == '\0'))
		return (free(stat_var), NULL);
	return (stat_var);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stat_var;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (!stat_var)
	{
		stat_var = ft_strdup("");
		if (!stat_var)
			return (free(buffer), NULL);
	}
	stat_var = read_and_concat(fd, buffer, stat_var);
	free(buffer);
	if (!stat_var || stat_var[0] == '\0')
		return (free(stat_var), stat_var = NULL, NULL);
	line = extract_line_and_update(&stat_var, NULL, 0);
	if (!line && stat_var)
		return (free(stat_var), stat_var = NULL, NULL);
	return (line);
}
