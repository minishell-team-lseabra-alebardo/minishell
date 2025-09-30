/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_ps1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:03:27 by lseabra-          #+#    #+#             */
/*   Updated: 2025/09/30 14:21:41 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (i < (size - 1) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size == 0)
	{
		return (src_len);
	}
	if (dst_len >= size)
	{
		return (src_len + size);
	}
	i = 0;
	while (i < (size - 1 - dst_len) && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
	{
		return (0);
	}
	i = 1;
	while ((unsigned char)*s1 && (unsigned char)*s2 && i < n)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
		{
			break ;
		}
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

static void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}

static void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

static void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0 && nmemb > SIZE_MAX / size)
	{
		return (NULL);
	}
	ptr = malloc(nmemb * size);
	if (!ptr)
	{
		return (NULL);
	}
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!ptr)
	{
		return (NULL);
	}
	ft_bzero(ptr, (s1_len + s2_len + 1) * sizeof(char));
	ft_strlcat(ptr, s1, s1_len + 1);
	ft_strlcat(ptr, s2, s1_len + s2_len + 1);
	return (ptr);
}

static char	*ft_get_hostname(void)
{
	char	*ref;
	char	*hostname;
	char	*res;
	size_t	size;

	ref = "local/";
	hostname = getenv("SESSION_MANAGER");
	if (!hostname)
		return (NULL);
	while (ft_strncmp(hostname, ref, ft_strlen(ref)) != 0)
		hostname++;
	if (*hostname == 0)
		return (NULL);
	hostname += ft_strlen(ref);
	size = 0;
	while (hostname[size] && hostname[size] != '.' && hostname[size] != ':')
		size++;
	res = ft_calloc(size + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, hostname, size + 1);
	return (res);
}

char	*get_ps1(void)
{
	char	*username;
	char	*hostname;
	char	*cwd;
	char	*res;

	username = getenv("USER");
	hostname = get_hostname();
	cwd = getcwd(0, 0);
	res = "\0";
	if (username)
		res = ft_strjoin(res, username);
	if (hostname)
	{
		res = ft_strjoin(res, "@");
		res = ft_strjoin(res, hostname);
		res = ft_strjoin(res, " ");
	}
	res = ft_strjoin(res, cwd);
	free(cwd);
	res = ft_strjoin(res, "$ ");
	return (res);
}

#include <stdio.h>
int	main(void)
{
	printf("%s\n", get_ps1());
}