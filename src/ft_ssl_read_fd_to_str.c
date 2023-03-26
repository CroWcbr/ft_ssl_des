/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_read_fd_to_str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 16:22:33 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/26 21:33:23 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"

static char	*str_append(char *str_file, char *input_buff, \
						size_t r, uint64_t *len)
{
	char		*tmp;

	tmp = (char *)malloc(*len + r);
	if (!str_file)
		ft_err("Error malloc: ft_ssl.c - str_append - str_file");
	ft_memcpy(tmp, str_file, *len);
	free(str_file);
	ft_memcpy(tmp + *len, input_buff, r);
	*len += r;
	return (tmp);
}

char	*read_fd_to_str(int fd, uint64_t *len)
{
	char		*str_file;
	char		input_buff[1000];
	int			r;

	str_file = ft_strdup("");
	if (!str_file)
		ft_err("Error malloc: ft_ssl.c - hash_file - str_file");
	while (1)
	{
		r = read(fd, input_buff, 1000);
		if (r == 0)
			break ;
		if (r < 0)
		{
			free (str_file);
			ft_err("Error read: ft_ssl.c - str_file - r");
		}
		str_file = str_append(str_file, input_buff, r, len);
	}
	return (str_file);
}
