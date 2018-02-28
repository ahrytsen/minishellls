/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 11:02:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/28 21:28:43 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void	sig_handler(int signo)
{
  if (signo == SIGINT)
	  ft_printf("");
  return ;
}

void	msh_init()
{
	extern char	**environ;
	int			shlvl;
	char		*tmp;

	msh_get_environ()->env = ft_strdup_arr(environ);
	tmp = ft_getenv("SHLVL");
	shlvl = tmp ? ft_atoi(tmp) : 0;
	tmp = ft_itoa(shlvl + 1);
	ft_setenv("SHLVL", tmp, 1);
	free(tmp);
	signal(SIGINT, sig_handler);
	signal(SIGWINCH, sig_handler);
	signal(SIGINFO, sig_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void		interact_mod(void)
{
	char	pwd[MAXPATHLEN];
	int		st;
	char	*cmds;
	char	**cmd;
	int		i;

	while (1)
	{
		ft_printf("%s $> ", getcwd(pwd, MAXPATHLEN));
		i = get_next_line(0, &cmds);
		if (!i || i == -1)
			exit(!i ? st : 1);
		i = 0;
		cmd = ft_strsplit(cmds, ';');
		while (cmd[i])
		{
			st = ft_exec(ft_strsplit(cmd[i], ' '), NULL);
			free(cmd[i++]);
		}
		free(cmd);
		free(cmds);
	}
}
/*
**void		script_mod();
*/
int			main(void)
{
	msh_init();
	interact_mod();
}
