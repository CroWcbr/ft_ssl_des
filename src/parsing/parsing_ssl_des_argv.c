/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ssl_des_argv.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:53:09 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/29 18:00:40 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_ssl.h"

t_bool	parse_ssl_des_argv(char **argv, t_ssl_des *ssl_des)
{
	while (*argv)
	{
		if (!ft_strcmp(*argv, "-d"))
			ssl_des->mode = 'D';
		else if (!ft_strcmp(*argv, "-e"))
			ssl_des->mode = 'E';
		else if (!ft_strcmp(*argv, "-i"))
		{
			argv++;
			if (!(*argv))
			{
				ft_putstr("Error parse_argv: flag -i, but no string after\n");
				return (0);
			}
			ssl_des->input_file = *argv;
		}
		else if (!ft_strcmp(*argv, "-o"))
		{
			argv++;
			if (!(*argv))
			{
				ft_putstr("Error parse_argv: flag -o, but no string after\n");
				return (0);
			}
			ssl_des->output_file = *argv;
		}
		else if (!ft_strcmp(*argv, "-a") && ssl_des->coding_func)
			ssl_des->a = true;
		else if (!ft_strcmp(*argv, "-k") && ssl_des->coding_func)
		{
			argv++;
			if (!(*argv))
			{
				ft_putstr("Error parse_argv: flag -k, but no string after\n");
				return (0);
			}
			ssl_des->k = *argv;
		}
		else if (!ft_strcmp(*argv, "-p") && ssl_des->coding_func)
		{
			argv++;
			if (!(*argv))
			{
				ft_putstr("Error parse_argv: flag -p, but no string after\n");
				return (0);
			}
			ssl_des->p = *argv;
		}
		else if (!ft_strcmp(*argv, "-s") && ssl_des->coding_func)
		{
			argv++;
			if (!(*argv))
			{
				ft_putstr("Error parse_argv: flag -s, but no string after\n");
				return (0);
			}
			ssl_des->s = *argv;
		}
		else if (!ft_strcmp(*argv, "-v") && ssl_des->coding_func)
		{
			argv++;
			if (!(*argv))
			{
				ft_putstr("Error parse_argv: flag -v, but no string after\n");
				return (0);
			}
			ssl_des->v = *argv;
		}
		else
		{
			ft_putstr(ssl_des->cmd);
			ft_putstr(": Unrecognized flag ");
			ft_putstr(*argv);
			ft_putstr("\n");
			return (0);
		}
		argv++;
	}
	return (1);
}
