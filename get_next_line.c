/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traomeli <traomeli@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:11:14 by traomeli          #+#    #+#             */
/*   Updated: 2026/03/04 00:52:14 by traomeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *readed, char *rest, char substitute)
{
	int		count;
	char	*buffer;

	if (rest[0] != '\0')
	{
		readed = ft_strjoin(readed, rest);
		rest[0] = '\0';
	}
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	count = 1;
	while (count != 0 && !ft_strchr(readed, substitute))
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free(readed);
			return (NULL);
		}
		buffer[count] = '\0';
		readed = ft_strjoin(readed, buffer);
	}
	free(buffer);
	return (readed);
}

static char	*clean_line(char *readed, char substitute)
{
	int			i;
	int			j;
	char		*result;

	i = 0;
	if (!readed)
		return (NULL);
	while (readed[i] != '\0' && readed[i] != substitute)
		i++;
	result = (char *)malloc(sizeof(char) * (i + 2));
	if (!result)
		return (NULL);
	j = 0;
	while (readed[j] != '\0' && readed[j] != substitute)
	{
		result[j] = readed[j];
		j++;
	}
	if (readed[j] == substitute)
	{
		result[j] = substitute;
		j++;
	}
	result[j] = '\0';
	return (result);
}

static void	get_left(char *readed, char *rest, char substitute)
{
	int		i;
	int		j;

	i = 0;
	while (readed[i] && readed[i] != substitute)
		i++;
	if (!readed[i])
	{
		free(readed);
		return ;
	}
	i++;
	j = 0;
	while (readed[i])
		rest[j++] = readed[i++];
	rest[j] = '\0';
	free(readed);
}

char	*get_next_line(int fd)
{
	char		*readed;
	char		*result;
	char		substitute;
	static char	rest[BUFFER_SIZE + 1];

	substitute = '\n';
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	readed = NULL;
	readed = read_line(fd, readed, rest, substitute);
	if (!readed || readed[0] == '\0')
	{
		free(readed);
		return (NULL);
	}
	result = clean_line(readed, substitute);
	get_left(readed, rest, substitute);
	return (result);
}
