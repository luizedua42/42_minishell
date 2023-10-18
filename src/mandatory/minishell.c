/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:07:51 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/18 20:55:14 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*expand_shell(t_minishell *minishell);
void		handle_command(t_minishell **minishell, char *command);
static void	exit_main(t_minishell *minishell, char *command);

int	main(int argc, char **argv, char **envp)
{
	char		*command;
	char		*prompt;
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	minishell = init_minishell(envp);
	while (1)
	{
		handle_signal();
		prompt = create_prompt();
		command = readline(prompt);
		if (command == NULL)
			exit_main(minishell, command);
		if (command[0] != '\0')
		{
			add_history(command);
			handle_command(&minishell, command);
		}
		else if (command[0] == '\0')
			free(command);
	}
}

t_minishell	*expand_shell(t_minishell *minishell)
{
	t_list		*tokens;
	t_minishell	*new_shell;

	tokens = minishell->tokens;
	new_shell = create_sub_shells(&tokens, minishell->envs);
	clear_shell(minishell);
	return (new_shell);
}

void	handle_command(t_minishell **minishell, char *command)
{
	bool			valid_syntax;
	t_token_type	*token_array;
	bool			success_create_tokens;

	success_create_tokens = create_tokens(&(*minishell)->tokens, command);
	token_array = create_token_array((*minishell)->tokens);
	valid_syntax = syntax_analysis(token_array);
	if (token_array != NULL)
	{
		free(token_array);
		if (!(success_create_tokens && valid_syntax))
			ft_fprintf(2, "minishell: syntax error\n");
		else
		{
			*minishell = expand_shell(*minishell);
			executor(*minishell);
			clear_subshells(*minishell);
		}
	}
	ft_lstclear(&(*minishell)->tokens, del_token);
	free(command);
}

static void	exit_main(t_minishell *minishell, char *command)
{
	free(command);
	rl_clear_history();
	clear_shell(minishell);
	ft_printf("exit\n");
	exit (EXIT_SUCCESS);
}
