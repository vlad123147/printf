/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcrivenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 11:58:02 by vcrivenc          #+#    #+#             */
/*   Updated: 2016/12/16 14:48:59 by vcrivenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char		*non_unicode(const char *e, va_list *args, t_flags *flags, int *i)
{
	char *str;
	char c;

	if ((c = e[*i]) == 's' || c == 'c' || c == '%')
		str = print_chars(e, args, *i, flags);
	else if (c == 'd' || c == 'D' || c == 'i')
		str = ints(e, args, *i, flags);
	else if (c == 'b' && (flags->base = 2))
		str = u_ints(e, args, *i, flags);
	else if ((c == 'o' || c == 'O') && (flags->base = 8))
		str = u_ints(e, args, *i, flags);
	else if ((c == 'u' || c == 'U') && (flags->base = 10))
		str = u_ints(e, args, *i, flags);
	else if ((c == 'x' || c == 'X' || c == 'p') && (flags->base = 16))
		str = u_ints(e, args, *i, flags);
	else
	{
		str = char_to_str(c, 1);
		if (c == '\0' && ((*i)--))
			flags->length = 0;
		else
			flags->length = 1;
	}
	return (str);
}

int			print_expression(const char *expr, va_list *args)
{
	int		i;
	char	c;
	char	*str;
	t_flags	*flags;

	i = 1;
	while (is_flag(expr[i]) == 0 && is_legal(expr[i]))
		i++;
	c = expr[i];
	flags = get_flags(expr, c, args);
	if (((c == 's' || c == 'c') && expr[i - 1] == 'l') || c == 'S' || c == 'C')
		w_s_c(expr, args, i, flags);
	else
	{
		str = non_unicode(expr, args, flags, &i);
		if (flags->min == 1)
			format_right(flags, str, c);
		else
			format_left(flags, str, c);
		free(str);
	}
	free(flags);
	return (i + 1);
}

int			ft_printf(const char *restrict str, ...)
{
	va_list	args;
	int		i;

	va_start(args, str);
	g_a = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '%')
			ft_putchar(str[i++]);
		else
			i += print_expression(str + i, &args);
	}
	va_end(args);
	return (g_a);
}
