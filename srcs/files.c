/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:41:31 by melhakki          #+#    #+#             */
/*   Updated: 2019/09/23 15:29:07 by sel-mort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*ft_fill_info(char *path, struct stat s, char *fname, int *specf)
{
	t_file		*finfo;
	char		*tmppath;

	if (!(finfo = (t_file *)malloc(sizeof(t_file))) ||
			!(finfo->info = (t_info *)malloc(sizeof(t_info))))
		return (NULL);
	if (S_ISLNK(s.st_mode))
		finfo->info->filename = ft_get_link(path, fname);
	else
		finfo->info->filename = ft_strdup(fname);
	if (path)
	{
		tmppath = ft_get_full_path(path, fname);
		finfo->info->perms = ft_get_perms(s.st_mode, tmppath);
		ft_strdel(&tmppath);
	}
	else
		finfo->info->perms = ft_get_perms(s.st_mode, fname);
	finfo->info->nlink = s.st_nlink;
	ft_get_user_group(s, &(finfo->info));
	finfo->info->size = s.st_size;
	ft_fill_extra_info(&finfo, s, specf);
	return (finfo);
}

t_file		*ft_add_file_l(t_file **ffile, t_file *file)
{
	t_file		*tmpfile;

	tmpfile = NULL;
	if (!*ffile)
	{
		*ffile = file;
		(*ffile)->next = NULL;
	}
	else
	{
		tmpfile = *ffile;
		while ((*ffile)->next)
			*ffile = (*ffile)->next;
		file->next = NULL;
		(*ffile)->next = file;
		*ffile = tmpfile;
	}
	return (*ffile);
}

t_file		*ft_get_file_info(char *path,
		t_vars *vars, blkcnt_t *total, int *specf)
{
	char		*tmppath;

	while ((vars->rep = readdir(vars->dir)))
	{
		tmppath = ft_get_full_path(path, vars->rep->d_name);
		if (lstat(tmppath, &vars->s) == 0)
		{
			if (*(vars->rep->d_name) == '.' && !(vars->options & A))
			{
				ft_strdel(&tmppath);
				continue ;
			}
			*total += vars->s.st_blocks;
			vars->file = ft_fill_info(path, vars->s, vars->rep->d_name, specf);
			ft_add_file_l(&vars->ffile, vars->file);
			if (vars->ffile == NULL)
				vars->ffile = vars->file;
		}
		ft_strdel(&tmppath);
	}
	return (vars->ffile);
}

t_file		*ft_get_file_l(int options, char *path, blkcnt_t *total, int *specf)
{
	t_vars		*vars;
	t_file		*file;

	if (!(vars = (t_vars *)malloc(sizeof(t_vars))))
		return (NULL);
	vars->ffile = NULL;
	vars->file = NULL;
	if ((vars->dir = opendir(path)))
	{
		vars->options = options;
		vars->ffile = ft_get_file_info(path, vars, total, specf);
		closedir(vars->dir);
	}
	if (vars->ffile)
		ft_sort_files(options, &vars->ffile);
	file = vars->ffile;
	free(vars);
	vars = NULL;
	return (file);
}

t_file		*ft_files(int options, char **args)
{
	t_file		*file;
	t_file		*ffile;
	struct stat	s;
	int			i;
	int			specf;

	ffile = NULL;
	file = NULL;
	i = -1;
	specf = 0;
	while (*(args + ++i))
	{
		if (lstat(*(args + i), &s) == 0)
		{
			if (S_ISREG(s.st_mode) || options & D || (S_ISLNK(s.st_mode) &&
						*(*(args + i) + ft_strlen(*(args + i)) - 1) != '/'))
			{
				file = ft_fill_info(NULL, s, *(args + i), &specf);
				ft_add_file_l(&ffile, file);
				if (!ffile)
					ffile = file;
			}
		}
	}
	return (ffile);
}
