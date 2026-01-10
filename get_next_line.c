/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumagni <gumagni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:17:37 by gumagni           #+#    #+#             */
/*   Updated: 2026/01/10 19:49:51 by gumagni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*char *_fill_line_buffer(int fd, char *left_c, char *buffer)
{
	while (fd)
	{
		read(fd, buffer, sizeof(buffer));
		return buffer;
	}
	return buffer;
}*/

char	*get_next_line(int fd)
{
	char	*polpetta;
	char	*polpetta2;
	static char	*left_c;
	int bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!left_c)
		left_c = ft_strdup("");
	polpetta = ft_strdup(left_c);
	free (left_c);
	left_c = NULL;
	polpetta2 = malloc(sizeof(char) * BUFFER_SIZE +1);
	if (!polpetta2)
		return (NULL);
	while (!ft_strchr(polpetta, '\n'))
	{
		bytes = read(fd, polpetta2, BUFFER_SIZE);
		if (bytes <= 0)
			break;
		polpetta2[bytes] = '\0';
		polpetta = ft_strjoin(polpetta, polpetta2);
	}
	free (polpetta2);
	if (!*polpetta)
	{
		free (polpetta);
		return (NULL);
	}
	if (ft_strchr(polpetta, '\n'))
	{
		left_c = ft_strdup(ft_strchr(polpetta, '\n') + 1);
		polpetta[ft_strlen(polpetta) - ft_strlen(left_c) - 1] = '\0';
	}
	return polpetta;
}

int	main()
{
	int	fd;

	fd = open("ciao.txt", O_RDONLY);
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
}

/*int main(void) {
	int fd = open("ciao.txt", O_RDONLY);
	if (fd == -1) {
		printf("Error opening file\n");
		return 1;
	}
	char buffer[10];
	int bytes;
	while ((bytes = read(fd, buffer, sizeof(buffer))) > 0)
	{
		write(1, buffer, bytes);
		printf("\n%d bytes read\n", bytes);
	}
	close(fd);
	return 0;
}*/