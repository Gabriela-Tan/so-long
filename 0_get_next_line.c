/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_get_next_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:14:08 by gabriela          #+#    #+#             */
/*   Updated: 2023/06/27 14:40:01 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free(char **memory)
{
	free(*memory);
	*memory = NULL;
}

char	*ft_reading(char **s, size_t rd)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	if (rd != 0)
		return (ft_extract(&*s));
	if (*s == 0)
		ft_free(&*s);
	else
	{
		if (ft_strchr(*s, '\n') == NULL)
		{
			if (*s[i] != 0)
			{
				line = ft_strdup(*s);
				ft_free(&*s);
				return (line);
			}
			else
				ft_free(&*s);
		}
	}
	return (NULL);
}

char	*ft_strnjoin(char *s1, char *s2, size_t rd)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 != NULL)
		rd = ft_strlen(s1);
	str = (char *)malloc((rd + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	if (s1)
		ft_free(&s1);
	return (str);
}

char	*ft_extract(char **s)
{
	int		i;
	char	*line;
	char	*rd;

	i = 0;
	while (((*s)[i] != '\n') && ((*s)[i]) != '\0')
		i++;
	line = ft_substr(*s, 0, i + 1);
	if (ft_strlen(line) == 0)
	{
		ft_free(&*s);
		return (NULL);
	}
	rd = ft_substr(*s, i + 1, ft_strlen(*s));
	ft_free(&*s);
	*s = ft_strdup(rd);
	free(rd);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buf;
	int		rd;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	rd = 1;
	while (rd > 0 && ft_strchr(line, '\n') == NULL)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == 0 || rd == -1)
			break ;
		buf[rd] = 0;
		line = ft_strnjoin(line, buf, rd);
	}
	free(buf);
	if (rd == -1)
		return (NULL);
	return (ft_reading(&line, rd));
}