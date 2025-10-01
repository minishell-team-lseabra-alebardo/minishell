/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseabra- <lseabra-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:25:23 by lseabra-          #+#    #+#             */
/*   Updated: 2025/08/11 14:25:31 by lseabra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>

char	*get_next_line_bonus(int fd);
char	*ft_readline(int fd, char *line, char *buffer);
int		ft_findlinebreak(char	*str);
size_t	ft_strlen_chr(char *str, char c);
char	*ft_bufferlinejoin_bonus(char *line, char *buffer);
void	ft_clean_buffer_bonus(char *buffer);

#endif