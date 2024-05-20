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
    free(prompt);
    return (uprompt);
}
char    **ft_tokeniser(char *uprompt)
{
    char **tb;
    char **tokens;

    tb = ft_sort_uprompt(uprompt);
    free(uprompt);
    tokens = ft_sort_token(tb);
    return (tokens);
}

t_tokens    *ft_receive_uprompt(char *uprompt)
{
    t_tokens *tokens;
    char **tmpt;
    int i;

    i = 0;
    tmpt = ft_tokeniser(uprompt);
    while (tmpt[i])
        i++;
    tokens = ft_calloc(sizeof(*tokens), i + 1);
    i = 0;
    while (tmpt[i])
    {
        tokens[i].token = tmpt[i];
        tokens[i].args = ft_sort_uprompt(tmpt[i]);
        i++;
    }
    return (tokens);
}

char    **ft_sort_uprompt(char *str)
{
    t_index index;
    t_arg   arg;
    
    index.i = 0;
    index.j = 0;
    index.k = 0;
    arg.agstate = SEARCH;
    arg.args = NULL;
    arg.arg = NULL;
    while(str[index.i])
    {
        
        arg.strstate = ft_change_agstate(ft_find_cstate(str[index.i], str[index.i + 1]), &arg.agstate);
        if ((arg.strstate == 1 || arg.strstate == 2) && (str[index.i] != 32 || arg.arg))
            ft_joinarg(&arg, str, &index);
        else if (arg.strstate == 3)
            ft_new_arg(&arg, &index);
        index.i++;
    }
    ft_new_arg(&arg, &index);
    return (arg.args);
}

char    **ft_sort_token(char **tb)
{
    int i;
    int j;
    char    **tokens;

    i = 0;
    j = 0;
    tokens = NULL;
    tokens = ft_tb_realloc(tokens);
    while (tb[i])
    {
        if (tb[i][0] == '|' && ft_strlen(tb[i]) == 1)
        {
            tokens = ft_tb_realloc(tokens);
            j++;
            i++;
        }
        tokens[j] = ft_join_space(tokens[j], tb[i]);
        i++;
    }
    ft_freetabtab(tb);
    return (tokens);
}