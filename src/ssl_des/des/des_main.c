/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:46:36 by cdarrell          #+#    #+#             */
/*   Updated: 2024/07/05 17:33:16 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/provider.h>

#include "../../../include/ssl_des/des.h"

void char_to_hex(uint8_t *dest, unsigned char c)
{
    const char *hex_chars = "0123456789abcdef";
    dest[0] = hex_chars[c >> 4];
    dest[1] = hex_chars[c & 0x0f];
}

void text_to_hex(const char *str, size_t len, uint8_t *out)
{
    size_t i = 0;
    while(str[i])
    {
        char_to_hex(out + i * 2, (unsigned char)str[i]);
        ++i;
    }
    
    for(; i < len; ++i)
    {
        out[i * 2] = '0';
        out[i * 2 + 1] = '0';
    }
}

#include <stdio.h>

uint8_t		*des_main(const char *cmd, const char mode, const char *const_input, const size_t const_inp_len, size_t *out_len,
						t_bool a, char *k, char *p, char *s, char *v)
{
    t_des   des_param;

    if (a && mode == 'D')
        des_param.input = base64_main(mode, const_input, const_inp_len, &des_param.inp_len);
    else
    {
        des_param.input = ft_strdup(const_input);
        if (!des_param.input)
            ft_err("Error malloc: des_main.c - des_main - des_param.input");
        des_param.inp_len = const_inp_len;
    }

    // if (v)
    //     text_to_hex(v, 8, des_param.v);
    printf("!!!%ld %s\n", ft_strlen(k), k);
    // if (k)
        text_to_hex(k, 8, des_param.k);
    
    des_param.output = NULL;
    
    printf("!!!%ld %s\n", ft_strlen(des_param.k), des_param.k);
    // else
    // {
        
    //     if (s)
    //         text_to_hex(s, 8, des_param.s);
    //     else
    //     {

    //     }

    //     // pbkdf2
 

    // }

    // algo des




    free(des_param.input);
    if (a && mode == 'E')
    {
        char *tmp;
        tmp = des_param.output;
        des_param.output = base64_main(mode, tmp, des_param.out_len, &des_param.out_len);
        free(tmp);
    }

    *out_len = des_param.out_len;
    return des_param.output;

}
