#include "../include/minishell.h"

char	*ft_realloc(char *str)
{
	char	*newstr;
	int		i;

	i = 0;
	if (!str)
		return (ft_calloc((2), sizeof(char)));
	newstr = (ft_calloc((ft_strlen((char *)str) + 2), sizeof(char)));
	while (str[i])
	{
		newstr[i] = str[i];
		i++;
	}
	free(str);
	str = NULL;
	return (newstr);
}

char	**ft_tb_realloc(char **tb)
{
	char	**newtb;
	int		i;


	i = 0;
	if (!tb)
		return (ft_calloc((2), sizeof(char *)));
    while (tb[i])
        i++;
	newtb = ft_calloc(sizeof(char *) , i + 2);
    i = 0;
	while (tb[i])
	{
		newtb[i] = ft_strdup(tb[i]);
		i++;
	}
	ft_freetabtab(tb);
	tb = NULL;
	return (newtb);
}

static void	*ft_freetabtab(char **tb)
{
    int i;

    i = 0;
	while (tb[i])
	{
		free(tb[i]);
        i++;
	}
    free(tb[i]);
	free (tb);
	return (NULL);
}
