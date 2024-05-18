#include "../include/minishell.h"

char    *ft_print_prompt()
{
    char buff[4096];
    char *prompt;
    char *uprompt;
    char *tmp;
    int i;

    prompt = ft_strjoin(getcwd(buff, 4096), "$ ");
    i = 6;
    while(prompt[i] && prompt[i] != '/')
        i++;
    tmp = ft_strdup(&prompt[i]);
    free (prompt);
    prompt = ft_strjoin("~", tmp);
    free(tmp);
    tmp = ft_strdup(prompt);
    free(prompt);
    if (ft_strcmp(tmp, "~") == 0)
        prompt = ft_strjoin(tmp, "$ ");
    else
        prompt = ft_strdup(tmp);
    free(tmp);
    uprompt = readline(prompt);
    add_history(uprompt);
    return (uprompt);
}
char    **ft_tokeniser(char *uprompt)
{
    char **tb;
    char **tokens;

    tb = ft_receive_prompt(uprompt);
    free(uprompt);
    tokens = ft_sort_token(tb);
    return (tokens);
}
int main(void)
{
    char **tokens;
    char *uprompt;

    int j = 0;
    while (j++ != 2)
    {   
        uprompt = ft_print_prompt();
        tokens = ft_tokeniser(uprompt);
        ft_printtabtab(tokens);
        ft_freetabtab(tokens);
    }
    rl_clear_history();
    return (0);
}