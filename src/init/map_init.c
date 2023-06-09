#include "cub3D.h"

void	parse_map(t_memory **block, t_game **game_data, t_map **map_data)
{
	int		i;
	char	**map;
	int		sequence;
	int		index;

	i = -1;
	map = (*map_data)->map_array;
	sequence = 0;
	while (map[++i])
	{
		if (ft_strlen(map[i]))
		{
			if (sequence < 6)
			{
				index = is_valid_element(map_data, map[i]);
				if (index >= 0)
				{
					parse_element(block, game_data, (map[i]) + index);
					sequence++;
				}
				else
				{
					free_all_memory_blocks(block);
					exit(1);
				}
			}
			else
			{
				(*map_data)->map = map + sequence;
				(*map_data)->map_copy = (*map_data)->map_copy + sequence;
				(*map_data)->width = ft_strlen(map[0]) * TILE;
				(*map_data)->height = arrtools_arrlen(map) * TILE;
				check_borders((*map_data)->map_copy);
				check_map_symbols(block, (*map_data)->map, game_data);
				break ;
			}
		}
	}
}

void	malloc_map_struct(t_memory **block, t_map **map_data)
{
	(*map_data) = malloc_to_block(block, sizeof(t_map));
	if ((*map_data) == NULL)
	{
		free_all_memory_blocks(block);
		exit(errno);
	}
}

void	init_map_data(t_memory **block, t_game **game_data, t_map **map_data, char *map_file)
{
	char	*map_string;

	map_string = try_read_map(block, map_file);
	add_memory_block(block, map_string, sizeof(char *));
	malloc_map_struct(block, map_data);
	(*map_data)->elements[0] = "NO";
	(*map_data)->elements[1] = "SO";
	(*map_data)->elements[2] = "EA";
	(*map_data)->elements[3] = "WE";
	(*map_data)->elements[4] = "C";
	(*map_data)->elements[5] = "F";
	(*map_data)->elements[6] = NULL;
	(*map_data)->map_array = try_split_string(block, map_string);
	(*map_data)->map_copy = try_split_string(block, map_string);
	(*map_data)->width = ft_strlen((*map_data)->map_array[0]) * TILE;
	(*map_data)->height = arrtools_arrlen((*map_data)->map_array) * TILE;
	parse_map(block, game_data, map_data);
}
