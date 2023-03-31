/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:59:18 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/31 13:41:08 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ssl_des/base64.h"

static uint32_t	base64_find_pack_4_bytes(const char *input, int *i)
{
	int			i_tmp;
	uint32_t	pack_4_bytes;
	char		*ptr;

	pack_4_bytes = 0;
	i_tmp = 0;
	while (i_tmp < 4)
	{
		if (input[*i] != '\n' && input[*i] != ' ')
		{
			ptr = ft_strchr(g_b64, input[*i]);
			if (ptr)
				pack_4_bytes |= (ptr - g_b64) << (18 - i_tmp * 6);
			i_tmp++;
		}
		(*i)++;
	}
	return (pack_4_bytes);
}

static void	base64_decode_algo(const char *input, \
									const size_t inp_len, \
									char *result, \
									const size_t out_len)
{
	int			i;
	int			j;
	uint32_t	pack_4_bytes;

	i = 0;
	j = 0;
	while (j < out_len && i < inp_len)
	{
		pack_4_bytes = base64_find_pack_4_bytes(input, &i);
		if (j < out_len)
			result[j++] = (pack_4_bytes >> (2 * 8)) & 0xFF;
		if (j < out_len)
			result[j++] = (pack_4_bytes >> (1 * 8)) & 0xFF;
		if (j < out_len)
			result[j++] = (pack_4_bytes >> (0 * 8)) & 0xFF;
	}
}

static void	base64_find_out_len(const char *input, \
									const size_t inp_len, \
									size_t *out_len)
{
	size_t	update_input_len;
	size_t	eq;
	size_t	i;

	update_input_len = 0;
	i = 0;
	eq = 0;
	while (i < inp_len)
	{
		if (ft_isalnum(input[i]) || input[i] == '+' || input[i] == '/')
			update_input_len++;
		else if (input[i] == '=' && eq < 2)
		{
			update_input_len++;
			eq++;
		}
		else if (input[i] == '\n' || input[i] == ' ')
			;
		else
			return ;
		i++;
	}
	if (update_input_len % 4 != 0)
		return ;
	*out_len = 3 * update_input_len / 4 - eq;
}

char	*base64_decode(const char *input, \
						const size_t inp_len, \
						size_t *out_len)
{
	char		*result;

	base64_find_out_len(input, inp_len, out_len);
	if (!(*out_len))
	{
		result = ft_strdup("");
		if (!result)
			ft_err("Error malloc: base64_decode.c - base64_decode - result");
	}
	else
	{
		result = malloc(*out_len + 1);
		if (!result)
			ft_err("Error malloc: base64_decode.c - base64_decode - result");
		result[*out_len] = '\0';
		base64_decode_algo(input, inp_len, result, *out_len);
	}
	return (result);
}
