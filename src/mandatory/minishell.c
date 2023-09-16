/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:01:24 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/16 19:35:31 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_type type, char * value)
{
	t_token *token;
	token = ft_calloc(1, sizeof(t_token));
	token->type = type;
	token->value = value;
	return (token);
}

int main(int argc, char **argv)
{
	t_list *tokens;
	t_token *teste;

	int i = 0;
	if (argc != 2)
		return 1;
	tokens  = NULL;
	while(argv[1][i])
	{
		if(ft_strncmp(&argv[1][i],"|",1) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(PIPE, "|")));
		else if (ft_strncmp(&argv[1][i],"&&",1) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(AND, "&&")));
		else if (ft_strncmp(&argv[1][i],"&&",1) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(AND, "&&")));
		else if (ft_strncmp(&argv[1][i],"&&",1) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(AND, "&&")));
		else if (ft_strncmp(&argv[1][i],"&&",1) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(AND, "&&")));
		else if (ft_strncmp(&argv[1][i],"&&",1) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(AND, "&&")));
		else if (ft_strncmp(&argv[1][i],"&&",1) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(AND, "&&")));
		i++;
	}
	teste = (t_token*)(tokens->content);
	ft_printf("%s", teste->value);
	return (0);
}
