/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <enzovella6603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:26:25 by evella            #+#    #+#             */
/*   Updated: 2024/06/10 14:50:31 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cd(char **args)
{
	char	*path;
	char	buff[4096];
	char	*cutdir;

	path = getcwd(buff, 4096);
	cutdir = ft_cutdir(path, args[1]);
	chdir(cutdir);
	free(cutdir);
}
static int	ft_find_option(char *arg)
{
	int	i;
	
	i = 2;
	if (arg[0] == '-' && arg[1] == 'n')
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	else
		return (1);
}

void    ft_echo(t_tokens token)
{
    int    i;
    int    j;

    i = 1;
    j = 0;
    while (token.args[i])
    {
        if (ft_find_option(token.args[i]) == 0 && j == 0)
            i++;
        else if (ft_find_option(token.args[i]) == 1 || (ft_find_option(token.args[i]) == 0 && j > 0))
        {
            printf("%s", token.args[i]);
            j++;
            i++;
        }
        if (token.args[i] != NULL && ft_find_option(token.args[i - 1]) == 1)
            printf(" ");
    }
    if (token.args[1])
        if (ft_find_option(token.args[1]) == 1)
            printf("\n");
}

char	**ft_unset(char *varname, char **env)
{
	int	pos;

	if (!varname)
		return (env);
	pos = ft_check_var(varname, env);
	if (pos != 0)
		env = ft_tab_cat(env, pos);
	return (env);
}
