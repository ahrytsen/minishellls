/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:37:14 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/28 21:31:12 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parse_line(char **line)
{
	char	*res;
	t_buf	*head;
	t_buf	*cur;

	if (!(head = ft_memalloc(sizeof(t_buf))))
		malloc_fail();
	while (**line)
	{
		if (**line == '$')
			;
		ft_putchar_buf(&head, **line);
	}
	return (0);
}

/*int	quote_checker(char **line)
{
	t_quote	quote[3];

	quote = {
		{'\'', "quote", 0},

	}
	while (**line)
	{
		if (**line == '\'')
			while (**line && )
			{

			}

	}
	}*/
