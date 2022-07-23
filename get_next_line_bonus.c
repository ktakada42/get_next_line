/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakada <ktakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:32:23 by ktakada           #+#    #+#             */
/*   Updated: 2022/07/23 11:48:06 by ktakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

ssize_t	get_lf_index(char *buf);

char	*read_till_found_lf(int fd, char *save);

char	*create_line_from_save(char *save);

char	*move_save_next_to_lf(char *save);

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*line;

	if (fd < 0 || OPEN_MAX < fd || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = read_till_found_lf(fd, save[fd]);
	if (save[fd] == NULL)
		return (NULL);
	line = create_line_from_save(save[fd]);
	save[fd] = move_save_next_to_lf(save[fd]);
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
	if (save[0] == '\0')
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
	{
		free(save);
		return (NULL);
	}
	ft_strlcpy(new_save, save + i + 1, new_save_len + 1);
	free(save);
	return (new_save);
}

/*
#include <stdio.h>
#include <fcntl.h>
int	main(int argc, char **argv)
{
	int		files = argc - 1;
	int		fd[files];
	char	*str;
	char	*strs[files];
	int		j = 0;
	bool	end;

	for (int i = 0; i < files; i++)
		strs[i] = NULL;
	if (argc >= 2)
	{
		for (int i = 0; i < files; i++)
		{
			fd[i] = open(argv[i + 1], O_RDONLY);
			if (fd[i] == -1)
			{
				perror("open");
				exit(1);
			}
		}
		while (true)
		{
			str = get_next_line(fd[j]);
			printf("fd: %d, line: %s", j + 3, str);
			strs[j] = str;
			free(str);
			for (int i = 0; i < files; i++)
			{
				if (strs[i] != NULL)
				{
					end = false;
					break ;
				}
				end = true;
			}
			if (end)
				break ;
			j++;
			if (j == files)
				j = 0;
		}
	for (int i = 0; i < files; i++)
		close(fd[i]);
	printf("\n\n");
	system("leaks -q a.out");
	return (0);
	}
}
*/