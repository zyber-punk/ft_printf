/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 01:03:07 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/01/03 16:19:37 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	handle_numeric_format(t_data *data, char specifier)
{
	t_union_int	int_values;
	void		*ptr;

	int_values.uint64 = 0;
	if (my_strchr("di", specifier))
	{
		int_values.int64 = (long)va_arg(data->ap, int);
		data->format.signed_value = true;
		if (int_values.int64 < 0)
			data->format.is_negative = true;
	}
	else if ('p' == specifier)
	{
		ptr = va_arg(data->ap, void *);
		if (ptr == NULL)
		{
			putstr_buffer("(nil)", 5, data);
			return ;
		}
		int_values.uint64 = (unsigned long)ptr;
	}
	else if (my_strchr("xXub", specifier))
		int_values.uint64 = (unsigned long)va_arg(data->ap, unsigned int);
	print_int(data, int_values);
}

void	render_format(t_data *data)
{
	char		specifier;

	specifier = data->format.specifier;
	if ('%' == specifier)
		print_char(data, '%');
	else if ('c' == specifier)
		print_char(data, va_arg(data->ap, int));
	else if ('s' == specifier)
		print_str(data, va_arg(data->ap, char *));
	else
		handle_numeric_format(data, specifier);
}

static int	init_data(t_data *data, const char *format)
{
	data -> chars_written = 0;
	data -> s = format;
	data -> buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!data -> buffer)
		return (MALLOC_ERROR);
	my_memset(data -> buffer, 0, BUFFER_SIZE * sizeof(char));
	data -> buffer_index = 0;
	return (OK);
}

int	ft_printf(const char *format, ...)
{
	t_data	data;

	va_start(data.ap, format);
	if (init_data(&data, format))
		return (MALLOC_ERROR);
	while (*data.s)
	{
		if (*data.s == '%' && *(++data.s))
		{
			if (parse_format(&data))
			{
				free(data.buffer);
				va_end(data.ap);
				return (PARSE_ERROR);
			}
			render_format(&data);
		}
		else
			write_buffer(&data, *data.s);
		++data.s;
	}
	flush_buffer(&data);
	va_end(data.ap);
	free(data.buffer);
	return (data.chars_written);
}

/*
void	test_char(void)
{
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf char: " Y "[%c]" RST "\n", 'A'));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf char: " G "[%c]" RST "\n", 'A'));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf char: " Y "[%10c]" RST "\n", 'A'));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf char: " G "[%10c]" RST "\n", 'A'));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf char: " Y "[%-10c]" RST "\n", 'A'));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf char: " G "[%-10c]" RST "\n", 'A'));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf char: " Y "[%*c]" RST "\n", 10, 'A'));
	printf(G "printf=%d" RST "\n", printf("og_printf char: " G "[%*c]" RST "\n",
			10, 'A'));
}

void	test_str(void)
{
	char	*s;

	s = "Bonjour je m'appelle Ulysse";
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf str: " Y "[%s]" RST "\n", s));
	printf(G "printf=%d" RST "\n\n", printf("og_printf str: " G "[%s]" RST "\n",
			s));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf str: " Y "[%10s]" RST "\n", s));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf str: " G "[%10s]" RST "\n", s));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf str: " Y "[%10.3s]" RST "\n", s));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf str: " G "[%10.3s]" RST "\n", s));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf str: " Y "[%-10.3s]" RST "\n", s));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf str: " G "[%-10.3s]" RST "\n", s));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf str: " Y "[%*.*s]" RST "\n", 3, 6, s));
	printf(G "printf=%d" RST "\n",
		printf("og_printf str: " G "[%*.*s]" RST "\n", 3, 6, s));
}

void	test_int(void)
{
	int	num;

	num = 42;
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf int: " Y "[%d]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n", printf("og_printf int: " G "[%d]" RST "\n",
			num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf int: " Y "[%10d]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf int: " G "[%10d]" RST "\n", num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf int: " Y "[%-10d]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf int: " G "[%-10d]" RST "\n", num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf int: " Y "[%010d]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf int: " G "[%010d]" RST "\n", num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf int: " Y "[%+d]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf int: " G "[%+d]" RST "\n", num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf int: " Y "[% d]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf int: " G "[% d]" RST "\n", num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf int: " Y "[%*d]" RST "\n", 10, num));
	printf(G "printf=%d" RST "\n", printf("og_printf int: " G "[%*d]" RST "\n",
			10, num));
}

void	test_unsigned_int(void)
{
	unsigned int	num;

	num = 42;
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf uint: " Y "[%u]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf uint: " G "[%u]" RST "\n", num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf uint: " Y "[%10u]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf uint: " G "[%10u]" RST "\n", num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf uint: " Y "[%-10u]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf uint: " G "[%-10u]" RST "\n", num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf uint: " Y "[%010u]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf uint: " G "[%010u]" RST "\n", num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf uint: " Y "[%*u]" RST "\n", 10, num));
	printf(G "printf=%d" RST "\n", printf("og_printf uint: " G "[%*u]" RST "\n",
			10, num));
}

void	test_hex(void)
{
	int	num;

	num = 42;
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf hex: " Y "[%x]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n", printf("og_printf hex: " G "[%x]" RST "\n",
			num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf hex: " Y "[%10x]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf hex: " G "[%10x]" RST "\n", num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf hex: " Y "[%-10x]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf hex: " G "[%-10x]" RST "\n", num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf hex: " Y "[%010x]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf hex: " G "[%010x]" RST "\n", num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf hex: " Y "[%#x]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf hex: " G "[%#x]" RST "\n", num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf hex: " Y "[%X]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n", printf("og_printf hex: " G "[%X]" RST "\n",
			num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf hex: " Y "[%#X]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf hex: " G "[%#X]" RST "\n", num));
}

void	test_pointer(void)
{
	int	num;
	int	*ptr;

	num = 42;
	ptr = &num;
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf ptr: " Y "[%p]" RST "\n", ptr));
	printf(G "printf=%d" RST "\n\n", printf("og_printf ptr: " G "[%p]" RST "\n",
			ptr));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf ptr: " Y "[%20p]" RST "\n", ptr));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf ptr: " G "[%20p]" RST "\n", ptr));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf ptr: " Y "[%-20p]" RST "\n", ptr));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf ptr: " G "[%-20p]" RST "\n", ptr));
}

void	test_binary(void)
{
	int	num;

	num = 42;
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf bin: " Y "[%b]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n", printf("og_printf bin: " G "[%b]" RST "\n",
			num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf bin: " Y "[%10b]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf bin: " G "[%10b]" RST "\n", num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf bin: " Y "[%-10b]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf bin: " G "[%-10b]" RST "\n", num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf bin: " Y "[%010b]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf bin: " G "[%010b]" RST "\n", num));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf bin: " Y "[%#b]" RST "\n", num));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf bin: " G "[%#b]" RST "\n", num));
}

void	test_percent(void)
{
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf percent: " Y "[%%]" RST "\n"));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf percent: " G "[%%]" RST "\n"));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf percent: " Y "[%10%%]" RST "\n"));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf percent: " G "[%10%%]" RST "\n"));
	printf(Y "ft_printf=%d" RST "\n",
		ft_printf("ft_printf percent: " Y "[%-10%%]" RST "\n"));
	printf(G "printf=%d" RST "\n\n",
		printf("og_printf percent: " G "[%-10%%]" RST "\n"));
}

void	test(void)
{
	ft_printf("%-106p%--%%---16.39i%-62.45s%032.34u\n" ,
		(void*)4820041568133212049lu,1496653732,"78iTF|2mbbziDh\n0^?Q0",3823859301u);
	printf("%-106p%--%%---16.39i%-62.45s%032.34u\n" ,
		(void*)4820041568133212049lu,1496653732,"78iTF|2mbbziDh\n0^?Q0",3823859301u);
}

int	main(void)
{
	test_char();
	test_str();
	test_int();
	test_unsigned_int();
	test_hex();
	test_pointer();
	test_binary();
	test_percent();
	test();
	return (0);
}
*/
