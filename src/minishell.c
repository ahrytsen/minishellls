/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 11:02:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/27 16:24:49 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


/*void	sig_handler(int signo)
{
  if (signo == SIGINT)
	  ft_printf("");
  return ;
  }*/
void	msh_init()
{
	extern char	**environ;
	//int					shlvl;

	msh_get_environ()->env = ft_strdup_arr(environ);
/*	signal(SIGINT, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGINT, sig_handler);*/
}

int		main(void)
{
	char	pwd[MAXPATHLEN];
	char	*cmds;
	char	**cmd;
	int		i;
/*	struct termios tty;

	tcgetattr (0, &tty);
	tty.c_lflag &= ~(ECHOCTL);
	tcsetattr (0, TCSASOFT, &tty);

	env = ft_cpyenv(envp);*/
	msh_init();
	while (1)
	{
		ft_printf("%s $> ", getcwd(pwd, MAXPATHLEN));
		if (!get_next_line(0, &cmds))
			return 0;
		i = 0;
		cmd = ft_strsplit(cmds, ';');
		while (cmd[i])
		{
			ft_exec(ft_strsplit(cmd[i], ' '), NULL);
			free(cmd[i++]);
		}
		free(cmd);
		free(cmds);
	}
}
