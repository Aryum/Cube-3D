/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:04:57 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 22:04:59 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include <unistd.h>
# include <stddef.h>
# include <stdarg.h>

typedef struct s_base
{
	char	*str;
	size_t	size;
}	t_base;

typedef struct s_buffer
{
	char	str[1024];
	int		count;
	int		fd;
}	t_buf;

void	h_put_char(t_buf *b, int c, int *counter);

void	h_put_int(t_buf *b, int n, int *counter);

void	h_put_ulongbase(t_buf *b, unsigned long nbr, char *base, int *counter);

void	h_put_uintbase(t_buf *b, unsigned int nbr, char *base, int *counter);

void	h_put_ptr(t_buf *b, void *ptr, int *counter);

void	h_put_str(t_buf *b, char *str, int *counter);

void	h_put_uint(t_buf *b, unsigned int i, int *counter);

int		h_strlen(const char *s);

void	*h_memset(void *s, int c, size_t n);

void	h_put_buf(t_buf *b);

int		print_fd(int fd, const char *string, ...);

int		print(const char *string, ...);

#endif
