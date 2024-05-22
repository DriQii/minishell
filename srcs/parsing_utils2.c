#include "../include/minishell.h"

static char    *ft_cut_gnl(void)
{
    char *tmp;
    char *tmp2;

    tmp2 = get_next_line(0);
    tmp = ft_calloc(sizeof(char), ft_strlen(tmp2) + 1);
    ft_strncpy(&tmp[1], tmp2, ft_strlen(tmp2) - 1);
    tmp[0] = '\n';
    if (tmp2)
        free(tmp2);
    return (tmp);
}

int    ft_find_arg(char *str, t_arg *arg, t_index *index)
{
    while(str[index->i])
    {
        arg->strstate = ft_change_agstate(ft_find_cstate(str[index->i], str[index->i + 1]), &arg->agstate);
        if ((arg->strstate == 1 || arg->strstate == 2) && (str[index->i] != 32 || arg->arg))
            ft_joinarg(arg, str, index);
        else if (arg->strstate == 3)
            ft_new_arg(arg, index);
        index->i++;
    }
    if (arg->agstate == FSPACE)
        return (ft_new_arg(arg, index), 0);
    return (1);
}

char    *ft_gnl(char *str)
{
    char    *tmp;
    char    *tmp2;

    write(1, "> ", 2);
    tmp2 = ft_cut_gnl();
    tmp = ft_strdup(str);
    str = ft_strjoin(tmp, tmp2);
    if (tmp)
        free(tmp);
    if(tmp2)
        free(tmp2);
    return (str);
}

char   *ft_add_var(char *str, int *i, int *j)
{
    char    *var;
    char    *tmp;

    while (str[*i] && ft_find_cstate(str[*i], str[(*i) + 1]) == SEARCH)
    {
        (*i)++;
        (*j)++;
    }
    tmp = ft_calloc(sizeof(char), (*j) + 1);
    ft_strncpy(tmp, &str[(*i + 1) - (*j)], (*j) - 1);
    *j = 0;
    var = getenv(tmp);
    free(tmp);
    return (var);
}

char    *ft_swap_var(char *str)
{
    char    *newstr;
    char    *var;
    char    *tmp;
    int     i;
    int     j;
    int     k;

    i = 0;
    j = 0;
    k = 0;
    newstr = NULL;
    while (str[i])
    {
        if (str[i] == '$')
        {
            var = ft_add_var(str, &i, &j);
            if (var)
            {
                tmp = ft_strjoin(newstr, var);
                if (tmp)
                    k = ft_strlen(tmp);
                if (newstr)
                    free(newstr);
                newstr = ft_calloc(sizeof(char), k + 1);
                ft_strcpy(newstr, tmp);
            }
        }
        if (str[i])
        {
            newstr = ft_realloc(newstr);
            newstr[k] = str[i];
            k++;
        }
        i++;

    }
    if (str)
        free(str);
    return (newstr);
}

void    ft_vr(char **tb)
{
    int i;

    i = 0;
    while(tb[i])
    {
        tb[i] = ft_swap_var(tb[i]);
        i++;
    }
}