/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ascii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:02:59 by reasuke           #+#    #+#             */
/*   Updated: 2023/09/14 19:13:14 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(char c, t_format_spec *fs, t_format_log *fl)
{
	if (fs->width && !(fs->flag & FLAG_MINUS) && !(fs->flag & FLAG_ZERO))
		print_padding(' ', fs->width - 1);
	else if (fs->width && !(fs->flag & FLAG_MINUS) && fs->flag & FLAG_ZERO)
		print_padding('0', fs->width - 1);
	ft_putchar_fd(c, STDOUT_FILENO);
	if (fs->width && fs->flag & FLAG_MINUS)
		print_padding(' ', fs->width - 1);
	if (fs->width)
		fl->cnt += fs->width;
	else
		fl->cnt++;
}

void	print_str(char *str, t_format_spec *fs, t_format_log *fl)
{
	int	str_len;

	str_len = ft_strlen(str);
	if (fs->precision != PREC_NONE && fs->precision < str_len)
		str_len = fs->precision;
	if (fs->width && !(fs->flag & FLAG_MINUS) && !(fs->flag & FLAG_ZERO))
		print_padding(' ', fs->width - str_len);
	else if (fs->width && !(fs->flag & FLAG_MINUS) && fs->flag & FLAG_ZERO)
		print_padding('0', fs->width - str_len);
	write(STDOUT_FILENO, str, str_len);
	if (fs->width && fs->flag & FLAG_MINUS)
		print_padding(' ', fs->width - str_len);
	if (fs->width)
		fl->cnt += fs->width;
	else
		fl->cnt += str_len;
}