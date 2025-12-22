/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:24:19 by alebarbo          #+#    #+#             */
/*   Updated: 2025/12/22 16:58:40 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H
# include <signal.h>

int	ft_sigint_listener(void);
int	ft_sigint_readline_listener(void);
int	ft_sigquit_listener(void);
int	ft_sigint_default(void);
int	ft_sigquit_default(void);

#endif