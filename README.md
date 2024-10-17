# Minishell
As beautifull as a shell
Write a shell

## Program name : minisell

### **Description des fonctions pratiques et exemples d'utilisation**
_________________________________________________________________________________________________________________________________________________
- readline (GNU Library)

> [!NOTE]
> cette fonction lit une ligne de texte depuis l'entrée standard (**stdin**) jusqu'à ce qu'un caractère de fin de ligne (généralement \n) soit rencontré, ou que l'utilisateur termine l'entrée avec EOF (Ctrl+D dans la plupart des systèmes Unix). Elle offre aussi la possibilité de naviguer dans l'historique des lignes tapées et d'éditer la ligne en cours.

  - Prototype :

         char *readline(const char *prompt);

  - Description
    - prompt: Une chaîne de caractères affichée avant de lire l'entrée utilisateur (comme une invite de commande).
    - Retourne : Un pointeur vers une chaîne allouée dynamiquement contenant la ligne lue, ou NULL en cas d'erreur ou si EOF est atteint.
  
  - Quand utiliser **readline()** :

:diamond_shape_with_a_dot_inside:Pour des applications interactives : si vous développez une application interactive qui nécessite des entrées fréquentes de l'utilisateur (comme un shell ou un interpréteur).

:diamond_shape_with_a_dot_inside:Si vous avez besoin d'édition de ligne avancée : l'utilisation de la bibliothèque GNU Readline offre des fonctionnalités d'édition de ligne très pratiques (navigation dans l'historique, autocomplétion, etc.).


:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *input;
    
    // Affiche une invite à l'utilisateur et lit la ligne saisie
    input = readline("Entrez une commande: ");
    
    if (input) {
        // Si l'utilisateur a entré quelque chose, l'afficher
        printf("Vous avez entré: %s\n", input);
        
        // Libérer la mémoire allouée pour la ligne lue
        free(input);
    }

    return 0;
}

```
```C
// Gérer les entrées utilisateur
// Lire les commandes tapées par l'utilisateur

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>  // pour fork, exec, etc.

int main(void) {
    char *input;
    
    while (1) {
        // Lire la commande de l'utilisateur avec une invite personnalisée
        input = readline("minishell> ");
        
        // Si l'utilisateur entre "Ctrl+D" ou une erreur survient
        if (input == NULL) {
            printf("exit\n");
            break;
        }
        
        // Si l'utilisateur n'a pas entré de commande vide
        if (*input != '\0') {
            // Ajouter la commande à l'historique
            add_history(input);
            
            // Ici, on pourrait forker un processus et utiliser exec pour exécuter la commande
            printf("Commande reçue: %s\n", input);
        }
        
        // Libérer la mémoire allouée pour la ligne lue
        free(input);
    }

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
- rl_clear_history, 
  - Prototype :

- rl_on_new_line,
  - Prototype :

- rl_replace_line, 
  - Prototype :

- rl_redisplay, 
  - Prototype :


- add_history,
  - Prototype :
















  - printf, 



  - malloc, 



  - free, 



  - write, 



  - access, 


  - open, 


  - read,



  - close, 


  - fork, 



  - wait, 



  - waitpid, 


  - wait3, 


  - wait4, 



  - signal,



  - sigaction, 



  - sigemptyset, 


  - sigaddset, 



  - kill, 



  - exit,



  - getcwd, 



  - chdir, 


  - stat, 



  - lstat, 


  - fstat, 


  - unlink, 


  - execve,


  - dup, 


  - dup2, 

  - pipe, 


  - opendir, 



  - readdir, 



  - closedir,



  - strerror, 



  - perror, 


  - isatty, 




  - ttyname, 



  - ttyslot, 



  - ioctl,



  - getenv, 


  - tcsetattr, 


  - tcgetattr, 


  - tgetent, 


  - tgetflag,



  - tgetnum, 



  - tgetstr, 



  - tgoto, 




  - tputs






















