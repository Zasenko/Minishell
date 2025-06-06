/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:23:25 by ibondarc          #+#    #+#             */
/*   Updated: 2025/05/09 12:50:28 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	show_error_message(char *str)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(NAVI, 2);
}

void	handle_export_showing(char **str, int *i, int *g)
{
	int	f;
	int	e;

	f = 1;
	e = 0;
	while (str[*i][*g])
	{
		printf("%c", str[*i][*g]);
		if (str[*i][*g] == '=' && f)
		{
			f = 0;
			e = 1;
			printf("%c", '"');
		}
		(*g)++;
	}
	if (e)
		printf("%c", '"');
}

void	free_lib_list(t_lib **lib)
{
	if (!lib)
		return ;
	if ((*lib)->key)
	{
		free((*lib)->key);
		(*lib)->key = NULL;
	}
	if ((*lib)->value)
	{
		free((*lib)->value);
		(*lib)->value = NULL;
	}
	free(*lib);
	*lib = NULL;
}

int	check_export_key(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (len == 0 || (len == 1 && !ft_isalpha(str[i])))
		return (0);
	else
	{
		while (str[i])
		{
			if (!ft_isprint(str[i]))
				return (0);
			else if (i == 0 && (!ft_isalpha(str[i]) && str[i] != '_'))
				return (0);
			else if (!ft_isalnum(str[i]) && str[i] != '_')
				return (0);
			i++;
		}
	}
	return (1);
}

void	sort_2d_env(char **env)
{
	int		i;
	int		sorted;
	char	*tmp;

	if (!env)
		return ;
	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (env[i] && env[i + 1])
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}
