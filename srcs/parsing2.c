/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:04:27 by evella            #+#    #+#             */
/*   Updated: 2024/06/06 16:07:09 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_tokeniser(char *uprompt, char **env)
{
	char	**tb;
	char	**tokens;

	tb = NULL;
	tb = ft_sort_uprompt(uprompt);
	ft_vr(tb, env);
	free(uprompt);
	tokens = ft_sort_token(tb);
	return (tokens);
}

char	**ft_sort_uprompt(char *str)
{
	t_index	index;
	t_arg	arg;
	char	*newstr;
	int		l;

	index.i = 0;
	index.j = 0;
	index.k = 0;
	l = 1;
	arg.agstate = SEARCH;
	arg.args = NULL;
	arg.arg = NULL;
	newstr = ft_strdup(str);
	while (l)
	{
		l = ft_find_arg(newstr, &arg, &index);
		if (l == 1)
			newstr = ft_gnl(newstr);
	}
	if (newstr)
		free(newstr);
	return (arg.args);
}
