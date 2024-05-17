#include "../include/minishell.h"

int main(void)
{
    char **tb;
    char **tokens;
    char *str;
    char buff[4096];
    char *line;
    char *tmp;
    int i;

    while (1)
    {   
        
        line = ft_strjoin(getcwd(buff, 4096), "$ ");
        i = 6;
        while(line[i] && line[i] != '/')
            i++;
        tmp = ft_strdup(&line[i]);
        free (line);
        line = ft_strjoin("~", tmp);
        free(tmp);
        tmp = ft_strdup(line);
        free(line);
        if (ft_strcmp(tmp, "~") == 0)
            line = ft_strjoin(tmp, "$ ");
        else
            line = ft_strdup(tmp);
        free(tmp);
        str = readline(line);
        tb = ft_receive_prompt(str);
        tokens = ft_sort_token(tb);
        ft_printtabtab(tokens);
        ft_freetabtab(tokens);
        tb = NULL;
    }
    rl_clear_history();
    return (0);
}