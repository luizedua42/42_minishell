/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:01:33 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/16 18:04:28 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h" 

typedef enum e_token_type
{
	AND,
	OR,
	PIPE,
	WORD,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC_IN,
	HEREDOC_OUT,
	QUOTE,
	DQUOTE,
	DOLLAR_SIGN,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
}	t_token_type;

typedef struct s_token
{
	t_token_type type;
	char	*value;	
}	t_token;

#endif
