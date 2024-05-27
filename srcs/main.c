#include "../include/minishell.h"


char    **ft_checkredirect(char **args, int *fd)
{
    int i;
    char    **newargs;

    newargs = NULL;
    i = 0;
    while (args[i])
    {
        if(args[i][0] == '>')
        {
            *fd = open(args[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
            dup2(*fd, STDOUT_FILENO);
            ft_freetabtab(args);
            return (newargs);
        }
        else
        {
            newargs = ft_tb_realloc(newargs);
            newargs[i] = ft_strdup(args[i]);
        }
        i++;
    }
    ft_freetabtab(args);
    return (newargs);
}

int main(int ac, char **av, char **envp)
{
    t_tokens    *tokens;
    t_index     index;
    char        **env;
    int         bexec;
    int         fd;
    int         savestdout;

    fd = 0;
    (void)ac;
    (void)av;
    index.i = 0;
    bexec = 0;
    env = ft_create_env(envp);
    savestdout = dup(STDOUT_FILENO);
    while (bexec != 2)
    {
        index.j = 0;
        tokens = ft_receive_uprompt(ft_print_prompt(), env);
        while(tokens[index.j].args)
        {
            tokens[index.j].args = ft_checkredirect(tokens[index.j].args, &fd);
            if(ft_strcmp(tokens[index.j].args[0], "export") == 0)
                env = ft_create_var(tokens[index.j].args[1], env);
            else if (ft_strcmp(tokens[index.j].args[0], "unset") == 0)
                env = ft_unset(tokens[index.j].args[1], env);
            else
                bexec = ft_builtins_exec(tokens[index.j], env);
            ft_freetabtab(tokens[index.j].args);
            free(tokens->token);
            
            index.j++;
        }
        free(tokens);
        if (fd != 0)
        {
            dup2(savestdout, STDOUT_FILENO);
            close(fd);
        }
        //ft_printtabtab(tokens[0].args);
        //free(tokens);
    }
    ft_freetabtab(env);
    rl_clear_history();
    if (fd != 0)
        
    return (0);
}


/* int main (void)
{
    int fd;

    fd = open("tester.txt", O_CREAT | O_WRONLY, 0777);
    printf("dup2 = %d\n" , dup2(fd, 1));

} */