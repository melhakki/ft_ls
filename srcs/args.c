/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:26:47 by melhakki          #+#    #+#             */
/*   Updated: 2019/09/23 20:16:35 by melhakki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_args		*ft_process_option_r(int options, t_args *arg, char **path)
{
	struct stat		s;
	char			*str;
	t_args			*targ;

	targ = NULL;
	str = arg->file->info->filename;
	*path = ft_get_full_path(arg->pathname, str);
	if (*str != '.' && *(str + 1) != '.')
	{
		if (lstat(*path, &s) == 0)
		{
			if (S_ISDIR(s.st_mode))
			{
				if ((targ = ft_get_path_info(options, *path)))
					ft_putchar('\n');
				targ->next = NULL;
			}
		}
	}
	return (targ);
}

void		ft_process_args(int options, t_args *arg, int count)
{
	t_args			*targ;
	t_file			*tfile;
	t_args			*tmpa;
	char			*path;

	ft_print_path_info(options, arg, count);
	if (arg->file != NULL)
		ft_print_list(options, arg->file, arg->len);
	if (options & RC)
	{
		tmpa = arg;
		tfile = tmpa->file;
		while (tmpa->file)
		{
			if ((targ = ft_process_option_r(options, tmpa, &path)))
			{
				ft_process_args(options, targ, 1);
				ft_free_args(&targ);
			}
			ft_strdel(&path);
			tmpa->file = tmpa->file->next;
		}
		arg->file = tfile;
	}
}

void		ft_fill_args(int options, t_args *args, int nbdir)
{
	t_args		*farg;
	t_args		*tmparg;

	farg = ft_fill_args_list(options, args);
	tmparg = farg;
	while (farg)
	{
		ft_process_args(options, farg, nbdir);
		nbdir++;
		if ((farg = farg->next))
			ft_putchar('\n');
	}
	ft_free_args(&tmparg);
}

t_args		*ft_add_arg(t_args **farg, t_args *arg)
{
	t_args		*tmparg;

	tmparg = NULL;
	if (!(*farg))
	{
		*farg = arg;
		(*farg)->next = NULL;
	}
	else
	{
		tmparg = *farg;
		while ((*farg)->next)
			*farg = (*farg)->next;
		arg->next = NULL;
		(*farg)->next = arg;
		*farg = tmparg;
	}
	return (*farg);
}

t_args		*ft_fill_args_list(int options, t_args *args)
{
	t_args			*farg;
	t_args			*arg;
	struct stat		s;

	farg = NULL;
	while (args)
	{
		if (lstat(args->pathname, &s) == 0)
		{
			arg = ft_get_path_info(options, args->pathname);
			ft_add_arg(&farg, arg);
			if (farg == NULL)
				farg = arg;
		}
		args = args->next;
	}
	return (farg);
}
