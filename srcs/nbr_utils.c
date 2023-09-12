/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:48:21 by reasuke           #+#    #+#             */
/*   Updated: 2023/09/07 22:07:09 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_base_rec(uintmax_t l_nb, size_t radix, const char *base)
{
	if (l_nb / radix)
		ft_putnbr_base_rec(l_nb / radix, radix, base);
	ft_putchar_fd(base[l_nb % radix], 1);
}

void	ft_putnbr_base(intmax_t nb, const char *base, bool is_unsigned)
{
	uintmax_t	ul_nb;
	size_t		radix;

	radix = ft_strlen(base);
	if (radix < 2 || !base)
		return ;
	if (nb < 0 && !is_unsigned)
	{
		ul_nb = -nb;
		ft_putchar_fd('-', 1);
	}
	else
		ul_nb = nb;
	ft_putnbr_base_rec(ul_nb, radix, base);
}
