/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzasenko <dzasenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:20:03 by ibondarc          #+#    #+#             */
/*   Updated: 2025/05/07 13:53:13 by dzasenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int make_lib_without_value(t_lib *lib, char *str)
{
	char *new_key;

	if (!check_export_key(str))
		return (show_error_message(str),  2);
	new_key = ft_strdup(str);
	if (!new_key)
		return (0);
	lib->key = new_key;
	lib->value = NULL;
	return 1;
}
char *get_value(char *str)
{
	char *arg_value;
	char *value;

	value = NULL;
	arg_value = ft_strchr(str, '=', true);
	if (!arg_value)
	{
		value = ft_strdup("");
		if (!value)
			return (NULL);
	}
	else 
	{
		value = ft_strdup(arg_value);
		if (!value)
			return (NULL);
	}
	return value;
}
int make_lib_with_existed_value(t_lib *lib, char *str, int *i)
{
	char *value = NULL;
	char	*key;

	while (str[*i] != '=')
		(*i)++;
	key = (char *)ft_calloc(sizeof(char), *i + 1);
	if (!key)
		return 0;
	ft_strlcpy(key, str, *i + 1);
	if (!check_export_key(key))
		return (show_error_message(str), free(key), 2);
	value = get_value(str);
	if (!value)
		return (free(key), 0);
	lib->key = key;
	lib->value = value;
	return 1;
}

t_lib *check_export_arg(char *str, int *exit_code, t_app *shell, bool is_child)
{
	t_lib	*lib;
	int 	res;
	int		i;

	i = 0;
	res = -1;
	lib = ft_calloc(sizeof(t_lib), 1);
	if (!lib)
		return (NULL);
	if (ft_strchr(str, '=', false) == NULL)
		res = make_lib_without_value(lib, str);
	else
		res = make_lib_with_existed_value(lib, str, &i);
	if (res == 0)
	{
		free_lib_list(&lib);
		exit_malloc(shell, is_child);
	}
	else if (res == 2)
		return (free_lib_list(&lib), *exit_code = 1, NULL);
	return lib;
}