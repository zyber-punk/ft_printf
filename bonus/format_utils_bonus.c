/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:45:58 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/26 20:56:27 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_nbr_len(t_data *data)
{
	if (data -> format.precision > data -> format.nbr_len)
	{
		data -> format.padding_zeros = data -> format.precision - \
			data -> format.nbr_len;
		return ;
	}
}

void	set_padding_zeros(t_data *data)
{
	if (data -> format.precision >= 0)
	{
		set_nbr_len(data);
		return ;
	}
	if (data->format.zero)
	{
		if (data->format.left_justify)
			return ;
		if (data->format.width > data->format.nbr_len)
			data->format.padding_zeros = data->format.width - \
				data->format.nbr_len;
		if (data->format.specifier == 'u')
			return ;
		else if ((my_strchr("xX", data->format.specifier) && data->format.hash
				&& data->format.tmp_buffer[0] != '0')
			|| data->format.specifier == 'p')
			data->format.padding_zeros -= 2;
		else if (data->format.is_negative || (!data->format.is_negative
				&& (data->format.plus || data->format.space)))
			data->format.padding_zeros--;
	}
	if (data->format.padding_zeros < 0)
		data->format.padding_zeros = 0;
}

void	set_padding_spaces(t_data *data)
{
	data -> format.padding_spaces = data -> format.width - \
		data -> format.padding_zeros - data -> format.nbr_len;
	if (my_strchr("uxXp", data -> format.specifier))
	{
		if ((my_strchr("xX", data->format.specifier) && data->format.hash
				&& data->format.tmp_buffer[0] != '0')
			|| data->format.specifier == 'p')
			data->format.padding_spaces -= 2;
		return ;
	}
	if (data -> format.is_negative)
	{
		data -> format.padding_spaces--;
		return ;
	}
	if (!data -> format.is_negative && (data -> format.plus))
	{
		data -> format.padding_spaces--;
		return ;
	}
	if (!data -> format.is_negative && (data -> format.space))
	{
		data -> format.padding_spaces--;
		return ;
	}
}
