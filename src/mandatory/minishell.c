/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:07:51 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/11 20:56:39 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_redirects(t_minishell *minishell)
{
	ft_printf("INPUT = redirect_to: %s	redirect_type: %i\n", \
		minishell->fds.fd_in.redirect_to,
		minishell->fds.fd_in.type);
	ft_printf("OUTPUT = redirect_to: %s	redirect_type: %i\n", \
		minishell->fds.fd_out.redirect_to,
		minishell->fds.fd_out.type);
	ft_printf("ERROR = redirect_to: %s	redirect_type: %i\n", \
		minishell->fds.fd_error.redirect_to,
		minishell->fds.fd_error.type);
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
	print_redirects(minishell);
}

void	handle_command(t_minishell *minishell, char *command)
{
	bool			success_create_tokens;
	t_token_type	*token_array;
	t_minishell		*new_shell;
	t_list			*tokens;

	success_create_tokens = create_tokens(&minishell->tokens, command);
	token_array = create_token_array(minishell->tokens);
	if (!(success_create_tokens && syntax_analysis(token_array)))
		ft_fprintf(2, "minishell: syntax error\n");
	else
	{
		tokens = minishell->tokens;
		new_shell = create_sub_shells(&tokens, minishell->envs);
		executor(*new_shell);
		ft_lstclear(&(minishell)->tokens, del_token);
		ft_lstclear(&(minishell)->shells, clear_shells);
		clear_fds((minishell));
		clear_shells(new_shell);
	}
	free(token_array);
	ft_lstclear(&minishell->tokens, del_token);
	free(command);
}

int	main(int argc, char **argv, char **envp)
{
	char		*command;
	char		*prompt;
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	init_minishell(&minishell, envp);
	while (1)
	{
		prompt = create_prompt();
		command = readline(prompt);
		if (command == NULL || ft_strncmp("exit", command, 4) == 0)
		{
			free(command);
			return (minishell_exit(&minishell));
		}
		if (command[0] != '\0')
		{
			add_history(command);
			handle_command(&minishell, command);
		}
		else if (command[0] == '\0')
			free(command);
	}
}
