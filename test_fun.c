# include "test_me/libft/libft.h"
#include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# define RUN 1

int main(int argc, char **argv, char **envp)
{
    char *input;
    static char data_cmd[255] = "";
    enum builtins {echo, cd, pwd, export, unset, env, exit};

    printf("%d", cd);

    while (RUN)
    {
        int i = 0;
        int test;

        input = readline("$");
       
        
        while(input[i])
        {
            if(input[i] != '\0')
            {
                data_cmd[i] = input[i];
                printf("%c", data_cmd[i]);
            }
            i++;
            
        }
        printf("\n-------------\n");
        printf("%s", input);

        
    }
    

    return (0);
}