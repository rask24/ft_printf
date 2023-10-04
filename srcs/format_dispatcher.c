/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_dispatcher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:13:31 by reasuke           #+#    #+#             */
/*   Updated: 2023/10/04 16:44:44 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	signed_integer_dispatcher(
				t_format_spec *fs, t_format_result *fr, va_list *ap)
{
	if (fs->length == LENGTH_NONE)
		print_integer(va_arg(*ap, int), fs, fr);
	else if (fs->length == LENGTH_L)
		print_integer(va_arg(*ap, long), fs, fr);
	else if (fs->length == LENGTH_LL)
		print_integer(va_arg(*ap, long long), fs, fr);
	else if (fs->length == LENGTH_H)
		print_integer((short)va_arg(*ap, int), fs, fr);
	else if (fs->length == LENGTH_HH)
		print_integer((char)va_arg(*ap, int), fs, fr);
}

static void	unsigned_integer_dispatcher(
				t_format_spec *fs, t_format_result *fr, va_list *ap)
{
	if (fs->length == LENGTH_NONE)
		print_integer(va_arg(*ap, unsigned int), fs, fr);
	else if (fs->length == LENGTH_L)
		print_integer(va_arg(*ap, unsigned long), fs, fr);
	else if (fs->length == LENGTH_LL)
		print_integer(va_arg(*ap, unsigned long long), fs, fr);
	else if (fs->length == LENGTH_H)
		print_integer((unsigned short)va_arg(*ap, int), fs, fr);
	else if (fs->length == LENGTH_HH)
		print_integer((unsigned char)va_arg(*ap, int), fs, fr);
}

static void	n_dispatcher(
				t_format_spec *fs, t_format_result *fr, va_list *ap)
{
	if (fs->length == LENGTH_NONE)
		*va_arg(*ap, int *) = fr->cnt;
	else if (fs->length == LENGTH_L)
		*va_arg(*ap, long *) = fr->cnt;
	else if (fs->length == LENGTH_LL)
		*va_arg(*ap, long long *) = fr->cnt;
	else if (fs->length == LENGTH_H)
		*va_arg(*ap, short *) = fr->cnt;
	else if (fs->length == LENGTH_HH)
		*va_arg(*ap, signed char *) = fr->cnt;
}

void	format_dispatcher(
			t_format_spec *fs, t_format_result *fr, va_list *ap)
{
	if (fs->conversion == '%')
		print_char('%', fs, fr);
	else if (fs->conversion == 'c')
		print_char(va_arg(*ap, int), fs, fr);
	else if (fs->conversion == 's')
		print_str(va_arg(*ap, char *), fs, fr);
	else if (fs->conversion == 'd' || fs->conversion == 'i')
		signed_integer_dispatcher(fs, fr, ap);
	else if (ft_strchr("uxXo", fs->conversion))
		unsigned_integer_dispatcher(fs, fr, ap);
	else if (fs->conversion == 'p')
		print_address(va_arg(*ap, uintptr_t), fs, fr);
	else if (fs->conversion == 'n')
		n_dispatcher(fs, fr, ap);
}
