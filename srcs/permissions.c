/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permitions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:59:24 by melhakki          #+#    #+#             */
/*   Updated: 2019/09/22 16:12:07 by sel-mort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		ft_get_filetype(int mode)
{
	char	type;
	int		mod;

	mod = mode & S_IFMT;
	if (mod == S_IFIFO)
		type = 'p';
	else if (mod == S_IFBLK)
		type = 'b';
	else if (mod == S_IFCHR)
		type = 'c';
	else if (mod == S_IFDIR)
		type = 'd';
	else if (mod == S_IFLNK)
		type = 'l';
	else if (mod == S_IFREG)
		type = '-';
	else if (mod == S_IFSOCK)
		type = 's';
	else if (mod == S_IFWHT)
		type = 'w';
	else
		type = '?';
	return (type);
}

char		*ft_get_perms(int mode, char *fodname)
{
	static char	*lsperms[] = {"---", "--x",
		"-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
	char		*perms;

	if (!(perms = (char *)malloc(sizeof(char) * 12)))
		return (NULL);
	perms[0] = ft_get_filetype(mode);
	ft_strcpy(&perms[1], lsperms[(mode >> 6) & 7]);
	ft_strcpy(&perms[4], lsperms[(mode >> 3) & 7]);
	ft_strcpy(&perms[7], lsperms[(mode & 7)]);
	if (mode & S_ISUID)
		perms[3] = (mode & S_IXUSR) ? 's' : 'S';
	if (mode & S_ISGID)
		perms[6] = (mode & S_IXGRP) ? 's' : 'S';
	if (mode & S_ISVTX)
		perms[9] = (mode & S_IXOTH) ? 't' : 'T';
	perms[10] = ft_get_xttre(fodname);
	perms[11] = '\0';
	return (perms);
}

void		ft_get_user_group(struct stat s, t_info **file)
{
	(*file)->user = getpwuid(s.st_uid)->pw_name;
	(*file)->group = getgrgid(s.st_gid)->gr_name;
}

char		*ft_get_date(char type, struct stat s)
{
	time_t	cdate;
	time_t	typetime;
	char	*t1;
	char	*t2;
	char	*tstr;

	time(&cdate);
	if (type == 'm')
		typetime = s.st_mtime;
	else
		typetime = s.st_atime;
	if (cdate > typetime + 15780000)
	{
		t1 = ft_strsub(ctime(&typetime), 4, 7);
		t2 = ft_strsub(ctime(&typetime), 19, 23);
		*(t2 + 5) = '\0';
		tstr = ft_strjoin(t1, t2);
		ft_strdel(&t1);
		ft_strdel(&t2);
		return (tstr);
	}
	return (ft_strsub(ctime(&typetime), 4, 12));
}
