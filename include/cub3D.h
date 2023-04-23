
#ifndef CUB3D_H
# define CUB3D_H

# include <assert.h>
# include <errno.h>
# include <fcntl.h>
# include "libft.h"
# include "MLX42/MLX42.h"
# include "libarrtools.h"
# define TRUE 1
# define FALSE 0
# define TILE 64
# define EMPTY_MAP 254
# define IS_DIRECTORY 21
# define BAD_MAP_FILE 255
# define PLAYER 'P'
# define WALL '1'

typedef struct s_game	t_game;
typedef struct s_map	t_map;

struct s_position
{
	int	*x_axis;
	int	*y_axis;
};

struct s_static_position
{
	int	x_axis;
	int	y_axis;
};

struct s_player_data
{
	struct s_static_position	initial_position;
	struct s_position			current_position;
	mlx_image_t					*player_image;
};

struct s_game
{
	mlx_t					*mlx;
	mlx_image_t				*bg_img;
	struct s_map			*map_data;
	struct s_player_data	player_data;
};

struct s_map
{
	char	**map_array;
	int		height;
	int		width;
};

void		game_setup(char *argv);

/**
 * @brief Initializes map data.
 *
 * This function initializes a map_data struct and sets its map_string
 *	map_array, width, and height values.
 *
 * @param map_data A pointer to the map_data struct to be initialized.
 * @param map_file The file path of the map file to be read.
 */
void		init_map_data(t_map **map_data, char *map_file);

/**
 * @brief Destroys map data.
 *
 * This function frees memory allocated for a map_data struct and its 
 *	components.
 *
 * @param map_data A pointer to the map_data struct to be destroyed.
 */
void		destroy_map_data(t_map *map_data);

/**
 * @brief Prints an error message to the standard error output and exits 
 *	with the function parameter passed error code.
 *
 * @param error The error number to print.
 *
 * @return void.
 */
void		print_error(int error);

/**
 * @brief Frees any allocated memory and exits the program with the given 
 *	error number.
 *
 * @param error The error number to print.
 * @param file The file descriptor to close.
 * @param buffer The buffer to free.
 *
 * @return void.
 */
void		cleanup_and_exit(int error, int file, char *buffer);

/**
 * @brief Returns the total number of bytes in the file with the given 
 *	filename.
 *
 * @param filename The name of the file.
 *
 * @return The total number of bytes in the file.
 */
int			get_total_bytes(char *filename);

/**
 * @brief Reads the contents of the file with the given name into a 
 *	dynamically allocated buffer.
 *
 * @param file The name of the file.
 *
 * @return A pointer to the dynamically allocated buffer containing the file 
 *	contents, or NULL on error.
 */
char		*read_map(char *filename);

/**
 * @brief Checks if the given filename has a valid extension.
 *
 * This function checks if the extension of the given filename is ".cub".
 *
 * @param filename The filename to check.
 * @return Returns TRUE (1) if the extension is valid, and FALSE (0) otherwise.
 */
int			has_invalid_map_extension(char *filename);

/**
 * @brief Checks if the given filename is valid.
 *
 * This function checks if the extension of the given filename is valid.
 * If the extension is not valid, it calls the handle_error() function with 
 *	the error code BAD_MAP_FILE.
 *
 * @param filename The filename to check.
 * @return Returns TRUE (1) if the filename is valid, and the handle_error() 
 *	function does not return an error code. Otherwise, it returns FALSE (0).
 */
int			is_valid_filename(char *filename);
void		protected_malloc(void **parameter, size_t size_of_parameter);
void		init_game_data(t_game **game_data,
				t_map *map_data);
void		destroy_game_data(t_game *game_data);
void		place_image(mlx_image_t *img, mlx_t *mlx, int width, int height);
void		create_img(mlx_image_t **img, mlx_t *mlx, int width, int height);
void		turn_right(char **map, t_game *game_data);
void		turn_left(char **map, t_game *game_data);
void		turn_down(char **map, t_game *game_data);
void		turn_up(char **map, t_game *game_data);
void		place_wall_or_player(char **map, t_game *game_data, int x, int y);
void		draw_grid(t_map *map_data, mlx_image_t *image);

#endif
