#include "../include/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_tokens    *tokens;
    t_index     index;
    char        **env;

    (void)ac;
    (void)av;
    index.i = 0;
    env = ft_create_env(envp);
    while (index.i++ != 10)
    {
        index.j = 0;
        tokens = ft_receive_uprompt(ft_print_prompt(), env);
        while(tokens[index.j].token)
            ft_builtins_exec(tokens[index.j++], env);
        //ft_print_tokens(tokens);
    }
    ft_freetabtab(env);
    rl_clear_history();
    return (0);
}