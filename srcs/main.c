/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <enzovella6603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:36 by evella            #+#    #+#             */
/*   Updated: 2024/06/07 13:48:24 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b");
	}
}

static void	ft_pipe(t_tokens *tokens, t_index *index)
{
	pipe(tokens[index->j].pipefd);
	dup2(tokens[index->j].pipefd[1], STDOUT_FILENO);
	close(tokens[index->j].pipefd[1]);
}

static int	set_tmp(t_tokens *tokens, int tmp)
{
	tmp = tokens[0].rexit;
	free(tokens);
	tokens = NULL;
	return (tmp);
}

static int	ft_minishell(t_tokens *tokens, t_index *index, t_flux *brulux,
		char ***env)
{
	int	tmp;

	tmp = 0;
	while (index->k < 0)
	{
		index->j = -1;
		tokens = ft_receive_uprompt(ft_print_prompt(), *env, &tmp);
		while (tokens[++index->j].token)
		{
			if (tokens[index->j + 1].token)
				ft_pipe(tokens, index);
			else if (!tokens[index->j + 1].token && index->j > 0)
				dup2(brulux->saveout, STDOUT_FILENO);
			ft_prompt_exec(tokens, index, env, brulux);
			if (tokens[index->j + 1].token)
			{
				dup2(tokens[index->j].pipefd[0], STDIN_FILENO);
				close(tokens[index->j].pipefd[0]);
			}
			else if (!tokens[index->j + 1].token && index->j > 0)
				dup2(brulux->savein, STDIN_FILENO);
		}
		tmp = set_tmp(tokens, tmp);
	}
	return (tmp);
}

int	main(int ac, char **av, char **envp)
{
	t_tokens	*tokens;
	t_index		index;
	char		***env;
	t_flux		brulux;

	(void)ac;
	(void)av;
	index.i = 0;
	index.k = -1;
	tokens = NULL;
	brulux.actualfd = 0;
	brulux.saveout = dup(STDOUT_FILENO);
	brulux.savein = dup(STDIN_FILENO);
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
	env = ft_calloc(sizeof(char **), 1);
	*env = ft_create_env(envp);
	*env = ft_shlvl(*env, ft_atoi(ft_get_env(*env, "SHLVL")));
	ft_clear(*env);
	index.r = ft_minishell(tokens, &index, &brulux, env);
	ft_freetabtab(*env);
	free(env);
	rl_clear_history();
	return (index.r);
}
