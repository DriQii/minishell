#include "../include/minishell.h"

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
        if (token.args[i][0] == '$')
            ft_check_env(token.args[i]);
        else
            printf("%s", token.args[i]);
        i++;
        if (token.args[i] != NULL)
            printf(" ");
    }
    if (ft_strcmp(token.args[1], "-n") != 0)
        printf("\n");
}

void    ft_env(char **envp)
{
    int     i;

    i = 0;
    while (envp[i])
        printf("%s\n", envp[i++]);
}

/* void    ft_unset(char *varname)
{

} */