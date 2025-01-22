/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:50:41 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/30 20:10:38 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(t_data *data, int c)
{
	int	width;

	width = data -> format.width;
	if (width > 1)
	{
		if (data -> format.left_justify)
		{
			putchar_buffer((char)c, 1, data);
			putchar_buffer(' ', width - 1, data);
		}
		else
		{
			putchar_buffer(' ', width - 1, data);
			putchar_buffer((char)c, 1, data);
		}
	}
	else
		putchar_buffer((char)c, 1, data);
}

static void	set_str_padding_spaces(t_data *data, char *s)
{
	int	len;

	len = my_strlen(s);
	if (data -> format.width > 0)
	{
		if (data -> format.precision >= 0)
		{
			if (data -> format.precision > len)
				data -> format.padding_spaces = data -> format.width - len;
			else if (data -> format.precision < len)
				data -> format.padding_spaces = data -> format.width - \
					data -> format.precision;
		}
		else
		{
			data -> format.padding_spaces = data -> format.width - len;
		}	
	}
}

void	print_str(t_data *data, char *s)
{
	if (NULL == s)
		s = "(null)";
	set_str_padding_spaces(data, s);
	if (data -> format.left_justify)
	{
		if (data -> format.precision >= 0)
			putstr_buffer(s, data -> format.precision, data);
		else
			putstr_buffer(s, my_strlen(s), data);
		putchar_buffer(' ', data -> format.padding_spaces, data);
	}
	else
	{
		putchar_buffer(' ', data -> format.padding_spaces, data);
		if (data -> format.precision >= 0)
			putstr_buffer(s, data -> format.precision, data);
		else
			putstr_buffer(s, my_strlen(s), data);
	}
}
