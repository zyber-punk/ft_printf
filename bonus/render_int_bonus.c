/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:59:16 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/26 19:45:40 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	put_0x(t_data *data)
{
	if ((my_strchr("xX", data->format.specifier)
			&& data->format.hash
			&& data->format.tmp_buffer[0] != '0')
		|| data->format.specifier == 'p')
	{
		if (data -> format.uppercase)
			putstr_buffer("0X", 2, data);
		else
			putstr_buffer("0x", 2, data);
	}
}

static void	put_0b(t_data *data)
{
	if (data -> format.specifier == 'b' && data -> format.hash)
		putstr_buffer("0b", 2, data);
}

static void	put_sign(t_data *data)
{
	if (data -> format.base == BASE_16)
		put_0x(data);
	else if (data -> format.base == BASE_2)
		put_0b(data);
	else if (data -> format.signed_value)
	{
		if (data -> format.is_negative)
			putchar_buffer('-', 1, data);
		else if (!data -> format.is_negative)
		{
			if (data -> format.plus)
				putchar_buffer('+', 1, data);
			else if (data -> format.space)
				putchar_buffer(' ', 1, data);
		}
	}
}

void	print_int(t_data *data, t_union_int int_values)
{
	itoa_base(data, int_values);
	set_padding_zeros(data);
	set_padding_spaces(data);
	if (data -> format.left_justify)
	{
		put_sign(data);
		putchar_buffer('0', data -> format.padding_zeros, data);
		putstr_buffer(data -> format.tmp_buffer, data -> format.nbr_len, data);
		putchar_buffer(' ', data -> format.padding_spaces, data);
	}
	else
	{
		putchar_buffer(' ', data -> format.padding_spaces, data);
		put_sign(data);
		putchar_buffer('0', data -> format.padding_zeros, data);
		putstr_buffer(data -> format.tmp_buffer, data -> format.nbr_len, data);
	}
}
