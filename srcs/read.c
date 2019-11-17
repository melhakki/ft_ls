/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:05:38 by melhakki          #+#    #+#             */
/*   Updated: 2019/09/23 20:14:38 by melhakki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_error_option(char op)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(op);
	ft_putstr("\nusage: ft_ls [-lartRSd1@ugG] [file ...]\n");
	exit(1);
}

int		ft_is_option(char op)
{
	char	*options;
	int		i;
	int		ops;

	options = "lartRSd1@ugG";
	i = -1;
	ops = 1;
	while (*(options + ++i) != '\0')
	{
		if (op == *(options + i))
			return (ops << i);
	}
	return (0);
}

void	ft_altern(char argv, int *options)
{
	if (ft_is_option(argv))
	{
		if (*options & ONE && argv == 'l')
			*options = *options & ~ONE;
		else if (*options & L && argv == '1')
			*options = *options & ~L;
		*options = *options | ft_is_option(argv);
	}
	else
		ft_error_option(argv);
}

int		ft_get_options(int argc, char **argv, int *i)
{
	int		j;
	int		options;

	options = 0;
	*i = 0;
	while (++*i < argc)
	{
		j = 0;
		if (*(*(argv + (*i)) + 0) == '-' && *(*(argv + *i) + 1) != '-')
		{
			while (*(*(argv + (*i)) + ++j) != '\0')
				ft_altern(argv[*i][j], &options);
		}
		else
			break ;
	}
	return (options);
}

char	**ft_get_args(int argc, char **argv, int pos)
{
	char	**args;
	int		i;

	if (!(args = (char **)malloc(sizeof(char *) * (argc - pos + 1))))
		return (NULL);
	if (pos < argc)
	{
		if (argv[pos][0] == '-' && argv[pos][1] == '-' && argv[pos][2] == '\0')
			pos++;
		else if (argv[pos][0] == '-' &&
				argv[pos][1] == '-' && argv[pos][2] != '\0')
			ft_error_option('-');
	}
	i = -1;
	if (pos == argc)
		*(args + ++i) = ft_strdup(".");
	else
	{
		while (pos < argc)
			*(args + ++i) = ft_strdup(*(argv + pos++));
	}
	*(args + i + 1) = NULL;
	return (args);
}
