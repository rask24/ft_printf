/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:59:33 by reasuke           #+#    #+#             */
/*   Updated: 2023/10/03 14:17:18 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	format_dispather(t_format_spec *fs,
				t_format_result *fr, va_list *ap)
{
	char	*str;

	if (fs->specifier == '%')
		print_char('%', fs, fr);
	else if (fs->specifier == 'c')
		print_char(va_arg(*ap, int), fs, fr);
	else if (fs->specifier == 's')
	{
		str = va_arg(*ap, char *);
		if (!str)
			str = STR_NULL;
		print_str(str, fs, fr);
	}
	else if (fs->specifier == 'd' || fs->specifier == 'i')
		print_integer(va_arg(*ap, int), fs, fr);
	else if (ft_strchr("uxX", fs->specifier))
		print_integer(va_arg(*ap, unsigned int), fs, fr);
	else if (fs->specifier == 'p')
		print_address(va_arg(*ap, uintptr_t), fs, fr);
}

int	ft_printf(const char *format, ...)
{
	va_list			ap;
	t_format_result	fr;
	t_format_spec	fs;

	fr = (t_format_result){format, 0};
	va_start(ap, format);
	while (*fr.format)
	{
		if (*fr.format == '%')
		{
			fs = (t_format_spec){FLAG_NONE, WIDTH_NONE, PREC_NONE, '\0'};
			parse_spec(&fs, &fr, &ap);
			format_dispather(&fs, &fr, &ap);
		}
		else
		{
			ft_putchar_fd(*fr.format, STDOUT_FILENO);
			fr.cnt++;
			fr.format++;
		}
	}
	va_end(ap);
	return (fr.cnt);
}
