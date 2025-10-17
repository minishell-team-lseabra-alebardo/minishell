/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:46:59 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/17 16:47:15 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

int	main(int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	char	**ms_envp;

	if (ft_listener() < 0)
	{
		perror(strerror(errno));
		exit(-1);
	}
	ms_envp = ft_strarr_dup(envp);
	ft_read_line(ms_envp);
}
