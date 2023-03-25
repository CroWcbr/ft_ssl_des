/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ssl_md5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 12:20:30 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/25 16:53:10 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_ssl.h"

static void	init_ssl_md5_function(t_ssl_md5 *ssl_md5)
{
	if (!ft_strcmp(ssl_md5->hash_to_upper, "MD5"))
	{
		ssl_md5->hash_func = &md5_main;
		ssl_md5->crypt_len = 16;
	}
	else if (!ft_strcmp(ssl_md5->hash_to_upper, "SHA256"))
	{
		ssl_md5->hash_func = &sha256_main;
		ssl_md5->crypt_len = 32;
	}
	else if (!ft_strcmp(ssl_md5->hash_to_upper, "SHA512"))
	{
		ssl_md5->hash_func = &sha512_main;
		ssl_md5->crypt_len = 64;
	}
	else
	{
		ssl_md5->hash_func = &whirlpool;
		ssl_md5->crypt_len = 64;
	}
}

static t_ssl_md5	*init_ssl_md5(char *cmd)
{
	t_ssl_md5	*ssl_md5;
	size_t		i;

	ssl_md5 = malloc(sizeof(t_ssl_md5));
	if (!ssl_md5)
		ft_err("Error malloc: parse_ssl_md5.c - ssl_md5");
	ssl_md5->cmd = cmd;
	ssl_md5->hash_to_upper = ft_strdup(cmd);
	if (!ssl_md5->hash_to_upper)
		ft_err("Error malloc: parsing_ssl_md5.c - init - hash_to_upper");
	i = 0;
	while (i < ft_strlen(ssl_md5->hash_to_upper))
	{
		ssl_md5->hash_to_upper[i] = ft_toupper(ssl_md5->hash_to_upper[i]);
		i++;
	}
	init_ssl_md5_function(ssl_md5);
	ssl_md5->p = false;
	ssl_md5->q = false;
	ssl_md5->r = false;
	ssl_md5->s = false;
	ssl_md5->hash_list = NULL;
}

t_hash_md5	*create_ssl_md5_hash_node(char *name)
{
	t_hash_md5	*input;

	input = malloc(sizeof(t_hash_md5));
	if (!input)
		ft_err("Error malloc: parsing.c - parse_hash_list - input");
	input->type = true;
	input->name = ft_strdup(name);
	if (!input->name)
		ft_err("Error malloc: parsing.c - parse_hash_list - input->name");
	return (input);
}

t_ssl_md5	*parse_ssl_md5(char *cmd, char **argv)
{
	t_ssl_md5	*ssl_md5;

	ssl_md5 = init_ssl_md5(cmd);



	if (!parse_ssl_md5_argv(argv, ssl_md5))
	{
		free(ssl_md5->hash_to_upper);
		free(ssl_md5);
		return (NULL);
	}
	if (ssl_md5->p == true || !ssl_md5->hash_list)
		parse_ssl_md5_flag_p(ssl_md5);
	return (ssl_md5);
}
