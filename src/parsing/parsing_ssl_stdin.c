/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ssl_stdin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:45:23 by cdarrell          #+#    #+#             */
/*   Updated: 2024/07/01 13:40:34 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_ssl.h"

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

char	*read_stdin(char *tmp_stdin, char *tmp_del)
{
	int		r;
	char	*line;

	if (!tmp_stdin)
		ft_err("Error malloc: read_stdin - tmp_stdin");
	while (1)
	{
		r = gnl(0, &line);
		if (r < 0)
			ft_err("Error gnl: read_stdin - line in gnl");
		if (line)
		{
			tmp_del = tmp_stdin;
			tmp_stdin = ft_strjoin_add_n(tmp_stdin, line, r);
			if (!tmp_stdin)
				ft_err("Error malloc: read_stdin - tmp");
			free(tmp_del);
			free(line);
		}
		if (r == 0)
			break ;
	}
	return (tmp_stdin);
}
