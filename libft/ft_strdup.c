/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 18:49:24 by sel-mort          #+#    #+#             */
/*   Updated: 2018/10/18 10:54:19 by sel-mort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*strdup;

	len = 0;
	while (*(s1 + len) != '\0')
		len++;
	strdup = (char *)malloc(sizeof(char) * (len + 1));
	if (strdup != NULL)
	{
		i = -1;
		while (++i < len)
			*(strdup + i) = *(s1 + i);
		*(strdup + i) = '\0';
	}
	return (strdup);
}
