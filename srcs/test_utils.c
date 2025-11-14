/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:13:45 by lseabra-          #+#    #+#             */
/*   Updated: 2025/11/14 15:24:54 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_print_redirs(t_redir *redir)
{
	int	i;

	i = 0;
	while (redir)
	{
		printf("redir[%d]\n", i);
		printf("\ttype: %s\n", redir->type);
		printf("\tfilename: %s\n", redir->filename);
		printf("\tfd_from: %d\n", redir->fd_from);
		printf("\tfd_to: %d\n", redir->fd_to);
		redir = redir->next;
	}
}

void	ft_print_cmds(t_data *dt)
{
	int		i;
	int		cmd_counter;
	t_cmd	*cmd;

	cmd = dt->cmd_ll;
	cmd_counter = 0;
	while (cmd)
	{
		printf("-----------CMD[%d]------------\n", cmd_counter);
		i = 0;
		while (cmd->args[i])
		{
			printf("arg[%d]: %s\n", i, cmd->args[i]);
			i++;
		}
		printf("infile: %d\n", cmd->infile);
		printf("outfile: %d\n", cmd->outfile);
		i = 0;
		ft_print_redirs(cmd->redir_ll);
		printf("------------------------------\n\n");
		cmd = cmd->next;
		cmd_counter++;
	}
}
