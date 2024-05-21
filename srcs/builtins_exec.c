#include "../include/minishell.h"

int    ft_builtins_exec(t_tokens token, char **envp)
{
    char    buf[4096];

    if (ft_strcmp(token.args[0], "cd") == 0)
        return (ft_cd(token.args), 0);
    else if (ft_strcmp(token.args[0], "echo") == 0)
        return (ft_echo(token), 0);
    else if (ft_strcmp(token.args[0], "pwd") == 0)
        return (printf("%s\n", getcwd(buf, 4096)), 0);
    else if (ft_strcmp(token.args[0], "env") == 0)
        return (ft_env(envp), 0);
    return (1);
}

