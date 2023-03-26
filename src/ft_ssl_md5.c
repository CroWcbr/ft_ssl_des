/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 16:22:33 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/26 21:26:32 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"

static void	free_ssl(t_ssl_md5 *ssl_md5)
{
	ft_lstclear(&ssl_md5->hash_list, free);
	free(ssl_md5->hash_to_upper);
	free(ssl_md5);
}

static uint8_t	*read_file(uint8_t *(*hash_func)(const char *str, \
												const uint64_t len), \
						t_hash_md5 *hash, char *hash_type)
{
	char		*str_file;
	uint64_t	len;
	int			fd;
	uint8_t		*result;

	fd = open(hash->name, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("ft_ssl: ");
		ft_putstr(hash_type);
		ft_putstr(": ");
		ft_putstr(hash->name);
		ft_putstr(": No such file or directory\n");
		return (NULL);
	}
	len = 0;
	str_file = read_fd_to_str(fd, &len);
	result = hash_func(str_file, len);
	free(str_file);
	close(fd);
	return (result);
}

void	make_ssl_md5(t_ssl_md5 *ssl_md5)
{
	t_list		*tmp;
	t_hash_md5	*hash;
	uint8_t		*result;

	tmp = ssl_md5->hash_list;
	while (tmp)
	{
		hash = (t_hash_md5 *)tmp->content;
		if (hash->type == false)
			result = ssl_md5->hash_func(hash->name, ft_strlen(hash->name));
		else
			result = read_file(ssl_md5->hash_func, hash, ssl_md5->cmd);
		print_hash(ssl_md5, hash, result);
		free(hash->name);
		tmp = tmp->next;
		free(result);
	}
	free_ssl(ssl_md5);
}
