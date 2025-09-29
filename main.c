/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:53:23 by lseabra-          #+#    #+#             */
/*   Updated: 2025/09/29 16:10:56 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*dir_name;
	int		i;

	(void)argc;
	(void)argv;
	i = -1;
	dir_name = get_current_dir_name();
	while (envp[++i])
		printf("envp[%d]: %s\n", i, envp[i]);
	line = readline("type what you want to print:\n");
	printf("%s\n", line);
	free(line);
}
