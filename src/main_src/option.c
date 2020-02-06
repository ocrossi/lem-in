/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   option.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/06 15:05:20 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/28 16:46:26 by matheme     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

/*
**  1024 512 256 128  64  32  16   8   4   2   1
**    -   -   -   -    -   -   l   m   i   v   d
**    0   0   0   0    0   0   0   0   0   0   0
**
** Lors d'ajout d'option penser a rajouter l'option dans la liste des options
*/

/*
** permet de desactivé des options par rapport à d'autre option
** pour rajouter une option il suffit de recopier le patern suivant
*/

static int	ft_plugout_option(char c, int option)
{
	(void)c;
	return (option);
}

/*
** liste des options
** pour rajouter une option il suffit de recopier le patern suivant
*/

static int	ft_listing_option(char c, int option)
{
	c == 'd' ? option = option | 1 : 0;
	c == 'v' ? option = option | 2 : 0;
	c == 'i' ? option = option | 4 : 0;
	c == 'm' ? option = option | 8 : 0;
	c == 'l' ? option = option | 16 : 0;
	option = ft_plugout_option(c, option);
	return (option);
}

/*
** permet de scruter les options
** aussi bien sur le meme arg que sur plusieur arg
*/

static int	ft_option(int ac, char **av)
{
	int option;
	int	i;

	option = 0;
	i = 1;
	if ((*av)[0] != '-' || !(*av)[1])
	{
		ac != 1 ? usage() : 0;
		ac != 1 ? exit(1) : 0;
		return (option);
	}
	while ((*av)[i])
	{
		option = ft_listing_option((*av)[i], option);
		if (ft_strchr(LIST_OPTION, (*av)[i]) == NULL)
		{
			usage_option((*av)[i]);
			exit(1);
		}
		i++;
	}
	if (ac > 1)
		return (option | ft_option(ac - 1, &av[1]));
	return (option);
}

/*
** permet de ce diriger apres les options
** la fonction prend en compte le cas ou il n'y a que le tiret
** et aucune option
** dans ce cas la fonction ne deplace pas le pointeur
*/

static char	**ft_go_after_option(char **av)
{
	if (*av && **av == '-' && (*av)[1])
		return (ft_go_after_option(&av[1]));
	return (av);
}

/*
** fonction visible de l'exterieur
** elle permet de recuperer les options via ...
** ...l'adresse d'un int que l'on passe en parametre
** et elle retourne l'argument qui suit les options
*/

char		**get_option(int ac, char **av, int *option)
{
	*option = ft_option(ac, av);
	return (ft_go_after_option(av));
}

/*
**  1024 512 256 128  64  32  16   8   4   2   1
**    -   -   -   -    -   -   l   m   i   v   d
**    0   0   0   0    0   0   0   0   0   0   0
**
** Lors d'ajout d'option penser a rajouter l'option dans la liste des options
*/
