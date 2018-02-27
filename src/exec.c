/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:27:15 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/27 16:25:58 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

const static t_builtins	g_builtins[] =
{
	{"echo", &ft_echo},
	{"cd", &ft_cd},
	{"setenv", &ft_setenv_builtin},
	{"unsetenv", &ft_unsetenv_builtin},
	{"env", &ft_env},
	{"exit", &ft_exit},
	{NULL, NULL}
};

static int	ft_exec_builtin(char **cmd)
{
	int	i;

	i = 0;
	while(g_builtins[i].cmd && ft_strcmp(cmd[0], g_builtins[i].cmd))
		i++;
	return (g_builtins[i].cmd ? g_builtins[i].ft_builtin(cmd + 1)
			: -1);
}

static int	ft_exec_bypath(char **cmd, char *path)
{
	int	st;

	st = 0;
	if (path && (access(path, X_OK) == 0))
		fork() ? wait(&st) : execve(path, cmd, msh_get_environ()->env);
	else
	{
		st = 127;
		ft_dprintf(2, "%s: command not found or permission denied\n", *cmd);
	}
	return (st);
}

static char	*ft_search_bin(char *bin_name, const char *altpath)
{
	int				i;
	char			*exec_path;
	char			**path;

	i = 0;
	exec_path = NULL;
	if (!(path = ft_strsplit(altpath ? altpath : ft_getenv("PATH"), ':')))
		return (NULL);
	while (path[i])
	{
		if (!(exec_path = malloc(ft_strlen(path[i]) + ft_strlen(bin_name) + 2)))
			return (NULL);
		ft_strcpy(exec_path, path[i]);
		ft_strcat(exec_path, "/");
		ft_strcat(exec_path, bin_name);
		if (!access(exec_path, X_OK))
			break;
		ft_memdel((void**)&exec_path);
		free(path[i++]);
	}
	while (path[i])
		free(path[i++]);
	free(path);
	return (exec_path);
}

int			ft_exec(char **cmd, char *altpath)
{
	char	*bin_path;
	int		st;
	int		i;

	bin_path = NULL;
	if (!cmd)
		return (-1);
	if (ft_strchr(*cmd, '/'))
		st = ft_exec_bypath(cmd, *cmd);
	else if ((st = ft_exec_builtin(cmd)) == -1)
	{
		bin_path = ft_search_bin(*cmd, altpath);
		st = ft_exec_bypath(cmd, bin_path);
	}
	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
	free(bin_path);
	return (st);
}