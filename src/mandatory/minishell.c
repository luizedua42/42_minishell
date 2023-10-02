/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:07:51 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/28 19:22:12 by pdavi-al         ###   ########.fr       */
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

void	handle_command(t_minishell *minishell, char *command)
{
	bool			success_create_tokens;
	t_token_type	*token_array;
	size_t			i;

	i = 0;
	success_create_tokens = create_tokens(&minishell->tokens, command);
	token_array = create_token_array(minishell->tokens, &i);
	if (!(success_create_tokens && syntax_analysis(token_array)))
		ft_fprintf(2, "minishell: syntax error\n");
	else
	{
		get_redirects(minishell);
		sanitize_tokens(minishell);
		print_tokens(minishell, minishell->tokens);
		print_redirects(minishell);
		clear_fds(minishell);
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
		prompt = "\001\x1b[32m\002minishell$ \001\x1b[0m\002";
		command = readline(prompt);
		add_history(command);
		if (ft_strncmp("exit", command, 4) == 0)
		{
			free(command);
			return (minishell_exit(&minishell));
		}
		handle_command(&minishell, command);
	}
	return (minishell.exit_status);
}
