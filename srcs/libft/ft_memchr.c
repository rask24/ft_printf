/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 00:54:42 by reasuke           #+#    #+#             */
/*   Updated: 2023/09/24 16:10:31 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*u;

	u = (const unsigned char *)s;
	while (n--)
	{
		if (*u == (unsigned char)c)
			return ((void *)u);
		u++;
	}
	return (NULL);
}
