/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:46:59 by alebarbo          #+#    #+#             */
/*   Updated: 2025/11/08 23:23:43 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

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

static void	ft_close_error(t_data *dt)
{
	perror(strerror(errno));
	if (dt)
	{
		if (dt->ms_envp)
			ft_free_ms_envp(dt->ms_envp);
		free(dt);
	}
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*dt;

	(void) argc;
	(void) argv;
	if (ft_listener() < 0)
		ft_close_error(0);
	dt = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!dt)
		return (EXIT_FAILURE);
	dt->ms_envp = ft_strarr_dup(envp);
	if (!dt->ms_envp)
		return (EXIT_FAILURE);
	if (ft_ms_path(dt) < 0)
		ft_close_error(dt);
	dt->lst_stat = 0;
	dt->cmd_ll = NULL;
	ft_read_line(dt);
}
