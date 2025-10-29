/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 03:08:09 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/29 15:16:57 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <ft_minishell.h>

static void	ft_free_prompt_line(char *prompt, char *line)
{
	if (prompt)
		free(prompt);
	if (line)
		free(line);
}

static void	ft_free_ms_envp(char **ms_envp)
{
	int		i;

	i = 0;
	while (ms_envp[i])
	{
		free(ms_envp[i]);
		i++;
	}
	free(ms_envp);
}

static void	ft_exiting(char *prompt, char *line, t_data *dt)
{
	ft_free_prompt_line(prompt, line);
	ft_free_ms_envp(dt->ms_envp);
	free(dt);
	printf("exit\n");
	exit(0);
}

static void	ft_print_cmds(t_data *dt)
{
	int		i;
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = dt->list;

	while (cmd)
	{
		printf("-----------------------\n");
		i = 0;
		while (cmd->args[i])
		{
			printf("arg%d: %s\n", i, cmd->args[i]);
			i++;
		}
		printf("infile: %d\n", cmd->infile);
		printf("outfile: %d\n", cmd->outfile);
		redir = cmd->redir_ll;
		i = 0;
		while (redir)
		{
			printf("redir%d\n", i);
			printf("\ttype: %s\n", redir->type);
			printf("\tfilename: %s\n", redir->filename);
			printf("\tfd_from: %d\n", redir->fd_from);
			printf("\tfd_to: %d\n", redir->fd_to);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

void	ft_read_line(t_data *dt)
{
	char	*prompt;
	char	*line;

	while (1)
	{
		prompt = ft_get_ps1();
		line = readline(prompt);
		if (!line)
			ft_exiting(prompt, line, dt);
		if (line && *line)
		{
			add_history(line);
			if (ft_check_unclosed(line) < 0 || ft_check_commands(line) < 0)
				write(2, ERR_SYNTAX, 13);
			else
			{
				dt->split_line = ft_split_prompt(line, WS_POSIX);
				ft_parser(dt);
				ft_print_cmds(dt);
			}
		}
		ft_free_prompt_line(prompt, line);
	}
}
