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
```C
//Gestion des signaux

// Ctrl+C (SIGINT) pour interrompre l'exécution d'une commande.



// Ctrl+D (EOF) pour terminer le shell.



// Ctrl+Z (SIGTSTP) pour mettre un processus en arrière-plan.


```
_________________________________________________________________________________________________________________________________________________
- rl_clear_history (GNU LIbrary)
> [!NOTE]
>
> Effacer l'historique des commandes stocké en mémoire pendant l'exécution du programme

  - Prototype:

        void rl_clear_history(void);

:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main() {
    char *input;

    while (1) {
        // Afficher le prompt et lire la commande utilisateur
        input = readline("minishell> ");

        if (input == NULL) {
            // L'utilisateur a appuyé sur Ctrl+D (EOF)
            printf("exit\n");
            rl_clear_history();  // Efface l'historique avant de quitter
            break;
        }

        if (*input != '\0') {
            add_history(input);  // Ajouter la commande à l'historique
        }

        // Simuler une commande quelconque
        printf("Commande exécutée: %s\n", input);

        free(input);
    }

    return 0;
}

// Effacer l'historique
  // Effacer l'historique si l'utilisateur tape "clear_history"
        if (strcmp(input, "clear_history") == 0){
            rl_clear_history();  // Efface tout l'historique
            printf("Historique effacé.\n");
        } else {
            printf("Commande reçue: %s\n", input);
        }

```
_________________________________________________________________________________________________________________________________________________
- rl_on_new_line (GNU LIbrary)

> [!NOTE]
>
> indiquer que le curseur doit se positionner sur une nouvelle ligne dans le terminal.



  - Prototype :

        int rl_on_new_line(void);

:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void handle_sigint(int sig) {
    // Indiquer que l'on souhaite réafficher une nouvelle ligne propre
    rl_on_new_line();
    // Efface la ligne actuelle partiellement saisie, si nécessaire
    rl_replace_line("", 0);
    // Réafficher le prompt
    rl_redisplay();
}

int main() {
    char *input;

    // Associer le signal SIGINT à notre gestionnaire de signal personnalisé
    signal(SIGINT, handle_sigint);

    while (1) {
        // Lire la commande utilisateur
        input = readline("minishell> ");

        if (input == NULL) {
            printf("exit\n");
            break;
        }

        if (*input != '\0') {
            add_history(input);  // Ajouter la commande à l'historique
        }

        printf("Commande reçue: %s\n", input);
        free(input);
    }

    return 0;
}

```

_________________________________________________________________________________________________________________________________________________
- rl_replace_line (GNU LIbrary)

> [!NOTE]
>
> permet de remplacer le contenu de la ligne courante que l'utilisateur est en train de taper par un nouveau texte.

  - Prototype :

        int rl_replace_line(const char *text, int clear_undo);

  - Description :
    - text : C'est la nouvelle chaîne de caractères qui va remplacer la ligne actuelle. Si vous voulez effacer la ligne, vous pouvez passer une chaîne vide ("").
    - clear_undo : Si cette valeur est non nulle (par exemple, 1), l'historique des

:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

// Gestionnaire de signal pour Ctrl+C
void handle_sigint(int sig) {
    // Indiquer qu'une nouvelle ligne va commencer
    rl_on_new_line();
    // Remplacer la ligne actuelle par une chaîne vide (effacer la ligne)
    rl_replace_line("", 0);
    // Réafficher le prompt
    rl_redisplay();
}

int main() {
    char *input;

    // Associer le signal SIGINT à notre gestionnaire personnalisé
    signal(SIGINT, handle_sigint);

    while (1) {
        // Lire la commande utilisateur avec le prompt
        input = readline("minishell> ");

        if (input == NULL) {
            printf("exit\n");
            break;
        }

        if (*input != '\0') {
            add_history(input);  // Ajouter la commande à l'historique
        }

        printf("Commande exécutée: %s\n", input);
        free(input);
    }

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
- rl_redisplay (GNU LIbrary)

> [!NOTE]
>
> Elle est utilisée pour rafraîchir l'affichage du prompt et de la ligne de commande actuelle dans le terminal, ce qui est particulièrement utile lorsque des modifications ont été apportées à la ligne en cours ou que le curseur doit être repositionné.

  - Prototype :

        void rl_redisplay(void);

:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

// Gestionnaire de signal pour Ctrl+C
void handle_sigint(int sig) {
    rl_on_new_line();            // Indiquer qu'une nouvelle ligne va commencer
    rl_replace_line("", 0);      // Effacer la ligne courante
    rl_redisplay();              // Réafficher le prompt correctement
}

int main() {
    char *input;

    // Associer le signal SIGINT à notre gestionnaire personnalisé
    signal(SIGINT, handle_sigint);

    while (1) {
        // Lire la commande utilisateur
        input = readline("minishell> ");

        if (input == NULL) {
            printf("exit\n");
            break;
        }

        if (*input != '\0') {
            add_history(input);  // Ajouter la commande à l'historique
        }

        printf("Commande exécutée: %s\n", input);
        free(input);
    }

    return 0;
}

```


_________________________________________________________________________________________________________________________________________________
- add_history (GNU LIbrary)

> [!NOTE]
>
> ajouter une entrée à l'historique des lignes de commande saisies par l'utilisateur.
> permet de naviguer facilement dans les commandes précédemment exécutées en utilisant les touches fléchées haut et bas.



  - Prototype :

        void add_history(const char *line);

  - Description :
    - line : C'est la chaîne de caractères (la commande) que vous souhaitez ajouter à l'historique. Cela doit être une chaîne de caractères null-terminée.

  :octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    while (1) {
        // Lire la commande de l'utilisateur
        input = readline("minishell> ");

        // Vérifier si l'entrée est NULL (utilisateur a tapé Ctrl+D)
        if (input == NULL) {
            printf("exit\n");
            break;
        }

        // Ne pas ajouter des lignes vides à l'historique
        if (*input != '\0') {
            add_history(input);  // Ajouter la commande à l'historique
        }

        // Traiter la commande (ici, on l'affiche simplement)
        printf("Commande exécutée: %s\n", input);
        free(input);  // Libérer la mémoire allouée par readline
    }

    return 0;
}
```
_________________________________________________________________________________________________________________________________________________
  - printf

        int printf(const char *format, ...);
    
  - malloc 

        void *malloc(size_t size);

  - free 

        void free(void *ptr);

  - write 

        ssize_t write(int fd, const void *buf, size_t count);

_________________________________________________________________________________________________________________________________________________

- access 

> [!NOTE]
>

  - Prototype :

        int access(const char *pathname, int mode);

  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- open, 
> [!NOTE]
>

  - Prototype :
  
  
  - Description :

:octocat:**EXEMPLES D'UTILISATION**:octocat:

_________________________________________________________________________________________________________________________________________________
- read,

> [!NOTE]
>
  - Prototype :
  
  
  - Description :

:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- close, 

> [!NOTE]
>
  - Prototype :
  
  
  - Description :

:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- fork, 

> [!NOTE]
>
  - Prototype :
  
  
  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- wait, 

> [!NOTE]
>
  - Prototype :
  
  
  - Description :

:octocat:**EXEMPLES D'UTILISATION**:octocat:
__________________________________________________________________________________________________________________________________________________
- waitpid, 

> [!NOTE]
>
  - Prototype :


  - Description :

:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- wait3, 

> [!NOTE]
>
  - Prototype :


  - Description :

:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- wait4, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- signal,

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- sigaction, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- sigemptyset, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- sigaddset, 

> [!NOTE]
>

  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- kill, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- exit,

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- getcwd, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- chdir, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- stat, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- lstat, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- fstat, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- unlink, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- execve,

> [!NOTE]
>
  - Prototype :


  - Description :

:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- dup, 

> [!NOTE]
>
  - Prototype :


  - Description :

:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- dup2, 

> [!NOTE]
>
  - Prototype :


  - Description :

:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- pipe, 

> [!NOTE]
>
  - Prototype :


  - Description :

:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- opendir, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- readdir, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- closedir,

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- strerror, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- perror, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- isatty, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:

_________________________________________________________________________________________________________________________________________________
- ttyname, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- ttyslot, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- ioctl,

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- getenv, 

> [!NOTE]
>
  - Prototype :


  - Description :

:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- tcsetattr, 

> [!NOTE]
>
  - Prototype :


  - Description :

:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- tcgetattr, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- tgetent, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- tgetflag,

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- tgetnum, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- tgetstr, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:
_________________________________________________________________________________________________________________________________________________
- tgoto, 

> [!NOTE]
>
  - Prototype :


  - Description :


:octocat:**EXEMPLES D'UTILISATION**:octocat:

_________________________________________________________________________________________________________________________________________________
- tputs

> [!NOTE]
>
  - Prototype :


  - Description :



:octocat:**EXEMPLES D'UTILISATION**:octocat:


_________________________________________________________________________________________________________________________________________________
















