/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:53:49 by cdarrell          #+#    #+#             */
/*   Updated: 2023/03/25 17:04:05 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdio.h>
# include <stdint.h>
# include "../libft/include/libft.h"

# define IS_DEBUG 1

typedef enum s_bool
{
	false,
	true
}			t_bool;

typedef struct s_ssl_md5
{
	char			*cmd;
	char			*hash_to_upper;
	uint32_t		crypt_len;
	uint8_t			*(*hash_func)(const char *str, const uint64_t len);
	t_bool			p;
	t_bool			q;
	t_bool			r;
	t_bool			s;
	t_list			*hash_list;
}				t_ssl_md5;

// type : 0 - string, 1 - file
typedef struct s_hash_md5
{
	t_bool			type;
	char			*name;
}				t_hash_md5;

typedef struct s_ssl_des
{

}				t_ssl_des;

typedef struct s_ssl
{
	char			*cmd;
	t_ssl_md5		*ssl_md5;
	t_ssl_des		*ssl_des;
}					t_ssl;

t_ssl		*parse(char **argv);
t_ssl_md5	*parse_ssl_md5(char *cmd, char **argv);
t_bool		parse_ssl_md5_argv(char **argv, t_ssl_md5 *ssl_md5);
void		parse_ssl_md5_flag_p(t_ssl_md5 *ssl_md5);
t_hash_md5	*create_ssl_md5_hash_node(char *name);
void		parse_print(t_ssl *ssl);

void		make_ssl_md5(t_ssl_md5 *ssl_md5);
uint8_t		*md5_main(const char *str, const uint64_t len);
uint8_t		*sha256_main(const char *str, const uint64_t len);
uint8_t		*sha512_main(const char *str, const uint64_t len);
uint8_t		*whirlpool(const char *str, const uint64_t len);
void		print_hash(t_ssl_md5 *ssl, t_hash_md5 *hash, uint8_t *result);

void		print_test(char *err, uint8_t *tt, int len_byte);
void		ft_err(char *str);

#endif