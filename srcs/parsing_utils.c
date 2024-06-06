/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:41 by evella            #+#    #+#             */
/*   Updated: 2024/06/06 16:23:29 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_arg_state	ft_find_cstate(char c, char next)
{
	if (c == '|' || c == '>' || (c == '>' && next == '>') || c == '<'
		|| (c == '<' && next == '<'))
		return (OP);
	if (c == 32 && next != 32)
		return (FSPACE);
	else if (c == 0)
		return (FSPACE);
	else if (c == 39)
		return (QUOTE);
	else if (c == 34)
		return (DQUOTE);
	else if (c == 32)
		return (DSPACE);
	else
		return (SEARCH);
}

int	ft_change_agstate(t_arg_state cstate, t_arg_state *agstate, int j)
{
	if ((*agstate == SEARCH && cstate != DSPACE) || (*agstate == FSPACE
			&& cstate == OP))
	{
		if (*agstate == FSPACE && cstate == OP && j > 0)
		{
			*agstate = SEARCH;
			return (3);
		}
		if (cstate == DQUOTE || cstate == QUOTE)
			*agstate = cstate;
		else if (cstate == OP)
			*agstate = OP;
		else
			*agstate = FSPACE;
		return (1);
	}
	else if (*agstate == SEARCH && cstate == DSPACE)
		return (0);
	else if (((cstate == FSPACE || cstate == DSPACE || cstate == OP)
			&& *agstate == FSPACE) || ((cstate == SEARCH || cstate == DQUOTE
				|| cstate == QUOTE) && *agstate == OP))
	{
		*agstate = SEARCH;
		return (3);
	}
	else if ((cstate == DQUOTE && *agstate == DQUOTE) || (cstate == QUOTE
			&& *agstate == QUOTE))
		*agstate = FSPACE;
	else if ((cstate == DQUOTE || cstate == QUOTE) && (*agstate != DQUOTE
			&& *agstate != QUOTE))
		*agstate = cstate;
	return (2);
}

void	ft_new_arg(t_arg *arg, t_index *index)
{
	(*arg).args = ft_tb_realloc((*arg).args);
	(*arg).args[(*index).k] = ft_strdup((*arg).arg);
	(*index).k++;
	(*index).i--;
	(*index).j = 0;
	free((*arg).arg);
	(*arg).arg = NULL;
}

void	ft_joinarg(t_arg *arg, char *str, t_index *index)
{
	(*arg).arg = ft_realloc((*arg).arg);
	(*arg).arg[(*index).j] = str[(*index).i];
	(*index).j++;
}

char	*ft_join_space(char *s1, char *s2)
{
	char	*newstr;
	char	sp[2];

	sp[0] = ' ';
	if (!s1)
		return (ft_strdup(s2));
	newstr = ft_strjoin(s1, sp);
	if (s1)
		free(s1);
	s1 = newstr;
	newstr = ft_strjoin(newstr, s2);
	if (s1)
		free(s1);
	return (newstr);
}
