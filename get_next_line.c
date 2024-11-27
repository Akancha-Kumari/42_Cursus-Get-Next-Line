/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:43:41 by akumari           #+#    #+#             */
/*   Updated: 2024/11/27 13:02:26 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_next_line(char **temp, int i)
{
	char	*line;
	char	*temp_line;

	while ((*temp)[i] != '\n' && (*temp)[i] != '\0')
		i++;
	if ((*temp)[i] == '\n')
	{
		line = ft_substr(*temp, 0, i + 1);
		temp_line = *temp;
		*temp = ft_strdup(temp_line + i + 1);
		free(temp_line);
		if ((*temp)[0] == '\0')
		{
			free(*temp);
			*temp = NULL;
		}
	}
	else
	{
		line = ft_strdup(*temp);
		free(*temp);
		*temp = NULL;
	}
	return (line);
}

static char	*read_next_line(char *temp, int fd, char *buff)
{
	char	*newline;
	int		read_line;
	char	*temp_line;

	read_line = 1;
	temp_line = NULL;
	newline = ft_strchr(temp, '\n');
	while (newline == NULL && read_line > 0)
	{
		read_line = read(fd, buff, BUFFER_SIZE);
		if (read_line <= 0)
			break ;
		buff[read_line] = '\0';
		temp_line = temp;
		temp = ft_strjoin(temp_line, buff);
		free(temp_line);
		newline = ft_strchr(temp, '\n');
	}
	if (read_line == -1 || (read_line <= 0 && temp && temp[0] == '\0'))
	{
		free(temp);
		temp = NULL;
		return (NULL);
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*temp = NULL;
	char		*line;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (!temp)
		temp = ft_strdup("");
	temp = read_next_line(temp, fd, buff);
	free(buff);
	if (!temp)
		return (NULL);
	line = extract_next_line(&temp, i);
	if (!line)
	{
		free(temp);
		temp = NULL;
	}
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	char	*line1;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	line = get_next_line(fd);
// 	line1 = get_next_line(fd);
// 	printf("%s\n", line);
// 	printf("%s\n", line1);
// 	free(line);
// 	free(line1);
// 	close(fd);
// 	return (0);
// }


/*
This code is a function get_next_line which reads a single line from a file descriptor. It's often used in C programming to handle reading files one line at a time, which is very handy for file parsing. Let's break it down into smaller parts:

Function: get_next_line
This is the main function to get the next line from the file descriptor:
Initial checks: It checks if fd is valid and if the buffer size is positive.
Allocate buffer: It allocates memory for the buffer to read from the file.
Initialize temp: If temp is NULL, it initializes it to an empty string.
Read from file: It calls read_next_line to read the next line from the file into temp.
Extract line: It calls extract_next_line to get the next line from temp.
Return line: It returns the extracted line.

Function: read_next_line
This function reads from the file descriptor (fd) into a buffer (buff) until a newline is found or the end of the file is reached:
Initializations: It initializes read_line to 1, sets temp_line to NULL, and searches for a newline in temp.
Loop to read: If no newline is found, it reads from the file descriptor into buff using read(). It continues reading until it finds a newline or reaches the end of the file.
Handle errors: If reading returns -1 (error) or the end of the file and temp is empty, it frees temp and returns NULL.

Function: extract_next_line
This function extracts the next line from a temporary buffer (temp):
Loop through temp: The function goes through the buffer character by character until it finds a newline character (\n) or the end of the string (\0).
If newline found: It creates a substring of temp up to and including the newline character, assigns it to line, and then adjusts temp to start from the next character after the newline. It also frees the old temp memory.
If end of string: It duplicates the entire temp into line, then frees and nullifies temp.
*/