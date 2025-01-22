/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:26:49 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/26 19:50:36 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	my_atoi(t_data *data)
{
	int	value;

	value = 0;
	while (my_strchr(NUMBERS, *data -> s))
	{
		value = value * 10 + (*data -> s - '0');
		++data -> s;
	}
	return (value);
}

static void	parse_flags(t_data *data)
{
	while (my_strchr(FLAGS, *data -> s))
	{
		if ('0' == *data -> s)
			data -> format.zero = true;
		else if ('-' == *data -> s)
			data -> format.left_justify = true;
		else if ('+' == *data -> s)
			data -> format.plus = true;
		else if (' ' == *data -> s)
			data -> format.space = true;
		else if ('#' == *data -> s)
			data -> format.hash = true;
		++data -> s;
	}
}

static void	get_value(t_data *data, int *value)
{
	if ('*' == *data->s)
	{
		*value = va_arg(data->ap, int);
		++data->s;
		return ;
	}
	*value = my_atoi(data);
}

int	parse_format(t_data *data)
{
	my_memset(&data -> format, 0, sizeof(t_format));
	data -> format.precision = -1;
	parse_flags(data);
	get_value(data, &data -> format.width);
	if (*data -> s == '.' && *(++data -> s))
		get_value(data, &data -> format.precision);
	if (!my_strchr (SPECIFIERS, *data -> s))
		return (PARSE_ERROR);
	else
	{
		data -> format.specifier = *data -> s;
		if (my_strchr("diu", data -> format.specifier))
			data -> format.base = BASE_10;
		else if (my_strchr("xXp", data -> format.specifier))
		{
			data -> format.base = BASE_16;
			if ('X' == data -> format.specifier)
				data -> format.uppercase = true;
		}
		else if ('b' == data -> format.specifier)
			data -> format.base = BASE_2;
	}
	return (OK);
}
