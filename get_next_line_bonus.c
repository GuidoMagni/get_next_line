/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumagni <gumagni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:17:37 by gumagni           #+#    #+#             */
/*   Updated: 2026/02/02 18:22:17 by gumagni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>
#ifndef OPEN_MAX
# define OPEN_MAX 1024
#endif

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
	static char	*rest[OPEN_MAX];
	off_t		off;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	off = lseek(fd, 0, SEEK_CUR);
	if (off == 0 && rest[fd])
	{
		free(rest[fd]);
		rest[fd] = NULL;
	}
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

/*int main(void)
{
	int		fd;
	char	*line;
	int		line_count;

	// Test 1: Read from a regular file
	printf("=== Test 1: Reading from a regular file ===\n");
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}

	line_count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: %s", line_count + 1, line);
		free(line);
		line_count++;
	}
	printf("\nTotal lines read: %d\n\n", line_count);
	close(fd);

	// Test 2: Read from the same file again (fd should start fresh)
	printf("=== Test 2: Reading the same file again ===\n");
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}

	line = get_next_line(fd);
	if (line)
	{
		printf("First line: %s", line);
		free(line);
	}
	close(fd);

	// Test 3: Multiple file descriptors
	printf("\n=== Test 3: Multiple file descriptors ===\n");
	int fd1 = open("test.txt", O_RDONLY);
	int fd2 = open("test.txt", O_RDONLY);

	if (fd1 < 0 || fd2 < 0)
	{
		perror("open");
		return (1);
	}

	char *line1 = get_next_line(fd1);
	char *line2 = get_next_line(fd2);

	printf("FD1 first line: %s", line1);
	printf("FD2 first line: %s", line2);

	if (line1)
		free(line1);
	if (line2)
		free(line2);

	close(fd1);
	close(fd2);

	// Test 4: Test with a file containing empty lines
	printf("\n=== Test 4: File with empty lines ===\n");
	fd = open("empty.txt", O_RDONLY);
	if (fd >= 0)
	{
		line_count = 0;
		while ((line = get_next_line(fd)) != NULL)
		{
			printf("Line %d: [%s]", line_count + 1, line);
			free(line);
			line_count++;
		}
		close(fd);
	}
	else
		printf("Could not open empty_lines.txt (optional test)\n");

	// Test 5: Invalid file descriptor
	printf("\n=== Test 5: Invalid file descriptor ===\n");
	line = get_next_line(-1);
	if (line == NULL)
		printf("Correctly returned NULL for invalid fd\n");

	printf("\n=== All tests completed ===\n");
	return (0);
}
*/