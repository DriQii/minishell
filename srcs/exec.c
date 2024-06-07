/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <enzovella6603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:27 by evella            #+#    #+#             */
/*   Updated: 2024/06/07 12:48:19 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_prompt_exec(t_tokens *tokens, t_index *index, char ***env,
		t_flux *brulux)
{
	int	i;

	i = 0;
	tokens[index->j].args = ft_checkredirect(tokens, brulux, index->j);
	if (tokens[index->j].args == NULL)
		return (ft_change_flux(&brulux->actualflux, brulux->savein,
				brulux->saveout));
	if (ft_strcmp(tokens[index->j].args[0], "export") == 0)
		*env = ft_export_exec(tokens[index->j].args, *env);
	else if (ft_strcmp(tokens[index->j].args[0], "unset") == 0)
	{
		while (tokens[index->j].args[++i])
			*env = ft_unset(tokens[index->j].args[i], *env);
	}
	else
		index->k = ft_builtins_exec(tokens[index->j], env, &tokens[0].rexit);
	ft_freetabtab(tokens[index->j].args);
	free(tokens[index->j].strstate);
	free(tokens[index->j].token);
	if (brulux->actualflux != INIT)
		ft_change_flux(&brulux->actualflux, brulux->savein, brulux->saveout);
}

char	**ft_create_path(char *path, char *cmd)
{
	char	**tbpath;
	char	**tmppath;
	char	*tmp;
	int		i;
	int		j;

	tbpath = NULL;
	tmppath = ft_split(path, ':');
	i = 0;
	j = 1;
	tbpath = ft_tb_realloc(tbpath);
	tbpath[0] = ft_strdup(cmd);
	while (tmppath[i])
	{
		tbpath = ft_tb_realloc(tbpath);
		tmp = ft_strjoin(tmppath[i], "/");
		tbpath[j] = ft_strjoin(tmp, cmd);
		free(tmp);
		i++;
		j++;
	}
	ft_freetabtab(tmppath);
	return (tbpath);
}

void	ft_child_exec(char *cmd, char **arg, char **env)
{
	int		execr;
	int		i;
	char	**path;

	i = 0;
	path = ft_create_path(getenv("PATH"), cmd);
	execr = access(path[0], X_OK);
	while (execr == -1 && path[++i])
		execr = access(path[i], X_OK);
	if (execr == -1)
		printf("bash: %s: command not found\n", cmd);
	else
		execve(path[i], arg, env);
	ft_freetabtab(path);
	ft_freetabtab(env);
	ft_freetabtab(arg);
	exit(127);
}

void	ft_exec(char *cmd, char **arg, char **env, int *rexit)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		ft_child_exec(cmd, arg, env);
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			if (rexit)
				*rexit = WEXITSTATUS(status);
		}
	}
}
