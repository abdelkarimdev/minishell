/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-el- <aben-el-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:22:01 by aben-el-          #+#    #+#             */
/*   Updated: 2025/08/15 16:03:21 by aben-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	replace_old_and_pwd(char *var_name)
{
	int		i;
	char	**envp;
	char	*tmp;

	i = 0;
	envp = ft_envp(NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, 3) == 0)
		{
			tmp = envp[i];
			envp[i] = var_name;
			tmp = NULL;
		}
		i++;
	}
	ft_envp(envp);
}

char	*ft_get_pwd_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PWD", envp[i], 3) == 0)
			return (&envp[i][4]);
		i++;
	}
	return (NULL);
}

static int	error_checker(t_list *path)
{
	if (!path)
	{
		ft_print_error("cd: path required\n");
		return (1);
	}
	if (path->next)
	{
		ft_print_error("minishell: cd : too many arguments\n");
		return (1);
	}
	return (0);
}

static void	get_old_pwd(char **old_pwd, char **envp)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
		collector(COLLECT, cwd);
	if (!cwd)
	{
		ft_print_error("%s %s %s",
			"minishell: cd: error retrieving current directory: ",
			"getcwd : cannot access parent directories: ",
			"No such file or directory\n");
		cwd = ft_get_pwd_from_env(envp);
		if (cwd)
			*old_pwd = ft_strjoin("OLDPWD=", cwd);
	}
	else
		*old_pwd = ft_strjoin("OLDPWD=", cwd);
}

int	ft_cd(t_list *cmd)
{
	char	**envp;
	char	*pwd;
	char	*old_pwd;

	old_pwd = NULL;
	envp = ft_envp(NULL);
	if (error_checker(cmd))
		return (1);
	get_old_pwd(&old_pwd, envp);
	if (chdir(cmd->content) != 0)
	{
		ft_print_error("minishell :cd : %s: %s\n", cmd->content,
			strerror(errno));
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);
	collector(COLLECT, pwd);
	pwd = ft_strjoin("PWD=", pwd);
	replace_old_and_pwd(old_pwd);
	replace_old_and_pwd(pwd);
	return (0);
}
