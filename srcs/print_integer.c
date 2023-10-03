/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:12:55 by reasuke           #+#    #+#             */
/*   Updated: 2023/10/03 16:49:24 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_width(
				t_integer_info *info, intmax_t nb, t_format_spec *fs)
{
	info->prefix_width = ft_strlen(info->prefix);
	if (nb == 0 && fs->precision == 0)
		info->digits = 0;
	else
		info->digits = digits_base(nb, ft_strlen(info->base), info->is_signed);
	if (fs->width && fs->precision == PREC_NONE && fs->flag & FLAG_ZERO)
	{
		info->space_width = 0;
		info->zero_width = ft_max(fs->width
				- info->digits - info->prefix_width, 0);
	}
	else
	{
		info->space_width = ft_max(fs->width
				- ft_max(fs->precision, info->digits) - info->prefix_width, 0);
		info->zero_width = ft_max(fs->precision - info->digits, 0);
	}
}

static void	init_prefix(t_integer_info *info, intmax_t nb, t_format_spec *fs)
{
	info->prefix = "";
	if (info->is_signed && nb < 0)
		info->prefix = "-";
	else if (info->is_signed && fs->flag & FLAG_PLUS)
		info->prefix = "+";
	else if (info->is_signed && fs->flag & FLAG_SPACE)
		info->prefix = " ";
	else if (fs->flag & FLAG_HASH
		&& !info->is_signed && fs->specifier == 'x' && nb)
		info->prefix = HEX_PREFIX_LOWER;
	else if (fs->flag & FLAG_HASH
		&& !info->is_signed && fs->specifier == 'X' && nb)
		info->prefix = HEX_PREFIX_UPPER;
}

static void	init_integer_info(
				t_integer_info *info, intmax_t nb, t_format_spec *fs)
{
	info->is_signed = fs->specifier == 'd' || fs->specifier == 'i';
	if (fs->specifier == 'x')
		info->base = HEX_BASE_LOEWR;
	else if (fs->specifier == 'X')
		info->base = HEX_BASE_UPPER;
	else if (fs->specifier == 'o')
		info->base = OCT_BASE;
	else
		info->base = DEC_BASE;
	init_prefix(info, nb, fs);
	init_width(info, nb, fs);
	if (fs->flag & FLAG_HASH && !info->is_signed && fs->specifier == 'o'
		&& !info->zero_width && (nb || fs->precision == 0))
	{
		info->prefix = OCT_PREFIX;
		info->prefix_width = 1;
		if (info->space_width)
			info->space_width--;
	}
}

void	print_integer(intmax_t nb, t_format_spec *fs, t_format_result *fr)
{
	t_integer_info	info;

	init_integer_info(&info, nb, fs);
	if (!(fs->flag & FLAG_MINUS) && info.space_width)
		print_padding(' ', info.space_width);
	if (*info.prefix)
		ft_putstr_fd(info.prefix, STDOUT_FILENO);
	if (info.zero_width)
		print_padding('0', info.zero_width);
	if (info.digits)
		ft_putnbr_base(nb, info.base, info.is_signed);
	if (fs->flag & FLAG_MINUS && info.space_width)
		print_padding(' ', info.space_width);
	fr->cnt += info.space_width
		+ info.prefix_width + info.zero_width + info.digits;
}

void	print_address(uintptr_t ptr, t_format_spec *fs, t_format_result *fr)
{
	int	space_width;
	int	digits;

	digits = digits_base(ptr, 16, false);
	if (fs->width)
		space_width = ft_max(fs->width - (digits + 2), 0);
	else
		space_width = 0;
	if (!(fs->flag & FLAG_MINUS) && space_width)
		print_padding(' ', space_width);
	ft_putstr_fd(HEX_PREFIX_LOWER, STDOUT_FILENO);
	ft_putnbr_base(ptr, HEX_BASE_LOEWR, false);
	if (fs->flag & FLAG_MINUS && space_width)
		print_padding(' ', space_width);
	fr->cnt += ft_max(fs->width, digits + 2);
}
