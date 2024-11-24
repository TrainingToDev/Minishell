# Minishell
As beautifull as a shell
Write a shell

# Test
- testing a redirection in bash:

>$ > echo hello > file.txt

Error output:

```
Command 'hello' not found, but can be installed with:
snap install hello              # version 2.10, or
apt  install hello              # version 2.10-2ubuntu4
apt  install hello-traditional  # version 2.10-5
See 'snap info hello' for additional versions.
```


>$ 


# DOC
[GNU Bash manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual)<br>
[Explain Shell](https://explainshell.com/)<br>
[Tutorial - Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c)<br>
[Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)<br>
[How to Use "Here Documents" in Bash on Linux](https://www.howtogeek.com/719058/how-to-use-here-documents-in-bash-on-linux)<br>
[Writing a Unix Shell - Part I](https://indradhanush.github.io/blog/writing-a-unix-shell-part-1)<br>
[Writing a Unix Shell - Part II](https://indradhanush.github.io/blog/writing-a-unix-shell-part-2)<br>
[Writing a Unix Shell - Part III](https://indradhanush.github.io/blog/writing-a-unix-shell-part-3)<br>
[Tiny Shell - Case Study](http://www.cems.uwe.ac.uk/~irjohnso/coursenotes/lrc/system/shell/)<br>
[42Cursus-Minishell](https://achrafbelarif.medium.com/42cursus-minishell-29cd25f972e6)<br>
[Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)<br>
[guide]https://42-cursus.gitbook.io/guide/rank-03/minishell<br>

# Tuto
[Unix Processes in C](https://youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&si=HT0Zjn8jon9jTXhs)<br>
[Shell Program Explained](https://youtu.be/ubt-UjcQUYg)<br>
![42-Minishell](https://www.youtube.com/watch?v=ubt-UjcQUYg&list=PLGU1kcPKHMKj5yA0RPb5AK4QAhexmQwrW&index=4) <br>
[explain](https://carlagoeshacking.wordpress.com/wp-content/uploads/2017/01/minisheel.pdf)<br>
[info](https://ocw.cs.pub.ro/courses/sde2/teme/tema_fr_3)

# TESTER
[42_minishell_tester](https://github.com/zstenger93/42_minishell_tester)<br>
[minishell_tester](https://github.com/thallard/minishell_tester)<br>
[minishell_test](https://pypi.org/project/minishell-test/)<br>
[minitester](https://github.com/LucasKuhn/minishell_tester) <br>
.[eval](https://hackmd.io/@ep5KljplTku1JOdkIKLI3A/H1TY3jqfj) <br>

# info

-> Tube anonymes (|),
-> Tube nommés


# Mandatory:
> Objectif général : Créer un shell qui lit des commandes entrées par l'utilisateur, analyse ces commandes, et les exécute tout en reproduisant un comportement proche de celui de Bash pour certaines commandes.
## Principales Fonctionnalités à Implémenter :

1- Prompt d’attente et historique des commandes : Le shell doit afficher un prompt chaque fois qu’il attend une commande. Il doit aussi sauvegarder chaque commande dans l’historique.

2- Exécution des commandes (basé sur PATH ou chemin absolu/relatif) : Le shell doit pouvoir exécuter des commandes en recherchant l’exécutable approprié dans le **PATH**.

3- Gestion des signaux : Le shell doit capturer les signaux comme **ctrl-C**, **ctrl-D**, et **ctrl-\** pour imiter le comportement de Bash dans ces cas.

4- Gestion des citations et des métacaractères : Les citations simples **' '** désactivent l’interprétation des métacaractères, tandis que les citations doubles **" "** désactivent l'interprétation des métacaractères sauf pour **$**.

5- Redirections d'entrée et de sortie :

- **<** : Redirection d'entrée.
- **>** : Redirection de sortie.
- **<<** : Ici-documents (ou "here-documents").
- **>>** : Redirection de sortie en mode append.

6- Pipes (|) : Enchaîner les commandes, où la sortie d’une commande devient l'entrée de la suivante.

7- Variables d’environnement ($VAR) : Le shell doit pouvoir interpréter et remplacer les variables d’environnement par leur valeur.

8- Builtins : Implémentation des commandes intégrées suivantes :

 - echo avec l'option -n
 - cd avec un chemin relatif ou absolu
 - pwd sans options
 - export sans options
 - unset sans options
 - env sans options
 - exit sans options

9- Gestion de la sortie de la dernière commande : La variable $? doit afficher le code de sortie de la commande précédente.

10- Gestion de la mémoire : Tout espace alloué dynamiquement doit être libéré de manière appropriée, et aucun « double free » ni fuite de mémoire n'est autorisé.


# Bonus part

implémenter :

  - && et || avec des parenthèses pour les priorités.
  - Les jokers * doivent fonctionner pour le répertoire de travail actuel.


## :green_square:Program name : minishell:green_square:

### **Description des fonctions pratiques et exemples d'utilisation**
_________________________________________________________________________________________________________________________________________________
1) **readline (GNU Library)**

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
2) **rl_clear_history (GNU LIbrary)**
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
3) **rl_on_new_line (GNU LIbrary)**

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
4)** rl_replace_line (GNU LIbrary)**

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
5) **rl_redisplay (GNU LIbrary)**

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
6) **add_history (GNU LIbrary)**

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
7) printf

        int printf(const char *format, ...);
    
8) malloc 

        void *malloc(size_t size);

9) free 

        void free(void *ptr);

10) write 

        ssize_t write(int fd, const void *buf, size_t count);

_________________________________________________________________________________________________________________________________________________

11) access 

> [!NOTE]
>
> pour vérifier les permissions d'accès à un fichier

  - Prototype :

        int access(const char *pathname, int mode);

  - Description :
    - pathname : Une chaîne de caractères qui spécifie le chemin du fichier à vérifier.
    - mode : Un entier qui spécifie les permissions à vérifier. Il peut prendre l'une des valeurs suivantes :
      - F_OK : Vérifie si le fichier existe.
      - R_OK : Vérifie si le fichier est lisible.
      - W_OK : Vérifie si le fichier est inscriptible.
      - X_OK : Vérifie si le fichier est exécutable.
  

:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
    const char *filename = "test.txt";

    // Vérifier si le fichier existe et s'il est lisible
    if (access(filename, F_OK) == 0) {
        printf("Le fichier '%s' existe.\n", filename);
        
        if (access(filename, R_OK) == 0) {
            printf("Le fichier '%s' est lisible.\n", filename);
        } else {
            printf("Le fichier '%s' n'est pas lisible.\n", filename);
        }
    } else {
        printf("Le fichier '%s' n'existe pas. Erreur : %s\n", filename, strerror(errno));
    }

    return 0;
}

```
```C
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void execute_command(const char *command) {
    // Vérifier si la commande est exécutable
    if (access(command, X_OK) == 0) {
        printf("Exécution de la commande : %s\n", command);
        // Logique pour exécuter la commande
    } else {
        fprintf(stderr, "Erreur : La commande '%s' n'est pas exécutable. Erreur : %s\n", command, strerror(errno));
    }
}

int main() {
    const char *cmd = "my_script.sh";
    execute_command(cmd); // Appeler la fonction pour exécuter la commande
    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
12) open 
> [!NOTE]
>
> ouvrir un fichier ou un périphérique et obtenir un descripteur de fichier, qui pourra être utilisé pour lire ou écrire des données dans ce fichier.

  - Prototype :

        int open(const char *pathname, int flags);
        int open(const char *pathname, int flags, mode_t mode);

  - Description :
    - pathname : Le chemin du fichier que vous voulez ouvrir. Il peut être absolu (comme /home/user/fichier.txt) ou relatif (comme ./fichier.txt).
    - flags : Un ou plusieurs drapeaux qui spécifient le mode d'ouverture du fichier. Les drapeaux les plus courants sont :
      - O_RDONLY : Ouvrir en lecture seule.
      - O_WRONLY : Ouvrir en écriture seule.
      - O_RDWR : Ouvrir en lecture et écriture.
      - O_CREAT : Créer le fichier s'il n'existe pas.
      - O_TRUNC : Tronquer le fichier à une taille de 0 octet s'il existe déjà.
      - O_APPEND : Écrire à la fin du fichier.
    - mode (optionnel) : Ce paramètre est utilisé si vous créez un fichier avec le drapeau O_CREAT. Il définit les permissions d'accès du fichier (comme 0644, qui donne les permissions lecture/écriture au propriétaire et lecture pour les autres).



:octocat:**EXEMPLES D'UTILISATION**:octocat:

_________________________________________________________________________________________________________________________________________________
13) read

> [!NOTE]
>
> lire des données depuis un descripteur de fichier dans un buffer.

  - Prototype :
  
        ssize_t read(int fd, void *buf, size_t count);
  
  - Description :
    - fd : Le descripteur de fichier depuis lequel on veut lire. Cela peut être un fichier ouvert ou un périphérique (par exemple, le descripteur pour l'entrée standard stdin, qui est 0).
    - buf : Un pointeur vers un buffer où les données lues seront stockées.
    - count : Le nombre d'octets à lire depuis le descripteur de fichier dans le buffer.
   

:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
    const char *filename = "test.txt";
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        // Gestion d'erreur
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s. Erreur : %s\n", filename, strerror(errno));
        return 1;
    }

    char buffer[256];
    ssize_t bytes_read;

    // Lire le contenu du fichier
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        fprintf(stderr, "Erreur de lecture du fichier. Erreur : %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    // Terminer la chaîne avec un caractère nul pour affichage
    buffer[bytes_read] = '\0';
    printf("Contenu lu :\n%s\n", buffer);

    // Fermer le fichier
    close(fd);

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
14) close

> [!NOTE]
>
> pour fermer un descripteur de fichier ouvert, libérant ainsi les ressources associées à ce descripteur.


  - Prototype :

        int close(int fd);

  
  - Description :
    - fd : Le descripteur de fichier que vous souhaitez fermer. Ce descripteur est obtenu lors de l'ouverture du fichier (par exemple, via la fonction open()).

:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
    const char *filename = "test.txt";
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        // Gestion d'erreur
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s. Erreur : %s\n", filename, strerror(errno));
        return 1;
    }

    // Lire le contenu du fichier
    char buffer[256];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        fprintf(stderr, "Erreur lors de la lecture du fichier. Erreur : %s\n", strerror(errno));
        close(fd);  // Fermer le fichier avant de quitter
        return 1;
    }

    // Ajouter un caractère nul pour terminer la chaîne
    buffer[bytes_read] = '\0';
    printf("Contenu lu : %s\n", buffer);

    // Fermer le fichier
    if (close(fd) == -1) {
        fprintf(stderr, "Erreur lors de la fermeture du fichier. Erreur : %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
```

_________________________________________________________________________________________________________________________________________________
15) fork

> [!NOTE]
>
> créer un nouveau processus en clonant le processus appelant.
> Après l'appel à fork(), deux processus s'exécutent en parallèle : **le processus parent (l'original) et le processus enfant (la copie).**


  - Prototype :

        pid_t fork(void);


:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    // Création d'un nouveau processus
    pid = fork();

    if (pid < 0) {
        // Gestion d'erreur
        perror("Erreur lors du fork");
        return 1;
    } else if (pid == 0) {
        // Code exécuté par le processus enfant
        printf("Je suis le processus enfant. PID : %d\n", getpid());
    } else {
        // Code exécuté par le processus parent
        printf("Je suis le processus parent. PID du parent : %d, PID de l'enfant : %d\n", getpid(), pid);
    }

    return 0;
}

```

- Utilisation typique de fork()

  - Création de processus fils pour effectuer une tâche différente ou en parallèle au parent.<br>
  - Multiprocessing : fork() est couramment utilisé pour créer des processus séparés dans des serveurs Unix, comme des serveurs web qui traitent plusieurs requêtes simultanément.<br>
  - Interprétation de commandes : Dans des projets comme Minishell, fork() est souvent utilisé pour créer un nouveau processus lorsque l'utilisateur entre une commande à exécuter. Le processus enfant exécute la commande, tandis que le parent attend sa fin.<br>

  

_________________________________________________________________________________________________________________________________________________
16) wait

> [!NOTE]
>
> permet à un processus parent d'attendre que l'un de ses processus enfants se termine.
> Elle est utilisée dans les systèmes Unix/Linux pour synchroniser les processus parent et enfant, assurant que le parent récupère l'état de l'enfant à sa fin.
> Elle est définie dans la bibliothèque <sys/wait.h>.

  - Prototype :

        pid_t wait(int *wstatus);

  - Description :
    - wstatus : Un pointeur vers un entier où sera stocké le code de sortie du processus enfant. Ce code peut être analysé avec des macros comme WIFEXITED(wstatus) et    WEXITSTATUS(wstatus) pour déterminer la raison de la terminaison de l'enfant.

  - Utilisation :
    - Attendre la fin d'un processus enfant : wait() bloque le processus parent jusqu'à ce qu'un de ses processus enfants se termine. C'est souvent utilisé pour s'assurer que le parent ne continue pas son exécution avant que l'enfant ait fini son travail.
    - Récupération de l'état de l'enfant : Le parent peut utiliser wait() pour connaître comment le processus enfant s'est terminé (exécution normale, signal, etc.).

:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Gestion d'erreur
        perror("Erreur lors du fork");
        return 1;
    } else if (pid == 0) {
        // Processus enfant
        printf("Processus enfant en cours, PID : %d\n", getpid());
        sleep(2);  // Simuler un travail dans l'enfant
        printf("Fin du processus enfant.\n");
        return 42;  // Retourne 42 comme code de sortie
    } else {
        // Processus parent
        int wstatus;
        printf("Processus parent en attente de la fin de l'enfant...\n");

        // Attendre la fin de l'enfant
        wait(&wstatus);

        // Vérifier comment l'enfant s'est terminé
        if (WIFEXITED(wstatus)) {
            printf("L'enfant s'est terminé normalement avec le code de sortie %d\n", WEXITSTATUS(wstatus));
        } else {
            printf("L'enfant ne s'est pas terminé normalement.\n");
        }
    }

    return 0;
}

```

- Macros pour analyser le statut de l'enfant :
  - WIFEXITED(wstatus) : Retourne vrai si l'enfant s'est terminé normalement.
  - WEXITSTATUS(wstatus) : Donne le code de sortie de l'enfant (utilisé uniquement si WIFEXITED() est vrai).
  - WIFSIGNALED(wstatus) : Retourne vrai si l'enfant a été terminé par un signal.
  - WTERMSIG(wstatus) : Donne le numéro du signal qui a terminé l'enfant (si WIFSIGNALED() est vrai).
__________________________________________________________________________________________________________________________________________________
17) waitpid

> [!NOTE]
>
> permet à un processus parent d'attendre la terminaison d'un processus enfant spécifique.
> Elle est plus flexible que la fonction wait(), qui attend la fin de n'importe quel processus enfant.
> Avec waitpid(), vous pouvez attendre un processus enfant particulier, ou utiliser certaines options pour modifier le comportement de l'attente.
> Elle est définie dans la bibliothèque <sys/wait.h>.

  - Prototype :

        pid_t waitpid(pid_t pid, int *wstatus, int options);

  - Description :
    - pid : Ce paramètre détermine quel processus enfant le parent attend. Il peut prendre plusieurs valeurs :
      - pid > 0 : Attend le processus enfant avec le PID spécifié.
      - pid == 0 : Attend un processus enfant dont le groupe de processus est égal à celui du processus parent.
      - pid < -1 : Attend n'importe quel processus enfant dont le groupe de processus est égal à la valeur absolue de pid.
      - pid == -1 : Fonctionne comme wait(), c'est-à-dire qu'il attend n'importe quel processus enfant.
  - wstatus : Un pointeur vers un entier où sera stocké le code de sortie du processus enfant. Vous pouvez analyser ce code avec les macros WIFEXITED(), WEXITSTATUS(), etc.
  - options : Vous pouvez spécifier des options pour modifier le comportement de l'attente. Voici quelques-unes des options courantes :
    - WNOHANG : Ne bloque pas si aucun processus enfant n'est terminé ; dans ce cas, waitpid() retourne immédiatement avec 0.
    - WUNTRACED : Permet à waitpid() de retourner si un enfant est arrêté (mais non terminé), par exemple, si un signal SIGSTOP est envoyé à l'enfant.

:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Erreur lors du fork");
        return 1;
    } else if (pid == 0) {
        // Processus enfant
        printf("Processus enfant en cours, PID : %d\n", getpid());
        sleep(2);  // Simule un travail dans l'enfant
        printf("Fin du processus enfant.\n");
        return 42;  // Retourne un code de sortie
    } else {
        // Processus parent
        int wstatus;
        printf("Processus parent en attente de la fin de l'enfant...\n");

        // Attendre la fin du processus enfant spécifique
        pid_t waited_pid = waitpid(pid, &wstatus, 0);

        if (waited_pid == -1) {
            perror("Erreur lors de waitpid");
            return 1;
        }

        if (WIFEXITED(wstatus)) {
            printf("L'enfant s'est terminé avec le code de sortie : %d\n", WEXITSTATUS(wstatus));
        }
    }

    return 0;
}
```

_________________________________________________________________________________________________________________________________________________
18) wait3

> [!NOTE]
>
> une variante de wait() qui, en plus d'attendre la fin d'un processus enfant,
> permet de récupérer des informations supplémentaires sur l'utilisation des ressources par ce processus.
> Elle est principalement utilisée dans des environnements Unix/Linux et est définie dans <sys/wait.h>.


  - Prototype :

        pid_t wait3(int *wstatus, int options, struct rusage *rusage);

  - Description :
    - wstatus : Un pointeur vers un entier où sera stocké le statut de fin du processus enfant. Vous pouvez analyser ce statut avec les macros habituelles telles que WIFEXITED(), WEXITSTATUS(), WIFSIGNALED(), etc.
    - options : Ce paramètre contrôle le comportement de wait3(), avec des options similaires à waitpid(). Par exemple, vous pouvez utiliser :
      - WNOHANG : Ne bloque pas si aucun enfant n'est terminé ; retourne immédiatement avec 0.
      - WUNTRACED : Permet à wait3() de retourner si un enfant a été arrêté mais pas terminé (ex : si un signal SIGSTOP lui a été envoyé).
    - rusage : Un pointeur vers une structure struct rusage où seront stockées les informations d'utilisation des ressources du processus enfant (par exemple, le temps processeur consommé, les entrées/sorties, etc.). Si vous ne voulez pas ces informations, vous pouvez passer NULL.

:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
/*
La structure rusage :
La structure struct rusage contient des informations détaillées sur l'utilisation des ressources par le processus enfant. Voici à quoi ressemble cette structure (définie dans <sys/resource.h>) :
*/
struct rusage {
    struct timeval ru_utime;    /* Temps CPU en mode utilisateur */
    struct timeval ru_stime;    /* Temps CPU en mode système */
    long   ru_maxrss;           /* Mémoire maximale résidente utilisée */
    long   ru_ixrss;            /* Mémoire partagée utilisée */
    long   ru_idrss;            /* Mémoire privée utilisée */
    long   ru_isrss;            /* Mémoire pour la pile utilisée */
    long   ru_minflt;           /* Nombre de pages mineures */
    long   ru_majflt;           /* Nombre de pages majeures */
    long   ru_nswap;            /* Nombre de swaps */
    long   ru_inblock;          /* Opérations d'entrées */
    long   ru_oublock;          /* Opérations de sorties */
    long   ru_msgsnd;           /* Messages IPC envoyés */
    long   ru_msgrcv;           /* Messages IPC reçus */
    long   ru_nsignals;         /* Nombre de signaux reçus */
    long   ru_nvcsw;            /* Commutations volontaires de contexte */
    long   ru_nivcsw;           /* Commutations involontaires de contexte */
};

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Erreur lors du fork");
        return 1;
    } else if (pid == 0) {
        // Processus enfant
        printf("Processus enfant en cours, PID : %d\n", getpid());
        sleep(2);  // Simule un travail
        printf("Fin du processus enfant.\n");
        return 42;  // Code de sortie
    } else {
        // Processus parent
        int wstatus;
        struct rusage usage;

        printf("Processus parent en attente...\n");

        // Attendre la fin de l'enfant et récupérer les informations sur l'utilisation des ressources
        wait3(&wstatus, 0, &usage);

        if (WIFEXITED(wstatus)) {
            printf("L'enfant s'est terminé avec le code de sortie : %d\n", WEXITSTATUS(wstatus));
        }

        // Afficher les informations d'utilisation des ressources
        printf("Temps CPU utilisateur : %ld.%06lds\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
        printf("Temps CPU système : %ld.%06lds\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
        printf("Mémoire maximale résidente : %ld KB\n", usage.ru_maxrss);
    }

    return 0;
}

```
- Quand utiliser wait3() :
  - Lorsque vous voulez attendre un processus enfant tout en récupérant des informations sur son utilisation des ressources.
  - Programmes de monitoring ou d'optimisation : Vous pouvez utiliser wait3() pour évaluer la performance des processus enfants en termes de temps processeur et de mémoire utilisée.
  - Systèmes multitâches : Dans des applications où il est important de mesurer l'efficacité ou l'impact des processus enfants sur les ressources système, wait3() peut fournir des données utiles.
    - Optimisation

_________________________________________________________________________________________________________________________________________________
19) wait4

> [!NOTE]
>
> très similaire à wait3()
> offre un peu plus de flexibilité en permettant d'attendre la fin d'un processus enfant spécifique, tout en collectant des informations sur l'utilisation des ressources du processus terminé..
> Comme waitpid(), elle permet de sélectionner un processus spécifique à attendre.
> Elle est définie dans <sys/wait.h>.

  - Prototype :

        pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);


  - Description :
    - pid : Le processus enfant à attendre, avec les mêmes options que pour waitpid() :
      - pid > 0 : Attend le processus enfant avec ce PID spécifique.
      - pid == 0 : Attend un processus enfant dont le groupe de processus est égal à celui du parent.
      - pid < -1 : Attend n'importe quel processus enfant dont le groupe de processus est égal à la valeur absolue de pid.
      - pid == -1 : Fonctionne comme wait(), c'est-à-dire qu'il attend n'importe quel processus enfant.
    - wstatus : Un pointeur vers un entier où sera stocké le code de statut de fin du processus enfant. Vous pouvez utiliser des macros comme WIFEXITED() ou WEXITSTATUS() pour analyser ce statut.
    - options : Modifie le comportement de l'attente, avec les mêmes options que pour waitpid() :
      - WNOHANG : Ne bloque pas si aucun enfant n'est terminé ; retourne immédiatement avec 0.
      - WUNTRACED : Retourne si un enfant a été arrêté mais non terminé (ex. signal SIGSTOP).
    - rusage : Un pointeur vers une structure struct rusage pour récupérer les informations d'utilisation des ressources du processus enfant terminé (par exemple, le temps processeur, mémoire utilisée, etc.). Si vous ne voulez pas récupérer ces informations, passez NULL.


:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Erreur lors du fork");
        return 1;
    } else if (pid == 0) {
        // Processus enfant
        printf("Processus enfant en cours, PID : %d\n", getpid());
        sleep(2);  // Simule un travail
        printf("Fin du processus enfant.\n");
        return 42;  // Code de sortie
    } else {
        // Processus parent
        int wstatus;
        struct rusage usage;

        printf("Processus parent en attente...\n");

        // Attendre la fin de l'enfant et récupérer les informations d'utilisation des ressources
        pid_t waited_pid = wait4(pid, &wstatus, 0, &usage);

        if (waited_pid == -1) {
            perror("Erreur lors de wait4");
            return 1;
        }

        if (WIFEXITED(wstatus)) {
            printf("L'enfant s'est terminé avec le code de sortie : %d\n", WEXITSTATUS(wstatus));
        }

        // Afficher les informations d'utilisation des ressources
        printf("Temps CPU utilisateur : %ld.%06lds\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
        printf("Temps CPU système : %ld.%06lds\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
        printf("Mémoire maximale résidente : %ld KB\n", usage.ru_maxrss);
    }

    return 0;
}
```

- Quand utiliser wait4() :
  - Si vous avez besoin d'attendre un processus enfant spécifique tout en récupérant des informations sur l'utilisation des ressources.
  - Comme waitpid(), mais avec le bénéfice supplémentaire d'avoir accès aux statistiques des ressources utilisées par le processus terminé.
  - Utilisable dans des projets comme Minishell où chaque commande est exécutée dans un processus enfant et où vous voulez récupérer les performances (temps CPU, mémoire) de chaque commande exécutée.


_________________________________________________________________________________________________________________________________________________
20) signal

> [!NOTE]
>
> utilisée pour définir ou modifier le comportement du programme lorsqu'il reçoit certains signaux (comme SIGINT, SIGTERM, etc.).
> Elle permet de spécifier une fonction de gestion des signaux, appelée un gestionnaire de signal, qui sera exécutée lorsqu'un signal particulier est reçu par le programme.

> [!TIP}
> Les signaux sont des mécanismes utilisés par le système d'exploitation pour interrompre l'exécution normale d'un programme afin de lui notifier des événements, tels qu'une demande d'interruption (Ctrl+C), l'arrêt d'un processus, une erreur de segmentation, etc.
> 


  - Prototype :

        void (*signal(int signum, void (*handler)(int)))(int);


  - Description :
    - signum : Numéro du signal que vous voulez capturer ou traiter. Il existe de nombreux signaux prédéfinis dans Unix/Linux, comme :
      - SIGINT : Interruption (Ctrl+C).
      - SIGTERM : Demande d'arrêt.
      - SIGKILL : Arrêt forcé (ne peut pas être capturé ou ignoré).
      - SIGSEGV : Erreur de segmentation.
      - SIGTSTP : Suspendre un processus (Ctrl+Z).
     
    - handler : Pointeur vers la fonction de gestion qui sera appelée lorsque le signal spécifié est reçu. Il existe trois comportements possibles :
      - Fonction utilisateur : Vous pouvez définir une fonction qui sera appelée lorsque le signal est reçu. Cette fonction doit prendre un entier (le numéro du signal) en argument et ne pas renvoyer de valeur.
      - SIG_IGN : Ignore le signal.
      - SIG_DFL : Comportement par défaut pour ce signal.

:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Fonction de gestion du signal SIGINT
void handle_sigint(int sig) {
    printf("\nSignal SIGINT reçu. Appuyez sur Ctrl+C encore pour quitter.\n");
}

int main() {
    // Associe le signal SIGINT à la fonction handle_sigint
    signal(SIGINT, handle_sigint);

    while (1) {
        printf("En attente d'un signal... (Appuyez sur Ctrl+C)\n");
        sleep(2);  // Pause de 2 secondes
    }

    return 0;
}

// utilisation avec plusieurs signaux :

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig) {
    printf("\nSIGINT reçu (Ctrl+C)\n");
}

void handle_sigterm(int sig) {
    printf("\nSIGTERM reçu\n");
}

void handle_sigstop(int sig) {
    printf("\nSIGTSTP reçu (Ctrl+Z)\n");
}

int main() {
    signal(SIGINT, handle_sigint);  // Ctrl+C
    signal(SIGTERM, handle_sigterm); // Signal de terminaison
    signal(SIGTSTP, handle_sigstop); // Ctrl+Z

    while (1) {
        printf("Attente des signaux... (Appuyez sur Ctrl+C, Ctrl+Z)\n");
        sleep(2);
    }

    return 0;
}

```

- Quand utiliser signal() :
  - Pour gérer les interruptions utilisateur : Par exemple, dans un shell (comme Minishell), vous pouvez intercepter SIGINT (Ctrl+C) pour empêcher la fermeture du shell et simplement annuler la commande en cours.
  - Pour gérer les signaux système : Vous pouvez utiliser SIGTERM pour gérer les demandes d'arrêt ordonnées ou SIGCHLD pour traiter les processus enfants terminés.
  - Pour créer un comportement personnalisé en fonction des signaux reçus, comme sauvegarder l'état du programme avant qu'il ne soit terminé par un signal.
 
- Gestion avancée des signaux :

Dans les programmes complexes, il est recommandé d'utiliser sigaction() à la place de signal() car il offre un meilleur contrôle des signaux et garantit un comportement plus fiable et portable. Par exemple, signal() peut avoir un comportement différent selon le système d'exploitation, tandis que sigaction() suit les normes POSIX de manière plus stricte.

_________________________________________________________________________________________________________________________________________________
21) sigaction

> [!NOTE]
>
> une méthode plus avancée et plus fiable pour gérer les signaux par rapport à signal()
> permet de définir un gestionnaire de signal avec un contrôle précis sur son comportement.
> Cette fonction est standard dans les systèmes conformes à POSIX, ce qui en fait un choix idéal pour la gestion des signaux dans des applications C sur des systèmes Unix/Linux.
  
  - Prototype :

         int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

  - Description :
    - signum : Numéro du signal que vous souhaitez gérer (par exemple, SIGINT, SIGTERM, etc.).
    - act : Pointeur vers une structure struct sigaction qui définit le nouveau comportement à associer au signal. Cette structure contient les informations suivantes :
      - sa_handler : Pointeur vers la fonction de gestion qui sera appelée lorsque le signal est reçu. Cette fonction doit prendre un entier en argument (le numéro du signal) et ne doit pas retourner de valeur. Vous pouvez aussi utiliser SIG_IGN pour ignorer le signal ou SIG_DFL pour restaurer le comportement par défaut.
      - sa_mask : Masque des signaux qui seront bloqués pendant l'exécution du gestionnaire de signal. Cela permet de spécifier d'autres signaux à ignorer pendant le traitement du signal courant.
      - sa_flags : Options supplémentaires qui modifient le comportement du gestionnaire. Par exemple :
        - SA_RESTART : Permet à certaines fonctions système interrompues par le signal d'être redémarrées.
        - SA_SIGINFO : Indique que le gestionnaire de signal doit prendre trois arguments : le numéro du signal, un pointeur vers une structure siginfo_t et un pointeur vers un contexte d'exécution (ucontext_t).
      - oldact : Pointeur vers une structure struct sigaction où seront stockées les anciennes informations de gestion du signal. Cela vous permet de restaurer le comportement précédent si nécessaire.

:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
// La structure sigaction est définie comme suit :
struct sigaction {
    void (*sa_handler)(int);      // Pointeur vers la fonction de gestion du signal
    sigset_t sa_mask;             // Masque de signaux à bloquer pendant l'exécution du gestionnaire
    int sa_flags;                 // Options (SA_RESTART, SA_SIGINFO, etc.)
    void (*sa_sigaction)(int, siginfo_t *, void *); // Pour SA_SIGINFO
};

// un exemple simple de l'utilisation de sigaction() pour gérer le signal SIGINT (Ctrl+C) :

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Fonction de gestion du signal
void handle_sigint(int sig) {
    printf("\nSignal SIGINT reçu. Pour quitter, utilisez Ctrl+D.\n");
}

int main() {
    struct sigaction sa;

    // Initialisation de la structure sigaction
    sa.sa_handler = handle_sigint;  // Spécifie la fonction de gestion
    sigemptyset(&sa.sa_mask);        // Aucune signal bloqué pendant la gestion
    sa.sa_flags = 0;                  // Aucun drapeau spécial

    // Associe le signal SIGINT à la fonction handle_sigint
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Erreur lors de sigaction");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("En attente d'un signal... (Appuyez sur Ctrl+C)\n");
        sleep(2);  // Pause de 2 secondes
    }

    return 0;
}

// Gestion avancée avec SA_SIGINFO
/*
  Si vous souhaitez obtenir plus d'informations lorsque le signal est reçu, vous pouvez utiliser le drapeau SA_SIGINFO et définir sa_sigaction au lieu de sa_handler.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Fonction de gestion du signal
void handle_sigint(int sig, siginfo_t *info, void *context) {
    printf("\nSignal SIGINT reçu. PID: %d\n", info->si_pid);
}

int main() {
    struct sigaction sa;

    // Initialisation de la structure sigaction
    sa.sa_sigaction = handle_sigint; // Spécifie la fonction de gestion
    sigemptyset(&sa.sa_mask);         // Aucune signal bloqué pendant la gestion
    sa.sa_flags = SA_SIGINFO;         // Utilise le gestionnaire avec 3 arguments

    // Associe le signal SIGINT à la fonction handle_sigint
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Erreur lors de sigaction");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("En attente d'un signal... (Appuyez sur Ctrl+C)\n");
        sleep(2);  // Pause de 2 secondes
    }

    return 0;
}

```

- Quand utiliser sigaction() :
  - Gestion des signaux : Utilisez sigaction() pour définir un comportement personnalisé pour divers signaux, en particulier lorsque vous devez gérer des signaux comme SIGINT, SIGTERM, ou SIGCHLD.
  - Interruption sécurisée : Lorsque vous devez gérer les interruptions d'utilisateur et assurer une sortie propre ou une gestion des ressources.
  - Contexte de processus : Utilisez le drapeau SA_SIGINFO pour obtenir plus d'informations sur le signal, ce qui peut être utile pour le débogage ou la gestion des processus enfants.


_________________________________________________________________________________________________________________________________________________
22) sigemptyset

> [!NOTE]
>
> utilisée pour initialiser un ensemble de signaux à un état vide.
> Cela signifie que l'ensemble ne contient aucun signal. Cette fonction est souvent utilisée lors de la configuration de la gestion des signaux, notamment avec des structures comme sigaction, pour définir quels signaux doivent être bloqués pendant l'exécution d'un gestionnaire de signal.
  
  
  - Prototype :

         int sigemptyset(sigset_t *set);

  - Description :
    - set : Pointeur vers un objet de type sigset_t qui représente l'ensemble de signaux à initialiser.

  - Utilisation :
    - Initialisez un ensemble de signaux avant de l'utiliser dans des appels à sigprocmask() ou sigaction().
    - Assurez-vous que l'ensemble de signaux est vide lorsque vous configurez la gestion des signaux pour éviter de bloquer des signaux indésirables.
   

:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
// Voici un exemple simple montrant comment utiliser sigemptyset() pour initialiser un ensemble de signaux avant de le passer à sigaction()

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig) {
    printf("\nSignal SIGINT reçu. Quittez avec Ctrl+D.\n");
}

int main() {
    struct sigaction sa;
    sigset_t mask;

    // Initialiser l'ensemble de signaux à vide
    if (sigemptyset(&mask) == -1) {
        perror("Erreur lors de sigemptyset");
        exit(EXIT_FAILURE);
    }

    // Initialisation de la structure sigaction
    sa.sa_handler = handle_sigint; // Fonction de gestion du signal
    sa.sa_mask = mask;              // Masque des signaux à bloquer (vide ici)
    sa.sa_flags = 0;                // Aucune option spéciale

    // Associe le signal SIGINT à la fonction handle_sigint
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Erreur lors de sigaction");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("En attente d'un signal... (Appuyez sur Ctrl+C)\n");
        sleep(2);  // Pause de 2 secondes
    }

    return 0;
}

```

_________________________________________________________________________________________________________________________________________________
23) sigaddset

> [!NOTE]
>
> pour ajouter un signal à un ensemble de signaux.
> Elle est souvent utilisée dans le cadre de la gestion des signaux, notamment pour définir quels signaux doivent être bloqués pendant l'exécution d'un gestionnaire de signal.

  - Prototype :

        int sigaddset(sigset_t *set, int signum);

  - Description :
    - set : Pointeur vers un objet de type sigset_t qui représente l'ensemble de signaux dans lequel vous souhaitez ajouter un signal.
    - signum : Numéro du signal que vous souhaitez ajouter à l'ensemble. Par exemple, cela peut être SIGINT, SIGTERM, etc.
   
  - Utilisation :
    - Utilisez sigaddset() pour modifier un ensemble de signaux en y ajoutant des signaux spécifiques, généralement avant de passer cet ensemble à des fonctions comme sigprocmask() ou sigaction().

:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig) {
    printf("\nSignal SIGINT reçu.\n");
}

int main() {
    struct sigaction sa;
    sigset_t mask;

    // Initialiser l'ensemble de signaux à vide
    if (sigemptyset(&mask) == -1) {
        perror("Erreur lors de sigemptyset");
        exit(EXIT_FAILURE);
    }

    // Ajouter SIGTERM à l'ensemble
    if (sigaddset(&mask, SIGTERM) == -1) {
        perror("Erreur lors de sigaddset");
        exit(EXIT_FAILURE);
    }

    // Initialisation de la structure sigaction
    sa.sa_handler = handle_sigint; // Fonction de gestion du signal
    sa.sa_mask = mask;              // Masque des signaux à bloquer
    sa.sa_flags = 0;                // Aucune option spéciale

    // Associe le signal SIGINT à la fonction handle_sigint
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Erreur lors de sigaction");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("En attente d'un signal... (Appuyez sur Ctrl+C ou envoyez SIGTERM)\n");
        sleep(2);  // Pause de 2 secondes
    }

    return 0;
}

```

_________________________________________________________________________________________________________________________________________________
24) kill 

> [!NOTE]
>
> pour envoyer un signal à un processus.
> Bien que son nom puisse prêter à confusion, kill() ne se limite pas à terminer des processus ; elle peut être utilisée pour envoyer n'importe quel signal spécifié à un processus donné.
  
  - Prototype :

        int kill(pid_t pid, int sig);


  - Description :
    - pid : Identifiant du processus (PID) auquel le signal doit être envoyé. Il peut également avoir des valeurs spéciales :
      - 0 : Envoie le signal à tous les processus du même groupe de processus que le processus appelant.
      - -1 : Envoie le signal à tous les processus, sauf ceux qui n'y ont pas accès.
      - Une valeur négative (par exemple, -pid) : Envoie le signal à tous les processus du groupe dont le PID est -pid.
    - sig : Numéro du signal à envoyer (par exemple, SIGTERM, SIGKILL, SIGINT, etc.).
   
  -  Utilisation :
    - Utilisez kill() pour envoyer des signaux à des processus, que ce soit pour les terminer, les suspendre, ou déclencher d'autres actions définies par des gestionnaires de signaux.


:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // Création d'un nouveau processus
    pid = fork();
    if (pid < 0) {
        perror("Erreur lors de fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Processus enfant
        while (1) {
            printf("Processus enfant en cours d'exécution (PID: %d)\n", getpid());
            sleep(2); // Pause de 2 secondes
        }
    } else {
        // Processus parent
        sleep(5); // Attendre 5 secondes avant d'envoyer le signal
        printf("Processus parent (PID: %d) envoie SIGTERM au processus enfant (PID: %d)\n", getpid(), pid);
        
        // Envoi du signal SIGTERM au processus enfant
        if (kill(pid, SIGTERM) == -1) {
            perror("Erreur lors de l'envoi du signal");
            exit(EXIT_FAILURE);
        }

        // Attendre la fin du processus enfant
        wait(NULL);
        printf("Processus enfant terminé.\n");
    }

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
25) exit

> [!NOTE]
>
> pour terminer un programme.
> Elle permet de quitter un programme de manière propre en libérant les ressources allouées et en fournissant un code de retour au système d'exploitation.
 
  - Prototype :

        void exit(int status);

  - Description :
    - status : Un entier représentant le code de sortie du programme. Conventionnellement, un code de retour de 0 indique un succès, tandis qu'un code non nul (par exemple, 1, -1, etc.) indique une erreur ou une condition d'échec.
   
  - Comportement :
    - Lorsque exit() est appelé, le programme termine son exécution et effectue les étapes suivantes :
      - Appelle les fonctions d'attribut d'exit (si définies avec atexit()).
      - Ferme tous les fichiers ouverts.
      - Libère toute mémoire allouée par le programme.
      - Remet le contrôle au système d'exploitation avec le code de retour spécifié.
     
  - Utilisation :
    - Utilisez exit() pour quitter un programme à tout moment, en particulier dans les situations d'erreur ou de conditions spécifiques où le programme ne peut pas continuer.

:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <stdlib.h>

int main() {
    int number;

    printf("Entrez un nombre (0 pour quitter) : ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Erreur de saisie.\n");
        exit(1); // Quitte avec un code d'erreur
    }

    if (number == 0) {
        printf("Vous avez choisi de quitter le programme.\n");
        exit(0); // Quitte avec succès
    }

    printf("Vous avez entré : %d\n", number);
    exit(0); // Quitte avec succès
}

```
_________________________________________________________________________________________________________________________________________________
26) getcwd

> [!NOTE]
>
> pour obtenir le répertoire de travail actuel d'un processus.
> Cela signifie qu'elle renvoie le chemin du répertoire dans lequel le programme s'exécute.
  
  - Prototype :

        char *getcwd(char *buf, size_t size);

  - Description :
    - buf : Pointeur vers un tableau de caractères (ou un buffer) où la chaîne du répertoire de travail actuel sera stockée. Si buf est NULL, la fonction alloue la mémoire nécessaire pour stocker le chemin.
    - size : Taille du buffer buf. Cela indique combien de caractères peuvent être écrits dans buf.
   
  - Utilisation :
    - Utilisez getcwd() pour obtenir le chemin du répertoire actuel, ce qui peut être utile pour les opérations sur les fichiers, la gestion des chemins, ou pour afficher le contexte actuel à l'utilisateur.


:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char *cwd;
    // Allouer de la mémoire pour le buffer
    cwd = getcwd(NULL, 0);
    if (cwd == NULL) {
        perror("Erreur lors de getcwd");
        exit(EXIT_FAILURE);
    }

    printf("Le répertoire de travail actuel est : %s\n", cwd);

    // Libération de la mémoire allouée par getcwd
    free(cwd);
    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
27) chdir

> [!NOTE]
>
> pour changer le répertoire de travail courant du processus appelant.
> Cela signifie que lorsque vous appelez chdir(), le processus se déplace vers le répertoire spécifié, modifiant ainsi son répertoire de travail actuel.
  
  - Prototype :

        int chdir(const char *path);

  - Description :
    - path : Une chaîne de caractères représentant le chemin du répertoire vers lequel vous souhaitez changer. Cela peut être un chemin absolu ou relatif.
   
  - Utilisation :
      - Utilisez chdir() lorsque vous souhaitez modifier le répertoire de travail d'un programme, par exemple, pour naviguer dans des répertoires avant d'ouvrir ou de créer des fichiers.

:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    const char *path = "/tmp"; // Répertoire cible

    // Changer le répertoire de travail
    if (chdir(path) == -1) {
        perror("Erreur lors de chdir");
        exit(EXIT_FAILURE);
    }

    // Vérification du répertoire de travail actuel
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Le répertoire de travail courant est maintenant : %s\n", cwd);
    } else {
        perror("Erreur lors de getcwd");
        exit(EXIT_FAILURE);
    }

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
28) stat 

> [!NOTE]
>
> pour obtenir des informations sur un fichier ou un répertoire spécifié.
> Elle remplit une structure stat avec des informations détaillées, telles que la taille, les permissions, le propriétaire, les dates de création et de modification, etc.

  - Prototype :
```C
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int stat(const char *pathname, struct stat *statbuf);
```


  - Description :
    -  pathname : Une chaîne de caractères représentant le chemin du fichier ou du répertoire dont vous souhaitez obtenir les informations.
    -  statbuf : Un pointeur vers une structure stat qui sera remplie avec les informations du fichier.

> [!INFO]
> Structure stat :
> La structure stat contient de nombreux champs, dont voici quelques-uns des plus courants :
> 
> st_dev : ID du périphérique.
> st_ino : Numéro d'inode.
> st_mode : Mode de fichier (permissions).
> st_nlink : Nombre de liens.
> st_uid : ID de l'utilisateur propriétaire.
> st_gid : ID du groupe propriétaire.
> st_size : Taille du fichier en octets.
> st_atime : Heure de dernier accès.
> st_mtime : Heure de dernière modification.
> st_ctime : Heure de dernier changement de statut.

  - Utilisation :
    - Utilisez stat() pour obtenir des métadonnées sur un fichier ou un répertoire, ce qui peut être utile pour des vérifications d'existence, des contrôles de permissions, et plus encore.
    - 
:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *filepath = "exemple.txt"; // Nom du fichier
    struct stat fileStat;

    // Obtenir les informations sur le fichier
    if (stat(filepath, &fileStat) < 0) {
        perror("Erreur lors de stat");
        exit(EXIT_FAILURE);
    }

    // Afficher les informations du fichier
    printf("Informations sur le fichier : %s\n", filepath);
    printf("Taille : %lld octets\n", (long long)fileStat.st_size);
    printf("Permissions : %o\n", fileStat.st_mode & 0777); // Permissions en octets
    printf("UID : %u\n", fileStat.st_uid);
    printf("GID : %u\n", fileStat.st_gid);
    printf("Dernière modification : %ld\n", fileStat.st_mtime);

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
29) lstat

> [!NOTE]
>
> similaire à stat(), mais elle est utilisée pour obtenir des informations sur un fichier ou un répertoire, même s'il s'agit d'un lien symbolique.
> En revanche, stat() suit le lien symbolique et renvoie des informations sur le fichier ou le répertoire pointé par le lien. Avec lstat(), vous pouvez obtenir des informations sur le lien lui-même.
  
  - Prototype :

```C
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int lstat(const char *pathname, struct stat *statbuf);

```

  - Description :
    - pathname : Une chaîne de caractères représentant le chemin du fichier ou du lien symbolique dont vous souhaitez obtenir les informations.
    - statbuf : Un pointeur vers une structure stat qui sera remplie avec les informations du fichier ou du lien. 

  - Structure stat :

La structure stat remplie par lstat() contient les mêmes champs que celle remplie par stat(), ce qui inclut des informations sur la taille, les permissions, le propriétaire, les dates de création et de modification, etc.

  - Utilisation :
    - Utilisez lstat() lorsque vous devez obtenir des informations sur un lien symbolique ou pour distinguer entre un lien symbolique et le fichier ou répertoire auquel il pointe.

:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char *linkname = "lien_symbole"; // Nom du lien symbolique
    struct stat linkStat;

    // Obtenir les informations sur le lien symbolique
    if (lstat(linkname, &linkStat) < 0) {
        perror("Erreur lors de lstat");
        exit(EXIT_FAILURE);
    }

    // Afficher les informations du lien symbolique
    printf("Informations sur le lien symbolique : %s\n", linkname);
    printf("Taille : %lld octets\n", (long long)linkStat.st_size);
    printf("Permissions : %o\n", linkStat.st_mode & 0777); // Permissions en octets
    printf("UID : %u\n", linkStat.st_uid);
    printf("GID : %u\n", linkStat.st_gid);
    printf("Dernière modification : %ld\n", linkStat.st_mtime);
    
    // Vérification si c'est un lien symbolique
    if (S_ISLNK(linkStat.st_mode)) {
        printf("%s est un lien symbolique.\n", linkname);
    } else {
        printf("%s n'est pas un lien symbolique.\n", linkname);
    }

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
30) fstat

> [!NOTE]
>
> utilisée pour obtenir des informations sur un fichier basé sur son descripteur de fichier, plutôt que sur son nom de fichier.
> Cela permet d'obtenir des métadonnées sur un fichier déjà ouvert, ce qui peut être plus efficace que d'utiliser stat() ou lstat().
 
  - Prototype :

```C
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int fstat(int fd, struct stat *statbuf);

```

  - Description :
    - fd : Le descripteur de fichier (un entier) pour le fichier dont vous souhaitez obtenir les informations. Ce descripteur est généralement obtenu via des fonctions comme open().
    - statbuf : Un pointeur vers une structure stat qui sera remplie avec les informations du fichier.

  - Structure stat :

La structure stat remplie par fstat() contient les mêmes champs que ceux remplis par stat() ou lstat(), ce qui inclut des informations sur la taille, les permissions, le propriétaire, les dates de création et de modification, etc.

  - Utilisation :

Utilisez fstat() lorsque vous avez un descripteur de fichier ouvert et que vous souhaitez obtenir des informations sur ce fichier, par exemple, après avoir ouvert un fichier avec open().


:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filepath = "exemple.txt"; // Nom du fichier
    struct stat fileStat;

    // Ouvrir le fichier
    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de open");
        exit(EXIT_FAILURE);
    }

    // Obtenir les informations sur le fichier à partir du descripteur
    if (fstat(fd, &fileStat) < 0) {
        perror("Erreur lors de fstat");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Afficher les informations du fichier
    printf("Informations sur le fichier : %s\n", filepath);
    printf("Taille : %lld octets\n", (long long)fileStat.st_size);
    printf("Permissions : %o\n", fileStat.st_mode & 0777); // Permissions en octets
    printf("UID : %u\n", fileStat.st_uid);
    printf("GID : %u\n", fileStat.st_gid);
    printf("Dernière modification : %ld\n", fileStat.st_mtime);

    // Fermer le descripteur de fichier
    close(fd);
    return 0;
}

```

_________________________________________________________________________________________________________________________________________________
31) unlink

> [!NOTE]
>
> utilisée pour supprimer un fichier ou un lien symbolique.
> Elle enlève l'entrée de fichier du système de fichiers, réduisant ainsi le nombre de liens pointant vers ce fichier.
> Si le nombre de liens devient zéro et qu'aucun processus n'a le fichier ouvert, le système libère l'espace utilisé par le fichier.
  
  - Prototype :
```C
#include <unistd.h>

int unlink(const char *pathname);

```

  - Description :
    - pathname : Une chaîne de caractères représentant le chemin du fichier ou du lien symbolique à supprimer.
   
  - Utilisation :
    - Utilisez unlink() pour supprimer des fichiers ou des liens symboliques lorsque vous n'en avez plus besoin. Il est souvent utilisé pour gérer des fichiers temporaires ou pour nettoyer les ressources.


:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const char *filepath = "fichier_a_supprimer.txt"; // Nom du fichier à supprimer

    // Supprimer le fichier
    if (unlink(filepath) == -1) {
        perror("Erreur lors de unlink");
        exit(EXIT_FAILURE);
    }

    printf("Le fichier %s a été supprimé avec succès.\n", filepath);
    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
32) execve

> [!NOTE]
>
> pour exécuter un programme à partir d'un programme courant, remplaçant ainsi le processus appelant par le nouveau programme.
> Cette fonction est l'une des fonctions de la famille exec, qui permet d'exécuter des programmes en remplaçant l'image du processus actuel avec celle d'un nouveau processus.
  
  - Prototype :
```C
#include <unistd.h>

int execve(const char *pathname, char *const argv[], char *const envp[]);

```

  - Description :
    - pathname : Une chaîne de caractères représentant le chemin absolu du programme à exécuter.
    - argv : Un tableau de chaînes de caractères représentant les arguments du programme. Le premier élément (argv[0]) est généralement le nom du programme, suivi des        - arguments. Le tableau doit se terminer par un pointeur nul (NULL).
    - envp : Un tableau de chaînes de caractères représentant l'environnement pour le nouveau programme. Cela inclut des variables d'environnement. Le tableau doit également se terminer par un pointeur nul (NULL). 

  - Utilisation :
    - Utilisez execve() lorsque vous souhaitez exécuter un programme différent à partir de votre programme actuel, par exemple, dans des applications de type shell ou lorsque vous implémentez un système de gestion de processus.

:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const char *program = "/bin/ls"; // Chemin du programme à exécuter
    char *const argv[] = { "ls", "-l", NULL }; // Arguments pour le programme
    char *const envp[] = { NULL }; // Environnement (vide pour cet exemple)

    // Exécuter le programme
    if (execve(program, argv, envp) == -1) {
        perror("Erreur lors de execve");
        exit(EXIT_FAILURE);
    }

    // Ce code ne sera jamais atteint si execve réussit
    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
33) dup

> [!NOTE]
>
> utilisée pour créer une copie d'un descripteur de fichier.
> Elle retourne un nouvel identifiant de descripteur de fichier qui est un duplicata du descripteur d'entrée, permettant de partager le même fichier entre plusieurs descripteurs.
> C'est utile pour rediriger l'entrée ou la sortie d'un processus.
  
  - Prototype :

```C
#include <unistd.h>

int dup(int oldfd);

```

  - Description :
    - oldfd : Le descripteur de fichier existant que vous souhaitez dupliquer. 

  - Utilisation :
    - Utilisez dup() pour rediriger l'entrée/sortie dans des programmes, par exemple, en redirigeant la sortie standard vers un fichier.
   

:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Ouvrir un fichier en mode écriture
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Erreur lors de open");
        exit(EXIT_FAILURE);
    }

    // Dupliquer le descripteur de fichier
    int newfd = dup(fd);
    if (newfd == -1) {
        perror("Erreur lors de dup");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Rediriger la sortie standard (stdout) vers le fichier
    if (dup2(newfd, STDOUT_FILENO) == -1) {
        perror("Erreur lors de dup2");
        close(fd);
        close(newfd);
        exit(EXIT_FAILURE);
    }

    // Écrire dans la sortie standard qui est maintenant redirigée vers le fichier
    printf("Ceci est écrit dans le fichier output.txt.\n");

    // Fermer les descripteurs de fichier
    close(fd);
    close(newfd);

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
34) dup2

> [!NOTE]
>
> une variante de la fonction dup().
> Elle permet de dupliquer un descripteur de fichier en le liant à un descripteur de fichier spécifié.
> Cela signifie que vous pouvez rediriger un descripteur de fichier vers un autre descripteur spécifique, souvent utilisé pour rediriger l'entrée ou la sortie d'un processus.
  
  - Prototype :
```C
#include <unistd.h>

int dup2(int oldfd, int newfd);

```

  - Description :
    - oldfd : Le descripteur de fichier que vous souhaitez dupliquer.
    - newfd : Le descripteur de fichier où oldfd sera dupliqué. Si newfd est déjà ouvert, il sera fermé avant d'être réutilisé.

  - Utilisation :
    - Utilisez dup2() pour rediriger des entrées ou des sorties, comme rediriger la sortie standard (stdout) vers un fichier ou un autre flux.
   

:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Ouvrir un fichier en mode écriture
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Erreur lors de open");
        exit(EXIT_FAILURE);
    }

    // Rediriger la sortie standard vers le fichier
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("Erreur lors de dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Écrire dans la sortie standard qui est maintenant redirigée vers le fichier
    printf("Ceci est écrit dans le fichier output.txt.\n");

    // Fermer le descripteur de fichier
    close(fd);

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
35) pipe

> [!NOTE]
>
> pour créer un canal de communication unidirectionnel entre deux processus.
> Elle permet d'établir une connexion entre un processus « écrivain » et un processus « lecteur », permettant ainsi au premier d'envoyer des données au second via un tampon.
  
  - Prototype :

```C
#include <unistd.h>

int pipe(int pipefd[2]);

```

  - Description :
    - pipefd : Un tableau de deux entiers où pipefd[0] sera utilisé pour la lecture (le descripteur de fichier de lecture) et pipefd[1] sera utilisé pour l'écriture (le descripteur de fichier d'écriture).

  - Utilisation :
    - Utilisez pipe() pour permettre la communication entre deux processus, souvent en conjonction avec fork() pour créer un processus enfant.


:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2]; // Tableau pour les descripteurs de fichier du pipe
    pid_t pid;
    char buffer[100];

    // Créer le pipe
    if (pipe(pipefd) == -1) {
        perror("Erreur lors de pipe");
        exit(EXIT_FAILURE);
    }

    // Créer un processus enfant
    pid = fork();
    if (pid == -1) {
        perror("Erreur lors de fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Processus enfant
        close(pipefd[1]); // Fermer le descripteur d'écriture du pipe

        // Lire des données depuis le pipe
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Processus enfant a reçu : %s\n", buffer);

        close(pipefd[0]); // Fermer le descripteur de lecture du pipe
        exit(EXIT_SUCCESS);
    } else { // Processus parent
        close(pipefd[0]); // Fermer le descripteur de lecture du pipe

        // Écrire des données dans le pipe
        const char *message = "Bonjour depuis le processus parent!";
        write(pipefd[1], message, strlen(message) + 1); // +1 pour inclure le caractère nul

        close(pipefd[1]); // Fermer le descripteur d'écriture du pipe
        wait(NULL); // Attendre que le processus enfant se termine
    }

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
36) opendir 

> [!NOTE]
>
> pour ouvrir un répertoire afin de pouvoir lire son contenu.
> Elle retourne un pointeur vers une structure DIR, qui peut ensuite être utilisée avec d'autres fonctions pour lire les entrées du répertoire.
  
  - Prototype :

```C
#include <sys/types.h>
#include <dirent.h>

DIR *opendir(const char *name);

```

  - Description :
    - name : Une chaîne de caractères représentant le chemin du répertoire à ouvrir.
   
  - Utilisation :
    - Utilisez opendir() pour ouvrir un répertoire afin de pouvoir itérer à travers ses entrées avec readdir() ou pour effectuer d'autres opérations sur le répertoire.

:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    const char *directory = "."; // Chemin du répertoire à ouvrir (ici le répertoire courant)
    DIR *dir = opendir(directory); // Ouvrir le répertoire

    if (dir == NULL) {
        perror("Erreur lors de opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    // Lire les entrées du répertoire
    while ((entry = readdir(dir)) != NULL) {
        // Ignorer les entrées "." et ".."
        if (entry->d_name[0] != '.') {
            printf("Entrée : %s\n", entry->d_name);
        }
    }

    closedir(dir); // Fermer le répertoire

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
37) readdir 

> [!NOTE]
>
> pour lire les entrées d'un répertoire qui a été ouvert avec opendir().
> Elle permet de récupérer des informations sur les fichiers et sous-répertoires contenus dans un répertoire donné.
  
  - Prototype :
```C
#include <sys/types.h>
#include <dirent.h>

struct dirent *readdir(DIR *dirp);

```

  - Description :
    - dirp : Un pointeur vers une structure DIR, qui a été retourné par opendir() pour désigner le répertoire à lire.

  - Structure dirent :

La structure dirent contient plusieurs membres, mais les plus pertinents sont :
- d_name : Un tableau de caractères contenant le nom de l'entrée (fichier ou répertoire).
- d_type : Un entier qui indique le type de l'entrée (fichier ordinaire, répertoire, lien symbolique, etc.).

  - Utilisation :
    - Utilisez readdir() pour itérer à travers les fichiers et répertoires d'un répertoire ouvert.


:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    const char *directory = "."; // Chemin du répertoire à ouvrir (répertoire courant)
    DIR *dir = opendir(directory); // Ouvrir le répertoire

    if (dir == NULL) {
        perror("Erreur lors de opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    // Lire les entrées du répertoire
    while ((entry = readdir(dir)) != NULL) {
        // Ignorer les entrées "." et ".."
        if (entry->d_name[0] != '.') {
            printf("Entrée : %s\n", entry->d_name);
        }
    }

    closedir(dir); // Fermer le répertoire

    return 0;
}

```

_________________________________________________________________________________________________________________________________________________
38) closedir

> [!NOTE]
>
> pour fermer un répertoire qui a été ouvert avec la fonction opendir().
> Cela libère les ressources associées au répertoire ouvert.
  
  - Prototype :

```C
#include <sys/types.h>
#include <dirent.h>

int closedir(DIR *dirp);

```

  - Description :
    -  dirp : Un pointeur vers une structure DIR, qui représente le répertoire à fermer.
   
  - Utilisation :
    - Utilisez closedir() pour fermer un répertoire après avoir terminé la lecture de ses entrées, afin de libérer les ressources système.


:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    const char *directory = "."; // Chemin du répertoire à ouvrir (répertoire courant)
    DIR *dir = opendir(directory); // Ouvrir le répertoire

    if (dir == NULL) {
        perror("Erreur lors de opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    // Lire les entrées du répertoire
    while ((entry = readdir(dir)) != NULL) {
        // Ignorer les entrées "." et ".."
        if (entry->d_name[0] != '.') {
            printf("Entrée : %s\n", entry->d_name);
        }
    }

    // Fermer le répertoire
    if (closedir(dir) == -1) {
        perror("Erreur lors de closedir");
        exit(EXIT_FAILURE);
    }

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
39) strerror 

> [!NOTE]
>
>  pour obtenir une chaîne de caractères décrivant l'erreur correspondante à un code d'erreur spécifié.
> Elle est souvent utilisée pour fournir des messages d'erreur compréhensibles lors de la gestion des erreurs dans les programmes.
  
  - Prototype :

```C
#include <string.h>

char *strerror(int errnum);

```

  - Description :
    - errnum : Un entier représentant le code d'erreur pour lequel vous souhaitez obtenir une description.
   
  - Utilisation :
    - Utilisez strerror() après qu'une fonction système échoue et retourne un code d'erreur pour afficher des messages d'erreur plus compréhensibles. Cela aide les utilisateurs à comprendre ce qui a mal tourné.


:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
    FILE *file = fopen("inexistant.txt", "r"); // Essayer d'ouvrir un fichier inexistant

    if (file == NULL) {
        // Afficher le message d'erreur en utilisant strerror
        fprintf(stderr, "Erreur : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Si le fichier était ouvert avec succès, il pourrait être traité ici

    fclose(file); // Fermer le fichier si ouvert
    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
40) perror

> [!NOTE]
>
> pour afficher un message d'erreur décrivant la dernière erreur survenue.
> Elle affiche une chaîne de caractères suivie d'une description de l'erreur correspondante à la valeur actuelle de errno.
> Cette fonction est utile pour fournir un feedback d'erreur informatif lors de l'exécution d'opérations système.
  
  - Prototype :
```C
#include <stdio.h>

void perror(const char *s);

```

  - Description :
    - perror() ne retourne rien (c'est une fonction de type void).
   
  - Utilisation :
    - Utilisez perror() après qu'une fonction système ait échoué et qu'elle ait modifié errno pour afficher un message d'erreur explicite. Cela aide à comprendre ce qui a mal tourné dans le programme.

:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("inexistant.txt", "r"); // Essayer d'ouvrir un fichier inexistant

    if (file == NULL) {
        // Afficher le message d'erreur en utilisant perror
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Si le fichier était ouvert avec succès, il pourrait être traité ici

    fclose(file); // Fermer le fichier si ouvert
    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
41) isatty

> [!NOTE]
>
> pour déterminer si un descripteur de fichier donné fait référence à un terminal (TTY).
> Cela permet de vérifier si une entrée ou une sortie est liée à un terminal interactif ou à un fichier.
  
  - Prototype :

```C
#include <unistd.h>

int isatty(int fd);

```

  - Description :
    - fd : Un entier représentant le descripteur de fichier à vérifier. Par exemple, 0 pour l'entrée standard (stdin), 1 pour la sortie standard (stdout), et 2 pour la sortie d'erreur standard (stderr).
   
  - Utilisation :
    - Utilisez isatty() pour déterminer si les entrées ou sorties d'un programme sont interactives (par exemple, pour ajuster le comportement en fonction du fait que le programme est exécuté dans un terminal ou redirigé vers un fichier).


:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <unistd.h>

int main() {
    // Vérifier si stdout est un terminal
    if (isatty(1)) {
        printf("La sortie standard est un terminal.\n");
    } else {
        printf("La sortie standard n'est pas un terminal.\n");
    }

    return 0;
}

```

_________________________________________________________________________________________________________________________________________________
42) ttyname 

> [!NOTE]
>
> pour obtenir le nom du terminal associé à un descripteur de fichier donné.
> Elle renvoie une chaîne de caractères contenant le nom du terminal (par exemple, /dev/tty1, /dev/pts/0) ou NULL si le descripteur de fichier ne correspond pas à un terminal.
  
  - Prototype :

```C
#include <unistd.h>

char *ttyname(int fd);

```

  - Description :
    - fd : Un entier représentant le descripteur de fichier dont vous souhaitez obtenir le nom du terminal. Typiquement, 0 pour l'entrée standard (stdin), 1 pour la sortie standard (stdout) ou 2 pour la sortie d'erreur standard (stderr).
   
  - Utilisation :
Utilisez ttyname() lorsque vous avez besoin de connaître le nom du terminal associé à un descripteur de fichier, par exemple, pour le débogage ou pour des fonctionnalités spécifiques liées au terminal.


:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <unistd.h>

int main() {
    // Obtenir le nom du terminal associé à stdout (descripteur 1)
    char *tty = ttyname(1); // 1 correspond à stdout

    if (tty != NULL) {
        printf("Le terminal associé à stdout est : %s\n", tty);
    } else {
        perror("Erreur lors de l'obtention du nom du terminal");
    }

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
43) ttyslot 

> [!NOTE]
>
>  pour obtenir le numéro du terminal virtuel (TTY) associé à l'exécution du processus.
> Cela peut être utile dans des environnements où plusieurs terminaux virtuels sont utilisés, comme dans un système de gestion de sessions multiples.
  
  - Prototype :

```C
#include <unistd.h>

int ttyslot(void);

```
  - Utilisation :
    - Utilisez ttyslot() pour identifier le terminal virtuel dans lequel votre programme s'exécute. Cela peut être utilisé pour des diagnostics ou des fonctionnalités spécifiques à la session.


:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <unistd.h>

int main() {
    // Obtenir le numéro du terminal virtuel associé
    int slot = ttyslot();

    if (slot != -1) {
        printf("Le numéro du terminal virtuel est : %d\n", slot);
    } else {
        perror("Erreur lors de l'obtention du numéro du terminal virtuel");
    }

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
44) ioctl

> [!NOTE]
>
> pour contrôler des périphériques en exécutant des opérations spécifiques sur des descripteurs de fichiers.
> Elle permet d'envoyer des commandes de contrôle à un périphérique, qui peuvent varier selon le type de périphérique.
> C'est une fonction très polyvalente utilisée dans la programmation système.
  
  - Prototype :

```C
#include <sys/ioctl.h>

int ioctl(int fd, unsigned long request, ...);

```

  - Description :
    - fd : Un entier représentant le descripteur de fichier du périphérique sur lequel vous souhaitez exécuter l'opération.
    - request : Un code de commande qui spécifie l'opération à effectuer. Ces codes sont généralement définis dans des fichiers d'en-tête spécifiques au périphérique (comme <linux/fs.h> ou <linux/soundcard.h>).
    - ... : Argument optionnel, dont le type et le nombre dépendent de la commande spécifiée par request. Cela peut être un pointeur vers une structure ou un entier, selon l'opération.
   
  - Utilisation :
    - Utilisez ioctl() pour effectuer des opérations qui ne peuvent pas être réalisées avec les fonctions standard de manipulation de fichiers. Cela inclut des opérations comme la configuration de paramètres de périphériques, la récupération d'informations, ou le contrôle du comportement des périphériques.


:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main() {
    struct winsize w;

    // Utiliser ioctl pour obtenir les dimensions du terminal
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("Erreur lors de ioctl");
        exit(EXIT_FAILURE);
    }

    printf("Largeur : %d, Hauteur : %d\n", w.ws_col, w.ws_row);

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
45) getenv

> [!NOTE]
>
> pour récupérer la valeur d'une variable d'environnement spécifique.
> Les variables d'environnement sont des paires clé-valeur qui peuvent être utilisées pour configurer l'environnement d'exécution d'un programme.
  
  - Prototype :

```C
#include <stdlib.h>

char *getenv(const char *name);

```

  - Description :
    - name : Une chaîne de caractères représentant le nom de la variable d'environnement dont vous souhaitez obtenir la valeur.

  - Utilisation :
    - Utilisez getenv() lorsque vous avez besoin d'accéder à des paramètres d'environnement dans votre programme, tels que des chemins d'accès, des paramètres de configuration ou d'autres données d'environnement.


:octocat:**EXEMPLES D'UTILISATION**:octocat:

```C
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Récupérer la variable d'environnement HOME
    char *home = getenv("HOME");

    if (home != NULL) {
        printf("Le répertoire personnel de l'utilisateur est : %s\n", home);
    } else {
        printf("La variable d'environnement HOME n'est pas définie.\n");
    }

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
46) tcsetattr 

> [!NOTE]
>
> utilisée pour configurer les attributs d'un terminal.
> Elle permet de modifier les paramètres d'entrée et de sortie d'un terminal, tels que les modes de transmission, les paramètres de contrôle de flux, et d'autres comportements liés au terminal.
  
  - Prototype :

```C
#include <termios.h>

int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);

```

  - Description :
    - fd : Un entier représentant le descripteur de fichier du terminal que vous souhaitez configurer. Par exemple, STDIN_FILENO pour l'entrée standard.
    - optional_actions : Un entier qui spécifie comment les changements doivent être appliqués. Il peut prendre les valeurs suivantes :
      - TCSANOW : Les changements sont appliqués immédiatement.
      - TCSADRAIN : Les changements sont appliqués après que toutes les données actuellement en cours de transmission aient été traitées.
      - TCSAFLUSH : Les changements sont appliqués immédiatement et les données en cours de transmission sont supprimées.
    - termios_p : Un pointeur vers une structure termios qui contient les nouveaux paramètres à appliquer au terminal.
   
  - Utilisation :
    - Utilisez tcsetattr() pour configurer le comportement d'un terminal, notamment pour changer le mode d'écho, le mode de saisie, ou d'autres paramètres d'entrée/sortie.

:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main() {
    struct termios oldt, newt;

    // Obtenir les attributs actuels du terminal
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Désactiver l'écho des caractères
    newt.c_lflag &= ~ECHO;

    // Appliquer les nouveaux attributs
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) != 0) {
        perror("Erreur lors de tcsetattr");
        exit(EXIT_FAILURE);
    }

    printf("Saisissez un mot de passe : ");
    char password[100];
    fgets(password, sizeof(password), stdin);
    printf("\nVous avez saisi : %s\n", password);

    // Rétablir les anciens attributs du terminal
    if (tcsetattr(STDIN_FILENO, TCSANOW, &oldt) != 0) {
        perror("Erreur lors de la restauration des attributs");
        exit(EXIT_FAILURE);
    }

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
47) tcgetattr

> [!NOTE]
>
> utilisée pour récupérer les attributs de configuration d'un terminal.
> Elle permet de lire les paramètres d'entrée et de sortie d'un terminal, ce qui est essentiel pour gérer le comportement du terminal dans un programme.
  
  - Prototype :
```C
#include <termios.h>

int tcgetattr(int fd, struct termios *termios_p);

```

  - Description :
    -  fd : Un entier représentant le descripteur de fichier du terminal dont vous souhaitez obtenir les attributs. Par exemple, STDIN_FILENO pour l'entrée standard.
    -  termios_p : Un pointeur vers une structure termios où les paramètres du terminal seront stockés.
   
  - Utilisation :
    - Utilisez tcgetattr() lorsque vous devez obtenir les paramètres actuels d'un terminal, tels que les modes d'écho, les paramètres de vitesse de transmission, ou d'autres réglages d'entrée/sortie.



:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main() {
    struct termios term;

    // Récupérer les attributs du terminal
    if (tcgetattr(STDIN_FILENO, &term) != 0) {
        perror("Erreur lors de tcgetattr");
        exit(EXIT_FAILURE);
    }

    // Afficher des informations sur les attributs récupérés
    printf("Vitesse d'entrée : %d\n", cfgetispeed(&term));
    printf("Vitesse de sortie : %d\n", cfgetospeed(&term));

    if (term.c_lflag & ECHO) {
        printf("L'écho des caractères est activé.\n");
    } else {
        printf("L'écho des caractères est désactivé.\n");
    }

    return 0;
}

```
_________________________________________________________________________________________________________________________________________________
48) tgetent

> [!NOTE]
>
> utilisée pour initialiser les informations sur un terminal à partir de la base de données des terminaux, généralement située dans le fichier /etc/termcap.
> Elle permet de récupérer les capacités d'un terminal en fonction de son type, ce qui est utile pour développer des applications qui interagissent avec différents types de terminaux.
  
  - Prototype :
```C
#include <term.h>

int tgetent(char *bp, const char *name);
```

  - Description :
    - bp : Un pointeur vers une chaîne de caractères utilisée comme tampon pour stocker les informations récupérées. Si vous passez NULL, la mémoire sera allouée automatiquement pour le tampon.
    - name : Une chaîne de caractères représentant le nom ou le type du terminal que vous souhaitez initialiser (par exemple, xterm, linux, etc.).

  - Utilisation :
    - Utilisez tgetent() pour récupérer les capacités d'un terminal avant d'appeler d'autres fonctions qui dépendent de ces capacités, comme tgetflag(), tgetnum(), ou tgetstr(). Celles-ci permettent d'interroger des informations spécifiques sur le terminal.
   

:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <stdlib.h>
#include <term.h>

int main() {
    char *term_type = getenv("TERM"); // Récupérer le type de terminal depuis la variable d'environnement
    char *buffer = NULL;

    // Initialiser les informations sur le terminal
    int result = tgetent(buffer, term_type);
    if (result < 0) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de terminaux.\n");
        return EXIT_FAILURE;
    } else if (result == 0) {
        fprintf(stderr, "Le type de terminal '%s' est inconnu.\n", term_type);
        return EXIT_FAILURE;
    }

    // Afficher une capacité de terminal (exemple : le code pour le retour à la ligne)
    int h = tgetnum("lines"); // Récupérer le nombre de lignes du terminal
    if (h > 0) {
        printf("Le terminal a %d lignes.\n", h);
    } else {
        printf("Capacité de nombre de lignes non disponible.\n");
    }

    return EXIT_SUCCESS;
}

```
_________________________________________________________________________________________________________________________________________________
49) tgetflag

> [!NOTE]
>
> utilisée pour récupérer une capacité booléenne d'un terminal, c'est-à-dire une information qui peut être vraie ou fausse.
> Elle est généralement appelée après que tgetent() a été utilisé pour initialiser les informations sur le terminal.
  
  - Prototype :
```C
#include <term.h>

int tgetflag(const char *id);

```

  - Description :
    - id : Une chaîne de caractères représentant le nom de la capacité que vous souhaitez vérifier. Par exemple, "am" pour le mode d'ajout, ou "bs" pour le support de la touche de retour arrière.

  - Utilisation :
    - Utilisez tgetflag() pour vérifier des capacités spécifiques du terminal qui sont représentées par des valeurs booléennes, ce qui peut influencer le comportement de votre programme en fonction des capacités du terminal.


:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <stdlib.h>
#include <term.h>

int main() {
    char *term_type = getenv("TERM"); // Récupérer le type de terminal depuis la variable d'environnement
    char *buffer = NULL;

    // Initialiser les informations sur le terminal
    int result = tgetent(buffer, term_type);
    if (result < 0) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de terminaux.\n");
        return EXIT_FAILURE;
    } else if (result == 0) {
        fprintf(stderr, "Le type de terminal '%s' est inconnu.\n", term_type);
        return EXIT_FAILURE;
    }

    // Vérifier si le terminal prend en charge le mode d'ajout
    if (tgetflag("am")) {
        printf("Le terminal supporte le mode d'ajout.\n");
    } else {
        printf("Le terminal ne supporte pas le mode d'ajout.\n");
    }

    // Vérifier si le terminal supporte la touche de retour arrière
    if (tgetflag("bs")) {
        printf("Le terminal supporte la touche de retour arrière.\n");
    } else {
        printf("Le terminal ne supporte pas la touche de retour arrière.\n");
    }

    return EXIT_SUCCESS;
}

```

_________________________________________________________________________________________________________________________________________________
50) tgetnum 

> [!NOTE]
>
>  utilisée pour récupérer une capacité numérique d'un terminal.
> Elle permet de lire des valeurs qui ne sont pas simplement vraies ou fausses, mais qui ont des valeurs numériques, comme le nombre de lignes ou de colonnes du terminal.
  
  - Prototype :

```C
#include <term.h>

int tgetnum(const char *id);

```

  - Description :
    - id : Une chaîne de caractères représentant le nom de la capacité numérique que vous souhaitez récupérer. Par exemple, "lines" pour le nombre de lignes, ou "cols" pour le nombre de colonnes.
   
  - Utilisation :
    - Utilisez tgetnum() pour obtenir des valeurs numériques qui peuvent influencer la mise en forme ou l'affichage de votre programme en fonction des dimensions du terminal.

:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <stdlib.h>
#include <term.h>

int main() {
    char *term_type = getenv("TERM"); // Récupérer le type de terminal depuis la variable d'environnement
    char *buffer = NULL;

    // Initialiser les informations sur le terminal
    int result = tgetent(buffer, term_type);
    if (result < 0) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de terminaux.\n");
        return EXIT_FAILURE;
    } else if (result == 0) {
        fprintf(stderr, "Le type de terminal '%s' est inconnu.\n", term_type);
        return EXIT_FAILURE;
    }

    // Récupérer le nombre de lignes du terminal
    int lines = tgetnum("lines");
    if (lines > 0) {
        printf("Le terminal a %d lignes.\n", lines);
    } else {
        printf("Capacité de nombre de lignes non disponible.\n");
    }

    // Récupérer le nombre de colonnes du terminal
    int cols = tgetnum("cols");
    if (cols > 0) {
        printf("Le terminal a %d colonnes.\n", cols);
    } else {
        printf("Capacité de nombre de colonnes non disponible.\n");
    }

    return EXIT_SUCCESS;
}

```
_________________________________________________________________________________________________________________________________________________
51) tgetstr

> [!NOTE]
>
> utilisée pour récupérer une capacité sous forme de chaîne de caractères d'un terminal.
> Contrairement à tgetnum() qui renvoie des valeurs numériques, tgetstr() permet d'obtenir des séquences d'échappement spécifiques utilisées pour contrôler le comportement du terminal, comme la couleur ou le mouvement du curseur.
  
  - Prototype :
```C
#include <term.h>

char *tgetstr(const char *id, char **area);
```

  - Description :
    - id : Une chaîne de caractères représentant le nom de la capacité que vous souhaitez récupérer. Par exemple, "cm" pour le mouvement du curseur (cursor movement) ou "cl" pour effacer l'écran (clear screen).
    - area : Un pointeur vers une zone de mémoire (buffer) où la chaîne de caractères sera stockée. Si area est NULL, une mémoire sera allouée automatiquement pour stocker la chaîne.
   
  - Utilisation :
    - Utilisez tgetstr() pour récupérer des séquences d'échappement spécifiques au terminal qui peuvent être utilisées pour le formatage de l'affichage, la manipulation du curseur ou d'autres contrôles de terminal.


:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <stdlib.h>
#include <term.h>

int main() {
    char *term_type = getenv("TERM"); // Récupérer le type de terminal depuis la variable d'environnement
    char *buffer = NULL;

    // Initialiser les informations sur le terminal
    int result = tgetent(buffer, term_type);
    if (result < 0) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de terminaux.\n");
        return EXIT_FAILURE;
    } else if (result == 0) {
        fprintf(stderr, "Le type de terminal '%s' est inconnu.\n", term_type);
        return EXIT_FAILURE;
    }

    // Récupérer la séquence d'échappement pour effacer l'écran
    char *clear_screen = tgetstr("cl", &buffer);
    if (clear_screen) {
        // Afficher la séquence d'échappement pour effacer l'écran
        printf("Séquence d'échappement pour effacer l'écran : %s", clear_screen);
        // Envoyer la séquence au terminal
        tputs(clear_screen, 1, putchar);
    } else {
        printf("Capacité pour effacer l'écran non disponible.\n");
    }

    return EXIT_SUCCESS;
}

```
_________________________________________________________________________________________________________________________________________________
52) tgoto 

> [!NOTE]
>
> utilisée pour générer une séquence d'échappement pour déplacer le curseur à une position spécifique sur l'écran d'un terminal.
> Elle fait partie des fonctions de la bibliothèque terminfo et est souvent utilisée en conjonction avec d'autres fonctions de contrôle de terminal.
  
  - Prototype :
```C
#include <term.h>

char *tgoto(const char *cap, int col, int row);

```

  - Description :
    - cap : Une chaîne de caractères qui représente une capacité d'échappement pour le mouvement du curseur. Cette chaîne est généralement obtenue via tgetstr() pour une capacité de mouvement spécifique, comme "cm" (courser movement).
    - col : La colonne à laquelle déplacer le curseur (numérotée à partir de 0).
    - row : La ligne à laquelle déplacer le curseur (également numérotée à partir de 0).
   
  - Utilisation :
    - Utilisez tgoto() pour générer des séquences d'échappement qui peuvent être envoyées au terminal pour déplacer le curseur à des positions spécifiques. Cela est particulièrement utile dans les applications terminales qui nécessitent un contrôle précis de l'affichage.


:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <stdlib.h>
#include <term.h>

int main() {
    char *term_type = getenv("TERM"); // Récupérer le type de terminal depuis la variable d'environnement
    char *buffer = NULL;

    // Initialiser les informations sur le terminal
    int result = tgetent(buffer, term_type);
    if (result < 0) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de terminaux.\n");
        return EXIT_FAILURE;
    } else if (result == 0) {
        fprintf(stderr, "Le type de terminal '%s' est inconnu.\n", term_type);
        return EXIT_FAILURE;
    }

    // Récupérer la séquence d'échappement pour le mouvement du curseur
    char *move_cursor = tgetstr("cm", &buffer); // "cm" pour le mouvement du curseur
    if (move_cursor) {
        // Déplacer le curseur à la colonne 10, ligne 5
        char *cursor_position = tgoto(move_cursor, 10, 5);
        
        // Afficher la séquence d'échappement pour déplacer le curseur
        printf("%s", cursor_position);
        // Afficher le texte à la nouvelle position du curseur
        printf("Hello, World!");
    } else {
        printf("Capacité pour le mouvement du curseur non disponible.\n");
    }

    return EXIT_SUCCESS;
}

```
_________________________________________________________________________________________________________________________________________________
53) tputs

> [!NOTE]
>
> utilisée pour envoyer des séquences d'échappement à un terminal.
> Elle est particulièrement utile pour les opérations qui nécessitent un contrôle de l'affichage, comme déplacer le curseur, changer de couleur, ou modifier d'autres aspects de l'interface utilisateur dans un terminal.
  
  - Prototype :
```C
#include <term.h>

int tputs(const char *str, int affcnt, int (*outc)(int));

```

  - Description :
    - str : Une chaîne de caractères contenant la séquence d'échappement à envoyer au terminal.
    - affcnt : Un entier représentant le nombre de fois que la séquence d'échappement doit être affichée. Cela peut être utilisé par certaines séquences pour ajuster le délai d'affichage.
    - outc : Un pointeur vers une fonction qui prend un caractère en entrée et l'affiche. Par exemple, vous pouvez utiliser putchar().
   
  - Utilisation :
    - Utilisez tputs() pour envoyer des séquences d'échappement qui modifient l'état du terminal, telles que le mouvement du curseur, l'effacement de l'écran, ou le changement de couleur.


:octocat:**EXEMPLES D'UTILISATION**:octocat:
```C
#include <stdio.h>
#include <stdlib.h>
#include <term.h>

int main() {
    char *term_type = getenv("TERM"); // Récupérer le type de terminal depuis la variable d'environnement
    char *buffer = NULL;

    // Initialiser les informations sur le terminal
    int result = tgetent(buffer, term_type);
    if (result < 0) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier de terminaux.\n");
        return EXIT_FAILURE;
    } else if (result == 0) {
        fprintf(stderr, "Le type de terminal '%s' est inconnu.\n", term_type);
        return EXIT_FAILURE;
    }

    // Récupérer la séquence d'échappement pour effacer l'écran
    char *clear_screen = tgetstr("cl", &buffer);
    if (clear_screen) {
        // Utiliser tputs pour envoyer la séquence d'échappement
        tputs(clear_screen, 1, putchar);
    } else {
        printf("Capacité pour effacer l'écran non disponible.\n");
    }

    // Récupérer la séquence d'échappement pour le mouvement du curseur
    char *move_cursor = tgetstr("cm", &buffer); // "cm" pour le mouvement du curseur
    if (move_cursor) {
        // Déplacer le curseur à la colonne 10, ligne 5
        char *cursor_position = tgoto(move_cursor, 10, 5);
        tputs(cursor_position, 1, putchar);
        
        // Afficher un message à la nouvelle position
        printf("Hello, World!");
    } else {
        printf("Capacité pour le mouvement du curseur non disponible.\n");
    }

    return EXIT_SUCCESS;
}

```
_________________________________________________________________________________________________________________________________________________
















