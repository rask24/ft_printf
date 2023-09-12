/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:49:30 by reasuke           #+#    #+#             */
/*   Updated: 2023/09/03 13:04:40 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	ret = malloc(s1_len + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, s1_len + 1);
	return (ret);
}
