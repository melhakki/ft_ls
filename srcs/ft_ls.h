/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhakki <melhakki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:18:40 by sel-mort          #+#    #+#             */
/*   Updated: 2019/09/23 22:26:48 by melhakki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/types.h>

# define L		1
# define A		2
# define R		4
# define T		8
# define RC		16
# define S		32
# define D		64
# define ONE	128
# define ARO	256
# define U		512
# define G		1024
# define COLOR	2048

typedef	struct s_info		t_info;
struct						s_info
{
	char					*filename;
	char					*perms;
	nlink_t					nlink;
	char					*user;
	char					*group;
	off_t					size;
	unsigned int			maj;
	unsigned int			min;
	char					*mdate;
	char					*adate;
	time_t					mtime;
};

typedef	struct s_file		t_file;
struct						s_file
{
	t_info					*info;
	t_file					*next;
};

typedef	struct s_maxlen		t_maxlen;
struct						s_maxlen
{
	size_t					maxuser;
	size_t					maxgroup;
	size_t					maxsize;
	size_t					maxlink;
	size_t					maxmaj;
	size_t					maxmin;
	int						b;
};

typedef	struct s_args		t_args;
struct						s_args
{
	char					*pathname;
	t_file					*info;
	blkcnt_t				total;
	t_file					*file;
	t_maxlen				*len;
	int						specf;
	size_t					countarg;
	t_args					*next;
};

typedef	struct s_vars		t_vars;
struct						s_vars
{
	struct stat				s;
	struct dirent			*rep;
	DIR						*dir;
	t_file					*ffile;
	t_file					*file;
	t_args					*farg;
	int						options;
	t_maxlen				*len;
};

void						ft_process_args(int options,
		t_args *arg, int count);
void						ft_fill_args(int options, t_args *args, int nbdir);
t_args						*ft_add_arg(t_args **farg, t_args *arg);
t_args						*ft_args(char **args);
t_args						*ft_fill_args_list(int options, t_args *args);
t_file						*ft_get_arg_info(char *arg);
t_args						*ft_get_path_info(int options, char *arg);
t_args						*ft_get_init_path(char *arg);
t_args						*ft_process_option_r(int options,
		t_args *arg, char **path);
t_file						*ft_fill_info(char *path,
		struct stat s, char *fname, int *specf);
t_file						*ft_add_file_l(t_file **ffile, t_file *file);
t_file						*ft_get_file_info(char *path,
		t_vars *vars, blkcnt_t *total, int *specf);
t_file						*ft_get_file_l(int options,
		char *path, blkcnt_t *total, int *specf);
t_file						*ft_files(int options, char **args);
void						ft_free_info(t_info **info);
void						ft_free_args(t_args **arg);
void						ft_free_files(t_file **ffile);
void						ft_free_init_args(t_args **arg);
void						ft_free_all(char **args);
void						ft_ls(int options, char **args);
char						ft_get_filetype(int mode);
char						*ft_get_perms(int mode, char *fodname);
void						ft_get_user_group(struct stat s, t_info **file);
char						*ft_get_date(char type, struct stat s);
char						ft_get_xttre(char *fodname);
char						*ft_readlink(char *path);
void						ft_get_dev(struct stat s, t_info **file);
void						ft_get_notdev(t_info **info);
char						*ft_get_full_path(char *path, char *fname);
void						ft_fill_extra_info(t_file **finfo,
		struct stat s, int *specf);
char						*ft_get_link(char *path, char *fname);
void						ft_print_space(size_t min, size_t max);
void						ft_putsstr(char *str, int sp);
void						ft_print_min_maj(t_file *file, t_maxlen *len);
void						ft_putstrname(char *str);
void						ft_print_list(int options,
		t_file *file, t_maxlen *len);
void						ft_print_path_info(int options,
		t_args *path, int count);
void						ft_stat_errors(char *arg);
void						ft_putlong(long long nbr);
void						ft_display_extra_fileinfo(int options,
		int size, t_file *file, t_maxlen *len);
void						ft_display_fileinfo(int options,
		t_file *file, t_maxlen *len);
void						ft_error_option(char op);
int							ft_is_option(char op);
int							ft_get_options(int argc, char **argv, int *i);
char						**ft_get_args(int argc, char **argv, int pos);
void						ft_sort(char op, t_file **ffile);
int							ft_filecmp(char op, t_file *file1, t_file *file2);
void						ft_sort_revers(t_file **file);
void						ft_sort_files(int options, t_file **file);
int							ft_cmp(char op, char *pname1, char *pname2);
void						ft_sort_by(char op, t_args **args);
void						ft_sort_byascii(char **args);
void						ft_sort_r(t_args **farg);
void						sort(int options, t_args **args);
long long					ft_get_nbrcount(long long nbr);
void						ft_init_len(t_maxlen **len);
void						ft_get_maxlen(t_maxlen **len, t_file *file);
void						ft_print_errors(char **args);
t_file						*ft_get_files(int options, char **args, int *nbdir);
void						ft_color(char *perms, int options);
void						ft_split(char *name, char *perms, int options);

#endif
