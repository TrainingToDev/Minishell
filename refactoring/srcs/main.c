#include "minishell.h"


// void init_minishell(t_minishell *shell)
// {
//     shell.env_list = env_list;
// 	shell.last_exit_status = 0;
// 	shell.tokens = NULL;
// 	shell.ast = NULL;
// 	shell.running = 1;
// 	shell.fd_input = STDIN_FILENO;
// 	shell.fd_output = STDOUT_FILENO;
//     shell->heredoc_line_nb = 0;
// }

static void minishell_loop(t_env_var *env_list)
{
    char    *prompt = NULL;
    char    *input = NULL;
    t_token *token_list = NULL;
    t_ast   *ast_root = NULL;
    t_minishell shell;

// init shell
shell.env_list = env_list;
shell.last_exit_status = 0;
shell.tokens = NULL;
shell.ast = NULL;
shell.running = 1;
shell.fd_input = STDIN_FILENO;
shell.fd_output = STDOUT_FILENO;
shell.nb_line_heredoc = 0;

    while (1)
    {
        // 1)
        prompt = format_prompt();
        if (!prompt)
        {
            ft_putstr_fd("minishell: Error creating prompt\n", 2);
            break;
        }

        // 2)
        input = prompt_input(prompt);
        free(prompt);

        //ctrl+D
        if (!input)
            break;

    //    3)
        token_list = lexer(input);
        if (!token_list)
        {
            free(input);
            continue;
        }
		printf("------>>>> TOKEN:\n");
		print_tokens(token_list);


		// 4)

		// expand_token_list(token_list, &shell);

		// printf("------>>>> expander:\n");
		// print_tokens(token_list);

		



    //  5)
        ast_root = parse(token_list, input);

        free_token_list(token_list);
        token_list = NULL;

        if (!ast_root)
        {
            free(input);
            continue;
        }
		printf("------>>>> Parser:\n");
		print_ast(ast_root, 0);
       
     
    //  6)

		printf("\n------------execution---------\n");
        execute_ast(ast_root, &shell);

        free_ast(ast_root);
        ast_root = NULL;

        free(input);
        input = NULL;
    }
}

int main(int argc, char **argv, char **envp)
{
    t_env_var	*env_list; 

	env_list = NULL;
    check_args(argc, argv);
    env_list = convert_envp_to_list(envp);
    if (!env_list)
    {
        ft_putstr_fd("minishell: Failed to initialize environment\n", 2);
        return (1);
    }
    main_signals();
    minishell_loop(env_list);
    free_env_list(env_list);
    rl_clear_history();
    return (0);
}
