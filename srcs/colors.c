/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhakki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 18:35:04 by melhakki          #+#    #+#             */
/*   Updated: 2019/09/24 15:34:07 by melhakki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_color_by_type(char type)
{
	if (type == 'l')
		ft_putstr("\e[35m");
	else if (type == 'd')
		ft_putstr("\e[96m");
	else if (type == 'b')
		ft_putstr("\e[46m\e[34m");
	else if (type == 'c')
		ft_putstr("\e[43m\e[34m");
	else if (type == 'p')
		ft_putstr("\e[40m\e[33m");
}

void	ft_color_by_perms(char *perms)
{
	if (perms[0] == 'd' && perms[8] == 'w')
		ft_putstr("\e[43m\e[30m");
	if (perms[0] == '-')
		if (perms[3] == 'x' || perms[6] == 'x' || perms[9] == 'x')
			ft_putstr("\e[31m");
}

void	ft_color(char *perms, int options)
{
	if (options & COLOR)
	{
		ft_color_by_type(perms[0]);
		ft_color_by_perms(perms);
	}
}

void	ft_split(char *name, char *perms, int options)
{
	int i;

	ft_putchar(' ');
	i = 0;
	while (name[i] && name[i] != ' ' &&
			name[i + 1] != '-' && name[i + 2] != '>')
	{
		ft_color(perms, options);
		ft_putchar(name[i]);
		i++;
	}
	ft_putstr("\e[39m\e[49m");
	ft_putstr(&name[i]);
}
