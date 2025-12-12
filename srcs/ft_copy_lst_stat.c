/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_lst_stat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:29:40 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/12 18:13:32 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static int	ft_count_stat(char *arg)
{
	int		i;
	int		find;

	i = 0;
	find = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
			i = ft_avoid_quotes(arg, arg[i], i + 1);
		if (arg[i] == '(')
		{
			while (arg[i] != ')')
				i++;
		}
		if (arg[i] == '$' && arg[i + 1] == '?')
			find++;
		i++;
	}
	return (find);
}

static void	ft_transfer_lst_stat(char *arg, char *new_arg, int len)
{
	int		i;

	i = 0;
	while (*arg)
	{
		if (*arg == '$' && *(arg + 1) == '?')
		{
			ft_strlcat(new_arg, "\"$?\"", len);
			i += 4;
			arg += 2;
		}
		else
		{
			new_arg[i] = *arg;
			i++;
			arg++;
		}
	}
}

char	*ft_prep_lst_stat(char *arg)
{
	char	*new_arg;
	int		find;

	find = ft_count_stat(arg);
	if (!find)
		return (arg);
	new_arg = (char *) ft_calloc(ft_strlen(arg) + (find * 2) + 1, 1);
	ft_transfer_lst_stat(arg, new_arg, ft_strlen(arg) + (find * 2) + 1);
	free(arg);
	return (new_arg);
}

char	*ft_copy_lst_stat(int lst_stat, char *arg, int *i)
{
	char	*new_arg;
	char	*stat_string;
	int		env_var_len;
	int		j;

	stat_string = ft_itoa(lst_stat);
	if (!stat_string)
		return (arg);
	env_var_len = ft_strlen(stat_string);
	new_arg = ft_calloc(ft_strlen(arg) + env_var_len, 1);
	if (!new_arg)
		return (arg);
	j = ft_copy_start(new_arg, arg, *i);
	ft_copy_rest(new_arg, stat_string);
	j += 2;
	ft_copy_rest(new_arg, &arg[j]);
	*i += env_var_len - 1;
	free(stat_string);
	free(arg);
	return (new_arg);
}
