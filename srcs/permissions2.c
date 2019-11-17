/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permitions2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 17:01:13 by melhakki          #+#    #+#             */
/*   Updated: 2019/09/23 15:16:58 by sel-mort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		ft_get_xttre(char *fodname)
{
	char			xach;
	acl_t			acl;
	acl_entry_t		buff;
	ssize_t			xattr;

	acl = NULL;
	xattr = 0;
	acl = acl_get_link_np(fodname, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &buff) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(fodname, NULL, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		xach = '@';
	else if (acl)
		xach = '+';
	else
		xach = ' ';
	return (xach);
}

char		*ft_readlink(char *path)
{
	char		*link;
	ssize_t		len;
	char		buff[4096];

	len = readlink(path, buff, 4095);
	if (len == -1)
	{
		ft_putendl(path);
		ft_stat_errors(path);
		exit(1);
	}
	buff[len] = '\0';
	link = ft_strdup(buff);
	return (link);
}

void		ft_get_dev(struct stat s, t_info **file)
{
	(*file)->maj = major(s.st_rdev);
	(*file)->min = minor(s.st_rdev);
}

void		ft_get_notdev(t_info **info)
{
	(*info)->maj = -1;
	(*info)->min = -1;
}
