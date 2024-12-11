/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:43:41 by akumari           #+#    #+#             */
/*   Updated: 2024/12/11 14:12:31 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *extract_line(char **temp, int i)
{
    char *line;
    char *temp_new;

    while ((*temp)[i] != '\n' && (*temp)[i] != '\0')
        i++;
    if ((*temp)[i] == '\n')
    {
        line = ft_substr(*temp, 0, i + 1);
        temp_new = *temp;
        *temp = ft_strdup(temp_new + i + 1);
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


static char *read_line(int fd, char *buffer, char *temp)
{
    int     bytes_read;
    char    *temp_new;
    char    *newline_ptr;

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


char *get_next_line(int fd)
{
    static char *temp;
    char        *buffer;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
        return (NULL);
    if (!temp)
        temp = ft_strdup("");
    temp = read_line(fd, buffer, temp);
    free(buffer);
    if (!temp)
        return (NULL);
    line = extract_line(&temp, 0);
    if (!line && temp)
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

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	line = get_next_line(fd);
// 	printf("%s\n", line);
// 	free(line);
// 	close(fd);
// 	return (0);
// }
























































// static char	*extract_next_line(char **temp, int i)
// {
// 	char	*line;
// 	char	*temp_line;

// 	while ((*temp)[i] != '\n' && (*temp)[i] != '\0')
// 		i++;
// 	if ((*temp)[i] == '\n')
// 	{
// 		line = ft_substr(*temp, 0, i + 1);
// 		temp_line = *temp;
// 		*temp = ft_strdup(temp_line + i + 1);
// 		free(temp_line);
// 		if ((*temp)[0] == '\0')
// 			*temp = NULL;
// 		free(*temp);
// 	}
// 	else
// 	{
// 		line = ft_strdup(*temp);
// 		free(*temp);
// 		*temp = NULL;
// 	}
// 	return (line);
// }

// static char	*read_next_line(char *temp, int fd, char *buff)
// {
// 	char	*newline;
// 	int		read_line;
// 	char	*temp_line;

// 	read_line = 1;
// 	temp_line = NULL;
// 	newline = ft_strchr(temp, '\n');
// 	while (newline == NULL && read_line > 0)
// 	{
// 		read_line = read(fd, buff, BUFFER_SIZE);
// 		if (read_line <= 0)
// 			break ;
// 		buff[read_line] = '\0';
// 		temp_line = temp;
// 		temp = ft_strjoin(temp_line, buff, 0, 0);
// 		free(temp_line);
// 		newline = ft_strchr(temp, '\n');
// 	}
// 	if (read_line == -1 || (read_line <= 0 && temp && temp[0] == '\0'))
// 	{
// 		free(temp);
// 		temp = NULL;
// 		return (NULL);
// 	}
// 	return (temp);
// }

// char	*get_next_line(int fd)
// {
// 	char		*buff;
// 	static char	*temp = NULL;
// 	char		*line;
// 	int			i;

// 	i = 0;
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	buff = (char *)malloc(BUFFER_SIZE + 1);
// 	if (!buff)
// 		return (NULL);
// 	if (!temp)
// 		temp = ft_strdup("");
// 	temp = read_next_line(temp, fd, buff);
// 	free(buff);
// 	if (!temp)
// 		return (NULL);
// 	line = extract_next_line(&temp, i);
// 	if (!line)
// 	{
// 		free(temp);
// 		temp = NULL;
// 	}
// 	return (line);
// }






















































// static char	*error_check(char *str)
// {
// 	if (str == NULL)
// 	{
// 		return (NULL);
// 	}
// 	return (str);
// }

// static char	*extract_next_line(char **temp, int i)
// {
// 	char	*line;
// 	char	*temp_line;

// 	while ((*temp)[i] != '\n' && (*temp)[i] != '\0')
// 		i++;
// 	if ((*temp)[i] == '\n')
// 	{
// 		line = ft_substr(*temp, 0, i + 1);
// 		//error_check(line);
// 		temp_line = *temp;
// 		*temp = ft_strdup(temp_line + i + 1);
// 		// if (*temp == NULL)
// 		// 	return (NULL);
// 		free(temp_line);
// 		if ((*temp)[0] == '\0')
// 			*temp = NULL;
// 		free(*temp);
// 	}
// 	else
// 	{
// 		line = ft_strdup(*temp);
// 		free(*temp);
// 		*temp = NULL;
// 	}
// 	return (line);
// }

// static char	*read_next_line(char *temp, int fd, char *buff)
// {
// 	char	*newline;
// 	int		read_line;
// 	char	*temp_line;

// 	read_line = 1;
// 	temp_line = NULL;
// 	newline = ft_strchr(temp, '\n');
// 	while (newline == NULL && read_line > 0)
// 	{
// 		read_line = read(fd, buff, BUFFER_SIZE);
// 		if (read_line <= 0)
// 			break ;
// 		buff[read_line] = '\0';
// 		temp_line = temp;
// 		temp = ft_strjoin(temp_line, buff, 0, 0);
// 		// if (!temp)
// 		// 	break ;
// 		free(temp_line);
// 		newline = ft_strchr(temp, '\n');
// 	}
// 	if (read_line == -1 || (read_line <= 0 && temp && temp[0] == '\0')) 
// 	{
// 		free(buff);
// 		free(temp);
// 		return (NULL);
// 	}
// 	return (temp);
// }

// char	*get_next_line(int fd)
// {
// 	char		*buff;
// 	static char	*temp = NULL;
// 	char		*line;
// 	int			i;

// 	i = 0;
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	buff = (char *)malloc(BUFFER_SIZE + 1);
// 	if (!buff)
// 		return (NULL);
// 	if (!temp)
// 		temp = ft_strdup("");
// 	//error_check(temp);
// 	temp = read_next_line(temp, fd, buff);
// 	free(buff);
// 	if (!temp)
// 		return (NULL);
// 	line = extract_next_line(&temp, i);
// 	if (!line)
// 	{
// 		free(temp);
// 		temp = NULL;
// 	}
// 	return (line);
// }

