/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-el- <aben-el-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:28:20 by aben-el-          #+#    #+#             */
/*   Updated: 2025/08/14 11:00:35 by aben-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_and_update_var(char *new_var)
{
	int		i;
	int		exit_code;
	size_t	len;
	char	**env;

	i = 0;
	env = ft_envp(NULL);
	exit_code = 1;
	while (env[i])
	{
		if (ft_strlen_key(env[i]) > ft_strlen_key(new_var))
			len = ft_strlen_key(env[i]);
		else
			len = ft_strlen_key(new_var);
		if (ft_strncmp(env[i], new_var, len) == 0)
		{
			if (new_var[ft_strlen_key(new_var)] == '=')
				env[i] = ft_strdup(new_var);
			exit_code = 0;
		}
		i++;
	}
	ft_envp(env);
	return (exit_code);
}

static char	**add_var(char **_env, char *var)
{
	char	**env;
	int		i;

	i = 0;
	env = copy_envp(_env, ADD);
	while (env[i])
		i++;
	if (env[i] == NULL)
		env[i] = ft_strdup(var);
	env[i + 1] = NULL;
	return (ft_envp(env));
}

static int	add_or_update(t_list *args)
{
	char	**env;
	int		exit_status;

	exit_status = 0;
	while (args)
	{
		env = ft_envp(NULL);
		if (check_identifier(args->content))
		{
			if (is_and_update_var(args->content) == 1)
				add_var(env, args->content);
		}
		else
		{
			ft_print_error("export : '%s': not a valid identifier\n",
				args->content);
			exit_status = 1;
		}
		args = args->next;
	}
	return (exit_status);
}

int	ft_export(t_list *args)
{
	char	**envp;
	int		f_flag;

	f_flag = 0;
	envp = ft_envp(NULL);
	if (args == NULL)
		print_env(envp);
	else
	{
		if (add_or_update(args))
			return (1);
	}
	return (0);
}
