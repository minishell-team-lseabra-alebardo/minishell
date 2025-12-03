/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ordered_exp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:51:45 by lseabra-          #+#    #+#             */
/*   Updated: 2025/12/03 17:03:14 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static int	ft_strcmp_all(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	max_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len >= s2_len)
		max_len = s1_len;
	else
		max_len = s2_len;
	return (ft_strncmp(s1, s2, max_len));
}

static void	ft_strarr_bubble_sort(char **strarr, size_t len)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	if (!strarr)
		return ;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strcmp_all(strarr[j], strarr[j + 1]) > 0)
			{
				tmp = strarr[j];
				strarr[j] = strarr[j + 1];
				strarr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	ft_print_formatted_env(char *env)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!env)
		return ;
	res = ft_calloc(ft_strlen(EXP_PREFIX) + ft_strlen(env) + 4, sizeof(char));
	if (!res)
		return ;
	i = ft_strlcpy(res, EXP_PREFIX, ft_strlen(EXP_PREFIX) + 1);
	j = 0;
	while (env[j] && env[j] != '=')
		j++;
	ft_strlcpy(res + i, env, j + 1);
	i += j;
	if (env[j] == '=')
	{
		i += ft_strlcpy(res + i, "=\"", 2 + 1);
		i += ft_strlcpy(res + i, env + j + 1, ft_strlen(env) + 1);
		i += ft_strlcpy(res + i, "\"", 1 + 1);
	}
	i += ft_strlcpy(res + i, "\n", 1 + 1);
	write(STDOUT_FILENO, res, ft_strlen(res));
	free(res);
}

int	ft_print_ordered_exp(char **strarr)
{
	char	**ordered;
	size_t	i;

	if (!strarr)
		return (EXIT_FAILURE);
	i = 0;
	while (strarr[i])
		i++;
	ordered = ft_calloc(i + 1, sizeof(char *));
	if (!ordered)
		return (EXIT_FAILURE);
	ft_memcpy(ordered, strarr, i * sizeof(char *));
	ft_strarr_bubble_sort(ordered, i);
	i = 0;
	while (ordered[i])
	{
		ft_print_formatted_env(ordered[i]);
		i++;
	}
	free(ordered);
	return (EXIT_SUCCESS);
}
