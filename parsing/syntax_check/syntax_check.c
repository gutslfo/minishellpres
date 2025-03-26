/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:54:09 by pitran            #+#    #+#             */
/*   Updated: 2025/03/26 13:57:12 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int syntax_is_valid(t_token **token_list)
{
    if (!quote_syntax_is_valid(token_list))
        return (0);
    if (!redir_syntax_is_valid(token_list))
        return (0);
    if (!redir_syntax_is_valid(token_list))
        return (0);
    if (!operator_syntax_is_valid(token_list))
        return (0);
    return (1);
}