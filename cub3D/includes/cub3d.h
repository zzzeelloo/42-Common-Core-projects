/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpetit <anpetit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 20:16:41 by anpetit           #+#    #+#             */
/*   Updated: 2026/02/23 21:03:36 by anpetit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <limits.h>

# include "mlx.h"
# include "src.h"

// ------------------------------------------------------
//                     CONSTANTES
// ------------------------------------------------------
// Dimensions de la fenêtre
# ifdef __APPLE__
#  define WIDTH  1000
#  define HEIGHT 700
#  define TILE 10
# elif defined(__linux__)
#  define WIDTH  1500
#  define HEIGHT 1050
#  define TILE 8
# endif
# define PI		3.14159265358979323846

/* ------------------------------------------------------ */
/*                     KEYS                             */
/* ------------------------------------------------------ */

# ifdef __APPLE__

/* Keys (macOS by default) */
#  define KEY_W        13
#  define KEY_A        0
#  define KEY_S        1
#  define KEY_D        2
#  define KEY_Y        16
#  define KEY_N        45
#  define KEY_LEFT     123
#  define KEY_RIGHT    124
#  define KEY_ESC      53

# elif defined(__linux__)

/* Keys (Linux) */
#  define KEY_W        119
#  define KEY_A        97
#  define KEY_S        115
#  define KEY_D        100
#  define KEY_Y        121
#  define KEY_N        110
#  define KEY_LEFT     65361
#  define KEY_RIGHT    65363
#  define KEY_ESC      65307

# else
#  error "Operating system not supported"
# endif

// Velocities of movement and rotation
# define ROT_SPEED		0.05
# define MOVE_SPEED		4.0
# define TILE_SIZE		64
# define PLAYER_RADIUS	8

// ------------------------------------------------------
//                     STRUCTURES
// ------------------------------------------------------

// Structure to draw the textured line
typedef struct s_column
{
	int				x;
	double			wall_height;
	double			wall_x;
	int				draw_start;
	int				draw_end;
	double			step;
	double			tex_pos;
	int				y;
	int				tex_x;
	int				tex_y;
	double			start_y;
}	t_column;

// Structure for the DDA algorithm
typedef struct s_dda
{
	double	ray_dir_x;		// Direction of the ray X
	double	ray_dir_y;		// Direction of the ray Y
	int		map_x;			// Map position X
	int		map_y;			// Map position Y
	double	side_dist_x;	// Distance to the next side X
	double	side_dist_y;	// Distance to the next side Y
	double	delta_dist_x;	// Distance between sides X
	double	delta_dist_y;	// Distance between sides Y
	int		step_x;			// Step in X
	int		step_y;			// Step in Y
	int		hit;			// Has it hit a wall?
	int		side;			// Has it hit a wall vertically or horizontally?
	double	raw_dist;
}	t_dda;

// Image generated with mlx_new_image
typedef struct s_img
{
	void	*img;			// Pointer to the image
	char	*addr;			// Pointer to the image data
	int		bpp;			// Bits per pixel
	int		line_len;		// Length of a line in bytes
	int		endian;			// Endianness
}	t_img;

// Player information
typedef struct s_player
{
	double	x;				// Position X
	double	y;				// Position Y
	double	dir_x;			// Direction X
	double	dir_y;			// Direction Y
	double	plane_x;		// Camera plane X
	double	plane_y;		// Camera plane Y
}	t_player;

// Map in matrix
typedef struct s_map
{
	char	**grid;			// Map matrix
	int		width;			// Map width
	int		height;			// Map height
}	t_map;

typedef struct s_tex
{
	char	*path;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
	int		num;
}	t_tex;

// Configuration of the .cub file
typedef struct s_config
{
	unsigned int		floor_color;	// Floor color
	bool				floor_color_found;
	unsigned int		ceil_color;		// Ceiling color
	bool				ceil_color_found;
	double				fov;			// Field of view
	double				player_angle;	// Initial player angle
	t_map				*map;
	t_tex				no;
	t_tex				so;
	t_tex				we;
	t_tex				ea;
}	t_config;

// Main structure of the game
typedef struct s_game
{
	void		*mlx;			// Pointer to the MLX instance
	void		*win;			// Pointer to the window
	t_img		img;			// Image to render
	t_config	config;			// Game configuration
	t_player	player;			// Player information
	int			keys[65364];		// Keys state
}	t_game;

// auxiliary structure for drawing

typedef struct s_draw
{
	int	x;
	int	y;
	int	w;
	int	h;
	int	color;
}	t_draw;

#endif
