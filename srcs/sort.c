/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:19:07 by melhakki          #+#    #+#             */
/*   Updated: 2019/09/18 17:56:31 by melhakki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_sort(char op, t_file **ffile)
{
	t_file		*file1;
	t_file		*file2;
	t_info		*tmp;

	file1 = *ffile;
	while (file1->next)
	{
		file2 = file1->next;
		while (file2)
		{
			if (ft_filecmp(op, file1, file2) < 0)
			{
				tmp = file1->info;
				file1->info = file2->info;
				file2->info = tmp;
			}
			file2 = file2->next;
		}
		file1 = file1->next;
	}
}

int			ft_filecmp(char op, t_file *file1, t_file *file2)
{
	if (op == 'a')
		return (ft_strcmp(file2->info->filename, file1->info->filename));
	else if (op == 't')
		return (file1->info->mtime - file2->info->mtime);
	else if (op == 'S')
		return (file1->info->size - file2->info->size);
	else
		return (0);
}

void		ft_sort_revers(t_file **file)
{
	t_file		*first;
	t_file		*current;
	t_file		*next;

	first = NULL;
	current = *file;
	next = NULL;
	while (current)
	{
		next = current->next;
		current->next = first;
		first = current;
		current = next;
	}
	*file = first;
}

void		ft_sort_files(int options, t_file **file)
{
	ft_sort('a', file);
	if (options & T)
		ft_sort('t', file);
	if (options & S)
		ft_sort('S', file);
	if (options & R)
		ft_sort_revers(file);
}
