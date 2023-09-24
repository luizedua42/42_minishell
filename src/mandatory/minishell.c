/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:07:51 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/24 03:02:15 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_envs(t_list *envs)
{
	t_env	*aux;

	while (envs != NULL)
	{
		aux = envs->content;
		ft_printf("key : %s		value: %s\n", aux->key, aux->value);
		envs = envs->next;
	}
}

void	verify_syntax(t_minishell *minishell)
{
	t_token_type	*token_array;
	int				i;

	token_array = create_token_array(minishell->tokens, &i);
	if (syntax_analysis(token_array) == false)
		ft_fprintf(2, "minishell : syntax error\n");
	else
		print_tokens(minishell->tokens);
	free(token_array);
}

int	main(int argc, char **argv, char **envp)
{
	char		*command;
	char		*prompt;
	char		**unset_args;
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
		print_envs(minishell.envs);
		minishell.tokens = create_tokens(command);
		verify_syntax(&minishell);
		ft_lstclear(&minishell.tokens, del_token);
		free(command);
	}
	return (minishell.exit_status);
}
