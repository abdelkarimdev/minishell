/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:22:43 by aben-el-          #+#    #+#             */
/*   Updated: 2025/08/14 08:39:13 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_list *cmd)
{
	char	**envp;
	char	*pwd;
	char	*new_pwd;

	cmd = cmd->next;
	envp = ft_envp(NULL);
	pwd = NULL;
	new_pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		new_pwd = ft_get_pwd_from_env(envp);
		if (new_pwd)
			printf("%s\n", new_pwd);
		else
			perror("PWD");
		return (1);
	}
	collector(COLLECT, pwd);
	printf("%s\n", pwd);
	return (0);
}
