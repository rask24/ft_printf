/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 16:18:20 by reasuke           #+#    #+#             */
/*   Updated: 2023/09/29 12:15:02 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define LOWER_BASE "0123456789abcdefghijklmnopqrstuvwxyz"
#define UPPER_BASE "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define MAX_OVERFLOW 0b01
#define MIN_OVERFLOW 0b10

typedef struct s_conv_spec{
	const char	*str;
	char		**endptr;
	long		nb;
	int			base;
	int			sign;
	int			digit_cnt;
	int			overflow;
}	t_conv_spec;

static int	parse_prefix(t_conv_spec *sp)
{
	ptrdiff_t	index;
	char		*ptr;

	if (!ft_strncmp(sp->str, "0x", 2))
	{
		index = -1;
		ptr = ft_strchr(UPPER_BASE, sp->str[2]);
		if (ptr)
			index = ptr - UPPER_BASE;
		ptr = ft_strchr(LOWER_BASE, sp->str[2]);
		if (ptr)
			index = ptr - LOWER_BASE;
		if (index < 0 || sp->base <= index)
		{
			sp->digit_cnt++;
			sp->str++;
			return (0);
		}
		sp->digit_cnt++;
		sp->str += 2;
	}
	return (1);
}

static void	convert_str_to_long(t_conv_spec *sp)
{
	ptrdiff_t	index;
	char		*ptr;

	if (sp->base == 16 && !parse_prefix(sp))
		return ;
	while (1)
	{
		index = -1;
		ptr = ft_strchr(UPPER_BASE, *sp->str);
		if (ptr)
			index = ptr - UPPER_BASE;
		ptr = ft_strchr(LOWER_BASE, *sp->str);
		if (ptr)
			index = ptr - LOWER_BASE;
		if (index < 0 || sp->base <= index)
			break ;
		if (sp->sign * sp->nb > (LONG_MAX - index) / sp->base && !sp->overflow)
			sp->overflow = MAX_OVERFLOW;
		if (sp->sign * sp->nb < (LONG_MIN + index) / sp->base && !sp->overflow)
			sp->overflow = MIN_OVERFLOW;
		sp->nb = sp->nb * sp->base + index;
		sp->digit_cnt++;
		sp->str++;
	}
}

static int	init_conv_spec(t_conv_spec *sp,
				const char *str, char **endptr, int base)
{
	sp->str = str;
	sp->endptr = endptr;
	if (sp->endptr)
		*sp->endptr = (char *)str;
	sp->nb = 0;
	sp->sign = 1;
	sp->digit_cnt = 0;
	sp->overflow = 0b00;
	if (!(base == 0 || (2 <= base && base <= 36)))
		return (0);
	while (*sp->str == ' ' || ('\t' <= *sp->str && *sp->str <= '\r'))
		sp->str++;
	if (*sp->str == '+' || *sp->str == '-')
		if (*sp->str++ == '-')
			sp->sign *= -1;
	if (base)
		sp->base = base;
	else if (*sp->str == '0' && (sp->str[1] == 'x' || sp->str[1] == 'X'))
		sp->base = 16;
	else if (*sp->str == '0')
		sp->base = 8;
	else
		sp->base = 10;
	return (1);
}

static long	ft_strtol(const char *str, char **endptr, int base)
{
	t_conv_spec	sp;

	if (init_conv_spec(&sp, str, endptr, base))
		convert_str_to_long(&sp);
	if (sp.endptr && sp.digit_cnt)
		*sp.endptr = (char *)(sp.str);
	if (sp.overflow)
		errno = ERANGE;
	else if (sp.digit_cnt == 0)
		errno = EINVAL;
	if (sp.overflow == MAX_OVERFLOW)
		return (LONG_MAX);
	else if (sp.overflow == MIN_OVERFLOW)
		return (LONG_MIN);
	return (sp.sign * sp.nb);
}

int	ft_atoi(const char *str)
{
	return (ft_strtol(str, NULL, 10));
}
