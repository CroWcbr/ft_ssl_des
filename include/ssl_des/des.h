/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:11:32 by cdarrell          #+#    #+#             */
/*   Updated: 2024/07/03 16:52:02 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# include "../../libft/include/libft.h"
# include <stdint.h>
# include "../ft_bool.h"

typedef struct s_des
{
    uint8_t     *input;
    size_t      inp_len;
    uint8_t     *output;
    size_t      out_len;    

    uint8_t     k[16];
    uint8_t     v[8];
}               t_des;

char		*base64_main(const char mode, const char *input, const size_t inp_len, size_t *out_len);

// char		*des_cbc_main(const char mode, const char *input, const size_t inp_len, size_t *out_len,
// 							t_bool a, char *k, char *p, char *s, char *v);
// char		*des_ecb_main(const char mode, const char *input, const size_t inp_len, size_t *out_len,
// 							t_bool a, char *k, char *p, char *s, char *v);


void	    ft_err(char *str);

#endif
