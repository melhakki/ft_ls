/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:32:48 by melhakki          #+#    #+#             */
/*   Updated: 2019/09/23 22:31:19 by melhakki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_print_path_info(int options, t_args *path, int count)
{
	if (path->next || count)
	{
		ft_putstr(path->pathname);
		ft_putstr(":\n");
	}
	if (path->file && options & L)
	{
		ft_putstr("total ");
		ft_putnbr(path->total);
		ft_putchar('\n');
	}
	if (path->info->info->perms[1] != 'r')
	{
		ft_putstr("ft_ls: ");
		ft_putstr(path->pathname);
		ft_putendl(": Permission denied");
	}
}

void		ft_stat_errors(char *arg)
{
	ft_putstr("ft_ls: ");
	ft_putstr(arg);
	ft_putstr(": ");
	ft_putendl(strerror(errno));
}

void		ft_putlong(long long nbr)
{
	if (nbr < 10)
		ft_putchar(nbr + 48);
	else
	{
		ft_putlong(nbr / 10);
		ft_putlong(nbr % 10);
	}
}

void		ft_display_extra_fileinfo(int options,
		int size, t_file *file, t_maxlen *len)
{
	if (len->b == 1)
	{
		if (*(file->info->perms) == 'b' || *(file->info->perms) == 'c')
			ft_print_min_maj(file, len);
		else
		{
			size = len->maxmaj + len->maxsize + 3;
			ft_print_space(0, size);
			ft_putlong((long long)file->info->size);
		}
	}
	else
		ft_putlong((long long)file->info->size);
	if (options & U)
		ft_putsstr(file->info->adate, 1);
	else
		ft_putsstr(file->info->mdate, 1);
	ft_split(file->info->filename, file->info->perms, options);
}

void		ft_display_fileinfo(int options, t_file *file, t_maxlen *len)
{
	size_t		size;

	ft_putsstr(file->info->perms, 0);
	size = len->maxlink - ft_get_nbrcount((long long)file->info->nlink);
	ft_print_space(0, size + 1);
	ft_putlong(file->info->nlink);
	size = len->maxuser - ft_strlen(file->info->user);
	if (!(options & G))
	{
		ft_putsstr(file->info->user, 1);
		ft_print_space(0, size);
		ft_putchar(' ');
	}
	size = len->maxgroup - ft_strlen(file->info->group);
	ft_putsstr(file->info->group, 1);
	ft_print_space(0, size);
	size = len->maxsize - ft_get_nbrcount((long long)file->info->size);
	ft_putstr("  ");
	ft_print_space(0, size);
	ft_display_extra_fileinfo(options, size, file, len);
}
