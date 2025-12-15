/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:27:46 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/15 20:52:50 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_init_pwd(t_data *dt)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_set_env(dt, "PWD", pwd);
	free(pwd);
}

t_data	**ft_expand_dt(t_data **dt_arr, t_data *dt)
{
	t_data	**new_dt_arr;
	int		i;

	i = 0;
	while (dt_arr && dt_arr[i])
		i++;
	new_dt_arr = (t_data **) ft_calloc(i + 2, sizeof(t_data *));
	if (!new_dt_arr)
		return (0);
	i = 0;
	while (dt_arr && dt_arr[i])
	{
		new_dt_arr[i] = dt_arr[i];
		i++;
	}
	new_dt_arr[i] = dt;
	return (new_dt_arr);
}

t_data	*ft_data_init(char **envp)
{
	t_data	*dt;

	dt = (t_data *) ft_calloc(1, sizeof(t_data));
	if (!dt)
		ft_close_error(0);
	dt->subshell = 0;
	dt->dt_arr = ft_expand_dt(0, dt);
	if (!dt->dt_arr)
		ft_close_error(dt);
	dt->ms_envp = ft_strarr_dup(envp);
	if (!dt->ms_envp)
		ft_close_error(dt);
	ft_init_pwd(dt);
	dt->last_status = ft_get_status(0, false);
	dt->prompt = NULL;
	dt->line = NULL;
	dt->cmd_ll = NULL;
	if (ft_shlvl(dt) < 0)
		ft_close_error(dt);
	return (dt);
}
