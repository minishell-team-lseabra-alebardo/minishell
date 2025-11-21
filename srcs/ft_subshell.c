/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:46:46 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/21 18:10:33 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_remove_parentheses(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		ft_memmove(&line[i], &line[i + 1], 1);
		i++;
	}
	i = 0;
	while (line[i])
	{
		if (line[i] == ')')
			line[i] = 0;
		i++;
	}
}

void	ft_subshell(t_data *dt, char **argv)
{
	char	*line;

	dt->pexit = 1;
	line = ft_strdup(argv[1]);
	if (line[0] == '(')
		ft_remove_parentheses(line);
	ft_args_treatment(&line, dt->ms_envp, 0);
	dt->split_line = ft_split_prompt(line, WS_POSIX);
	ft_parser(dt);
	ft_exec_line(dt);
	ft_exit(dt);
}

static char	*ft_get_ms_path(char **ms_envp)
{
	int		i;

	i = 0;
	while (ft_strncmp(ms_envp[i], "MS_PATH=", 8))
		i++;
	return (ms_envp[i] + 8);
}

static char	**ft_include_subshell(char **args)
{
	char	**new_args;
	int		i;
	int		j;

	i = 0;
	while (args[i])
		i++;
	new_args = (char **) ft_calloc(i + 2, sizeof(char *));
	new_args[0] = ft_strdup("minishell");
	i = 0;
	j = 1;
	while (args[i])
	{
		new_args[j] = args[i];
		i++;
		j++;
	}
	free(args);
	return (new_args);
}

int	ft_prepare_subshell(char **ms_envp, t_cmd *cmd, char **path)
{
	if (!ft_strncmp(cmd->args[0], "minishell", 10))
	{
		*path = ft_strdup(ft_get_ms_path(ms_envp));
		return (1);
	}
	if (cmd->args[0][0] == '(')
	{
		cmd->args = ft_include_subshell(cmd->args);
		*path = ft_strdup(ft_get_ms_path(ms_envp));
		return (1);
	}
	return (0);
}
