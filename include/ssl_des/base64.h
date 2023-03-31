/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:00:32 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/31 10:43:35 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "../libft/include/libft.h"
# include <stdint.h>

static const char	g_b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char	*base64_encode(const char *input, \
						const size_t inp_len, \
						size_t *out_len);
char	*base64_decode(const char *input, \
						const size_t inp_len, \
						size_t *out_len);

void	ft_err(char *str);

#endif
