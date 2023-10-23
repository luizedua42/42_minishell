/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:14:31 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/22 21:53:08 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static t_minishell	*copy_minishell(t_list *envs, int exit_status);
static t_list		*copy_envs(t_list *envs);
static void			copy_tokens(t_list **tokens, t_minishell *new_shell,
						char *value, t_token_type type);

t_minishell	*create_sub_shells(t_list **tokens, t_list *envs, int exit_status)
{
	t_token		*token;
	t_minishell	*new_shell;
	t_minishell	*shell;

	new_shell = copy_minishell(envs, exit_status);
	while (*tokens != NULL)
	{
		token = (*tokens)->content;
		if (token->type == OPEN_PARENTHESIS)
		{
			copy_tokens(tokens, new_shell, "subshell", SHELL);
			shell = create_sub_shells(tokens, envs, exit_status);
			ft_lstadd_back(&new_shell->shells, ft_lstnew(shell));
		}
		else if (token->type == CLOSE_PARENTHESIS)
		{
			*tokens = (*tokens)->next;
			break ;
		}
		else
			copy_tokens(tokens, new_shell, token->value, token->type);
	}
	return (new_shell);
}

static t_minishell	*copy_minishell(t_list *envs, int exit_status)
{
	t_minishell	*new_shell;

	new_shell = ft_calloc(1, sizeof(t_minishell));
	new_shell->envs = copy_envs(envs);
	new_shell->exit_status = exit_status;
	return (new_shell);
}

static t_list	*copy_envs(t_list *envs)
{
	t_list	*new_envs;
	t_env	*env;
	t_env	*sub_env;

	new_envs = NULL;
	while (envs != NULL)
	{
		env = envs->content;
		sub_env = ft_calloc(1, sizeof(t_env));
		if (env->value != NULL)
			sub_env->value = ft_strdup(env->value);
		sub_env->key = ft_strdup(env->key);
		ft_lstadd_back(&new_envs, ft_lstnew(sub_env));
		envs = envs->next;
	}
	return (new_envs);
}

static void	copy_tokens(t_list **tokens, t_minishell *new_shell, char *value,
		t_token_type type)
{
	t_token	*sub_token;

	sub_token = ft_calloc(1, sizeof(t_token));
	sub_token->value = ft_strdup(value);
	sub_token->type = type;
	ft_lstadd_back(&new_shell->tokens, ft_lstnew(sub_token));
	*tokens = (*tokens)->next;
}
