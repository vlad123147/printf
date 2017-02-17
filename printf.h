/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcrivenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 11:42:10 by vcrivenc          #+#    #+#             */
/*   Updated: 2016/12/16 15:21:18 by vcrivenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>

# define MIN(a, b) (a > b) ? b : a
# define MAX(a, b) (a > b) ? a : b
# define INITI int i = 0
# define INITIM int i = -1
# define INITF int f = 0

typedef	struct		s_flags
{
	unsigned char	min :1;
	unsigned char	plus :1;
	unsigned char	zero :1;
	unsigned char	space :1;
	unsigned char	htag :1;
	unsigned char	base;
	int				width;
	int				precision;
	int				length;
}					t_flags;

int					g_a;
void				ft_putchar(char c);
void				ft_putwchar(wchar_t c);
int					is_digit(char c);
int					ft_strlen(char *c);
int					ft_wstrlen(wchar_t *str);
void				ft_putstr_len(const char *i, int c);
int					is_flag(char c);
int					is_spec(char c);
int					is_legal(char c);
void				ft_reverse(char *c, int i);
char				*u_base(unsigned long long nb, size_t t, t_flags *f, int q);
char				*itoa_base(long long int nb, size_t q, t_flags *t);
char				*char_to_str(char c, int q);
int					ft_atoi(const char *s);
void				get_prec(const char *s, char e, t_flags *f, va_list *l);
void				get_width(const char *s, char e, t_flags *f, va_list *l);
t_flags				*new_flags(t_flags *t);
t_flags				*get_flags(const char *str, char c, va_list *l);
void				put_padd(char c, int len);
char				*dynamic_string(const char *s, int q);
int					nbr_bits(wchar_t w);
void				ft_putwstr(wchar_t *w, int i, t_flags *f);
wchar_t				*get_wstr(const char *w, va_list *l, int *i, t_flags *t);
wchar_t				*char_to_wchar(char	*str, int q);
void				w_s_c(const char *q, va_list *a, int o, t_flags *t);
char				*print_char(char e, t_flags *f, va_list *l);
char				*print_chars(const char *r, va_list *l, int q, t_flags *f);
char				*u_ints(const char *s, va_list *l, int q, t_flags *f);
char				*ints(const char *s, va_list *l, int q, t_flags *f);
void				put_prefix(t_flags *f, char c, char *s);
int					get_prefix_size(t_flags *f, char c, char *s);
void				format_right(t_flags *f, char *s, char c);
void				format_left(t_flags *f, char *s, char c);
char				*non_unicode(const char *s, va_list *q, t_flags *l, int *i);
int					print_expression(const char *s, va_list *l);
int					ft_printf(const char *restrict str, ...);

#endif
