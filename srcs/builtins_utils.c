#include "../include/minishell.h"

void    ft_check_env(char *str)
{
    str = ft_strtrim(str, "${}");
    str = getenv(str);
    if (!str)
    {
        printf("\n");
        return ;
    }
    printf ("%s", str);
}

char    *ft_cutdir(char *path , char *arg)
{
    int i;
    char    *newpath;

    i = 0;
    if (!arg || ft_strcmp(arg, "~") == 0)
    {
        i = 6;
        while(path[i + 1] != '/')
            i++;
        newpath = ft_calloc(sizeof(char), i + 2);
        ft_strncpy(newpath, path, i + 1);
    }
    else
    {  
        newpath = ft_strjoin(path, "/");
        newpath = ft_strjoin(newpath, arg);
    }
    return(newpath);
}

char    *ft_get_env(char **env, char *var_name)
{
    char    *value_var;
    char    **var_tab;
    int     i;

    i = 0;
    value_var = NULL;
    var_tab = NULL;
    while(env[i])
    {
        var_tab = ft_split(env[i], '=');
        if (ft_strcmp(var_name, var_tab[0]) == 0)
        {
            value_var = ft_strdup(var_tab[1]);
            return (ft_freetabtab(var_tab), value_var);
        }
        ft_freetabtab(var_tab);
        i++;
    }
    var_tab = NULL;
    return (value_var);
}

char    **ft_create_var(char *var_to_create, char **var_tab)
{
    int     i;

    var_tab = ft_tb_realloc(var_tab);
    i = 0;
    while(var_tab[i])
        i++;
    var_tab[i] = ft_strdup(var_to_create);
    return(var_tab);
}