/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakada <ktakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:24:18 by ktakada           #+#    #+#             */
/*   Updated: 2022/06/30 18:47:15 by ktakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	get_lf_index(char *buf);

char	*create_line_from_save(char *save, ssize_t lf_index);

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buf;
	char		*line;
	ssize_t		cc;
	ssize_t		lf_index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	cc = -1;
	lf_index = get_lf_index(save);
	if (lf_index != -1)
	{
		line = create_line_from_save(save, lf_index);
		if (line == NULL)
			return (NULL);
		save += lf_index + 1;
		return (line);
	}
	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	while (lf_index == -1 && cc != 0)
	{
		cc = read(fd, buf, BUFFER_SIZE);
		if (cc == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[cc] = '\0';
		save = ft_strjoin(save, buf);
		if (save == NULL)
		{
			free(buf);
			return (NULL);
		}
		lf_index = get_lf_index(save);
	}
	free(buf);
	if (save == NULL || *save == '\0')
		return (NULL);
	if (lf_index == -1)
		return (save);
	line = create_line_from_save(save, lf_index);
	if (line == NULL)
		return (NULL);
	save += lf_index + 1;
	return (line);
}

ssize_t	get_lf_index(char *buf)
{
	ssize_t	i;

	if (buf == NULL)
		return (-1);
	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char *create_line_from_save(char *save, ssize_t lf_index)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * lf_index + 1);
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, save, lf_index + 1);
	return (ret);
}

#include <stdio.h>
#include <fcntl.h>
int	main(int argc, char **argv)
{
	int		fd;
	char	*str;

	fd = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			perror("open");
			exit(1);
		}
		while (true)
		{
			str = get_next_line(fd);
			if (str == NULL)
				break ;
			printf("%s\n", str);
			free(str);
		}
	}
	close(fd);
	printf("\n\n");
	system("leaks -q a.out");
	return (0);
}
