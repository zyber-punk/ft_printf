/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:59:25 by uzyberaj          #+#    #+#             */
/*   Updated: 2024/12/26 21:01:29 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	my_memset(void *ptr, unsigned char value, size_t n)
{
	unsigned char	*ptr_byte;

	ptr_byte = (unsigned char *)ptr;
	while (n)
	{
		*ptr_byte++ = value;
		n--;
	}
}

bool	my_strchr(const char *s, char c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return (true);
		s++;
	}
	return (false);
}

int	my_strlen(const char *s)
{
	if (NULL == s || !*s)
		return (0);
	return (my_strlen(s + 1) + 1);
}

static void	set_symbol(t_data *data, t_union_int int_values)
{
	if (data -> format.uppercase)
		data -> format.tmp_buffer[data -> format.nbr_len++]
			= UPPER_SYMBOLS[int_values.uint64];
	else
		data -> format.tmp_buffer[data -> format.nbr_len++]
			= LOWER_SYMBOLS[int_values.uint64];
}

void	itoa_base(t_data *data, t_union_int int_values)
{
	t_union_int	tmp;

	if (data -> format.base < 2 || data -> format.base > 16)
		return ;
	if (data -> format.is_negative && !data -> format.is_converted)
	{
		int_values.int64 = -int_values.int64;
		data -> format.is_converted = true;
		itoa_base(data, int_values);
	}
	else if (int_values.uint64 < data -> format.base)
		set_symbol(data, int_values);
	else
	{
		tmp.uint64 = int_values.uint64 / data -> format.base;
		itoa_base(data, tmp);
		tmp.uint64 = int_values.uint64 % data -> format.base;
		itoa_base(data, tmp);
	}
}
