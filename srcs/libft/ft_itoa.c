/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 01:28:34 by reasuke           #+#    #+#             */
/*   Updated: 2023/09/04 12:29:31 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_digits(long n)
{
	int	digits;

	if (n == 0)
		return (1);
	digits = 0;
	while (n)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char	*ret;
	long	ln;
	int		digits;
	int		is_negative;

	ln = n;
	is_negative = ln < 0;
	digits = calc_digits(ln);
	ret = malloc(digits + is_negative + 1);
	if (!ret)
		return (NULL);
	if (is_negative)
	{
		ret[0] = '-';
		ln *= -1;
	}
	ret[digits + is_negative] = '\0';
	while (digits--)
	{
		ret[digits + is_negative] = '0' + ln % 10;
		ln /= 10;
	}
	return (ret);
}
