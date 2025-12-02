/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_lst_stat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:29:40 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/02 20:38:16 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

char	*ft_copy_lst_stat(int lst_stat, char *arg, int var_size, int *i)
{
	char	*new_arg;
	char	*stat_string;
	int		env_var_len;
	int		j;

	stat_string = ft_itoa(lst_stat);
	if (!stat_string)
		return (arg);
	env_var_len = ft_strlen(stat_string);
	new_arg = ft_calloc((ft_strlen(arg) + env_var_len) - var_size + 1, 1);
	if (!new_arg)
		return (arg);
	j = ft_copy_start(new_arg, arg, *i);
	ft_copy_rest(new_arg, stat_string);
	j += var_size;
	ft_copy_rest(new_arg, &arg[j]);
	*i += env_var_len - 1;
	free(stat_string);
	free(arg);
	return (new_arg);
}