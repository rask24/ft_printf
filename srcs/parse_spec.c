/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:17:21 by reasuke           #+#    #+#             */
/*   Updated: 2023/10/03 15:51:56 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_flags(t_format_spec *fs, t_format_result *fr)
{
	char		*ptr;
	ptrdiff_t	index;

	while (true)
	{
		ptr = ft_strchr(FLAGS, *fr->format);
		if (!ptr)
			break ;
		index = ptr - FLAGS;
		fs->flag |= 1 << index;
		fr->format++;
	}
}

static void	parse_width(t_format_spec *fs, t_format_result *fr, va_list *ap)
{
	if (*fr->format == '*')
	{
		fs->width = va_arg(*ap, int);
		if (fs->width < 0)
		{
			fs->width = -fs->width;
			fs->flag |= FLAG_MINUS;
		}
		fr->format++;
	}
	else
	{
		fs->width = ft_atoi(fr->format);
		while (ft_isdigit(*fr->format))
			fr->format++;
	}
}

static void	parse_precision(t_format_spec *fs, t_format_result *fr, va_list *ap)
{
	if (*fr->format == '.')
	{
		fr->format++;
		if (*fr->format == '*')
		{
			fs->precision = va_arg(*ap, int);
			if (fs->precision < 0)
				fs->precision = PREC_NONE;
			fr->format++;
		}
		else
		{
			fs->precision = ft_atoi(fr->format);
			while (ft_isdigit(*fr->format))
				fr->format++;
		}
	}
}

static void	parse_specifier(t_format_spec *fs, t_format_result *fr)
{
	if (!ft_strncmp(fr->format, "ll", 2))
		fs->size = SIZE_LL;
	else if (!ft_strncmp(fr->format, "l", 1))
		fs->size = SIZE_L;
	else if (!ft_strncmp(fr->format, "hh", 2))
		fs->size = SIZE_HH;
	else if (!ft_strncmp(fr->format, "h", 1))
		fs->size = SIZE_H;
	while (*fr->format == 'l' || *fr->format == 'h')
		fr->format++;
	fs->specifier = *fr->format;
}

void	parse_spec(t_format_spec *fs, t_format_result *fr, va_list *ap)
{
	fr->format++;
	parse_flags(fs, fr);
	parse_width(fs, fr, ap);
	if (fs->flag & FLAG_MINUS && fs->flag & FLAG_ZERO)
		fs->flag &= ~FLAG_ZERO;
	parse_precision(fs, fr, ap);
	parse_specifier(fs, fr);
	fr->format++;
}
