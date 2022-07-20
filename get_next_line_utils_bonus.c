/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakada <ktakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:32:40 by ktakada           #+#    #+#             */
/*   Updated: 2022/07/20 16:32:59 by ktakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	ret;

	i = 0;
	ret = ft_strlen(src);
	if (dstsize == 0)
		return (ret);
	while (i + 1 < dstsize && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ret);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	ret;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	j = ft_strlen(dst);
	ret = ft_strlen(dst) + ft_strlen(src);
	if (dstsize < ft_strlen(dst) + 1)
		return (dstsize + ft_strlen(src));
	while (j + 1 < dstsize && src[i] != '\0')
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (ret);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*heap;

	i = 0;
	heap = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (heap == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		heap[i] = s1[i];
		i++;
	}
	heap[i] = '\0';
	return (heap);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*joined_str;

	if (s1 == NULL && s2 == NULL)
		return (ft_strdup(""));
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined_str = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (joined_str == NULL)
		return (NULL);
	ft_strlcpy(joined_str, s1, s1_len + 1);
	ft_strlcat(joined_str, s2, s1_len + s2_len + 1);
	return (joined_str);
}
