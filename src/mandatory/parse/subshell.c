/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:14:31 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/03 21:26:34 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_minishell	*copy_minishell(t_minishell *minishell);
static t_list		*copy_envs(t_list *envs);
static void			copy_tokens(t_minishell **minishell, \
						t_minishell *new_shell, char *value, t_token_type type);

t_minishell	*create_sub_shells(t_minishell **minishell)
{
	t_token		*token;
	t_minishell	*new_shell;
	t_minishell	*shell;

	new_shell = copy_minishell(*minishell);
	while ((*minishell)->tokens != NULL)
	{
		token = (*minishell)->tokens->content;
		if (token->type == OPEN_PARENTHESIS)
		{
			copy_tokens(minishell, new_shell, "sdfas", SHELL);
			shell = create_sub_shells(minishell);
			ft_lstadd_back(&new_shell->shells, ft_lstnew(shell));
		}
		else if (token->type == CLOSE_PARENTHESIS)
		{
			(*minishell)->tokens = (*minishell)->tokens->next;
			break ;
		}
		else
			copy_tokens(minishell, new_shell, token->value, token->type);
	}
	return (new_shell);
}

static t_minishell	*copy_minishell(t_minishell *minishell)
{
	t_minishell	*new_shell;

	new_shell = ft_calloc(1, sizeof(t_minishell));
	new_shell->envs = copy_envs(minishell->envs);
	new_shell->tokens = NULL;
	new_shell->exit_status = EXIT_SUCCESS;
	new_shell->fds.fd_in.redirect_to = NULL;
	new_shell->fds.fd_in.type = END_ARRAY;
	new_shell->fds.fd_out.redirect_to = NULL;
	new_shell->fds.fd_out.type = END_ARRAY;
	new_shell->fds.fd_error.redirect_to = NULL;
	new_shell->fds.fd_error.type = END_ARRAY;
	new_shell->shells = NULL;
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
		sub_env->value = ft_strdup(env->value);
		sub_env->key = ft_strdup(env->key);
		ft_lstadd_back(&new_envs, ft_lstnew(sub_env));
		envs = envs->next;
	}
	return (new_envs);
}

static void	copy_tokens(t_minishell **minishell, t_minishell *new_shell, \
						char *value, t_token_type type)
{
	t_token	*sub_token;

	sub_token = ft_calloc(1, sizeof(t_token));
	sub_token->value = ft_strdup(value);
	sub_token->type = type;
	ft_lstadd_back(&new_shell->tokens, ft_lstnew(sub_token));
	(*minishell)->tokens = (*minishell)->tokens->next;
}
