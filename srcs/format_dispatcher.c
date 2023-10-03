/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_dispatcher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:13:31 by reasuke           #+#    #+#             */
/*   Updated: 2023/10/03 16:16:19 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	signed_integer_dispatcher(
		t_format_spec *fs, t_format_result *fr, va_list *ap)
{
	if (fs->size == SIZE_NONE)
		print_integer(va_arg(*ap, int), fs, fr);
	else if (fs->size == SIZE_L)
		print_integer(va_arg(*ap, long), fs, fr);
	else if (fs->size == SIZE_LL)
		print_integer(va_arg(*ap, long long), fs, fr);
	else if (fs->size == SIZE_H)
		print_integer((short)va_arg(*ap, int), fs, fr);
	else if (fs->size == SIZE_HH)
		print_integer((char)va_arg(*ap, int), fs, fr);
}

static void	unsigned_integer_dispatcher(
		t_format_spec *fs, t_format_result *fr, va_list *ap)
{
	if (fs->size == SIZE_NONE)
		print_integer(va_arg(*ap, unsigned int), fs, fr);
	else if (fs->size == SIZE_L)
		print_integer(va_arg(*ap, unsigned long), fs, fr);
	else if (fs->size == SIZE_LL)
		print_integer(va_arg(*ap, unsigned long long), fs, fr);
	else if (fs->size == SIZE_H)
		print_integer((unsigned short)va_arg(*ap, int), fs, fr);
	else if (fs->size == SIZE_HH)
		print_integer((unsigned char)va_arg(*ap, int), fs, fr);
}

void	format_dispatcher(
			t_format_spec *fs, t_format_result *fr, va_list *ap)
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
		signed_integer_dispatcher(fs, fr, ap);
	else if (ft_strchr("uxX", fs->specifier))
		unsigned_integer_dispatcher(fs, fr, ap);
	else if (fs->specifier == 'p')
		print_address(va_arg(*ap, uintptr_t), fs, fr);
}

