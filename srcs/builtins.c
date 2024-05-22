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

/*  void    ft_unset(char *varname, char **env, char **var_tab)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (env[i] || var_tab[j])
    {
        if (ft_strstr(varname, env[i]) == 0)
            ft_memset(env[i], '\0', 50);
        else if (ft_strstr(varname, var_tab[j]) == 0)
        {
            ft_memset(var_tab[j], '\0', 50);
        }
        i++;
        j++;
    }
}

int main(int ac, char **av, char **envp)
{
    char **env = ft_create_env(envp);
    char **var_tab;

    var_tab = NULL;
    var_tab = ft_tb_realloc(var_tab);

    var_tab = ft_create_var("test=bonjour", var_tab);

    //ft_printtabtab(env);
    printf("------------------------------------------------------------\n");
    ft_printtabtab(var_tab);


    ft_unset("test", env, var_tab);


    //ft_printtabtab(env);
    printf("------------------------------------------------------------\n");
    ft_printtabtab(var_tab);
    ft_freetabtab(env);
    ft_freetabtab(var_tab);

} */