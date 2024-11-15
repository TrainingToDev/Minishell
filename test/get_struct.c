/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:12:13 by miaandri          #+#    #+#             */
/*   Updated: 2024/11/15 09:07:51 by miaandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
static char *get_input(char *input)
{
	int	i;
	int len;
	char *input;

	i = 0;
	input = NULL;
	while (input[i])
	{
		if (input[i] == '>')
		{
			len = i;
			while(input[len] && input[len] != ' ')
				len++;
			if (input != NULL)
				
		}
		i++;
	}
}
static char	*get_command(char *input, int len)
{
	int		i;
	int		a;
	char	*command;

	if (is_quote(input) == 1)
		len -= 2;
	printf ("len : %i\n", len);
	command = (char *)malloc(sizeof(char) * len);
	if (!command)
		return (NULL);
	i = 0;
	a = 0;
	while (i < len)
	{
		if (input[i] != '"' && input[i] != '\'')
		{
			command[a] = input[i];
			a++;
		}
		i++;
	}
	command[a] = '\0';
	return (command);
}

static char	*get_option(char *input, int i)
{
	char	*option;

	if (input[i] != '-')
		return (NULL);
	i++;
	if (is_alpha(input[i]) == 1)
	{
		option = (char *)malloc(sizeof(char) * 3);
		if (!option)
			return (NULL);
		option[0] = '-';
		option[1] = input[i];
		option[2] = '\0';
		return (option);
	}
	return (NULL);
}

static char	*get_param(char *input, int len, int i)
{
	char	*param;
	int		c;

	c = 0;
	param = (char *)malloc(sizeof(char) * len);
	if (!param)
		return (NULL);
	while (input[i])
	{
		param[c] = input[i];
		i++;
		c++;
	}
	param[c] = '\0';
	return (param);
}

*/
//get_string copy and realloc

/*

static char *get_string(char *input, int end, int start)//end caractere de fin
{
	int i;
	int a;
	char *string;
	
	i = start;
	while (input[i] && input[i] != end)
		i++;
	i = i - start;
	string = (char *)malloc(sizeof(char) * i + 1);
	if (!string)
		return (NULL);
	a = 0;
	while (a < i)
	{
		string[a] = input[start];
		start++;
		a++;
	}
	string[a] = '\0';
	return (string);
}

char *get_rest(char *input, char *non, int start)
{
	char	*rest;
	int i;
	int a;
	int len;

	len = (int)ft_strlen(input) - (int)ft_strlen(non);
	rest = (char*)malloc(sizeof(char) * len + 1);
	if (!rest)
		return (NULL);
	i = 0;
	a = 0;
	while (input[i])
	{
		if (i == start)
		{
			
		}
		a++;
		i++;
	}
	
}
*/

t_parse	*	get_struct(char *input)//mbola mila zaraina ho roa
{
	t_parse	*data;
	//int		i;
	//int		len;

	data = (t_parse *)malloc(sizeof(t_parse));
	if (!data)
		return (NULL);
	data->command = NULL;
	data->output = NULL;
	data->param = NULL;
	data->input = NULL;
	data->pid = 0;
	//i = 0;
	data->input = input_file(input);
	data->output = output_file(input);
	/*
	while (input[i] && input[i] != ' ')
		i++;
	data->command = get_command(input, (i));
	if (input[i] == '\0')
	{
		free(input);
		return (data);
	}
	while (input[i] == ' ' && input[i])
		i++;
	data->option = get_option(input, i);
	if (data->option != NULL)
		i = i + 2;
	if (input[i] == '\0')
	{
		free(input);
		return (data);
	}
	len = 0;
	while (input[i] == ' ')
		i++;
	while (input[i])
	{
		len++;
		i++;
	}
	data->param = get_param(input, (len + 1), (i - len));
	*/
	free(input);
	return (data);
}
/*
void	get_stuct(char **data, t_parse *contain)
{
	int i;

	i = 0;
	while (data[i])
	{
		get_struct()
		i++;
	}
	
}
*/