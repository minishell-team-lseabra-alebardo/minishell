/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_ins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 01:43:42 by alebarbo          #+#    #+#             */
/*   Updated: 2025/09/30 02:21:17 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_minishell.h"
#include <string.h>

int	ft_built_ins(char *line)
{
	if (!strncmp(line, "echo -n", 7) 
		&& (!strncmp(line + 7, " ", 1) || !strncmp(line + 7, "\0", 1)))
		return (printf("%s", line + 8));
	else if (!strncmp(line, "echo ", 5))
		return (printf("%s\n", line + 5));
	return (-1);
}