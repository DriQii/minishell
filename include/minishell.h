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
    int l;
}               t_index;

typedef struct  s_tokens
{
    char    *token;
    char    **args;

}               t_tokens;

// BUILTINS

void     ft_echo(t_tokens token);
void     ft_cd(char **args);
void     ft_env(char **envp);
 void    ft_unset(char *varname, char **env, char **var_tab);

// BUILTINS.UTILS

void    ft_check_env(char *str);
char    *ft_cutdir(char *path , char *arg);
char    **ft_create_var(char *var_to_create, char **var_tab);
char    *ft_get_env(char **env, char *var_name);

// BUILTINS.EXEC

int    ft_builtins_exec(t_tokens token, char **env);

// PARSING.UTILS

int     ft_change_agstate(arg_state cstate, arg_state *agstate);
int     ft_find_arg(char *str, t_arg *arg, t_index *index);
void    ft_vr(char **tb);
void    ft_joinarg(t_arg *arg, char *str, t_index *index);
void    ft_new_arg(t_arg *arg, t_index *index);
char    *ft_gnl(char *str);
char    *ft_join_space(char *s1, char *s2);
arg_state ft_find_cstate(char c, char next);

// PARSING

char        *ft_print_prompt();
char        **ft_tokeniser(char *uprompt);
char        **ft_sort_uprompt(char *str);
char        **ft_sort_token(char **tb);
t_tokens    *ft_receive_uprompt(char *uprompt);

// UTILS

void    ft_print_tokens(t_tokens *tokens);
void	ft_printtabtab(char **tb);
void	*ft_freetabtab(char **tb);
char	*ft_realloc(char *str);
char	**ft_tb_realloc(char **tb);

// EXEC

char    **ft_create_path(char *path, char *cmd);
void    ft_exec(char *cmd, char **arg, char **env);
char    **ft_create_env(char **envp);

#endif