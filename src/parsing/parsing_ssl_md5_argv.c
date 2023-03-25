/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ssl_md5_argv.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 21:18:12 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/25 16:52:57 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_ssl.h"

static void	parse_hash_list(char **argv, t_ssl_md5	*ssl_md5)
{
	t_list		*new_list;
	t_hash_md5	*input;

	if (*argv && ssl_md5->s == true)
	{
		input = create_ssl_md5_hash_node(*argv);
		input->type = false;
		new_list = ft_lstnew(input);
		if (!new_list)
			ft_err("Error malloc: parsing.c - parse_hash_list - new_list");
		ft_lstadd_back(&ssl_md5->hash_list, new_list);
		argv++;
	}
	while (*argv)
	{
		input = create_ssl_md5_hash_node(*argv);
		new_list = ft_lstnew(input);
		if (!new_list)
			ft_err("Error malloc: parsing.c - parse_hash_list - new_list");
		ft_lstadd_back(&ssl_md5->hash_list, new_list);
		argv++;
	}
}

t_bool	parse_ssl_md5_argv(char **argv, t_ssl_md5 *ssl_md5)
{
	while (*argv)
	{
		if (!ft_strcmp(*argv, "-p"))
			ssl_md5->p = true;
		else if (!ft_strcmp(*argv, "-q"))
			ssl_md5->q = true;
		else if (!ft_strcmp(*argv, "-r"))
			ssl_md5->r = true;
		else if (!ft_strcmp(*argv, "-s"))
		{
			ssl_md5->s = true;
			argv++;
			if (!(*argv))
			{
				ft_putstr("Error parse_argv: flag s, but no string after\n");
				return (0);
			}
			break ;
		}
		else
			break ;
		argv++;
	}
	parse_hash_list(argv, ssl_md5);
	return (1);
}

static char	*ft_strjoin_add_n(char const *s1, char const *s2, int n)
{
	char	*tmp;
	size_t	len;

	if (!s1 || !s2)
		return ((void *)0);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (n > 0)
		len++;
	tmp = (char *)malloc(len * sizeof(char));
	if (!tmp)
		return ((void *)0);
	ft_strlcpy(tmp, s1, len);
	ft_strlcat(tmp, s2, len);
	if (n > 0)
		ft_strlcat(tmp, "\n", len);
	return (tmp);
}

static char	*read_stdin(char *tmp_stdin, char *tmp_del)
{
	int		r;
	char	*line;

	if (!tmp_stdin)
		ft_err("Error malloc: pars_flag_p.c - read_stdin - tmp_stdin");
	while (1)
	{
		r = gnl(0, &line);
		if (r < 0)
			ft_err("Error gnl: pars_flag_p.c - read_stdin - line in gnl");
		if (line)
		{
			tmp_del = tmp_stdin;
			tmp_stdin = ft_strjoin_add_n(tmp_stdin, line, r);
			if (!tmp_stdin)
				ft_err("Error malloc: pars_flag_p.c - read_stdin - tmp");
			free(tmp_del);
			free(line);
		}
		if (r == 0)
			break ;
	}
	return (tmp_stdin);
}

void	parse_ssl_md5_flag_p(t_ssl_md5 *ssl_md5)
{
	t_list		*new_list;
	t_hash_md5	*input;

	input = malloc(sizeof(t_hash_md5));
	if (!input)
		ft_err("Error malloc: parsing_flag_p.c - parse_flag_p - input");
	input->type = false;
	input->name = read_stdin(ft_strdup(""), NULL);
	if (!input->name)
		ft_err("Error malloc: pars_flag_p.c -  parse_flag_p - input->name");
	new_list = ft_lstnew(input);
	if (!new_list)
		ft_err("Error malloc: parsing_flag_p.c - parse_flag_p - new_list");
	ft_lstadd_front(&ssl_md5->hash_list, new_list);
}
