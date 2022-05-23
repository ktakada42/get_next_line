/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakada <ktakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:24:18 by ktakada           #+#    #+#             */
/*   Updated: 2022/05/22 14:46:36 by ktakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	chr;
	size_t	i;

	str = (char *)s;
	chr = (char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == chr)
			return (str + i);
		i++;
	}
	if (chr == '\0')
		return (str + i);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*save;
	ssize_t		read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	read_bytes = 1;
	printf("%ld\n", read_bytes);
	while (ft_strchr(save, '\n') == NULL && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		printf("%ld\n", read_bytes);
		if (read_bytes == -1)
		{
			free(buf);
			return(NULL);
		}
		buf[read_bytes] = '\0';
		save = ft_strjoin(save, buf);
	}
	printf("end_while\n");
	return (buf);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd;
	char  *str;

	fd = open("a.txt", O_RDONLY);
	printf("%d\n", fd);
	str = get_next_line(fd);
	printf("%s\n", str);
	return (0);
}
