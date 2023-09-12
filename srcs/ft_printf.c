/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:59:33 by reasuke           #+#    #+#             */
/*   Updated: 2023/09/12 20:25:00 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_spec(t_format_spec *fs, t_format_log *fl)
{
	ptrdiff_t	index;

	fl->format++;
	while (true)
	{
		index = ft_strchr(FLAGS, *(fl->format)) - FLAGS;
		if (index < 0)
			break ;
		fs->flag |= 1 << index;
		fl->format++;
	}
	fs->width = ft_atoi(fl->format);
	while (ft_isdigit(*(fl->format)))
		fl->format++;
	if (*(fl->format) == '.')
	{
		fs->precision = ft_atoi(++(fl->format));
		while (ft_isdigit(*(fl->format)))
			fl->format++;
	}
	fs->specifier = *(fl->format);
	fl->format++;
}

void	format_dispather(t_format_spec *fs, t_format_log *fl, va_list ap)
{
	char	*tmp;

	if (fs->specifier == '%')
		print_char('%', fs, fl);
	else if (fs->specifier == 'c')
		print_char(va_arg(ap, int), fs, fl);
	else if (fs->specifier == 's')
	{
		tmp = va_arg(ap, char *);
		if (!tmp)
			tmp = STR_NULL;
		print_str(tmp, fs, fl);
	}
	else if (fs->specifier == 'd' || fs->specifier == 'i')
		ft_putnbr_base(va_arg(ap, int), DEC_BASE, false);
	else if (fs->specifier == 'u')
		ft_putnbr_base(va_arg(ap, unsigned int), DEC_BASE, true);
	else if (fs->specifier == 'x')
		ft_putnbr_base(va_arg(ap, unsigned int), HEX_BASE_LOEWR, true);
	else if (fs->specifier == 'X')
		ft_putnbr_base(va_arg(ap, unsigned int), HEX_BASE_UPPER, true);
}

int	ft_printf(const char *format, ...)
{
	va_list			ap;
	t_format_log	fl;
	t_format_spec	fs;

	fl = (t_format_log){format, 0};
	va_start(ap, format);
	while (*(fl.format))
	{
		if (*(fl.format) == '%')
		{
			fs = (t_format_spec){FLAG_NONE, WIDTH_NONE, PREC_NONE, '\0'};
			parse_spec(&fs, &fl);
			format_dispather(&fs, &fl, ap);
		}
		else
		{
			ft_putchar_fd(*fl.format, STDOUT_FILENO);
			fl.cnt++;
			fl.format++;
		}
	}
	va_end(ap);
	return (fl.cnt);
}
