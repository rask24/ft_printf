/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:20:27 by reasuke           #+#    #+#             */
/*   Updated: 2023/09/14 19:12:48 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include "libft.h"

// for debug
# include <stdio.h>
# include <limits.h>
# ifdef __APPLE__
#  include <malloc/malloc.h>
# elif defined(__linux__)
#  include <malloc.h>
# endif

# define DEC_BASE       "0123456789"
# define HEX_BASE_UPPER "0123456789ABCDEF"
# define HEX_BASE_LOEWR "0123456789abcdef"

# define FLAGS "-+ #0"

# define FLAG_NONE  0b00000
# define FLAG_MINUS 0b00001
# define FLAG_PLUS  0b00010
# define FLAG_SPACE 0b00100
# define FLAG_HASH  0b01000
# define FLAG_ZERO  0b10000

# define WIDTH_NONE 0

# define PREC_NONE -1

# ifdef __APPLE__
#  define STR_NULL "(null)"
# else
#  define STR_NULL "(nil)"
# endif

// store format result
typedef struct s_format_log
{
	const char	*format;
	int			cnt;
}	t_format_log;

// format specification
typedef struct s_format_spec
{
	int		flag;
	int		width;
	int		precision;
	char	specifier;
}	t_format_spec;

int		ft_printf(const char *format, ...);

void	print_char(char c, t_format_spec *fs, t_format_log *fl);
void	print_str(char *str, t_format_spec *fs, t_format_log *fl);

void	ft_putnbr_base(intmax_t nb, const char *base, bool is_unsigned);

void	print_padding(char c, int len);

#endif
