/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:04:51 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 22:04:53 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

static void	formatstr(t_buf *b, char c, va_list a, int *ctr)
{
	if (c == 'c')
		h_put_char(b, va_arg(a, int), ctr);
	else if (c == 's')
		h_put_str(b, va_arg(a, char *), ctr);
	else if (c == 'p')
		h_put_ptr(b, va_arg(a, void *), ctr);
	else if (c == 'd' || c == 'i')
		h_put_int(b, va_arg(a, int), ctr);
	else if (c == 'u')
		h_put_uint(b, va_arg(a, unsigned int), ctr);
	else if (c == 'x')
		h_put_uintbase(b, va_arg(a, unsigned int), "0123456789abcdef", ctr);
	else if (c == 'X')
		h_put_uintbase(b, va_arg(a, unsigned int), "0123456789ABCDEF", ctr);
	else if (c == '%')
		h_put_char(b, '%', ctr);
	else
		*ctr = -1;
}

static void	loop_str(t_buf *buf, const char *str, va_list arg_v, int *ret)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '%')
			h_put_char(buf, str[i], ret);
		else
		{
			formatstr(buf, str[i + 1], arg_v, ret);
			if (*ret != -1)
				i++;
			else
				break ;
		}
		i++;
	}
}

int	print_fd(int fd, const char *str, ...)
{
	int		ret;
	va_list	arg_v;
	t_buf	buf;

	if (str == NULL || write(fd, 0, 0) == -1)
		return (-1);
	ret = 0;
	h_memset(&buf, 0, sizeof(t_buf));
	buf.fd = fd;
	va_start(arg_v, str);
	loop_str(&buf, str, arg_v, &ret);
	va_end(arg_v);
	h_put_buf(&buf);
	return (ret);
}

int	print(const char *str, ...)
{
	int		ret;
	va_list	arg_v;
	t_buf	buf;

	if (str == NULL || write(1, 0, 0) == -1)
		return (-1);
	ret = 0;
	h_memset(&buf, 0, sizeof(t_buf));
	buf.fd = 1;
	va_start(arg_v, str);
	loop_str(&buf, str, arg_v, &ret);
	va_end(arg_v);
	h_put_buf(&buf);
	return (ret);
}
