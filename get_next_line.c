/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:25:26 by mtravez           #+#    #+#             */
/*   Updated: 2022/11/07 16:33:48 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h> 
#include <stdio.h>

int	has_new_line(char *file)
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
		temp = ft_substr(file, 0, i + 1);
		i++;
		if (i == (int)ft_strlen(file))
		{
			free(temp);
			temp = ft_strdup(file);
			free(*newfile);
			*newfile = NULL;
			return (temp);
		}
		ft_memmove(file, &file[i], ft_strlen(file) - i);
		i = ft_strlen(&file[i]);
		while (file[i])
		{
			file[i] = '\0';
			i++;
		}
	}
	else if (file && ft_strlen(file) > 0)
		temp = ft_substr(file, 0, ft_strlen(file));
	return (temp);
}

static char*	fill_null(char *str, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		str[i] = 0;
		i++;
	}
	str[i] = 0;
	return(str);
}

char	*get_next_line(int fd)
{
	static char	*file = NULL;
	int			size;
	char		*line;
	if (file == NULL)
	{
		file = malloc(BUFFER_SIZE+1);
		if (!file)
			return (NULL);
		file = fill_null(file, BUFFER_SIZE + 1);
		if (!file)
			return (NULL);
		size = read(fd, file, BUFFER_SIZE);
		file[size] = 0;
		if (size <= 0)
		{
			free(file);
			file = NULL;
			return (NULL);
		}
	}
	line = NULL;
	while(file && !has_new_line(file))
	{
		line = ft_strjoin(line, get_line(file, &file));
		size = read(fd, &file[0], BUFFER_SIZE);
		if (size <= 0)
		{
			free(file);
			file = NULL;
			return (line);
		}
		file[size] = '\0';
	}
	if (has_new_line(file))
		line = ft_strjoin(line, get_line(file, &file));
	return (line);
}

// int	main(void)
// {
// 	int fd = open("hi.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	return (0);
// }