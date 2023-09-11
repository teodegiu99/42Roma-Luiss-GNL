/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-gius <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:02:18 by mde-gius          #+#    #+#             */
/*   Updated: 2021/02/02 12:02:33 by mde-gius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_isn(char *s)
{
	int			i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		ret_line(char **s, char **line, int i)
{
	char		*tmp_ptr;

	*line = ft_substr(*s, 0, i);
	tmp_ptr = ft_strdup(&(*s)[i + 1]);
	free(*s);
	*s = tmp_ptr;
	return (1);
}

int		ret_rest(char **s, char **line)
{
	int			i;

	if (*s == 0)
	{
		*line = ft_strdup("");
		return (0);
	}
	if (*s && (i = ft_isn(*s)) >= 0)
		return (ret_line(s, line, i));
	else if (*s[0] != '\0')
	{
		*line = ft_strdup(*s);
		free(*s);
		*s = 0;
		return (0);
	}
	*line = ft_strdup("");
	free(*s);
	*s = 0;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int			i;
	ssize_t		rd_size;
	char		buff[BUFFER_SIZE + 1];
	static char	*s[OPEN_MAX];

	if ((fd < 0) || !line || (BUFFER_SIZE <= 0))
		return (-1);
	while ((rd_size = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[rd_size] = '\0';
		s[fd] = gnl_strjoin(s[fd], buff);
		i = ft_isn(s[fd]);
		if (i >= 0)
			return (ret_line(&s[fd], line, i));
	}
	if (rd_size < 0)
		return (-1);
	return (ret_rest(&s[fd], line));
}
