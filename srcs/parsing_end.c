#include "../include/minishell.h"

char *ft_parsing_end(char *str)
{
    arg_state   strstate;
    arg_state  state;
    char        *newstr;
    int         i;
    int         j;
    

    i = 0;
    j = 0;
    state = SEARCH;
    newstr = NULL;
    while(str[i])
    {
        ft_change_agstate(ft_find_cstate(str[i], str[i + 1]), &strstate);
        if (state == SEARCH && (strstate == DQUOTE || strstate == QUOTE))
        {
            state = strstate;
            i++;
            ft_change_agstate(ft_find_cstate(str[i], str[i + 1]), &strstate);
        }
        if ((state == DQUOTE || strstate == QUOTE)  && (str[i] == '\'' || str[i] == '\"'))
        {
            state = SEARCH;
            i++;
            ft_change_agstate(ft_find_cstate(str[i], str[i + 1]), &strstate);
        }
        else
        {
            newstr = ft_realloc(newstr);
            newstr[j] = str[i];
            j++;
            i++;
        }
    }
    free(str);
    return (newstr);
}

char    **ft_last_parsing(char **tb)
{
    int i;

    i = 0;
    
    while(tb[i])
    {
        tb[i] = ft_parsing_end(tb[i]);
        i++;
    }
    return (tb);
}