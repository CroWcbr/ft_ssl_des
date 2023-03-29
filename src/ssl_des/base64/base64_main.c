/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:59:18 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/29 22:29:48 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ssl_des/base64.h"
#include <stdio.h>

static void	base64_encrypt_algo(const char *input, \
								const size_t inp_len, \
								char *result)
{
	uint32_t	pack_3_bytes;
	size_t		i;
	int			i3;
	size_t		j;

	i = 0;
	j = 0;
	while (i < inp_len)
	{
		pack_3_bytes = 0;
		i3 = -1;
		while (++i3 < 3)
			if (i + i3 < inp_len)
				pack_3_bytes |= (uint32_t)input[i + i3] << (16 - i3 * 8);
		i += i3;
		result[j++] = g_b64[(pack_3_bytes >> 3 * 6) & 0x3F];
		result[j++] = g_b64[(pack_3_bytes >> 2 * 6) & 0x3F];
		result[j++] = g_b64[(pack_3_bytes >> 1 * 6) & 0x3F];
		result[j++] = g_b64[(pack_3_bytes >> 0 * 6) & 0x3F];
	}
	while (i-- > inp_len)
		result[--j] = '=';
}

static char	*base64_encrypt(const char *input, \
						const size_t inp_len, \
						const size_t out_len)
{
	char	*result;

	result = malloc(out_len + 1);
	if (!result)
		ft_err("Error malloc: base64_main.c - base64_encrypt - result");
	result[out_len] = '\0';
	base64_encrypt_algo(input, inp_len, result);
	return (result);
}

static void	base64_decrypt_algo(const char *input, \
								const size_t inp_len, \
								char *result,
								const size_t out_len)
{
	uint32_t	pack_4_bytes;
	size_t		i;
	int			i4;
	size_t		j;
// DONT work!!!!!!!!!!!!!!!!!!!!!!
	i = 0;
	j = 0;
	while (i < inp_len)
	{
		pack_4_bytes = 0;
		i4 = -1;
		while (++i4 < 4)
			if (input[i + i4] != '=')
				pack_4_bytes |= g_b64[(unsigned char)input[i + i4]] << (18 - i4 * 6);
		i += i4;
		if (j < out_len)
			result[j++] = (pack_4_bytes >> 2 * 8) & 0xFF;
		if (j < out_len)
			result[j++] = (pack_4_bytes >> 1 * 8) & 0xFF;
		if (j < out_len)
			result[j++] = (pack_4_bytes >> 0 * 8) & 0xFF;
	}
}

static char	*base64_decrypt(const char *input, \
						const size_t inp_len, \
						const size_t out_len)
{
	char	*result;
	result = malloc(out_len + 1);
	if (!result)
		ft_err("Error malloc: base64_main.c - base64_decrypt - result");
	result[out_len] = '\0';
	base64_decrypt_algo(input, inp_len, result, out_len);
	return (result);
}

char	*base64_main(char mode, \
					const char *input, \
					const size_t inp_len, \
					size_t *out_len)
{
	char	*result;

	if (mode == 'E')
	{
		*out_len = 4 * ((inp_len + 2) / 3);
		result = base64_encrypt(input, inp_len, *out_len);
	}
	else
	{
		if (inp_len % 4 != 0)
			return NULL;
		*out_len = inp_len / 4 * 3;
		if (input[inp_len - 1] == '=')
			(*out_len)--;
		if (input[inp_len - 2] == '=')
			(*out_len)--;
		result = base64_decrypt(input, inp_len, *out_len);
	}
	printf("%s\n", result);
	return (result);
}
