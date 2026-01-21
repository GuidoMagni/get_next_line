/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guido <guido@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:17:37 by gumagni           #+#    #+#             */
/*   Updated: 2026/01/14 17:40:06 by guido            ###   ########.fr       */
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
	char		*s;
	char		*s1;
	static char	*left_c;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!left_c)
		left_c = ft_strdup("");
	s = ft_strdup(left_c);
	free (left_c);
	left_c = NULL;
	s1 = malloc(sizeof(char) * BUFFER_SIZE +1);
	if (!s1)
		return (NULL);
	while (!ft_strchr(s, '\n'))
	{
		bytes = read(fd, s1, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		s1[bytes] = '\0';
		s = ft_strjoin(s, s1);
	}
	free (s1);
	if (!*s)
	{
		free (s);
		return (NULL);
	}
	if (ft_strchr(s, '\n'))
	{
		left_c = ft_strdup(ft_strchr(s, '\n') + 1);
		s[ft_strlen(s) - ft_strlen(left_c) - 1] = '\0';
	}
	return (s);
}

int	main(void)
{
	int	fd;

	fd = open("ciao.txt", O_RDONLY);
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	close(fd);
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