/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 21:24:54 by sel-mort          #+#    #+#             */
/*   Updated: 2018/10/09 11:41:08 by sel-mort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int	l;

	if (n < 0)
	{
		ft_putchar('-');
		l = n * -1;
	}
	else
		l = n;
	if (l >= 10)
	{
		ft_putnbr(l / 10);
		ft_putchar(l % 10 + '0');
	}
	else
		ft_putchar(l + '0');
}
