/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:59:53 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/04 11:42:32 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_minishell.h>

static void	ft_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static int	ft_sigint_listener(void)
{
	sigset_t	sig_set;
	t_sigaction	sig_action;

	sigemptyset(&sig_set);
	sigaddset(&sig_set, SIGINT);
	sig_action.sa_handler = ft_signal_handler;
	sig_action.sa_mask = sig_set;
	sig_action.sa_flags = 0;
	if (sigaction(SIGINT, &sig_action, 0))
		return (ERROR);
	return (0);
}

static int	ft_sigquit_listener(void)
{
	sigset_t	sig_set;
	t_sigaction	sig_action;

	sigemptyset(&sig_set);
	sigaddset(&sig_set, SIGQUIT);
	sig_action.sa_handler = SIG_IGN;
	sig_action.sa_mask = sig_set;
	sig_action.sa_flags = 0;
	if (sigaction(SIGQUIT, &sig_action, 0))
		return (ERROR);
	return (0);
}

int	ft_listener(void)
{
	if (ft_sigquit_listener() < 0 || ft_sigint_listener() < 0)
		return (ERROR);
	return (0);
}
