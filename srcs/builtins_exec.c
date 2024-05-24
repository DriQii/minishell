#include "../include/minishell.h"

int    ft_builtins_exec(t_tokens token, char **env)
{
    char    buf[4096];

    if (!token.args[0][0])
        return (0);
    if (ft_strcmp(token.args[0], "cd") == 0)
        return (ft_cd(token.args), 0);
    else if (ft_strcmp(token.args[0], "echo") == 0)
        return (ft_echo(token), 0);
    else if (ft_strcmp(token.args[0], "pwd") == 0)
        return (printf("%s\n", getcwd(buf, 4096)), 0);
    else if (ft_strcmp(token.args[0], "env") == 0)
        return (ft_printtabtab(env), 0);
    else if (ft_strcmp(token.args[0], "export") == 0)
    {
        env = ft_create_var(token.args[1], env);
        printf("token = %s\nfirst = [%s]\n", token.args[1], env[52]);

        //ft_printtabtab(env);
        return (0);
    }
    else
        ft_exec(token.args[0], token.args, env);
    return (1);
}

char    **ft_create_env(char **envp)
{
    char    **env;
    int     i;

    i = 0;
    while (envp[i])
        i++;
    env = ft_calloc(i + 1, sizeof(char *));
    i = -1;
    while (envp[++i])
        env[i] = ft_strdup(envp[i]);
    env[i] = NULL;
    return (env);
}

