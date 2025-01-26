/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:21:52 by miaandri          #+#    #+#             */
/*   Updated: 2025/01/26 00:22:14 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	display_exported_vars(t_minishell *shell)
{
	t_env_var	*current;

	current = shell->env_list;
	while (current)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(current->key, STDOUT_FILENO);
		if (current->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		current = current->next;
	}
}
static t_env_var *new(char *key, char *value, t_env_var *current)
{
    t_env_var *new_node;

    new_node = malloc(sizeof(t_env_var));
    if (!new_node)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_node->key = ft_strdup(key);
    new_node->value = value ? ft_strdup(value) : NULL;
    new_node->next = current;
    return (new_node);
}

static void update_env(t_minishell *shell, char *key, char *value)
{
    t_env_var *current = shell->env_list;
    t_env_var *previous = NULL;
    t_env_var *new_node;

    current = shell->env_list;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = value ? ft_strdup(value) : NULL;
            return;
        }
        if (ft_strcmp(current->key, key) > 0)
            break;
        previous = current;
        current = current->next;
    }
    new_node = new(key, value, current);
    if (previous)
        previous->next = new_node;
    else
        shell->env_list = new_node;
}

int	export(t_minishell *shell, char **args)
{
	int i;
	int status = 0;
	char *key;
	char *value;
	char *equal_sign;

	if (!args[1])
	{
		display_exported_vars(shell);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
		{
			key = ft_substr(args[i], 0, equal_sign - args[i]);
			value = ft_strdup(equal_sign + 1);
		}
		else
		{
			key = ft_strdup(args[i]);
			value = NULL;
		}
		if (!is_valid_identifier(key))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			status = 1;
			free(key);
			free(value);
			i++;
			continue;
		}
		update_env(shell, key, value);
		free(key);
		free(value);
		i++;
	}
	return (status);
}


/*code lalaina 
int all_num(char *in)
{
    int i;

    i = 0;
    while (in[i])
    {
        if (in[i] >= 48 && in[i] <= 57)
            i++;
        else if (in[i] == '=')
            i++;
        else
            return (1);
    }
    return (0);
}

static int is_env(char *arg)
{
    int i;

    i = 0;
    if (!arg)
        return (-1);
    while (arg[i])
    {
        if (arg[i] == '=')
        {
            if (arg[i + 1])
                return (1);
            return (2);
        }
        i++;
    }
    return (0);
}

static int export(t_export *exp)//export without option and argument
{
    while (exp)
    {
        printf("%s", exp->proto);
        printf("%s", exp->var);
        printf("%s\n", exp->value);
        exp = exp->next;
    }
    return (0);
}

static void remplace(t_export **exp, char *token, int i)//rempace the exp->value 
{
    t_export *temp;

    temp = (*exp);
    while(i > 0)
    {
        i--;
        temp = temp->next;
    }
    free(temp->value);
    temp->value = get_value(token);
}
static void env_remplace(t_env **exp, char *token, int i)//rempace the env->value 
{
    t_env *temp;

    temp = (*exp);
    while(i > 0)
    {
        i--;
        temp = temp->next;
    }
    free(temp->value);
    temp->value = get_value(token);
}

static int command_export(t_env *env, char *token, t_export *exp)
{
    int state_exp;
    int state_env;

    state_exp = existing(get_var(token), exp);
    state_env = exist_env(get_var(token), env);
    //token = get_off_quote(token, count_quote(token));
    if (all_num(token) == 0)
    {
        write (2, "export `&token' : non valid identifier\n", (ft_strlen(token) + 33));
        return (1);
    }
    if (state_exp >= 0)
        remplace(&exp, token, state_exp);
    if (state_env >= 0)
        env_remplace(&env, token, state_env);
    if (state_env < 0)
    {
        if(is_env(token) == 1)
            add_new_env(&env, new_env(token, 1));
        if(is_env(token) == 2)
            add_new_env(&env, new_env(reform(token), 1));
    }
    if (state_exp < 0)
        add_new_exp(&exp, new_export(reform(token), 1));
    return (0);
}

int export_command(t_env *env, t_token **tok, t_export *exp)
{
    t_export *temp2;
    t_token *token;
    int state;

    temp2 = exp;
    state = 0;
    token = *tok;
    if (checking_redir(token) == 1)
        printf("need redirection function\n");
    if (token->next == NULL)
        return (export(temp2));
    while (token)
    {
        if (token->state == 6 && is_option(token->token) == 1)
        {
            write (2,"No option is tolerated\n", 23); // update
            return (2);////$? = 2 when the option don ' t exist
        }
        else if (token->state == 6)
        {
            if (command_export(env, token->token, exp) == 1)
                state = 1;
        }
        token = token->next;
    }
    if (state == 1)
        return (1);//value of $? in case one of the error command
    return (0);
}
*/