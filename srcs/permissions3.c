/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permitions3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:16:05 by melhakki          #+#    #+#             */
/*   Updated: 2019/09/23 15:30:49 by sel-mort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_get_full_path(char *path, char *fname)
{
	char	*tmppath;
	char	*full_path_name;

	if (ft_strcmp(path, "/") == 0)
		return (ft_strjoin("/", fname));
	tmppath = ft_strjoin(path, "/");
	full_path_name = ft_strjoin(tmppath, fname);
	ft_strdel(&tmppath);
	return (full_path_name);
}

void		ft_fill_extra_info(t_file **finfo, struct stat s, int *specf)
{
	(*finfo)->info->size = s.st_size;
	if (S_ISBLK(s.st_mode) || S_ISCHR(s.st_mode))
	{
		ft_get_dev(s, &(*finfo)->info);
		*specf = 1;
	}
	else
		ft_get_notdev(&(*finfo)->info);
	(*finfo)->info->mdate = ft_get_date('m', s);
	(*finfo)->info->mtime = s.st_mtime;
	(*finfo)->info->adate = ft_get_date('a', s);
}

char		*ft_get_link(char *path, char *fname)
{
	char		*tmppath;
	char		*tmpfullpath;
	char		*tmplnk;
	char		*link;

	tmppath = ft_strjoin(fname, " -> ");
	if (path)
		tmpfullpath = ft_get_full_path(path, fname);
	else
		tmpfullpath = ft_strdup(fname);
	tmplnk = ft_readlink(tmpfullpath);
	link = ft_strjoin(tmppath, tmplnk);
	ft_strdel(&tmppath);
	ft_strdel(&tmpfullpath);
	ft_strdel(&tmplnk);
	return (link);
}
