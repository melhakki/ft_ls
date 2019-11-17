/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 20:33:01 by sel-mort          #+#    #+#             */
/*   Updated: 2018/10/11 12:58:20 by sel-mort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*strsub;

	if (s)
	{
		if (!*s)
			return (NULL);
		strsub = (char *)malloc(len + 1);
		if (strsub != NULL)
		{
			i = -1;
			while (*(s + start + ++i) && i < len)
				*(strsub + i) = *(s + start + i);
			*(strsub + i) = '\0';
		}
		return (strsub);
	}
	return (NULL);
}
