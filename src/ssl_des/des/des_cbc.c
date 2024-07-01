/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:09:08 by cdarrell          #+#    #+#             */
/*   Updated: 2024/07/01 14:19:49 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/ssl_des/des_cbc.h"

char		*des_cbc_main(const char mode, const char *input, const size_t inp_len, size_t *out_len,
							t_bool a, char *k, char *p, char *s, char *v)
{
	char	*result = NULL;
	
	ft_putstr("des_cbc_main\n");
	// if (mode == 'E')
	// 	result = base64_encode(input, inp_len, out_len);
	// else
	// 	result = base64_decode(input, inp_len, out_len);
	return (result);
}
