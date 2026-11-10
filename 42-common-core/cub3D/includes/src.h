/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 20:16:46 by anpetit           #+#    #+#             */
/*   Updated: 2026/02/23 20:48:17 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRC_H
# define SRC_H

# include "cub3d.h"

typedef struct s_game	t_game;
typedef struct s_img	t_img;
typedef struct s_map	t_map;
typedef struct s_dda	t_dda;
typedef struct s_config	t_config;
typedef struct s_player	t_player;
typedef struct s_tex	t_tex;

// ------------------------------------------------------
// 							UTILS
// ------------------------------------------------------

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*get_next_line(int fd);
void	free_array(char **array);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isspace(int c);
char	**ft_split(char const *s, char c);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);

// ------------------------------------------------------
// 							CONFIG
// ------------------------------------------------------

// ERROR_HANDLER.C
int		error(char *msg);

// FREE_SRC.C
void	free_img(t_game *game);
void	free_config(t_game *game);
int		free_game(t_game *game, int ret);

// INITTIAL_SETTINGS.C
void	init_img(t_img *img);
void	init_player(t_player *player);
void	init_game(t_game *game);

// INITTIAL_CONFIG_SETTINGS.C
void	init_config(t_config *config);
void	init_tex(t_tex *tex);

// ------------------------------------------------------
// 							EVENTS
// ------------------------------------------------------

// MOVES.C
void	rotate_player(t_game *game);
void	move_player(t_game *game);
void	update_player(t_game *game);

//MAKE_MOVE.C
void	make_move(t_game *game, float dx, float dy);

// CLOSING.C
int		game_exit(t_game *game, int status);
int		close_window(t_game *game);

// KEYS.C
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);

// ------------------------------------------------------
// 							PARSING
// ------------------------------------------------------

// PARSE_FILE.C
int		parse_file(char *file, t_game *game);

// PARSE_FILE_UTILS.C
bool	all_textures_found(t_game *game);
int		find_map(char **lines, int i, int *map_index);
bool	is_map_line(char *line);
char	*skip_spaces(char *line);

// BUFFER.C
char	**get_buffer(char *file);

// TEXTURES.C
int		get_tex(char *line, t_game *game);

// COLORS.C
int		get_color(char *line, t_game *game);

// COLORS_UTILS.C
bool	valid_range(int color[3]);
bool	valid_chars(char *line, int color_index);

// MAP.C
int		parse_map(char **lines, t_game *game, int map_index);

// VALIDATE_MAP.C
int		validate_map(t_map *map);

// VALIDATE_MAP_EMPTY_LINE.C
int		check_for_empty_lines(char **grid);

// GRID_PADDED.C
char	**get_grid_padded(t_map *map);

// TEXTURES_DATA.C
int		init_textures(t_game *game);

// PLAYER_DATA.C
int		get_player_data(t_game *game);

// ------------------------------------------------------
// 							RENDERING
// ------------------------------------------------------

// BACKGROUND.C
void	paint_background(t_game *game);

// DDA.C
void	run_dda(t_game *game, double ray_angle, t_dda *dda);

// WALLS.C

void	render_walls(t_game *game);

// RENDER.C
int		render_frame(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color);

// TEXTURIZED_WALL.C
void	draw_wall_column_texturized(t_game *game, int x, double wall_height,
			t_dda *dda);

#endif
