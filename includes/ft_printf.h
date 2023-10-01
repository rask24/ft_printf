/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:20:27 by reasuke           #+#    #+#             */
/*   Updated: 2023/10/02 03:34:08 by reasuke          ###   ########.fr       */
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
# include "../srcs/libft/libft.h"

// for debug
// TODO DELETE
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

# define STR_NULL "(null)"

# define HEX_PREFIX_LOWER "0x"
# define HEX_PREFIX_UPPER "0X"

// store format result
typedef struct s_format_result
{
	const char	*format;
	int			cnt;
}	t_format_result;

// format specification
typedef struct s_format_spec
{
	int		flag;
	int		width;
	int		precision;
	char	specifier;
}	t_format_spec;

// integer infomation for print
typedef struct s_integer_info
{
	bool	is_unsigned;
	char	*base;
	char	*prefix;
	int		digits;
	int		space_width;
	int		zero_width;
}	t_integer_info;

int		ft_printf(const char *format, ...);

void	print_char(char c, t_format_spec *fs, t_format_result *fr);
void	print_str(char *str, t_format_spec *fs, t_format_result *fr);

void	print_nbr(intmax_t nb, t_format_spec *fs, t_format_result *fr);

void	print_address(void *ptr, t_format_spec *fs, t_format_result *fr);

void	ft_putnbr_base(intmax_t nb, const char *base, bool is_unsigned);
// number of digits except for signature
int		digits_base(intmax_t nb, size_t radix, bool is_negative);
int		ft_max(int a, int b);

void	print_padding(char c, int len);

#endif
