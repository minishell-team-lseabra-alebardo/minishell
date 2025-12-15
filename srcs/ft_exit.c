/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:31:53 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/15 15:33:51 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static unsigned char	ft_exit_args(t_cmd *cmd)
{
	int				i;

	if (cmd->args[1] && cmd->args[2])
		return (1);
	else if (cmd->args[1])
	{
		i = 0;
		while (cmd->args[1][i])
		{
			if (cmd->args[1][0] != '+' && cmd->args[1][0] != '-'
				&& !ft_isdigit(cmd->args[1][i]))
				return (2);
			i++;
		}
		return ((unsigned char) ft_atoi(cmd->args[1]));
	}
	return (0);
}

int	ft_exit(t_data *dt, t_cmd *cmd)
{
	int				pexit;
	unsigned char	code;

	code = ft_exit_args(cmd);
	pexit = dt->pexit;
	if (pexit && (!cmd || (cmd && !ft_is_in_pipeline(cmd))))
		printf("exit\n");
	ft_close_unused_fds(dt->cmd_ll);
	ft_free_strarr(dt->ms_envp);
	ft_free_prompt_line(dt);
	ft_cleanup_line(dt);
	free(dt);
	rl_clear_history();
	if (cmd->args[1])
		exit(code);
	if (ft_get_status(0, false) == EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}
