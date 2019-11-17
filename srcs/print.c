/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:17:09 by melhakki          #+#    #+#             */
/*   Updated: 2019/09/23 22:09:53 by melhakki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_print_space(size_t min, size_t max)
{
	while (min++ < max)
		ft_putchar(' ');
}

void		ft_putsstr(char *str, int sp)
{
	int		i;

	i = -1;
	while (++i < sp)
		ft_putchar(' ');
	ft_putstr(str);
}

void		ft_print_min_maj(t_file *file, t_maxlen *len)
{
	size_t		size;

	size = len->maxmaj - ft_get_nbrcount((long long)file->info->maj);
	ft_print_space(0, size);
	ft_putlong((long long)file->info->maj);
	ft_putstr(", ");
	size = len->maxmin - ft_get_nbrcount((long long)file->info->min);
	ft_print_space(0, size);
	ft_putlong((long long)file->info->min);
}

void		ft_putstrname(char *str)
{
	while (*str != ' ' && *str)
		ft_putchar(*str++);
}

void		ft_print_list(int options, t_file *file, t_maxlen *len)
{
	while (file)
	{
		if (!(options & A))
		{
			if (*(file->info->filename) == '.')
			{
				file = file->next;
				continue ;
			}
		}
		if (options & L)
			ft_display_fileinfo(options, file, len);
		else
		{
			ft_color(file->info->perms, options);
			ft_putstrname(file->info->filename);
			ft_putstr("\e[39m\e[49m");
		}
		ft_putstr("\n");
		file = file->next;
	}
}
