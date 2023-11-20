/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:41:43 by macbook           #+#    #+#             */
/*   Updated: 2023/11/17 16:50:40 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef io_H
# define io_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

int		ft_putchar_fd(char c, int fd);
int		ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_putstr_fd(char *s, int fd);
char	*get_next_line(int fd);
int		ft_printf(const char *str, ...);

#endif
