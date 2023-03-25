/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:43:45 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/25 15:38:55 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_ssl.h"

static int	check_usage(char *argv)
{
	if (ft_strcmp(argv, "md5") && \
			ft_strcmp(argv, "sha256") && \
			ft_strcmp(argv, "sha512") && \
			ft_strcmp(argv, "whirlpool") && \
			ft_strcmp(argv, "base64") && \
			ft_strcmp(argv, "des") && \
			ft_strcmp(argv, "des-ecb") && \
			ft_strcmp(argv, "des-cbc"))
	{
		ft_putstr("ft_ssl: Error: [");
		ft_putstr(argv);
		ft_putstr("] is an invalid command.\n");
		ft_putstr("\n");
		ft_putstr("Standard commands:\n");
		ft_putstr("\n");
		ft_putstr("Message Digest commands:\n");
		ft_putstr("md5\n");
		ft_putstr("sha256\n");
		ft_putstr("sha512\n");
		ft_putstr("whirlpool\n");
		ft_putstr("\n");
		ft_putstr("Cipher commands:\n");
		ft_putstr("base64\n");
		ft_putstr("des\n");
		ft_putstr("des-ecb\n");
		ft_putstr("des-cbc\n");
		ft_putstr("\n");
		return (0);
	}
	else
		return (1);
}

static t_ssl	*init_ssl(char *cmd)
{	
	t_ssl	*ssl;

	ssl = malloc(sizeof(t_ssl));
	if (!ssl)
		ft_err("Error malloc: parsing.c - init_ssl - ssl");
	ssl->cmd = cmd;
	ssl->ssl_md5 = NULL;
	ssl->ssl_des = NULL;
	return (ssl);
}

t_ssl	*parse(char **argv)
{
	t_ssl	*ssl;

	if (!check_usage(argv[0]))
		return (NULL);
	ssl = init_ssl(argv[0]);
	if (!ft_strcmp(ssl->cmd, "md5") || \
			!ft_strcmp(ssl->cmd, "sha256") || \
			!ft_strcmp(ssl->cmd, "sha512") || \
			!ft_strcmp(ssl->cmd, "whirlpool"))
		ssl->ssl_md5 = parse_ssl_md5(ssl->cmd, argv + 1);
	else
		ft_putstr("!!!!!!!!!!!!!!!!\n");
	return (ssl);
}
