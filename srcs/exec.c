
#include "../include/minishell.h"

int main(void)
{
    char *str;

    while (1)
    {
        str = readline("evella@defora:~/Desktop/42/minishell$ ");
        if (ft_strstr(str, "echo"))
            printf("%s\n", ft_strtrim(str, " echo"));
        free(str);
    }
    
}