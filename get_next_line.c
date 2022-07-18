/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakada <ktakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:24:18 by ktakada           #+#    #+#             */
/*   Updated: 2022/07/18 23:29:16 by ktakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	get_lf_index(char *buf);

char	*read_till_found_lf(int fd, char *save);

char	*create_line_from_save(char *save);

char	*move_save_next_to_lf(char *save);

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_till_found_lf(fd, save);
	if (save == NULL)
		return (NULL);
	line = create_line_from_save(save);
	save = move_save_next_to_lf(save);
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

char	*read_till_found_lf(int fd, char *save)
{
	char	*buf;
	char	*tmp_to_free;
	ssize_t	cc;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	cc = -1;
	while (get_lf_index(save) == -1 && cc != 0)
	{
		cc = read(fd, buf, BUFFER_SIZE);
		if (cc == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[cc] = '\0';
		tmp_to_free = save;
		save = ft_strjoin(save, buf);
		free(tmp_to_free);
	}
	free(buf);
	return (save);
}

char	*create_line_from_save(char *save)
{
	size_t	i;
	char	*line;

	i = 0;
	if (save[i] == '\0')
		return (NULL);
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 1);
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, save, i + 1);
	return (line);
}

char	*move_save_next_to_lf(char *save)
{
	char	*new_save;
	size_t	i;
	size_t	new_save_len;

	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	if (save[i] == '\0')
	{
		free(save);
		return (NULL);
	}
	new_save_len = ft_strlen(save) - i - 1;
	new_save = (char *)malloc(sizeof(char) * new_save_len + 1);
	if (new_save == NULL)
		return (NULL);
	ft_strlcpy(new_save, save + i + 1, new_save_len + 1);
	free(save);
	return (new_save);
}

/* #include <stdio.h> */
/* #include <fcntl.h> */
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
/* 	} */
/* 	close(fd); */
/* 	printf("\n\n"); */
/* 	system("leaks -q a.out"); */
/* 	return (0); */
/* } */
