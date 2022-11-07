/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:25:26 by mtravez           #+#    #+#             */
/*   Updated: 2022/11/07 17:19:18 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h> 
#include <stdio.h>

static int	has_new_line(char *file)
{
	int	i;

	i = 0;
	while (file && file[i])
	{
		if (file[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static void	*free_null(char	**file)
{
	free(*file);
	*file = NULL;
	return (NULL);
}

static char	*get_line(char *file, char **newfile)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	if (has_new_line(file))
	{
		while (file && file[i] && file[i] != '\n')
			i++;
		temp = ft_substr(file, 0, 1 + i++);
		if (i == (int)ft_strlen(file))
		{
			free(temp);
			temp = ft_substr(file, 0, ft_strlen(file));
			free_null(newfile);
			return (temp);
		}
		ft_memmove(file, &file[i], ft_strlen(file) - i);
		i = ft_strlen(&file[i]);
		while (file[i])
			file[i++] = '\0';
	}
	else if (file && ft_strlen(file) > 0)
		temp = ft_substr(file, 0, ft_strlen(file));
	return (temp);
}

static char	*loop_read(char **file, int fd)
{
	char	*line;
	int		size;
	char	*temp;

	line = NULL;
	temp = *file;
	while (temp && !has_new_line(temp))
	{
		line = ft_strjoin(line, get_line(temp, &temp));
		size = read(fd, temp, BUFFER_SIZE);
		if (size <= 0)
		{
			free_null(file);
			return (line);
		}
		temp[size] = '\0';
	}
	*file = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*file = NULL;
	int			size;
	char		*line;

	if (file == NULL)
	{
		file = malloc(BUFFER_SIZE + 1);
		if (!file)
			return (NULL);
		size = read(fd, file, BUFFER_SIZE);
		file[size] = 0;
		if (size <= 0)
			return (free_null(&file));
	}
	line = loop_read(&file, fd);
	if (has_new_line(file))
		line = ft_strjoin(line, get_line(file, &file));
	return (line);
}
