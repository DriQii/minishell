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