#include "../include/minishell.h"

int main(void)
{
    t_tokens    *tokens;
    t_index     index;
    
    index.i = 0;
    while (index.i++ != 10)
    {   
        index.j = 0;
        tokens = ft_receive_uprompt(ft_print_prompt());
        while(tokens[index.j].token)
            ft_builtins_exec(tokens[index.j++]);
    }
    rl_clear_history();
    return (0);
}