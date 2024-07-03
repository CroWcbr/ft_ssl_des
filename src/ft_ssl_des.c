/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:28:00 by cdarrell          #+#    #+#             */
/*   Updated: 2024/07/03 10:12:23 by cdarrell         ###   ########.fr       */
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
	
	if (ssl_des->input_buffer)
	{
		if (!ft_strcmp(ssl_des->cmd, "base64"))
			ssl_des->output_buffer = ssl_des->base64(ssl_des->mode, \
														ssl_des->input_buffer, \
														ssl_des->input_len, \
														&ssl_des->output_len);
		else
		{
			ssl_des->output_buffer = ssl_des->coding_func(ssl_des->mode, \
														ssl_des->input_buffer, \
														ssl_des->input_len, \
														&ssl_des->output_len,
														ssl_des->a, ssl_des->k, ssl_des->p, ssl_des->s, ssl_des->v);


			if (ssl_des->p_stdin)
				free(ssl_des->p);
		}

		// change output!!! to file if -o
		if (ssl_des->output_buffer)
		{
			printf("%s", ssl_des->output_buffer);
			free(ssl_des->output_buffer);	
		}

		free(ssl_des->input_buffer);
	}

	free(ssl_des);
}
