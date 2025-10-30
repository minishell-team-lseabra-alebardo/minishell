/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:53:17 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/28 15:56:26 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CHECKS_H
# define FT_CHECKS_H

int	ft_check_empty_line(char *line);
int	ft_check_operators(char *line);
int	ft_check_empty_parentheses(char *line);
int	ft_check_invalid_parentheses(char *line);
int	ft_check_unclosed(char *line);
int	ft_check_syntax(char *line);

#endif