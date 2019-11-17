/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppliment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 23:50:37 by melhakki          #+#    #+#             */
/*   Updated: 2019/09/23 22:14:25 by melhakki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

long long		ft_get_nbrcount(long long nbr)
{
	if (nbr < 10)
		return (1);
	else
		return (1 + ft_get_nbrcount(nbr / 10));
}

void			ft_init_len(t_maxlen **len)
{
	(*len)->maxuser = 0;
	(*len)->maxgroup = 0;
	(*len)->maxsize = 0;
	(*len)->maxlink = 0;
	(*len)->maxmin = 0;
	(*len)->maxmaj = 0;
	(*len)->b = 0;
}

void			ft_get_maxlen(t_maxlen **len, t_file *file)
{
	ft_init_len(len);
	while (file)
	{
		if (ft_strlen(file->info->user) > (*len)->maxuser)
			(*len)->maxuser = ft_strlen(file->info->user);
		if (ft_strlen(file->info->group) > (*len)->maxgroup)
			(*len)->maxgroup = ft_strlen(file->info->group);
		if (ft_get_nbrcount(file->info->size) > (long long)(*len)->maxsize)
			(*len)->maxsize = ft_get_nbrcount(file->info->size);
		if (ft_get_nbrcount(file->info->nlink) > (long long)(*len)->maxlink)
			(*len)->maxlink = ft_get_nbrcount(file->info->nlink);
		if (*(file->info->perms) == 'b' || *(file->info->perms) == 'c')
		{
			if (ft_get_nbrcount(file->info->maj) > (long long)(*len)->maxmaj)
				(*len)->maxmaj = ft_get_nbrcount(file->info->maj);
			if (ft_get_nbrcount(file->info->min) > (long long)(*len)->maxmin)
				(*len)->maxmin = ft_get_nbrcount(file->info->min);
			(*len)->b = 1;
		}
		file = file->next;
	}
}

void			ft_print_errors(char **args)
{
	int				i;
	struct stat		s;

	i = -1;
	while (*(args + ++i))
		if (lstat(*(args + i), &s) != 0)
			ft_stat_errors(*(args + i));
}

t_file			*ft_get_files(int options, char **args, int *nbdir)
{
	t_file		*ffile;
	t_maxlen	*len;

	ffile = NULL;
	*nbdir = 0;
	if (!(len = (t_maxlen *)malloc(sizeof(t_maxlen))))
		return (NULL);
	if ((ffile = ft_files(options, args)))
	{
		(*nbdir)++;
		ft_get_maxlen(&len, ffile);
		ft_sort_files(options, &ffile);
		ft_print_list(options, ffile, len);
		ft_free_files(&ffile);
		if (options & D)
		{
			free(len);
			len = NULL;
			exit(0);
		}
	}
	free(len);
	len = NULL;
	return (ffile);
}
