/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcrivenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 13:38:21 by vcrivenc          #+#    #+#             */
/*   Updated: 2016/12/16 14:20:46 by vcrivenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void		get_width(const char *str, char e, t_flags *flags, va_list *args)
{
	int nb;
	int f;

	f = 0;
	INITIM;
	while (is_flag(str[++i]) == 0)
	{
		if (str[i] == '.')
			break ;
		if (str[i] == '*')
		{
			nb = va_arg(*args, int);
			if (nb < 0)
			{
				flags->min = 1;
				nb = -nb;
			}
			flags->width = nb;
		}
		if (f == 0 && is_digit(str[i]) && (f = 1))
			flags->width = ft_atoi(str + i);
	}
	get_prec(str, e, flags, args);
}

t_flags		*new_flags(t_flags *flags)
{
	flags->min = 0;
	flags->plus = 0;
	flags->zero = 0;
	flags->space = 0;
	flags->htag = 0;
	flags->width = -1;
	flags->precision = -1;
	flags->length = 0;
	flags->base = 10;
	return (flags);
}

t_flags		*get_flags(const char *str, char e, va_list *args)
{
	char	c;
	t_flags	*flags;

	flags = new_flags(malloc(sizeof(t_flags)));
	INITI;
	while (is_flag(c = str[++i]) == 0 &&
			c != '.' && !(c > '0' && c <= '9') && c != '*')
		if (c == '-' && !(flags->zero = 0))
			flags->min = 1;
		else if (c == '+' && (e == 'd' || e == 'D' || e == 'i'))
		{
			flags->plus = 1;
			flags->space = 0;
		}
		else if (c == '0' && flags->min == 0)
			flags->zero = 1;
		else if (c == ' ' && flags->plus == 0
				&& (e == 'd' || e == 'D' || e == 'i'))
			flags->space = 1;
		else if (c == '#')
			flags->htag = 1;
	get_width(str + i, e, flags, args);
	return (flags);
}

void		put_padd(char c, int len)
{
	char *padd;

	if (len < 0)
		return ;
	padd = char_to_str(c, len);
	ft_putstr_len(padd, len);
	free(padd);
}

char		*dynamic_string(const char *str, int len)
{
	char *res;

	if (str == NULL)
		return (NULL);
	res = (char*)malloc(sizeof(char) * len);
	INITIM;
	while (str[++i])
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}
