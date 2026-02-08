/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumagni <gumagni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:17:37 by gumagni           #+#    #+#             */
/*   Updated: 2026/02/08 15:35:51 by gumagni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_until_newline(int fd, char *line)
{
	char	*buffer;
	char	*tmp;
	int		bytes;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (free(line), NULL);
	while (!ft_strchr(line, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buffer[bytes] = '\0';
		tmp = line;
		line = ft_strjoin(line, buffer);
		if (!line)
			return (free(tmp), free(buffer), NULL);
		free(tmp);
	}
	free(buffer);
	return (line);
}

static void	extract_line(char *line, char **rest)
{
	char	*newline_pos;

	newline_pos = ft_strchr(line, '\n');
	if (newline_pos)
	{
		*rest = ft_strdup(newline_pos + 1);
		line[newline_pos - line + 1] = '\0';
	}
	else
		*rest = NULL;
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (rest)
		line = ft_strdup(rest);
	else
		line = ft_strdup("");
	if (rest)
		free(rest);
	rest = NULL;
	line = read_until_newline(fd, line);
	if (!line || !*line)
		return (free(line), NULL);
	extract_line(line, &rest);
	return (line);
}

/*int main(void)
{
	int	fd;
	char *line;

	fd = open("ciao.txt", O_RDONLY);
	if (fd < 0)
		printf("error");
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	printf("\n");
	close(fd);
	return(0);
}
*/