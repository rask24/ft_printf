/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:59:33 by reasuke           #+#    #+#             */
/*   Updated: 2023/10/03 16:16:35 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
			fs = (t_format_spec){
				FLAG_NONE, WIDTH_NONE, PREC_NONE, SIZE_NONE, '\0'};
			parse_spec(&fs, &fr, &ap);
			format_dispatcher(&fs, &fr, &ap);
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
