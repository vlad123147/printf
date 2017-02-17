/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcrivenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 13:32:58 by vcrivenc          #+#    #+#             */
/*   Updated: 2016/12/16 14:03:58 by vcrivenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_putstr_len(const char *str, int len)
{
	write(1, str, len);
	g_a += len;
}

int		is_flag(char c)
{
	if (c == 's' || c == 'S' || c == 'd' || c == 'D' || c == 'i' || c == '%'
			|| c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x'
			|| c == 'X' || c == 'c' || c == 'C' || c == 'p' || c == '\0')
		return (1);
	return (0);
}

int		is_spec(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z' || c == '\0')
		return (1);
	return (0);
}

int		is_legal(char c)
{
	if (c == ' ' || c == '.' || c == '*' || c == '#' || c == '-' || c == '+')
		return (1);
	if (is_digit(c) || is_spec(c))
		return (1);
	return (0);
}

void	ft_reverse(char *str, int end)
{
	int		i;
	char	temp;

	i = 0;
	while (i < end)
	{
		temp = str[i];
		str[i] = str[end];
		str[end] = temp;
		i++;
		end--;
	}
}
