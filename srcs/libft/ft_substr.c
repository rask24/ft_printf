/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 12:34:33 by reasuke           #+#    #+#             */
/*   Updated: 2023/09/05 17:38:17 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	s_len;
	size_t	ret_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	if (len < s_len - start + 1)
		ret_len = len;
	else
		ret_len = s_len - start + 1;
	ret = malloc(ret_len + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s + start, ret_len + 1);
	return (ret);
}
