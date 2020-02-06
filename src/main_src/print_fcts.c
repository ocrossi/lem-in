/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_fcts.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ocrossi <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/12 16:29:55 by ocrossi      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/24 13:52:59 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	aprint_tab(UINT *tab, UINT len)
{
	UINT i;

	i = 0;
	while (i < len)
	{
		FPF(" %u ", tab[i]);
		i++;
	}
	FPF("\n+++++++++++++++++++++++++++++++++++++\n");
}



void	print_tab(UINT (*res)[], UINT max_paths)
{
	UINT tst = 0;

	FPF("====================================================================\n");
	while (tst < max_paths)
	{
		FPF("case num %u tab num %u\n", tst, (*res)[tst]);
		tst++;
	}
	FPF("====================================================================\n");
}

void	print_tab2(t_data *data, UINT (*res)[], UINT size)
{
	UINT tst = 0;

	FPF("====================================================================\nsize = %u\n", size);
	while (tst < size)
	{
		FPF("case num %u tab num %u len du tab %u\n", tst, (*res)[tst], data->paths[(*res)[tst]][1] - 4);
		tst++;
	}
	FPF("====================================================================\n");
}


void	print_tab_with_size(t_data *data, UINT (*res)[], UINT max_paths)
{
	UINT tst = 0;

	FPF("====================================================================\n");
	while (tst < max_paths)
	{
		if ((*res)[tst])
			FPF("case num %u tab num %u size = %u\n", tst, (*res)[tst], data->paths[tst][1] - 4);
		else
			FPF("case num %u tab num %u\n", tst, (*res)[tst]);
		tst++;
	}
	FPF("====================================================================\n");
}


void	print_potential_paths(t_data *data)
{
	UINT i;
	UINT j;

	i = 0;
	j = 0;
	FPF("nb de chemins trouves = %u\n", potential_path_counter(data));
	while (data->paths[i] != NULL)
	{
		j = 3;
		FPF("tab num %u id_path = %u size = %u\n", i, data->paths[i][0], data->paths[i][1] - 4);
		while (j < data->paths[i][1])
		{
			FPF("salle %u name = %s\n", j, data->r_tab[data->paths[i][j]].name);
			j++;
		}
		FPF("-----------------------------------\n");
		i++;
	}
}

void	print_one_potential_path(t_data *data, UINT i)
{
	UINT j;

	j = 3;
	FPF("tab num %u id_path = %u size = %u\n", i, data->paths[i][0], data->paths[i][1]);
	while (j < data->paths[i][1])
	{
		FPF("salle %u name = %s\n", j, data->r_tab[data->paths[i][j]].name);
		j++;
	}
}


void	print_final_path_tab(t_data *data)
{
	UINT i;
	UINT j;

	i = 0;
	while (data->ret[i])
	{
		j = 1;
		while (j < data->ret[i][0])
		{
			FPF("alle %s\n", data->r_tab[data->ret[i][j]].name);
			j++;
		}
		i++;
	}
	data->path_nbr = i;
}

void	print_cp_tab_binary(t_data *data)
{
	UINT i;
	UINT j;

	i = 0;
	while (data->ret[i])
	{
		if (data->ret[i][data->pp + 1] == 0)
		{
	//		FPF("heyyyyy le break ?\n");
			break ;
		}
		j = 0;
		FPF("\nret index %u nb de chemins trouves = %u taille du plus grand chemin trouve = %u\n", i, data->ret[i][data->pp + 1], data->ret[i][data->pp]);
		while (j < data->pp)
		{
			FPF(" %u ", data->ret[i][j]);
			j++;
		}
		i++;
		FPF("\n---------------------------\n");
	}
}

void	print_comp_tab(t_data *data)
{
	UINT i;
	UINT j;

	i = 0;
	while (data->ret[i])
	{
		j = 0;
		FPF("ret index %u nb de chemins trouves = %u taille du plus grand chemin trouve = %u\n", i, data->ret[i][data->pp + 1], data->ret[i][data->pp]);
		while (j < data->pp)
		{
			if (data->ret[i][j] == 1)
			{
				FPF("\nle tab %u est compatible\n", j);
				print_one_potential_path(data, j);
			}
			j++;
		}
		FPF("\n---------------------------\n");
		i++;
	}
}

void	print_res_tab(t_data *data, UINT (*rtab)[], UINT (*id_tab)[], UINT size)
{
	UINT i;
	UINT res;
	UINT sub;

	i = 0;
	FPF("nb de fourmis tot %u\n", data->ants);
	FPF("size qu on nous donne en params %u\n", size);
	while (i < size)
	{
		sub = data->paths[(*id_tab)[i]][1] - 5;
		res = (*rtab)[(*id_tab)[i]] - sub;
		printf("i = %u | res = %u | len = %u | substract = %u | path %u\n", i, res, sub, (*rtab)[(*id_tab)[i]], (*id_tab)[i]);
		i++;
	}
}

void	print_smallest_opt(t_data *data)
{
	UINT idx;
	UINT i;
	UINT ret;

	i = 0;
	ret = 0;
	idx = get_smallest_opt(data);
	FPF("\n---------------------------\n");
	FPF("idx = %u\nants = %u\n", idx, data->ants);
	FPF("ret index %u nb de chemins trouves = %u taille du plus grand chemin trouve = %u\n", idx, data->ret[idx][data->pp + 1], data->ret[idx][data->pp]);
	while (i < data->pp)
	{
		FPF(" %u ", data->ret[idx][i]);
		i++;
	}
	FPF("\n---------------------------\n");
	i = 0;
	FPF("avec taille des chemins ca donne\n");
	while (i < data->pp)
	{
		if (data->ret[idx][i] != 0)
		{
			FPF(" %u ", data->ret[idx][i] + (data->paths[i][1] - 5));
			ret++;
		}
		else
			FPF(" 0 ");
		i++;
	}
	FPF("\n---------------------------\nnb de chemins utilises = %u\n", ret);
}

