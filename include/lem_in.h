/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 08:38:20 by matheme      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/01 17:37:48 by ocrossi     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

/*
*************************************
**************INCLUDES***************
*************************************
*/

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <stdio.h>
# include "ft_printf.h"
# define UINT unsigned int
# define ULL unsigned long long int
# define ROOM_START 0
# define ROOM_END	1
# define NB_THREAD	8

/*
** help for option's comprehention
*/

# define BUF_SIZE 5000
# define USED 0
# define NUSED 1
# define O_D (option & 1)
# define O_V (option & 2)
# define O_I (option & 4)
# define O_M (option & 8)
# define O_L (option & 16)
# define LIST_OPTION "dviml"

enum	e_bool
{
	true = 0,
	false = 1
};

typedef struct		s_room
{
	char			*name;
	UINT			len_name;
	int				x;
	int				y;
	UINT			nb_link_tubes;
	UINT			*link_tubes;
	enum e_bool		used;
}					t_room;

typedef	struct		s_tube
{
	UINT			salle1;
	UINT			salle2;
	ULL				path_id;
	UINT			turn;
	UINT			*tmp_turn;
	enum e_bool		used;
}					t_tube;

typedef	struct		s_turn
{
	UINT			id_room;
	UINT			id_path;
	UINT			turn;
}					t_turn;

typedef struct		s_abc
{
	UINT			abc_len[128];
	UINT			abc_start[128];
	UINT			abc_id[128];
}					t_abc;

typedef struct		s_output
{
	char			**out;
	UINT			lap;
	UINT			ants;
	UINT			room_id;
	UINT			save;
	UINT			lap_cp;
}					t_opt;

typedef	struct		s_vp
{
	UINT	i;
	UINT	j;
	UINT	qt;
	UINT	pname;
	ULL		path_id_cp;
}					t_vp;

typedef struct		s_data
{
	enum e_bool		test;
	UINT			npath;
	UINT			pp;
	UINT			max_paths;
	UINT			pid;
	UINT			ants;
	UINT			rooms;
	UINT			tubes;
	UINT			**paths;
	UINT			**ret;
	UINT			path_nbr;
	UINT			index;
	UINT			lap;
	UINT			len_opt;
	enum e_bool		option_lines;
	char			*bopt;
	char			*opt;
	struct s_tube	*t_tab;
	struct s_room	*r_tab;
	struct s_abc	abc;
}					t_data;

typedef enum e_bool	t_bool;

/*
**************************************************
**********************PARSING*********************
**************************************************
*/

char				**get_option(int ac, char **av, int *option);
char				*parsing_into_line(const char *path);
char				*scan_line_line(char *s);

t_room				*create_room(UINT size);
t_tube				*create_tube(UINT size);
void				free_room(t_room *r_tab, UINT size);

UINT				get_number_of_room(const char *s);
UINT				get_number_of_tube(const char *s);
UINT				get_number_of_ants(const char *s);

t_bool				stock_anthill(char *file_line, t_data *data);
char				*get_room(char *file_line, t_data *data);
t_bool				get_tube(char *file_line, t_data *data, char *line);
t_bool				get_nodes(t_data *data);

void				check_duplicate_tube(t_tube *t_tab, UINT size);
t_bool				check_dup_room_se(UINT id, t_room *r_tab, UINT st, UINT s);
t_bool				check_dup_room_g(t_room room, t_room *r_tab, UINT st,
		UINT size);
int					is_room(const char *s);
int					is_tube(const char *s);
int					is_order(const char *s);
t_bool				skip_ants_number(char *s);
char				*skip_room(char *s);
t_bool				stock_anthill_for_threading(char *file_line, t_data *data);
void				get_abc_for_room(const char *s, UINT (*abc)[]);
void				get_abc_id_for_room(UINT (*abc_id)[], UINT abc[]);

/*
**************************************************
***********************PART 2*********************
**************************************************
*/

t_bool				browse_map(t_data *data);
void				recursive_bs_turn(t_data *d, t_turn *t, UINT nb, UINT lap);
UINT				get_id_room(t_tube tubes, UINT id_room);
UINT				destroy_turn(t_turn *turns, UINT o, UINT id, UINT c);

/*
**************************************************
***********************PART 3*********************
**************************************************
*/

void				print_potential_paths(t_data *data);
void				print_one_potential_path(t_data *data, UINT i);
UINT				fill_path_tab(t_data *data);
UINT				fill_tabs_with_current_room(UINT id_tab,
		UINT id_room, t_data *data, UINT cell);
UINT				fill_tabs_with_current_room2(UINT id_tab,
		UINT id_room, t_data *data, UINT cell);
void				fill_tabs_with_rooms(t_data *data);
void				print_number_paths(t_data *data);
UINT				count_bits(t_tube tube);
UINT				get_bit_place(ULL path_list);
UINT				find_pname(ULL *path_id, UINT nb_link_tubes_start);
UINT				potential_path_counter(t_data *data);
UINT				max_paths(t_data data);
void				reset_markers(t_data *data);
void				bruteforce_sorter(t_data *data, UINT max_paths,
		UINT (*res)[]);
void				set_used_rooms(UINT id_tab, t_data *data);
UINT				is_valid(UINT *tab, t_data *data);
UINT				get_compatible_tab_for_pid(UINT pid, t_data *data);
void				get_result_for_path_managment(t_data *data, UINT max_paths);
UINT				check_path_found(UINT (*curr)[], UINT max_paths,
		UINT path_nbr);
void				tab_cp(UINT (*curr)[], UINT (*res)[], UINT max_paths);
void				set_tab_for_bf(UINT (*tab)[], UINT path_nbr,
		UINT max_paths);
void				fill_ret_tab_norm(t_data *data, UINT (*id_tab)[],
		UINT index, UINT j);
UINT				get_biggest_turn(t_data *data, UINT (*id_tab)[],
		UINT index);
void				fill_all_paths(t_data *data, UINT (*id_tab)[], UINT index);
UINT				set_ref(t_data *data, UINT (*tab)[], UINT index);
void				set_tab_with_order(t_data *data, UINT (*tab)[], UINT index);
void				set_id_tab(t_data *data, UINT (*id_tab)[]);
UINT				get_shortest_path(t_data *data);
UINT				comp_unit_tab(t_data *data, UINT i1, UINT i2);
UINT				generic_sorter(t_data *data);
t_bool				init_stocker_tab(t_data *data);
t_bool				fill_comp_tab(t_data *data);
void				get_new_solution2(t_data *data, UINT index,
		UINT (*id_tab)[]);
UINT				superposition_tab(t_data *data, UINT index);
UINT				set_ppath_from_smallest(t_data *data,
		UINT index, UINT (*id_tab)[]);
void				set_tab_zero(UINT len, UINT (*tab)[]);
UINT				manage_lap_ovf(t_data *data, UINT i, UINT ids);
void				reset_marker_values(t_data *data);
UINT				get_smallest_path(t_data *data, UINT index);
t_bool				sort_opti2(t_data *data);
UINT				get_smallest_opt(t_data *data);
UINT				count_id_paths(t_data data);
UINT				get_pnum(UINT pid, t_data *data);
void				get_new_lenght(char **tab, UINT (*lenght)[]);
t_turn				*init_turn(UINT size);
UINT				get_id_room(t_tube tubes, UINT id_room);
void				print_smallest_opt(t_data *data);
void				print_comp_tab(t_data *data);
void				print_cp_tab_binary(t_data *data);
void				aprint_tab(UINT *tab, UINT len);
void				print_tab(UINT (*res)[], UINT max_paths);
void				print_tab2(t_data *data, UINT (*res)[], UINT size);
void				print_tab_with_size(t_data *data,
		UINT (*res)[], UINT max_paths);
void				print_res_tab(t_data *data, UINT (*rtab)[],
		UINT (*id_tab)[], UINT size);
void				print_final_path_tab(t_data *data);
t_bool				free_tab_turn(t_tube *tab, UINT size);
void				del_output(t_opt *opt);

/*
**************************************************
***********************PART 4*********************
**************************************************
*/

t_bool				new_output(t_data *data);
void				del_temp_str(char **s1, char **s2, char **s3);
void				stock_file_line(t_data *data, const char *s);
char				**fill_buffer(t_data *data, UINT (*lenght)[]);
void				insert_linefeed(t_opt *opt, UINT (*lenght)[], t_data *data);
void				get_name_lenght(t_data *data);
void				join_output_tab(t_opt *opt, t_data *data);
void				get_ant_move_ovf(t_opt *opt, char **s1,
		char **s2, UINT len);
void				get_ant_move(t_opt *opt, UINT (*lenght)[], t_data *data);
void				ant_march(t_opt *opt, t_data *data,
		UINT i, UINT (*lenght)[]);
void				len_tab_into_data(t_data *data, UINT (*lenght)[]);
void				stock_file_line(t_data *data, const char *s);
void				del_2d_int_tab(UINT **tab);
void				free_room_error(t_data *data, UINT nb_room);

/*
**************************************************
***********************ERROR**********************
**************************************************
*/

# define ERR_MALLOC 			1
# define ERR_OPEN				2
# define ERR_READ				3
# define ERR_OCCURD				4
# define ERR_DUPLICATE_STR		5
# define ERR_DUPLICATE_END		6
# define ERR_TUBES_FORMAT		7
# define ERR_TUBES				8
# define ERR_ROOMS				9
# define ERR_ANTS				10
# define ERR_ANTS_SPACE			11
# define ERR_LACK_BEGIN			12
# define ERR_LACK_END			13
# define ERR_ROOM_FORMAT		14
# define ERR_DUPL_ROOM			15
# define ERR_DUPL_XY_ROOM		16
# define ERR_DUPL_TUBE			17
# define ERR_LINK_TUBE_ITSELF	18
# define ERR_EMPTY_FILE			19
# define ERR_ORDER				20
# define ERR_OVERFLOW			21
# define ERR_ONLY_COMMENT		22
# define ERR_ROOM_NOT_DEFINE	23
# define ERR_ROOM_WRONG_POS		24
# define ERR_NO_ANTS			25
# define ERR_NO_PATHS			26

void				usage(void);
void				usage_option(char c);
void				*f_error(char value, void *data);
void				str_error(int error);

/*
***************************************************
*************debug*********************************
***************************************************
*/

void				debug_lem_in(t_data *data);
void				debug_main(int option);
void				global_info(t_data *data);
void				show_turns(t_turn *turns, UINT size);

/*
***************************************************
**********************lib_plus*********************
***************************************************
*/

size_t				ft_strlenc(const char *s, char c);
char				*ft_strsub_c(const char *src, char c);
char				*ft_revstrsub_c(const char *src, char c);
long				atol_id(const char *s, char c, UINT index, t_bool *boule);
ULL					bin(char c);
UINT				count_digits(UINT num);

/*
**************************************************
*******************VISUALISATEUR******************
**************************************************
*/

void				main_visualisateur(t_data data);

#endif
