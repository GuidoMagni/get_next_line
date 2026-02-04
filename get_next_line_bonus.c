/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumagni <gumagni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:17:37 by gumagni           #+#    #+#             */
/*   Updated: 2026/02/04 18:14:26 by gumagni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*rest[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (rest[fd])
		line = ft_strdup(rest[fd]);
	else
		line = ft_strdup("");
	if (rest[fd])
		free(rest[fd]);
	rest[fd] = NULL;
	line = read_until_newline(fd, line);
	if (!line || !*line)
		return (free(line), NULL);
	extract_line(line, &rest[fd]);
	return (line);
}

/*int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line;
	int		done1;
	int		done2;

	fd1 = open("ciao.txt", O_RDONLY);
	fd2 = open("ciao1.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
	{
		perror("open");
		return (1);
	}

	done1 = 0;
	done2 = 0;
	while ((line = get_next_line(fd1)))
	{
		printf("[fd1] %s", line);
		free(line);
	}
	printf("\n");
	while ((line = get_next_line(fd2)))
	{
		printf("[fd2] %s", line);
		free(line);
	}
	printf("\n");
	close(fd1);
	close(fd2);
	return (0);
}
*/