/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:00:49 by melhakki          #+#    #+#             */
/*   Updated: 2019/09/19 16:53:53 by melhakki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*ft_get_arg_info(char *arg)
{
	struct stat		s;

	if (lstat(arg, &s) == 0)
		return (ft_fill_info(NULL, s, arg, NULL));
	return (NULL);
}

t_args		*ft_get_path_info(int options, char *arg)
{
	t_args		*path;

	if (!(path = (t_args *)malloc(sizeof(t_args))) ||
			!(path->len = (t_maxlen *)malloc(sizeof(t_maxlen))))
		return (NULL);
	path->pathname = arg;
	path->info = ft_get_arg_info(arg);
	path->info->next = NULL;
	path->total = 0;
	path->specf = 0;
	path->file = ft_get_file_l(options, arg, &path->total, &path->specf);
	ft_get_maxlen(&path->len, path->file);
	return (path);
}

t_args		*ft_get_init_path(char *arg)
{
	t_args		*path;

	if (!(path = (t_args *)malloc(sizeof(t_args))) ||
			!(path->len = (t_maxlen *)malloc(sizeof(t_maxlen))))
		return (NULL);
	path->pathname = arg;
	path->info = NULL;
	path->total = 0;
	path->specf = 0;
	path->file = NULL;
	return (path);
}

void		ft_perms_error(char *str)
{
	ft_putstr("ft_ls: ");
	ft_putstr(str);
	ft_putendl(": Permission denied");
}

t_args		*ft_args(char **args)
{
	t_args		*arg;
	t_args		*farg;
	struct stat	s;
	int			i;

	farg = NULL;
	i = -1;
	while (*(args + ++i))
	{
		if (lstat(*(args + i), &s) == 0)
		{
			if (S_ISDIR(s.st_mode) || (S_ISLNK(s.st_mode) &&
						*(*(args + i) + ft_strlen(*(args + i)) - 1) == '/'))
			{
				if ((arg = ft_get_init_path(*(args + i))))
				{
					ft_add_arg(&farg, arg);
					if (!farg)
						farg = arg;
				}
			}
		}
	}
	return (farg);
}
