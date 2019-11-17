/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:04:29 by melhakki          #+#    #+#             */
/*   Updated: 2019/09/19 16:05:30 by melhakki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_free_info(t_info **info)
{
	if (*info)
	{
		if ((*info)->filename)
		{
			free((*info)->filename);
			(*info)->filename = NULL;
		}
		if ((*info)->perms)
		{
			free((*info)->perms);
			(*info)->perms = NULL;
		}
		if ((*info)->mdate)
		{
			free((*info)->mdate);
			(*info)->mdate = NULL;
		}
		if ((*info)->adate)
		{
			free((*info)->adate);
			(*info)->adate = NULL;
		}
		free((*info));
		*info = NULL;
	}
}

void		ft_free_args(t_args **arg)
{
	t_args		*targ;
	t_file		*tfile;

	while (*arg)
	{
		targ = *arg;
		if (targ->file)
		{
			while (targ->file)
			{
				tfile = targ->file;
				targ->file = targ->file->next;
				ft_free_info(&(tfile->info));
				free(tfile);
			}
		}
		*arg = (*arg)->next;
		ft_free_info(&(targ->info->info));
		free(targ->info);
		free(targ->len);
		free(targ);
		targ = NULL;
	}
}

void		ft_free_files(t_file **ffile)
{
	t_file		*tfile;

	if (*ffile)
	{
		while (*ffile)
		{
			tfile = *ffile;
			ft_free_info(&(*ffile)->info);
			*ffile = (*ffile)->next;
			free(tfile);
			tfile = NULL;
		}
	}
}

void		ft_free_init_args(t_args **arg)
{
	t_args		*tmparg;

	while (*arg)
	{
		tmparg = *arg;
		*arg = (*arg)->next;
		free(tmparg->len);
		free(tmparg);
		tmparg = NULL;
	}
}

void		ft_free_all(char **args)
{
	int		i;

	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
	args = NULL;
}
