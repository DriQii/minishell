#ifndef MINISHELL_H
# define  MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>  // Pour printf
#include <stdlib.h> // Pour malloc, free, getenv
#include <unistd.h> // Pour close, read, write, chdir, getcwd, access, dup, dup2, fork, execve, pipe, isatty, ttyname, ttyslot
#include <string.h> // Pour l'utilisation de certaines fonctions de manipulation de chaînes si nécessaire
#include <sys/stat.h> // Pour stat, lstat, fstat
#include <fcntl.h>    // Pour open
#include <dirent.h>   // Pour opendir, readdir, closedir
#include <errno.h>  // Pour errno utilisé avec perror et strerror
#include <signal.h> // Pour signal, sigaction, sigemptyset, sigaddset, kill
#include <readline/readline.h> // Pour readline, add_history
#include <readline/history.h>  // Pour rl_clear_history, et autres fonctions de gestion de l'historique de Readline
#include <termios.h>  // Pour tcsetattr, tcgetattr
#include <sys/ioctl.h> // Pour ioctl
#include <term.h>     // Pour tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <sys/types.h>
#include <sys/wait.h>

typedef enum    arg_state
{
    QUOTE,
    DQUOTE,
    FSPACE,
    DSPACE,
    SEARCH,
}               arg_state;

typedef struct  s_arg
{
    char        **args;
    char        *arg;
    int         strstate;
    arg_state   agstate;
}               t_arg;

typedef struct  s_index
{
    int i;
    int j;
    int k;
}               t_index; 

char	*ft_realloc(char *str);
char	**ft_tb_realloc(char **tb);
void	*ft_freetabtab(char **tb);
char    **ft_receive_prompt(char *str);
void	ft_printtabtab(char **tb);
char    **ft_sort_token(char **tb);

#endif