/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:07:51 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/26 01:35:39 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	handle_command(t_minishell **minishell, char *command);
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

static void	handle_command(t_minishell **minishell, char *command)
{
	bool			valid_syntax;
	t_token_type	*token_array;
	bool			success_create_tokens;

	success_create_tokens = create_tokens(&(*minishell)->tokens, command);
	token_array = create_token_array((*minishell)->tokens);
	valid_syntax = syntax_analysis(token_array);
	if (token_array != NULL)
		free(token_array);
	if (!(success_create_tokens && valid_syntax))
	{
		ft_fprintf(STDERR_FILENO, "minishell: syntax error\n");
		(*minishell)->exit_status = 2;
	}
	else
	{
		(*minishell)->exit_status = executor(*minishell);
		unlink_all((*minishell)->tokens);
		clear_shell_content(*minishell);
	}
	ft_lstclear(&(*minishell)->tokens, del_token);
	free(command);
}

static void	exit_main(t_minishell *minishell, char *command)
{
	int	ret;

	free(command);
	rl_clear_history();
	ret = minishell->exit_status;
	clear_shell(minishell);
	ft_printf("exit\n");
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(ret);
}
