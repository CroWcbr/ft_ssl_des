/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ssl_des.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:37:39 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/29 20:20:10 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_ssl.h"

static void	init_ssl_des_function(t_ssl_des *ssl_des)
{
	ssl_des->base64 = &base64_main;
	ssl_des->coding_func = NULL;
	if (ft_strcmp(ssl_des->cmd, "base64"))
	{
		if (!ft_strcmp(ssl_des->cmd, "des"))
		{
			
		}
		else if (!ft_strcmp(ssl_des->cmd, "des-ecb"))
		{
			
		}
		else if (!ft_strcmp(ssl_des->cmd, "des-cbc"))
		{
			
		}
	}
}

static t_ssl_des	*init_ssl_des(char *cmd)
{
	t_ssl_des	*ssl_des;

	ssl_des = malloc(sizeof(t_ssl_des));
	if (!ssl_des)
		ft_err("Error malloc: parse_ssl_des.c - ssl_des");
	ssl_des->cmd = cmd;
	init_ssl_des_function(ssl_des);
	ssl_des->mode = 'E';
	ssl_des->input_file = NULL;
	ssl_des->input_buffer = NULL;
	ssl_des->input_len = 0;
	ssl_des->output_file = NULL;
	ssl_des->output_buffer = NULL;
	ssl_des->output_len = 0;

	ssl_des->a = false;
	ssl_des->k = NULL;
	ssl_des->p = NULL;
	ssl_des->s = NULL;
	ssl_des->v = NULL;
	return (ssl_des);
}

t_ssl_des	*parse_ssl_des(char *cmd, char **argv)
{
	t_ssl_des	*ssl_des;

	ssl_des = init_ssl_des(cmd);
	if (!parse_ssl_des_argv(argv, ssl_des))
	{
		free(ssl_des);
		return (NULL);
	}
	if (!ssl_des->input_file)
	{
		ssl_des->input_buffer = read_stdin(ft_strdup(""), NULL);
		if (!ssl_des->input_buffer)
			ft_err("Error malloc: parse_ssl_des.c - input_buffer");
		ssl_des->input_len = ft_strlen(ssl_des->input_buffer);
	}
	return (ssl_des);
}
