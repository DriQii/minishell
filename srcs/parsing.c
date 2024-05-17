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
        *agstate = cstate;
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