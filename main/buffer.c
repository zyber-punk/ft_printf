/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:05:49 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/26 21:01:08 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_buffer(t_data *data, char c)
{
	if (data -> buffer_index == BUFFER_SIZE)
		flush_buffer(data);
	data -> buffer[data -> buffer_index++] = c;
}

void	flush_buffer(t_data *data)
{
	data -> chars_written += write(1, data -> buffer, data -> buffer_index);
	my_memset(data -> buffer, 0, BUFFER_SIZE * sizeof(char));
	data -> buffer_index = 0;
}

void	putchar_buffer(char c, int precision, t_data *data)
{
	if (precision <= 0)
		return ;
	while (precision--)
		write_buffer(data, c);
}

void	putstr_buffer(char *s, int precision, t_data *data)
{
	if (precision <= 0)
		return ;
	while (precision-- && *s)
		write_buffer(data, *s++);
}
