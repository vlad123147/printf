/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcrivenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 13:35:01 by vcrivenc          #+#    #+#             */
/*   Updated: 2016/12/16 14:21:40 by vcrivenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*u_base(unsigned long long nb, size_t base, t_flags *flags, int x)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * 75);
	if (nb == 0)
		str[i++] = '0';
	while (nb)
	{
		if (!x)
			str[i++] = "0123456789ABCDEF"[nb % base];
		else
			str[i++] = "0123456789abcdef"[nb % base];
		nb = nb / base;
	}
	str[i] = '\0';
	flags->length = i;
	ft_reverse(str, i - 1);
	return (str);
}

char	*itoa_base(long long int nb, size_t base, t_flags *flags)
{
	char	*str;
	int		sign;

	sign = 0;
	INITI;
	str = (char *)malloc(sizeof(char) * 75);
	if (nb == 0)
		str[i++] = '0';
	if (nb < 0)
	{
		if (base == 10)
			sign = 1;
		nb = -nb;
	}
	while (nb)
	{
		str[i++] = "0123456789ABCDEF"[nb % base];
		nb = nb / base;
	}
	if (sign)
		str[i++] = '-';
	str[i] = '\0';
	flags->length = i;
	ft_reverse(str, i - 1);
	return (str);
}

char	*char_to_str(char c, int n)
{
	char	*str;
	int		i;

	if (n < 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (n + 1));
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	return (str);
}

int		ft_atoi(const char *str)
{
	int			i;
	long long	nb;

	nb = 0;
	i = 0;
	while (str[i] && is_digit(str[i]) == 1)
		nb = nb * 10 + str[i++] - '0';
	return (nb);
}

void	get_prec(const char *str, char e, t_flags *flags, va_list *args)
{
	INITIM;
	INITF;
	while (is_flag(str[++i]) == 0)
		if (str[i] == '.')
		{
			if (str[++i] == '*')
			{
				if ((flags->precision = va_arg(*args, int)) < 0)
				{
					flags->min = 1;
					flags->precision = flags->width;
				}
				break ;
			}
			else if (++f)
			{
				flags->precision = is_digit(str[i]) ? ft_atoi(str + i) : 0;
				if (e != 'c' && e != 's' && e != '%' && e != 'S'
						&& (is_legal(e) == 1 || is_flag(e)))
					flags->zero = 0;
			}
		}
	flags->htag = (flags->precision > 0 && e == 'o') ? 0 : flags->htag;
}
