/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:53:23 by lseabra-          #+#    #+#             */
/*   Updated: 2025/09/30 16:06:40 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*ps1;

	(void)argc;
	(void)argv;
	(void)envp;
	ps1 = ft_get_ps1();
	line = readline(ps1);
	printf("%s\n", line);
	free(line);
}
