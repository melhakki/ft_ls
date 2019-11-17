/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sport2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:01:06 by melhakki          #+#    #+#             */
/*   Updated: 2019/09/18 17:58:08 by melhakki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_cmp(char op, char *pname1, char *pname2)
{
	struct stat		s1;
	struct stat		s2;

	if (lstat(pname1, &s1) == 0 && lstat(pname2, &s2) == 0)
	{
		if (op == 't')
			return (s1.st_mtime - s2.st_mtime);
		else if (op == 'S')
			return (s1.st_size - s2.st_size);
	}
	return (0);
}

void		ft_sort_by(char op, t_args **args)
{
	t_args		*arg1;
	t_args		*arg2;
	char		*tmp;

	arg1 = *args;
	while (arg1->next)
	{
		arg2 = arg1->next;
		while (arg2)
		{
			if (ft_cmp(op, arg1->pathname, arg2->pathname) > 0)
			{
				tmp = arg1->pathname;
				arg1->pathname = arg2->pathname;
				arg2->pathname = tmp;
			}
			arg2 = arg2->next;
		}
		arg1 = arg1->next;
	}
}

void		ft_sort_byascii(char **args)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (*(args + ++i))
	{
		j = i;
		while (*(args + ++j))
		{
			if (ft_strcmp(*(args + i), *(args + j)) > 0)
			{
				tmp = *(args + i);
				*(args + i) = *(args + j);
				*(args + j) = tmp;
			}
		}
	}
}

void		ft_sort_r(t_args **farg)
{
	t_args		*first;
	t_args		*current;
	t_args		*next;

	first = NULL;
	current = *farg;
	next = NULL;
	while (current)
	{
		next = current->next;
		current->next = first;
		first = current;
		current = next;
	}
	*farg = first;
}

void		sort(int options, t_args **args)
{
	if (options & T)
		ft_sort_by('t', args);
	if (options & S)
		ft_sort_by('S', args);
	if (options & R)
		ft_sort_r(args);
}
