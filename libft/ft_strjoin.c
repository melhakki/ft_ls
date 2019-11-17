/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 20:49:18 by sel-mort          #+#    #+#             */
/*   Updated: 2018/10/11 12:56:47 by sel-mort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len;
	char	*strjoin;

	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2) + 1;
		strjoin = (char *)malloc(sizeof(char) * len);
		if (strjoin != NULL)
		{
			i = -1;
			while (*(s1 + ++i) != '\0')
				*(strjoin + i) = *(s1 + i);
			len = -1;
			while (*(s2 + ++len) != '\0')
				*(strjoin + i++) = *(s2 + len);
			*(strjoin + i) = '\0';
		}
		return (strjoin);
	}
	return (NULL);
}
