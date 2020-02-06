/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scan_abc.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/23 21:27:14 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 11:49:28 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static void	set_abc_zero(int value, UINT (*abc)[])
{
	int i;

	i = 0;
	while (i < 128)
	{
		(*abc)[i] = value;
		i++;
	}
}

static char	*cpy_s(const char *s)
{
	char	*s_cpy;

	if (!(s_cpy = ft_strdup(s)))
	{
		f_error(ERR_MALLOC, NULL);
		return (NULL);
	}
	return (s_cpy);
}

void		get_abc_for_room(const char *s, UINT (*abc)[])
{
	char		*s_cpy;
	char		*line;
	static char	ret = 0;
	static int	order = 0;

	if (!(s_cpy = cpy_s(s)))
		return ;
	if (skip_ants_number(s_cpy))
		return ;
	set_abc_zero(0, abc);
	while ((line = scan_line_line(s_cpy)))
	{
		if ((ret = is_room(line)) == 0)
		{
			if (order == 0)
				(*abc)[line[0]] += 1;
			order = 0;
		}
		else if (ret == -1)
			break ;
		else if (ret == 1 && order == 0)
			order = is_order(line);
	}
	scan_line_line(NULL);
	free(s_cpy);
}

void		get_abc_id_for_room(UINT (*abc_id)[], UINT abc[])
{
	UINT id;
	UINT i;

	id = 2;
	i = 0;
	while (i < 128)
	{
		(*abc_id)[i] = id;
		id += abc[i];
		i++;
	}
}
