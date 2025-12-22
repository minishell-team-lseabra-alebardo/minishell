/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_default.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:58:00 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/22 17:01:04 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

int	ft_sigint_default(void)
{
	sigset_t	sig_set;
	t_sigaction	sig_action;

	sigemptyset(&sig_set);
	sigaddset(&sig_set, SIGINT);
	sig_action.sa_handler = SIG_DFL;
	sig_action.sa_mask = sig_set;
	sig_action.sa_flags = 0;
	if (sigaction(SIGINT, &sig_action, 0))
		return (ERROR);
	return (SUCCESS);
}

int	ft_sigquit_default(void)
{
	sigset_t	sig_set;
	t_sigaction	sig_action;

	sigemptyset(&sig_set);
	sigaddset(&sig_set, SIGQUIT);
	sig_action.sa_handler = SIG_DFL;
	sig_action.sa_mask = sig_set;
	sig_action.sa_flags = 0;
	if (sigaction(SIGQUIT, &sig_action, 0))
		return (ERROR);
	return (SUCCESS);
}
