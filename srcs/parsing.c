#include "../include/minishell.h"

arg_state ft_find_cstate(char c, char next)
{
    if (c == 32 && next != 32)
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

int ft_change_agstate(arg_state cstate, arg_state *agstate)
{
    if (*agstate == SEARCH && cstate != DSPACE)
    {
        *agstate = FSPACE;
        return (1);
    }
    else if (*agstate == SEARCH && cstate == DSPACE)
        return (0);
    else if ((cstate == FSPACE || cstate == DSPACE) && *agstate == FSPACE)
    {
        *agstate = SEARCH;
        return (3);
    }
    else if (cstate == DQUOTE && (*agstate != DQUOTE && *agstate != QUOTE))
        *agstate = cstate;
    else if (cstate == DQUOTE && *agstate == DQUOTE)
    {
        *agstate = FSPACE;
    }
    else if (cstate == QUOTE && (*agstate != DQUOTE && *agstate != QUOTE))
        *agstate = cstate;
    else if (cstate == QUOTE && *agstate == QUOTE)
        *agstate = FSPACE;
    return (2);
    
}

char    **ft_receive_prompt(char *str)
{
    char    **args;
    char    *arg;
    int     i;
    int     j;
    int     k;
    int     strstate;
    arg_state agstate;
    
    i = 0;
    j = 0;
    k = 0;
    agstate = SEARCH;
    args = NULL;
    arg = NULL;
    while(str[i])
    {
        strstate = ft_change_agstate(ft_find_cstate(str[i], str[i + 1]), &agstate);
        if (strstate == 1 || strstate == 2)
        {
        if(str[i] != 32 || arg)
        {  
            arg = ft_realloc(arg);
            arg[j] = str[i];
            j++;
        }
        }
        else if (strstate == 3)
        {
            args = ft_tb_realloc(args);
            args[k] = ft_strdup(arg);
            free(arg);
            arg = NULL;
            k++;
            i--;
            j = 0;
        }
        i++;
    }
    args = ft_tb_realloc(args);
    args[k] = ft_strdup(arg);
    free(arg);
    arg = NULL;
    return (args);
}

char    *ft_join_space(char *s1, char *s2)
{
    char *newstr;
    char sp[] = {" "};

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

char    **ft_sort_token(char **tb)
{
    int i;
    int j;
    char    **tokens;

    i = 0;
    j = 0;
    tokens = NULL;
    tokens = ft_tb_realloc(tokens);
    while (tb[i])
    {
        if (tb[i][0] == '|' && ft_strlen(tb[i]) == 1)
        {
            tokens = ft_tb_realloc(tokens);
            j++;
            i++;
        }
        tokens[j] = ft_join_space(tokens[j], tb[i]);
        i++;
    }
    ft_freetabtab(tb);
    return (tokens);
}

