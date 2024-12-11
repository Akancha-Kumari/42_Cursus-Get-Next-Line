/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:43:41 by akumari           #+#    #+#             */
/*   Updated: 2024/12/11 15:52:31 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_error(char *str)
{
	if (str == NULL)
		return (NULL);
    return (str);
}

/*
This function extracts a single line from the temp buffer.

Parameters:
temp: Pointer to the static buffer holding the file content.
i: Index used to locate the newline character (\n).
line: The extracted line.
temp_new: Temporary pointer for buffer manipulation.

Logic:
Iterates through temp to find the newline character (\n) or the end of the string (\0).
If a newline character is found:
    Extracts the line from the start of temp to the newline (including the newline) using ft_substr.
    Updates temp to contain the remaining content after the newline using ft_strdup.
    Handles memory cleanup for the old temp and ensures no dangling pointer exists.
If no newline character is found:
    Copies the entire temp into line using ft_strdup.
    Frees temp and sets it to NULL (indicating all content has been read).
Returns the extracted line.
*/

static char	*extract_line(char **temp, int i, char *line, char *temp_new)
{
	while ((*temp)[i] != '\n' && (*temp)[i] != '\0')
		i++;
	if ((*temp)[i] == '\n')
	{
		line = ft_substr(*temp, 0, i + 1);
		ft_error(line);
		temp_new = *temp;
		*temp = ft_strdup(temp_new + i + 1);
        if (!*temp)
			return (free(temp_new), free(line), NULL);
		free(temp_new);
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

/*
Reads data from the file descriptor (fd) into the temp buffer until a newline is found or the end of the file is reached.

Parameters:
fd: File descriptor for reading.
buffer: Temporary buffer to read file content in chunks.
temp: Static buffer holding accumulated content.

Logic:
Uses a loop to repeatedly read from fd into buffer with a size defined by BUFFER_SIZE.
If data is successfully read (bytes_read > 0):
    Appends the content of buffer to temp using ft_strjoin.
    Updates newline_ptr to check if the newly read content contains a newline character.
Handles errors:
    If bytes_read == -1, an error occurred; frees temp and returns NULL.
    If bytes_read == 0 and temp is empty, it indicates the end of the file; frees temp.
Returns the updated temp containing the accumulated data.
*/

static char	*read_line(int fd, char *buffer, char *temp)
{
	int		bytes_read;
	char	*temp_new;
	char	*newline_ptr;

	bytes_read = 1;
	newline_ptr = ft_strchr(temp, '\n');
	while (newline_ptr == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp_new = temp;
		temp = ft_strjoin(temp, buffer);
		if (!temp)
			return (free(temp_new), NULL);
		free(temp_new);
		newline_ptr = ft_strchr(temp, '\n');
	}
	if (bytes_read == -1 || (bytes_read == 0 && temp && temp[0] == '\0'))
		return (free(temp), NULL);
	return (temp);
}

/*
The main function that orchestrates reading a single line from a file descriptor.
Logic:
Validates the file descriptor and BUFFER_SIZE. Returns NULL if invalid.
Allocates memory for the buffer used for reading.
Initializes the temp buffer if it's the first call (temp == NULL).
Calls read_line to populate temp with file content.
Calls extract_line to extract the next line from temp.
Frees resources and handles errors appropriately.
Returns the extracted line.
*/

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);       
	if (!temp)
	{
		temp = ft_strdup("");
		ft_error(temp);  
	}
	temp = read_line(fd, buffer, temp);
	free(buffer);
	if (!temp)
		return (NULL);
	line = extract_line(&temp, 0, NULL, NULL);
	if (!line && temp)
	{
		free(temp); 
		temp = NULL;
	}
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while((line = get_next_line(fd)) != NULL)
    {
        	printf("%s\n", line);
	        free(line); 
    }
	close(fd);
	return (0);
}
