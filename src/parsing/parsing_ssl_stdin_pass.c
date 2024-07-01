/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ssl_stdin_pass.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:16:09 by cdarrell          #+#    #+#             */
/*   Updated: 2024/07/01 12:50:28 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_ssl.h"

char	*read_pass(char mode)
{
    char *pass;
    char* pass_tmp;
        
    if (mode == 'E')
    {
        pass_tmp = getpass("enter encryption password: ");
        if (!pass_tmp)
        {
            ft_putstr("Error in getpass - pass\n");
            return (NULL);
        }
        pass = ft_strdup(pass_tmp);
        if (!pass)
            ft_err("Error malloc: parsing_ssl_stdin_pass.c");
        pass_tmp = getpass("Verifying - enter encryption password: ");
        if (!pass_tmp)
        {
            ft_putstr("Error in getpass - pass verifying\n");
            free(pass);
            return (NULL);
        }

        if (ft_strcmp(pass, pass_tmp))
        {
            ft_putstr("Verify failure\n");
            free(pass);
            return (NULL);
        }
    }
    else
    {
        pass_tmp = getpass("enter decryption password: ");
        if (!pass_tmp)
        {
            ft_putstr("Error in getpass\n");
            return (NULL);
        }
        pass = ft_strdup(pass_tmp);
        if (!pass)
            ft_err("Error malloc: parse_ssl_des.c - getpass");
    }

    return pass;
}