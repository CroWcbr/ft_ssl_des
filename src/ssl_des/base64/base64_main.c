/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:59:18 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/31 12:02:25 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ssl_des/base64.h"

static void	base64_encode_algo(const char *input, \
								const size_t inp_len, \
								char *result, \
								const size_t out_len)
{
	uint32_t	pack_3_bytes;
	size_t		i;
	int			i_tmp;
	size_t		j;

	i = 0;
	j = 0;
	while (i < inp_len)
	{
		pack_3_bytes = 0;
		i_tmp = -1;
		while (++i_tmp < 3)
			if (i + i_tmp < inp_len)
				pack_3_bytes |= (uint32_t)input[i + i_tmp] << (16 - i_tmp * 8);
		i += i_tmp;
		i_tmp = -1;
		while (++i_tmp < 4)
			result[j++] = g_b64[(pack_3_bytes >> ((3 - i_tmp) * 6)) & 0x3F];
        if ((j + 1) % 65 == 0 && j < out_len - 4)
                result[j++] = '\n';
	}
	while (i-- > inp_len)
		result[--j] = '=';
}

char	*base64_encode(const char *input, \
						const size_t inp_len, \
						size_t *out_len)
{
	char	*result;

	*out_len = 4 * ((inp_len + 2) / 3);
	*out_len += *out_len / 64;
	if (*out_len)
		*out_len += 1 - ((*out_len) % 65 ? 0 : 1);
	
	result = malloc(*out_len + 1);
	if (!result)
		ft_err("Error malloc: base64_main.c - base64_encode - result");
	
	if ((*out_len) > 0)
		result[(*out_len) - 1] = '\n';
	result[*out_len] = '\0';

	base64_encode_algo(input, inp_len, result, *out_len);
	return (result);
}

char	*base64_main(const char mode, \
					const char *input, \
					const size_t inp_len, \
					size_t *out_len)
{
	char	*result;

	if (mode == 'E')
		result = base64_encode(input, inp_len, out_len);
	else
		result = base64_decode(input, inp_len, out_len);
	return (result);
}
