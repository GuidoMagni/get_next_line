/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumagni <gumagni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:01:08 by gumagni           #+#    #+#             */
/*   Updated: 2026/01/21 16:33:29 by gumagni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*final;
	size_t	i;
	size_t	len_tot;

	i = 0;
	len_tot = ft_strlen(s1) + ft_strlen(s2);
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	final = (char *)malloc(sizeof(char) * (len_tot + 1));
	if (final == NULL)
		return (NULL);
	while (s1[i])
	{
		final[i] = s1[i];
		i++;
	}
	len_tot = i;
	i = 0;
	while (s2[i])
	{
		final[len_tot + i] = s2[i];
		i++;
	}
	final[len_tot + i] = '\0';
	return (final);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_strdup(char *src)
{
	char	*dup;
	int		i;

	if (src == NULL)
		return (NULL);
	dup = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
