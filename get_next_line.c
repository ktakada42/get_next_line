/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakada <ktakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:24:18 by ktakada           #+#    #+#             */
/*   Updated: 2022/06/19 21:10:13 by ktakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	get_lf_index_from_buf(char	*buf);

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buf;
	char		*line;
	char		*tmp_to_free;
	ssize_t		cc;
	ssize_t		lf_index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	tmp_to_free = NULL;
	while (true)
	{
		buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (buf == NULL)
			return (NULL);
		cc = read(fd, buf, BUFFER_SIZE);
		if (cc == -1)
		{
			free (buf);
			return (NULL);
		}
		/* else if (cc == 0) */
		/* 	return (NULL); */
		lf_index = get_lf_index_from_buf(buf);
		if (lf_index == -1)
		{
			tmp_to_free = save;
			save = ft_strjoin(save, buf);
			if (save == NULL)
			{
				free(buf);
				free(line);
				free(tmp_to_free);
				return (NULL);
			}
			free(buf);
			free(tmp_to_free);
		}
		else
		{
			line = ft_strjoin(save, buf);
			if (line == NULL)
			{
				free(buf);
				free(save);
				free(line);
				return (NULL);
			}
			line[ft_strlen(save) + lf_index] = '\0';
			free(buf);
			free(save);
			return (line);
		}
	}
}

ssize_t	get_lf_index_from_buf(char	*buf)
{
	ssize_t	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

#include <fcntl.h>
#include <stdio.h>

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
		/* str = get_next_line(fd); */
		/* printf("%s\n", str); */
		/* free(str); */
	}
	close(fd);
	printf("\n\n");
	system("leaks -q a.out");
	return (0);
}
