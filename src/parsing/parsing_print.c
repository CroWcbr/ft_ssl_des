/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:30:46 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/25 16:51:40 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_ssl.h"

static void	print_ssl_md5(t_ssl_md5 *ssl_md5)
{
	t_list		*tmp;
	t_hash_md5	*th;

	ft_putstr("type = \t");
	ft_putstr(ssl_md5->cmd);
	ft_putstr("\np = \t");
	ft_putnbr_fd(ssl_md5->p, 1);
	ft_putstr("\nq = \t");
	ft_putnbr_fd(ssl_md5->q, 1);
	ft_putstr("\nr = \t");
	ft_putnbr_fd(ssl_md5->r, 1);
	ft_putstr("\ns = \t");
	ft_putnbr_fd(ssl_md5->s, 1);
	ft_putstr("\n");
	tmp = ssl_md5->hash_list;
	while (tmp)
	{
		th = (t_hash_md5 *)tmp->content;
		ft_putnbr_fd(th->type, 1);
		ft_putstr("\t|");
		ft_putstr(th->name);
		ft_putstr("|\n");
		tmp = tmp->next;
	}
}

void	parse_print(t_ssl *ssl)
{
	ft_putstr("----------------------------\n");
	if (!ft_strcmp(ssl->cmd, "md5") || \
			!ft_strcmp(ssl->cmd, "sha256") || \
			!ft_strcmp(ssl->cmd, "sha512") || \
			!ft_strcmp(ssl->cmd, "whirlpool"))
		print_ssl_md5(ssl->ssl_md5);
	else
		ft_putstr("!!!!!!!!!!!!!!!!\n");
	ft_putstr("----------------------------\n");
}