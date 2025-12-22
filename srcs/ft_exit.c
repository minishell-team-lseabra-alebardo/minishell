/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:31:53 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/22 18:02:54 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static unsigned char	ft_exit_args(t_cmd *cmd)
{
	int	i;

	if (cmd->args[1])
	{
		i = 0;
		if ((cmd->args[1][0] == '+' || cmd->args[1][0] == '-')
			&& ft_isdigit(cmd->args[1][1]))
			i++;
		while (cmd->args[1][i] && ft_isdigit(cmd->args[1][i]))
			i++;
		if (cmd->args[1][i] && !ft_isdigit(cmd->args[1][i]))
		{
			ft_puterror("exit", cmd->args[1], ERR_NUM_ARG_REQ);
			return (EXIT_MISUSE);
		}
		else if (cmd->args[2])
		{
			ft_puterror("exit", NULL, ERR_TOO_MANY_ARGS);
			return (EXIT_FAILURE);
		}
		return ((unsigned char) ft_atoi(cmd->args[1]));
	}
	else
		return (EXIT_SUCCESS);
}

bool	ft_is_subexit(t_data *dt, t_cmd *cmd)
{
	if (dt->subshell && !ft_strncmp(cmd->args[0], "exit", 5))
		return (true);
	return (false);
}

int	ft_cleanup_subshell(t_data **dt_arr, t_data *dt)
{
	int		i;

	i = 0;
	ft_close_unused_fds(dt->cmd_ll);
	ft_free_strarr(dt->ms_envp);
	ft_free_prompt_line(dt);
	ft_cleanup_line(dt);
	while (dt && dt_arr[i] != dt)
		i++;
	dt_arr[i] = NULL;
	free(dt);
	return (ft_get_status(0, false));
}

int	ft_exit(t_data **dt_arr, t_data *dt, t_cmd *cmd)
{
	if (dt->subshell && cmd && cmd->args[1])
		return (ft_get_status(ft_exit_args(cmd), true));
	else if (dt->subshell)
		return (ft_get_status(0, false));
	if (!cmd || (cmd && !ft_is_in_pipeline(cmd)))
		write(STDOUT_FILENO, "exit\n", 5);
	if (cmd && cmd->args[1])
		ft_get_status(ft_exit_args(cmd), true);
	ft_close_unused_fds(dt->cmd_ll);
	ft_free_strarr(dt->ms_envp);
	ft_free_prompt_line(dt);
	ft_cleanup_line(dt);
	free(dt);
	free(dt_arr);
	rl_clear_history();
	exit(ft_get_status(0, false));
}
