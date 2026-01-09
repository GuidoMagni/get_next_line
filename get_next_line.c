/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumagni <gumagni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:17:37 by gumagni           #+#    #+#             */
/*   Updated: 2026/01/09 12:57:27 by gumagni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/*char	*get_next_line(int fd)
{
	int	buffersize = 10;

	fd = open("ciao.txt", O_WRONLY)
	
}

*/

int main(void) {
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
}