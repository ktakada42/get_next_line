/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakada <ktakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:24:18 by ktakada           #+#    #+#             */
/*   Updated: 2022/06/28 21:03:49 by ktakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>

ssize_t	get_lf_index(char	*buf);

char *create_line_from_save(char *save, ssize_t lf_index);

char *create_line_from_save_and_buf(char *save, char *buf, ssize_t lf_index);

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buf;
	char		*line;
	ssize_t		cc;
	ssize_t		lf_index;
	bool		eof;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	eof = false;
	lf_index = get_lf_index(save);
	if (lf_index != -1)
	{
		line = create_line_from_save(save, lf_index);
		if (line == NULL)
			return (NULL);
		save += lf_index + 1;
		return (line);
	}
	while (true)
	{
		if (eof)
			return (save);
		buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (buf == NULL)
			return (NULL);
		cc = read(fd, buf, BUFFER_SIZE);
		if (cc == -1)
		{
			free (buf);
			return (NULL);
		}
		if (cc < BUFFER_SIZE)
			eof = true;
		buf[cc] = '\0';
		lf_index = get_lf_index(buf);
		if (lf_index == -1)
		{
			save = ft_strjoin(save, buf);
			free(buf);
			if (save == NULL)
				return (NULL);
		}
		else
		{
			line = ft_strjoin(save, buf);
			if (line == NULL)
			{
				free(buf);
				return (NULL);
			}
			line = create_line_from_save_and_buf(save, buf, lf_index);
			if (line == NULL)
			{
				free(buf);
				return (NULL);
			}
			save = buf + lf_index + 1;
			free(buf);
			return (line);
		}
	}
}

ssize_t	get_lf_index(char	*buf)
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
	char *ret;

	ret = (char *)malloc(sizeof(char) * lf_index + 1);
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, save, lf_index + 1);
	return (ret);
}

char *create_line_from_save_and_buf(char *save, char *buf, ssize_t lf_index)
{
	char *ret;
	char *tmp_to_free;

	ret = ft_strjoin(save, buf);
	if (ret == NULL)
		return (NULL);
	tmp_to_free = ret;
	ret = create_line_from_save(ret, ft_strlen(save) + lf_index);
	if (ret == NULL)
	{
		free(tmp_to_free);
		return (NULL);
	}
	return (ret);
}

/* #include <fcntl.h> */
/* #include <stdio.h> */

/* int	main(int argc, char **argv) */
/* { */
/* 	int		fd; */
/* 	char	*str; */

/* 	fd = 0; */
/* 	if (argc == 2) */
/* 	{ */
/* 		fd = open(argv[1], O_RDONLY); */
/* 		if (fd == -1) */
/* 		{ */
/* 			perror("open"); */
/* 			exit(1); */
/* 		} */
/* 		while (true) */
/* 		{ */
/* 			str = get_next_line(fd); */
/* 			if (str == NULL) */
/* 				break ; */
/* 			printf("%s\n", str); */
/* 			free(str); */
/* 		} */
/* 		/1* str = get_next_line(fd); *1/ */
/* 		/1* printf("%s\n", str); *1/ */
/* 		/1* free(str); *1/ */
/* 	} */
/* 	close(fd); */
/* 	printf("\n\n"); */
/* 	system("leaks -q a.out"); */
/* 	return (0); */
/* } */
