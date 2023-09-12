/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 00:10:11 by reasuke           #+#    #+#             */
/*   Updated: 2023/09/05 17:36:21 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void			*ret;
	unsigned char	*u_dst;
	unsigned char	*u_src;

	if (!dst && !src)
		return (dst);
	ret = dst;
	u_dst = (unsigned char *)dst;
	u_src = (unsigned char *)src;
	while (n--)
		*u_dst++ = *u_src++;
	return (ret);
}
