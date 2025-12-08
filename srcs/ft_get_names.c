/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_names.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 04:16:49 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/08 16:38:52 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

int	ft_count_names(void)
{
	DIR				*dir;
	struct dirent	*cont;
	int				i;

	dir = opendir(".");
	if (!dir)
		return (-1);
	i = 0;
	while (1)
	{
		cont = readdir(dir);
		if (!cont)
			break ;
		if (ft_strncmp(cont->d_name, ".", 1))
			i++;
	}
	closedir(dir);
	return (i);
}

char	**ft_get_names(int names_count)
{
	int				i;
	char			**names;
	DIR				*dir;
	struct dirent	*cont;

	names = (char **) ft_calloc(names_count + 1, sizeof(char *));
	if (!names)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (NULL);
	i = 0;
	while (1)
	{
		cont = readdir(dir);
		if (!cont)
			break ;
		if (ft_strncmp(cont->d_name, ".", 1))
			names[i++] = strdup(cont->d_name);
	}
	closedir(dir);
	return (names);
}
