/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 01:21:14 by reasuke           #+#    #+#             */
/*   Updated: 2023/09/06 13:21:39 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*u_dst;
	unsigned char	*u_src;

	if (!dst && !src)
		return (dst);
	if (dst < src)
	{
		u_dst = (unsigned char *)dst;
		u_src = (unsigned char *)src;
		while (len--)
			*u_dst++ = *u_src++;
	}
	else
	{
		u_dst = (unsigned char *)dst + len;
		u_src = (unsigned char *)src + len;
		while (len--)
			*--u_dst = *--u_src;
	}
	return (dst);
}
