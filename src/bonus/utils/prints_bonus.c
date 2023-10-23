/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:33:15 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/22 21:53:08 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	print_tokens(t_minishell *minishell, t_list *tokens)
{
	t_token	*token;
	char	*aux;

	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type == WORD)
		{
			aux = expand(minishell, token->value, false);
			free(token->value);
			token->value = aux;
		}
		ft_printf("value: %s	type: %i\n", token->value, token->type);
		tokens = tokens->next;
	}
}

void	print_envs(t_list *envs)
{
	t_env	*aux;

	while (envs != NULL)
	{
		aux = envs->content;
		ft_printf("key: %s		value: %s\n", aux->key, aux->value);
		envs = envs->next;
	}
}

void	print_sub_shells(t_minishell *minishell, int level)
{
	t_list	*shell;

	shell = minishell->shells;
	while (shell != NULL)
	{
		print_sub_shells(shell->content, level + 1);
		shell = shell->next;
	}
	ft_printf("level %d ------------------\n", level);
	print_tokens(minishell, minishell->tokens);
}
