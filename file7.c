/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcrivenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 13:55:30 by vcrivenc          #+#    #+#             */
/*   Updated: 2016/12/16 14:30:37 by vcrivenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		get_prefix_size(t_flags *flags, char c, char *s)
{
	int i;

	if (c != 'S' && c != 's')
	{
		if (s[0] == '0' && s[1] == '\0' &&
				flags->precision == 0 && !((c == 'o' || c == 'O')
					&& flags->htag == 1))
			flags->length = 0;
	}
	else if (flags->precision != -1 && flags->length != 0)
		flags->length = flags->precision;
	if (flags->length != 0 && flags->precision >= flags->length)
		i = flags->precision - flags->length + (s[0] == '-');
	else
		i = 0;
	if (flags->plus == 1 && s[0] != '-')
		return (i + 1);
	else if ((flags->htag == 1 && !(s[0] == '0' && s[1] == '\0')) || c == 'p')
	{
		if (c == 'x' || c == 'X' || c == 'p')
			return (i + 2);
		else if (c == 'O' || c == 'o')
			return (i + 1);
	}
	return (i);
}

void	format_right(t_flags *f, char *str, char c)
{
	f->width = f->width - get_prefix_size(f, c, str) - f->length;
	put_prefix(f, c, str);
	if (str[0] == '-')
		ft_putstr_len(str + 1, f->length - 1);
	else
		ft_putstr_len(str, f->length);
	if (f->width > 0)
		put_padd(' ', f->width);
}

void	format_left(t_flags *fs, char *str, char c)
{
	INITF;
	if (fs->width == -1)
		f = 1;
	fs->width = fs->width - get_prefix_size(fs, c, str) - fs->length;
	if (fs->space == 1 && (f || fs->width > 0))
	{
		ft_putchar(' ');
		fs->width = fs->width - 1;
	}
	if (fs->zero == 1)
	{
		put_prefix(fs, c, str);
		put_padd('0', fs->width);
	}
	else
	{
		put_padd(' ', fs->width);
		put_prefix(fs, c, str);
	}
	if (str[0] == '-')
		ft_putstr_len(str + 1, fs->length - 1);
	else
		ft_putstr_len(str, fs->length);
}
