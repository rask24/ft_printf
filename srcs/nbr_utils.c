/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:48:21 by reasuke           #+#    #+#             */
/*   Updated: 2023/10/02 12:06:07 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_base_rec(uintmax_t uim_nb, size_t radix, const char *base)
{
	if (uim_nb / radix)
		ft_putnbr_base_rec(uim_nb / radix, radix, base);
	ft_putchar_fd(base[uim_nb % radix], STDOUT_FILENO);
}

void	ft_putnbr_base(intmax_t nb, const char *base, bool is_signed)
{
	uintmax_t	uim_nb;
	size_t		radix;

	radix = ft_strlen(base);
	if (radix < 2 || !base)
		return ;
	if (nb < 0 && is_signed)
		uim_nb = -nb;
	else
		uim_nb = nb;
	ft_putnbr_base_rec(uim_nb, radix, base);
}

int	digits_base(intmax_t nb, size_t radix, bool is_signed)
{
	uintmax_t	uim_nb;
	int			digits;

	if (nb == 0)
		return (1);
	if (nb < 0 && is_signed)
		uim_nb = -nb;
	else
		uim_nb = nb;
	digits = 0;
	while (uim_nb)
	{
		uim_nb /= radix;
		digits++;
	}
	return (digits);
}

int	ft_max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}
