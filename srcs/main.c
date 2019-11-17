/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:55:01 by sel-mort          #+#    #+#             */
/*   Updated: 2019/09/23 16:26:12 by melhakki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_ls(int options, char **args)
{
	t_args		*farg;
	t_file		*ffile;
	int			nbdir;

	farg = NULL;
	ffile = NULL;
	ft_sort_byascii(args);
	ft_print_errors(args);
	ffile = ft_get_files(options, args, &nbdir);
	if ((farg = ft_args(args)))
	{
		if (nbdir)
			ft_putchar('\n');
		ft_fill_args(options, farg, nbdir);
		ft_free_init_args(&farg);
	}
}

int			main(int argc, char **argv)
{
	int		options;
	int		i;
	char	**args;

	options = ft_get_options(argc, argv, &i);
	args = ft_get_args(argc, argv, i);
	ft_ls(options, args);
	ft_free_all(args);
	return (0);
}
