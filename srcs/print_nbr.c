/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:12:55 by reasuke           #+#    #+#             */
/*   Updated: 2023/09/22 23:25:58 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_integer_info(t_integer_info *info,
				intmax_t nb, t_format_spec *fs)
{
	info->is_unsigned = !(fs->specifier == 'd' || fs->specifier == 'i');
	if (fs->specifier == 'x')
		info->base = HEX_BASE_LOEWR;
	else if (fs->specifier == 'X')
		info->base = HEX_BASE_UPPER;
	else
		info->base = DEC_BASE;
	info->prefix = "";
	if (fs->flag & FLAG_HASH && info->is_unsigned
		&& fs->specifier == 'x' && nb)
		info->prefix = HEX_PREFIX_LOWER;
	else if (fs->flag & FLAG_HASH && info->is_unsigned
		&& fs->specifier == 'X' && nb)
		info->prefix = HEX_PREFIX_UPPER;
	else if (!info->is_unsigned && nb < 0)
		info->prefix = "-";
	else if (!info->is_unsigned && fs->flag & FLAG_PLUS)
		info->prefix = "+";
	else if (!info->is_unsigned && fs->flag & FLAG_SPACE)
		info->prefix = " ";
	info->digits = digits_base(nb, ft_strlen(info->base), info->is_unsigned);
	info->space_width = fs->width
		- ft_max(fs->precision, info->digits) - ft_strlen(info->prefix);
	info->zero_width = fs->precision - info->digits;
}

void	print_nbr(intmax_t nb, t_format_spec *fs, t_format_result *fr)
{
	t_integer_info	info;

	init_integer_info(&info, nb, fs);
	if (!(fs->flag & FLAG_MINUS))
		print_padding(' ', info.space_width);
	if (*info.prefix)
		ft_putstr_fd(info.prefix, STDOUT_FILENO);
	print_padding('0', info.zero_width);
	ft_putnbr_base(nb, info.base, info.is_unsigned);
	if (fs->flag & FLAG_MINUS)
		print_padding(' ', info.space_width);
	if (info.space_width > 0)
		fr->cnt += info.space_width;
	if (*info.prefix)
		fr->cnt += ft_strlen(info.prefix);
	if (info.zero_width > 0)
		fr->cnt += info.zero_width;
	fr->cnt += info.digits;
}

void	print_address(void *ptr, t_format_spec *fs, t_format_result *fr)
{
	uintmax_t	address;

	address = (uintmax_t)ptr;
	(void)fs;
	ft_putstr_fd(HEX_PREFIX_LOWER, STDOUT_FILENO);
	ft_putnbr_base(address, HEX_BASE_LOEWR, true);
	fr->cnt += digits_base(address, ft_strlen(HEX_BASE_LOEWR), false)
		+ ft_strlen(HEX_PREFIX_LOWER);
}
