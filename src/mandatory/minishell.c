/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:07:51 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/19 20:49:47 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_token(void *content)
{
	t_token	*token;

	token = content;
	free(token->value);
	free(token);
}

void	print_tokens(t_list *tokens)
{
	t_token	*aux;

	while (tokens != NULL)
	{
		aux = tokens->content;
		ft_printf("value: %s	type : %i\n", aux->value, aux->type);
		tokens = tokens->next;
	}
}

int	main(int argc, char **argv)
{
	t_list	*tokens;
	char	*command;
	char	*prompt;

	(void)argc;
	(void)argv;
	while (1)
	{
		prompt = "minishell$ ";
		command = readline(prompt);
		if (command[0] == '[')
			break ;
		tokens = create_tokens(command);
		print_tokens(tokens);
		ft_lstclear(&tokens, del_token);
		free(command);
	}
	free(command);
	return (0);
}
