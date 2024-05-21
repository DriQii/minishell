#include "../include/minishell.h"

int main(int ac, char **av, char **envp)
{
    t_tokens    *tokens;
    t_index     index;
    
    (void)ac;
    (void)av;
    index.i = 0;
    while (index.i++ != 10)
    {   
        index.j = 0;
        tokens = ft_receive_uprompt(ft_print_prompt());
        while(tokens[index.j].token)
            ft_builtins_exec(tokens[index.j++], envp);
        //ft_print_tokens(tokens);
    }
    rl_clear_history();
    return (0);
}