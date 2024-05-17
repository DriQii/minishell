
/*#include "../include/minishell.h"

 char *cutdir(char *path , char *arg)
{
    int i;
    char    *newpath;

    i = 0;
    if (!arg || ft_strcmp(arg, "~") == 0)
    {

        i = 6;
        while(path[i + 1] != '/')
            i++;
        newpath = ft_calloc(sizeof(char), i + 2);
        ft_strncpy(newpath, path, i + 1);
    }
    else
    {  
        newpath = ft_strjoin(path, "/");
        newpath = ft_strjoin(newpath, arg);
    }
    return(newpath);
}

static void	*ft_freetabtab(char **args)
{
    int i;

    i = 0;
	while (args[i])
	{
		free(args[i]);
        i++;
	}
    free(args[i]);
	free (args);
	return (NULL);
}

int main(void)
{
    char *str;
    char buff[4096];
    char **arg;
    char *newdir;
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
        printf("str = %s\n", str);
        arg = ft_split(str, ' ');
        if (ft_strcmp(arg[0], "cd") == 0)
        {
            newdir = cutdir(getcwd(buff, 4096), arg[1]);
            chdir(newdir);
        }
        else if (ft_strcmp(arg[0], "exit") == 0)
            exit(0);
        else
            printf("bash: %s: command not found...\n", arg[0]);
        free(line);
        ft_freetabtab(arg);
    }
    rl_clear_history();

} */



