/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:59:18 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/29 23:52:35 by cdarrell         ###   ########.fr       */
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
								char *result, \
								const size_t out_len)
{
	uint32_t	pack_4_bytes;
	size_t		i;
	int			i_tmp;
	size_t		j;
	int			k;

	i = 0;
	j = 0;
	while (i < inp_len)
	{
		pack_4_bytes = 0;
		i_tmp = -1;
		while (++i_tmp < 4)
		{
			if (input[i + i_tmp] != '=')
			{
				k = -1;
				while (g_b64[++k])
					if (input[i + i_tmp] == g_b64[k])
						break ;
				if (!g_b64[k])
				{
					free (result);
					result = NULL;
					return ;
				}
				pack_4_bytes |= k << (18 - i_tmp * 6);
			}
		}
		i += i_tmp;
		i_tmp = -1;
		while (++i_tmp < 3)
			if (j < out_len)
				result[j++] = (pack_4_bytes >> ((2 - i_tmp) * 8)) & 0xFF;
	}
}

// static void	base64_decrypt_algo(const char *input, \
// 								const size_t inp_len, \
// 								char *result, \
// 								const size_t out_len)
// {
// 	uint32_t	pack_4_bytes;
// 	size_t		i;
// 	int			i4;
// 	size_t		j;

// 	char cd64[]="|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";

// 	i = 0;
// 	j = 0;
// 	while (i < inp_len)
// 	{
// 		pack_4_bytes = 0;
// 		i4 = -1;
// 		while (++i4 < 4)
// 		{
// 			if (input[i + i4] != '=')
// 			{
// 				int v;
// 				v = input[i + i4];
// 				v = ((v < 43 || v > 122) ? 0 : (int) cd64[ v - 43 ]);
// 				if( v != 0 )
// 					v = ((v == (int)'$') ? 0 : v - 61);

// 				pack_4_bytes |= (unsigned char) (v - 1) << (18 - i4 * 6);
// 			}
// 		}
// 		i += i4;
// 		i4 = -1;
// 		while (++i4 < 3)
// 			if (j < out_len)
// 				result[j++] = (pack_4_bytes >> (16 - 8 * i4)) & 0xFF;
// 	}
// }

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

char	*base64_main(const char mode, \
					const char *input, \
					size_t inp_len, \
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
		if (input[inp_len - 1] == '\n')
			inp_len--;
		if (inp_len % 4 != 0)
			return (NULL);
		*out_len = inp_len / 4 * 3 + 1;
		if (input[inp_len - 1] == '=')
			(*out_len)--;
		if (input[inp_len - 2] == '=')
			(*out_len)--;
		result = base64_decrypt(input, inp_len, *out_len);
	}
	printf("%s\n", result);
	return (result);
}
