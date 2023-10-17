/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:07:51 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/16 20:14:35 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_command(t_minishell *minishell, char *command)
{
	bool			success_create_tokens;
	t_token_type	*token_array;
	t_minishell		*new_shell;
	t_list			*tokens;
	bool			ret;

	success_create_tokens = create_tokens(&minishell->tokens, command);
	token_array = create_token_array(minishell->tokens);
	ret = syntax_analysis(token_array);
	free(token_array);
	if (!(success_create_tokens && ret))
		ft_fprintf(2, "minishell: syntax error\n");
	else
	{
		tokens = minishell->tokens;
		new_shell = create_sub_shells(&tokens, minishell->envs);
		ft_lstclear(&(minishell)->tokens, del_token);
		ft_lstclear(&(minishell)->shells, clear_shells);
		clear_fds(minishell);
		executor(new_shell, minishell);
		clear_shells(new_shell);
	}
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
