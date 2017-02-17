/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcrivenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 13:52:11 by vcrivenc          #+#    #+#             */
/*   Updated: 2016/12/16 14:26:15 by vcrivenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char		*print_char(char e, t_flags *flags, va_list *args)
{
	char c;
	char *str;

	str = NULL;
	if (e == 'c')
	{
		c = (char)va_arg(*args, int);
		str = char_to_str(c, 1);
		flags->length = 1;
	}
	else if (e == '%')
	{
		str = char_to_str('%', 1);
		flags->length = 1;
		flags->precision = 0;
	}
	return (str);
}

char		*print_chars(const char *expr, va_list *args, int i, t_flags *flags)
{
	char	*str;

	str = NULL;
	if (expr[i] == 's')
	{
		str = va_arg(*args, char*);
		if (str == NULL)
		{
			str = dynamic_string("(null)", 6);
			flags->length = 6;
		}
		else
		{
			flags->length = ft_strlen(str);
			str = dynamic_string(str, flags->length);
		}
	}
	else
		str = print_char(expr[i], flags, args);
	if (flags->precision > flags->length)
		flags->precision = flags->length;
	return (str);
}

char		*u_ints(const char *expr, va_list *args, int i, t_flags *f)
{
	char	*str;
	int		q;

	q = ((expr[i] == 'x' || expr[i] == 'p') ? 1 : 0);
	if (expr[i] == 'O' || expr[i] == 'U')
		str = u_base(va_arg(*args, long int), f->base, f, q);
	else if (expr[i - 1] == 'h')
		if (expr[i - 2] == 'h')
			str = u_base((unsigned char)va_arg(*args, int), f->base, f, q);
		else
			str = u_base((unsigned short)va_arg(*args, int), f->base, f, q);
	else if (expr[i - 1] == 'l')
		if (expr[i - 2] == 'l')
			str = u_base(va_arg(*args, unsigned long long), f->base, f, q);
		else
			str = u_base(va_arg(*args, unsigned long), f->base, f, q);
	else if (expr[i - 1] == 'j')
		str = u_base(va_arg(*args, uintmax_t), f->base, f, q);
	else if (expr[i - 1] == 'z')
		str = u_base(va_arg(*args, size_t), f->base, f, q);
	else if (expr[i] == 'p')
		str = u_base(((long)(unsigned *)va_arg(*args, void *)), f->base, f, q);
	else
		str = u_base(va_arg(*args, unsigned int), f->base, f, q);
	return (str);
}

char		*ints(const char *expr, va_list *args, int i, t_flags *flags)
{
	char *str;

	if (expr[i] == 'D')
		str = itoa_base(va_arg(*args, long int), 10, flags);
	else if (expr[i - 1] == 'h')
		if (expr[i - 2] == 'h')
			str = itoa_base((signed char)va_arg(*args, int), 10, flags);
		else
			str = itoa_base((short int)va_arg(*args, int), 10, flags);
	else if (expr[i - 1] == 'l')
		if (expr[i - 2] == 'l')
			str = itoa_base(va_arg(*args, long long int), 10, flags);
		else
			str = itoa_base(va_arg(*args, long int), 10, flags);
	else if (expr[i - 1] == 'j')
		str = itoa_base(va_arg(*args, intmax_t), 10, flags);
	else if (expr[i - 1] == 'z')
		str = itoa_base(va_arg(*args, size_t), 10, flags);
	else
		str = itoa_base(va_arg(*args, int), 10, flags);
	if (str[0] == '-' || flags->plus == 1)
		flags->space = 0;
	return (str);
}

void		put_prefix(t_flags *flags, char c, char *str)
{
	int len;

	if (str[0] == '-')
		ft_putchar('-');
	else if (flags->plus == 1)
		ft_putchar('+');
	else if ((flags->htag == 1 && !(str[0] == '0'
					&& str[1] == '\0')) || c == 'p')
	{
		if (c == 'x' || c == 'p')
			ft_putstr_len("0x", 2);
		else if (c == 'X')
			ft_putstr_len("0X", 2);
		else if (c == 'O' || c == 'o')
			ft_putchar('0');
	}
	if (str[0] == '0' && str[1] == '\0' && flags->precision == 0
			&& !((c == 'o' || c == 'O') && flags->htag == 1))
		flags->length = 0;
	len = flags->length - (str[0] == '-');
	flags->precision -= len;
	if (len != 0 && flags->precision > 0)
		put_padd('0', flags->precision);
}
