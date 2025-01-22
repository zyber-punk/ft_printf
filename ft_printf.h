/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 01:06:10 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/01/03 16:54:32 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>

# define BUFFER_SIZE	(4096)

# define FLAGS	"-+ #0"
# define NUMBERS	"0123456789"
# define SPECIFIERS	"cspdiuxXb%"
# define LOWER_SYMBOLS	"0123456789abcdef"
# define UPPER_SYMBOLS	"0123456789ABCDEF"

# define RST "\033[0m"
# define R "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define M "\033[1;35m"
# define C "\033[1;36m"

typedef union union_int
{
	unsigned long	uint64;
	long			int64;
}	t_union_int;

typedef enum e_error
{
	OK = 0,
	MALLOC_ERROR = -1337,
	PARSE_ERROR = -42,
}	t_error;

typedef enum e_base
{
	BASE_2 = 2,
	BASE_8 = 8,
	BASE_10 = 10,
	BASE_16 = 16,
}	t_base;

typedef struct s_format
{
	bool	left_justify;
	bool	zero;
	bool	plus;
	bool	space;
	bool	hash;
	int		width;
	int		precision;
	char	specifier;
	char	tmp_buffer[64];
	int		nbr_len;
	bool	uppercase;
	t_base	base;
	int		padding_spaces;
	int		padding_zeros;
	bool	is_negative;
	bool	is_converted;
	bool	signed_value;
}	t_format;

typedef struct s_data
{
	const char	*s;
	va_list		ap;
	int			chars_written;
	char		*buffer;
	int			buffer_index;
	t_format	format;
}	t_data;

int		ft_printf(const char *format, ...);
void	my_memset(void *ptr, unsigned char value, size_t n);
bool	my_strchr(const char *s, char c);
int		parse_format(t_data *data);
void	flush_buffer(t_data *data);
void	write_buffer(t_data *data, char c);
void	putchar_buffer(char c, int precision, t_data *data);
void	print_char(t_data *data, int c);
void	putstr_buffer(char *s, int precision, t_data *data);
int		my_strlen(const char *s);
void	print_str(t_data *data, char *s);
void	itoa_base(t_data *data, t_union_int int_values);
void	set_padding_zeros(t_data *data);
void	set_padding_spaces(t_data *data);
void	print_int(t_data *data, t_union_int int_values);

#endif