#include "../include/minishell.h"

static char *ft_cutdir(char *path , char *arg)
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

void    ft_cd(char **args)
{
    char    *path;
    char    buff[4096];

    path = getcwd(buff, 4096);
    chdir(ft_cutdir(path, args[1]));
}

void     ft_echo(t_tokens token)
{
    int i;

    i = 1;
    if (ft_strcmp(token.args[1], "-n") == 0)
        i++;
    while (token.args[i])
    {
        printf("%s", token.args[i++]);
        if (token.args[i] != NULL)
            printf(" ");
    }
    if (ft_strcmp(token.args[1], "-n") != 0)
        printf("\n");
}
