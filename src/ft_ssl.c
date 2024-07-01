/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:43:49 by cdarrell          #+#    #+#             */
/*   Updated: 2024/07/01 13:41:59 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"
#include <signal.h>

static char	*g_line;

void	_signal_handler(int signal)
{
	ft_putstr("\rSTOP SIGNAL");
	if (signal == SIGINT)
		ft_putstr(" Ctrl + C ");
	else if (signal == SIGQUIT)
		ft_putstr(" Ctrl + / ");
	else if (signal == SIGTSTP)
		ft_putstr(" Ctrl + Z ");
	else if (signal == SIGTERM)
		ft_putstr(" kill pid ");
	else
		ft_putstr(" Unknown signal ");
	ft_putstr("from user");
	free(g_line);
	exit(signal);
}

static void	mandatory_part(char **argv)
{
	t_ssl		*ssl;

	ssl = parse(argv);
	if (!ssl)
		return ;
	if (IS_DEBUG)
		parse_print(ssl);
	if (!ft_strcmp(ssl->cmd, "md5") || \
			!ft_strcmp(ssl->cmd, "sha256") || \
			!ft_strcmp(ssl->cmd, "sha512") || \
			!ft_strcmp(ssl->cmd, "whirlpool"))
		make_ssl_md5(ssl->ssl_md5);
	else
		make_ssl_des(ssl->ssl_des);
	free(ssl);
}

static void	work_like_openssl(void)
{
	int		r;
	char	**argv;

	signal(SIGINT, _signal_handler);
	signal(SIGQUIT, _signal_handler);
	signal(SIGTSTP, _signal_handler);
	signal(SIGTERM, _signal_handler);
	while (1)
	{
		ft_putstr("OPENSSL > ");
		r = gnl(0, &g_line);
		if (g_line && g_line[0] != '\0')
		{
			argv = ft_split(g_line, ' ');
			free(g_line);
			mandatory_part(argv);
			ft_free_split(argv);
		}
		if (r == 0)
			break ;	// ft_putstr(" Ctrl + D ");
		if (r < 0)
			ft_err("Error gnl: ft_ssl - work_like_openssl - line in gnl");
	}
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		work_like_openssl();
	else
		mandatory_part(argv + 1);
	return (0);
}
