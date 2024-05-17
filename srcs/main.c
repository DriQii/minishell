#include "../include/minishell.h"

int main(void)
{
    char **tb;

    tb = ft_receive_prompt("\"ec\'h\'o\" -n \"|\" | wc -l | ./push_swap 32 34 56 78 \"4 65 6\"");
    ft_printtabtab(tb);
    ft_freetabtab(tb);
    return (0);
}