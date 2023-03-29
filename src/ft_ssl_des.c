/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:28:00 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/29 20:41:06 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ssl.h"

static char	*read_file(char *cmd, char *input_file, size_t *len)
{
	char		*str_file;
	int			fd;

	fd = open(input_file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("ft_ssl: ");
		ft_putstr(cmd);
		ft_putstr(": ");
		ft_putstr(input_file);
		ft_putstr(": No such file or directory\n");
		return (NULL);
	}
	str_file = read_fd_to_str(fd, len);
	close(fd);
	return (str_file);
}

void	make_ssl_des(t_ssl_des *ssl_des)
{
	if (ssl_des->input_file)
		ssl_des->input_buffer = read_file(ssl_des->cmd, ssl_des->input_file, &ssl_des->input_len);
	if (!ft_strcmp(ssl_des->cmd, "base64"))
		ssl_des->output_buffer = ssl_des->coding_func(ssl_des->mode, \
													ssl_des->input_buffer, \
													ssl_des->input_len, \
													&ssl_des->output_len);
	else
		ft_putstr("make_des, not base64\n");;



	free(ssl_des->input_buffer);
}
