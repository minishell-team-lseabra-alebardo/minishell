/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skips.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:46:18 by alebarbo          #+#    #+#             */
/*   Updated: 2025/10/28 15:47:37 by alebarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SKIPS_H
# define FT_SKIPS_H

char	*ft_skip_whitespaces(char *line);
char	*ft_skip_quotes(char *line, char c);
char	*ft_skip_open_parentheses(char *line);
char	*ft_skip_and(char *line);
char	*ft_skip_pipe_or(char *line);

#endif