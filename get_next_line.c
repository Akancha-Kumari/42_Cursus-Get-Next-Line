/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:43:41 by akumari           #+#    #+#             */
/*   Updated: 2024/11/26 14:55:30 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *error_check_next_line(int fd, char **buff)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	*buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!*buff)
		return (NULL);
	return(*buff);
}
char	*free_line(int read_line, char **temp, char **line)
{
	if (read_line == -1 || (*temp == NULL && read_line == 0))
	{
		free(*temp);
		*temp = NULL;
		return (NULL);
	}
	if (*temp == NULL && **temp)
	{
		*line = *temp;
		*temp = NULL;
		return (*line);
	}
	free(*temp);
	*temp = NULL;
	return (NULL);
}

char *get_line(char **temp, char **buff)
{
	char		*newline;
	char *temp_new;
	char *line;
	
	temp_new = *temp;
	newline = ft_strchr(temp_new, '\n');
	if(newline != NULL)
	{
		*newline = '\0';
		line = ft_strdup(temp_new);
		*temp = ft_strdup(newline + 1);
	}
	else
	{
		line = ft_strdup(temp_new);
		free(*temp);
		*temp = NULL;
	}
	free(*buff);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*temp = NULL;
	int			read_line;
	char		*line;

	buff = error_check_next_line(fd, &buff);
	while (1)
	{
		read_line = read(fd, buff, BUFFER_SIZE);
		if(read_line == -1)
			return (NULL);
		buff[read_line] = '\0';
		if (!temp)
			temp = ft_strdup("");
		temp = ft_strjoin(temp, buff);
		if (ft_strchr(temp, '\n'))
		{
			line = get_line(&temp, &buff);
			return (line);
		}
	}
	free(buff);
	return (free_line(read_line, &temp, &line));
}

int	main(void)
{
	int		fd;
	char	*line;
	char	*line1;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	line1 = get_next_line(fd);
	printf("%s\n", line);
	printf("%s\n", line1);
	free(line);
	free(line1);
	close(fd);
	return (0);
}

