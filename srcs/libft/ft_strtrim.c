/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 23:01:26 by reasuke           #+#    #+#             */
/*   Updated: 2023/09/06 12:28:50 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*ret;
	long	begin;
	long	end;

	if (!s1 || !set)
		return (NULL);
	begin = 0;
	while (ft_strchr(set, s1[begin]))
		begin++;
	end = ft_strlen(s1) - 1;
	while (begin < end && ft_strchr(set, s1[end]))
		end--;
	if (end < begin)
		return (ft_strdup(""));
	ret = malloc(end - begin + 2);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1 + begin, end - begin + 2);
	return (ret);
}
