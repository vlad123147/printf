/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcrivenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 13:49:51 by vcrivenc          #+#    #+#             */
/*   Updated: 2016/12/16 14:22:38 by vcrivenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int			nbr_bits(wchar_t c)
{
	if (c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	else if (c <= 0x10FFFF)
		return (4);
	return (5);
}

void		ft_putwstr(wchar_t *s, int len, t_flags *flags)
{
	int		i;
	char	c;

	i = 0;
	while (i < len)
		flags->width -= nbr_bits(s[i++]);
	i = 0;
	if (flags->min == 1)
	{
		while (i < len)
			ft_putwchar(s[i++]);
		put_padd(' ', flags->width);
	}
	else
	{
		if (flags->width > 0)
		{
			c = flags->zero ? '0' : ' ';
			put_padd(c, flags->width);
		}
		while (i < len)
			ft_putwchar(s[i++]);
	}
}

wchar_t		*char_to_wchar(char *str, int len)
{
	wchar_t *res;

	INITIM;
	if (len < 0)
		return (NULL);
	res = (wchar_t *)malloc(sizeof(wchar_t) * (len + 1));
	while (++i < len)
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}

wchar_t		*get_wstr(const char *expr, va_list *args, int *i, t_flags *flags)
{
	wchar_t	*str;

	INITF;
	str = NULL;
	if ((expr[*i - 1] == 'l' && expr[*i] == 's') || expr[*i] == 'S')
	{
		str = va_arg(*args, wchar_t*);
		if (str == NULL && (f = 1))
		{
			str = char_to_wchar("(null)", 6);
			flags->length = 6;
		}
		else
			flags->length = ft_wstrlen(str);
	}
	else if ((expr[*i - 1] == 'l' && expr[*i] == 'c') || expr[*i] == 'C')
	{
		str = (wchar_t *)malloc(sizeof(wchar_t) * 2);
		str[0] = va_arg(*args, wint_t);
		str[1] = '\0';
		flags->length = 1;
		f = 1;
	}
	*i = f;
	return (str);
}

void		w_s_c(const char *expr, va_list *ag, int i, t_flags *f)
{
	wchar_t	*str;
	int		x;
	int		nb;

	str = get_wstr(expr, ag, &i, f);
	if (f->precision == 0 && str[0] != 0)
		f->length = 0;
	if (f->precision > 0)
	{
		x = 0;
		nb = 0;
		while (nb < f->precision && x < f->length)
		{
			nb += nbr_bits(str[x]);
			x++;
		}
		if (nb > f->precision)
			x--;
		f->length = x;
	}
	ft_putwstr(str, f->length, f);
	if (i)
		free(str);
}
