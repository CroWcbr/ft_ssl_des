/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ssl_des_argv.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:53:09 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/26 17:05:10 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_ssl.h"

t_bool	parse_ssl_des_argv(char **argv, t_ssl_des *ssl_des)
{
	while (*argv)
	{
		if (!ft_strcmp(*argv, "-a"))
			ssl_des->a = true;
		else if (!ft_strcmp(*argv, "-d"))
		{
			ssl_des->d = true;
			ssl_des->e = false;
		}
		else if (!ft_strcmp(*argv, "-e"))
		{
			ssl_des->e = true;
			ssl_des->d = false;
		}
		else if (!ft_strcmp(*argv, "-i"))
		{
			ssl_des->i = true;
			argv++;
			if (!(*argv))
			{
				ft_putstr("Error parse_argv: flag s, but no string after\n");
				return (0);
			}
			ssl_des->input_file = *argv;
		}
		else if (!ft_strcmp(*argv, "-k"))
			ssl_des->k = true;
		else if (!ft_strcmp(*argv, "-o"))
		{
			ssl_des->o = true;
			argv++;
			if (!(*argv))
			{
				ft_putstr("Error parse_argv: flag s, but no string after\n");
				return (0);
			}
			ssl_des->output_file = *argv;
		}
		else if (!ft_strcmp(*argv, "-p"))
			ssl_des->p = true;
		else if (!ft_strcmp(*argv, "-s"))
			ssl_des->s = true;
		else if (!ft_strcmp(*argv, "-v"))
			ssl_des->v = true;
		argv++;
	}
	return (1);
}
