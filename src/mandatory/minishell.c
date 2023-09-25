/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:07:51 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/25 20:28:50 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_list *tokens)
{
	t_token	*aux;

	while (tokens != NULL)
	{
		aux = tokens->content;
		ft_printf("value: %s	type: %i\n", aux->value, aux->type);
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
			minishell->fds.fd_in.redirect_to, minishell->fds.fd_in.type);
	ft_printf("OUTPUT = redirect_to: %s	redirect_type: %i\n", \
			minishell->fds.fd_out.redirect_to, minishell->fds.fd_out.type);
	ft_printf("ERROR = redirect_to: %s	redirect_type: %i\n", \
			minishell->fds.fd_error.redirect_to, minishell->fds.fd_error.type);
}

void	handle_command(t_minishell *minishell, char *command)
{
	t_token_type	*token_array;
	size_t			i;

	i = 0;
	minishell->tokens = create_tokens(command);
	token_array = create_token_array(minishell->tokens, &i);
	if (token_array == NULL)
		return ;
	if (syntax_analysis(token_array) == false)
		ft_fprintf(2, "minishell: syntax error\n");
	else
	{
		get_redirects(minishell);
		sanitize_tokens(minishell);
		print_tokens(minishell->tokens);
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
