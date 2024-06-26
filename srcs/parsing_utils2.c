/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <enzovella6603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:44 by evella            #+#    #+#             */
/*   Updated: 2024/06/07 17:14:50 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_cut_gnl(void)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = get_next_line(0);
	tmp = ft_calloc(sizeof(char), ft_strlen(tmp2) + 1);
	ft_strncpy(&tmp[1], tmp2, ft_strlen(tmp2) - 1);
	tmp[0] = '\n';
	if (tmp2)
		free(tmp2);
	return (tmp);
}

int	ft_find_arg(char *str, t_arg *arg, t_index *index)
{
	while (str && str[index->i])
	{
		arg->strstate = ft_change_agstate(ft_find_cstate(str[index->i],
					str[index->i + 1]), &arg->agstate, index->j);
		if ((arg->strstate == 1 || arg->strstate == 2) && (str[index->i] != 32
				|| arg->arg) && str[index->i] != '\n' && str[index->i] != '\t')
			ft_joinarg(arg, str, index);
		else if (arg->strstate == 3)
			ft_new_arg(arg, index);
		index->i++;
	}
	if (arg->agstate == FSPACE || arg->agstate == OP)
		return (ft_new_arg(arg, index), 0);
	else if (index->i == 0)
	{
		arg->args = ft_tb_realloc(arg->args);
		arg->args[index->k] = ft_calloc(sizeof(char), 1);
		return (0);
	}
	return (1);
}

int	ft_find_arg_2(char *str, t_arg *arg, t_index *index)
{
	while (str && str[index->i])
	{
		arg->strstate = ft_change_agstate_2(ft_find_cstate_2(str[index->i],
					str[index->i + 1]), &arg->agstate);
		if ((arg->strstate == 1 || arg->strstate == 2) && (str[index->i] != 32
				|| arg->arg))
			ft_joinarg(arg, str, index);
		else if (arg->strstate == 3)
			ft_new_arg(arg, index);
		index->i++;
	}
	if (arg->agstate == FSPACE)
		return (ft_new_arg(arg, index), 0);
	else if (index->i == 0)
	{
		arg->args = ft_tb_realloc(arg->args);
		arg->args[index->k] = ft_calloc(sizeof(char), 1);
		return (0);
	}
	return (1);
}

char	*ft_gnl(char *str)
{
	char	*tmp;
	char	*tmp2;

	write(1, "> ", 2);
	tmp2 = ft_cut_gnl();
	tmp = ft_strdup(str);
	if (str)
		free(str);
	str = ft_strjoin(tmp, tmp2);
	if (tmp)
		free(tmp);
	if (tmp2)
		free(tmp2);
	return (str);
}

char	**ft_shlvl(char **env, int shlvl)
{
	char	*tmp;
	char	*str;

	shlvl++;
	str = ft_itoa(shlvl);
	tmp = ft_strjoin("SHLVL=", str);
	env = ft_export(tmp, env);
	free(tmp);
	free(str);
	return (env);
}
