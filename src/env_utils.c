/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:44:16 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/22 14:11:40 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_new_env_str(const char *name, const char *value)
{
	char	*new_env;
	size_t	name_l;
	size_t	value_l;

	if (!name)
		return (NULL);
	name_l = ft_strlen(name);
	value_l = value ? ft_strlen(value) : 0;
	if (!(new_env = (char*)malloc(sizeof(char) * (name_l + value_l + 2))))
		return (NULL);
	ft_strcpy(new_env, name);
	new_env[name_l] = '=';
	ft_strcpy(new_env + name_l + 1, value ? value : "");
	return (new_env);
}

t_env		*msh_get_environ(void)
{
	static t_env	env;

	return (&env);
}

char		*ft_getenv(const char *name)
{
	char	**env;

	env = msh_get_environ()->env;
	if (!name || !env)
		return (NULL);
	while (*env)
	{
		if (ft_strcmp(*env, name) == '=')
			return (ft_strchr(*env, '=') + 1);
		env++;
	}
	return (NULL);
}

int			ft_setenv(const char *name, const char *value, int overwrite)
{
	size_t	i;
	char	**env;
	char	*tmp;

	i = -1;
	if (!(tmp = ft_new_env_str(name, value))
		|| !(env = msh_get_environ()->env))
		return (-1);
	while (env[++i])
		if (ft_strcmp(env[i], name) == '=')
		{
			if (!overwrite)
			{
				free(tmp);
				return (-1);
			}
			free((void*)env[i]);
			return ((env[i] = tmp) ? 0 : -1);
		}
	if (!(env = ft_memalloc(sizeof(char*) * (i + 2))))
		return (-1);
	ft_memcpy(env, msh_get_environ()->env, sizeof(char*) * i);
	env[i] = tmp;
	free(msh_get_environ()->env);
	return ((msh_get_environ()->env = env) ? 0 : -1);
}

int			ft_unsetenv(const char *name)
{
	char	**env;

	env = msh_get_environ()->env;
	if (!env || !name || ft_strchr(name, '='))
		return (-1);
	while (*env && ft_strcmp(*env, name) != '=')
		env++;
	if (!*env)
		return (-1);
	free(*env);
	while (*env++)
		*(env - 1) = *env;
	return (0);
}
