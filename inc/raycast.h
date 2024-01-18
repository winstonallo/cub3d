/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:36:59 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/18 03:24:47 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include "ansi_hex_codes.h"
# include "../libft/include/libft.h"
# include "cub3d.h"
# include "../minilibx-linux/mlx.h"

//constants
# define PI 3.1415926535
# define P2 1.570796327
# define P3 4.71238898
# define MAX_DISTANCE 1000
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000
# define SCREEN_HEIGHT2 500
# define SPEED 0.03
# define TURN_SPEED 10
# define DR 0.00872665
# define FIELD_OF_VIEW 1.04719755
# define MAX_DIST 1000000
# define WALL_HEIGHT 1.2
# define COLL_SENS 0.3
# define SOME_LARGE_VALUE 1000000

//keys
# define ESCAPE 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define E 101
# define Q 113

// colors
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF
# define BLUE 0x000000FF
# define CYAN 0x0000FFFF
# define MAGENTA 0x00FF00FF
# define ORANGE 0x00FFA500
# define TURQUOISE 0x0000FFA5
# define PINK 0x00FFC0CB
# define PURPLE 0x00800080
# define BROWN 0x00A52A2A
# define LIGHT_GRAY 0x00D3D3D3
# define DARK_GRAY 0x00A9A9A9
# define LIGHT_RED 0x00FFC0CB
# define LIGHT_GREEN 0x0090EE90
# define LIGHT_BLUE 0x00ADD8E6
# define LIGHT_YELLOW 0x00FFFFE0
# define LIGHT_CYAN 0x00E0FFFF
# define LIGHT_MAGENTA 0x00FFB6C1
# define LIGHT_ORANGE 0x00FFA07A
# define LIGHT_PINK 0x00FFB6C1
# define LIGHT_PURPLE 0x00E6E6FA
# define LIGHT_BROWN 0x00D2B48C
# define DARK_RED 0x008B0000
# define DARK_GREEN 0x00006400
# define DARK_BLUE 0x0000008B
# define DARK_YELLOW 0x00BFFF00
# define DARK_CYAN 0x00008B8B
# define DARK_MAGENTA 0x008B008B
# define DARK_ORANGE 0x00FF8C00
# define DARK_PINK 0x00FF1493
# define DARK_PURPLE 0x004B0082
# define DARK_BROWN 0x008B4513

# define LIGHT_AQUA 0x00A0E6E6
# define LIGHT_BEIGE 0x00F5F5DC
# define LIGHT_GOLD 0x00FFD700
# define LIGHT_LAVENDER 0x00E6E6FA
# define LIGHT_CORAL 0x00FF7F50
# define LIGHT_MAUVE 0x00E0B0FF
# define LIGHT_OLIVE 0x00808000
# define LIGHT_SILVER 0x00C0C0C0
# define LIGHT_RED 0x00FFC0CB
# define LIGHT_CYAN 0x00E0FFFF
# define LIGHT_INDIGO 0x00B0C4DE
# define LIGHT_GOLDENROD 0x00DAA520
# define LIGHT_SEAGREEN 0x002E8B57
# define LIGHT_TAN 0x00D2B48C
# define LIGHT_CORNFLOWER 0x006495ED
# define LIGHT_MEDIUMVIOLET 0x00715CB2
# define LIGHT_SALMON 0x00FFA07A
# define LIGHT_SKYBLUE 0x0087CEEB
# define LIGHT_LIME 0x00ADFF2F
# define LIGHT_SLATEGRAY 0x00708090
# define LIGHT_VIOLET 0x00EE82EE
# define LIGHT_SPRINGGREEN 0x0000FF7F
# define LIGHT_CORAL 0x00FF7F50
# define LIGHT_ROYALBLUE 0x004169E1
# define LIGHT_MAROON 0x00FFB6C1
# define LIGHT_GREENYELLOW 0x00ADFF2F
# define LIGHT_NAVAJOWHITE 0x00FFDEAD
# define LIGHT_CYANBLUE 0x008A2BE2
# define LIGHT_DARKORANGE 0x00FF8C00
# define LIGHT_DARKSEAGREEN 0x008FBC8B
# define LIGHT_PEACHPUFF 0x00FFDAB9
# define LIGHT_SLATEBLUE 0x006A5ACD
# define LIGHT_CHOCOLATE 0x00D2691E
# define LIGHT_PERU 0x00CD853F
# define LIGHT_TOMATO 0x00FF6347
# define LIGHT_MEDIUMSEAGREEN 0x003CB371
# define LIGHT_MEDIUMSLATEBLUE 0x007B68EE
# define LIGHT_DARKTURQUOISE 0x0000CED1
# define LIGHT_DARKGOLDENROD 0x00B8860B
# define LIGHT_MEDIUMORCHID 0x00BA55D3
# define LIGHT_LIGHTCORAL 0x00F08080
# define LIGHT_LIGHTGOLDENRODYELLOW 0x00FAFAD2
# define LIGHT_LIGHTSKYBLUE 0x0087CEFA
# define LIGHT_LIGHTSLATEGRAY 0x00778899
# define LIGHT_LIGHTSTEELBLUE 0x00B0C4DE
# define LIGHT_LIGHTCYAN 0x00E0FFFF
# define LIGHT_LIGHTGRAY 0x00D3D3D3
# define LIGHT_LINEN 0x00FAF0E6
# define LIGHT_PEACH 0x00FFE5B4
# define LIGHT_PALEGOLDENROD 0x00EEE8AA
# define LIGHT_PALEGREEN 0x0098FB98
# define LIGHT_PALETURQUOISE 0x00AFEEEE
# define LIGHT_PALEVIOLETRED 0x00DB7093
# define LIGHT_PAPAYAWHIP 0x00FFEFD5
# define LIGHT_ROSYBROWN 0x00BC8F8F
# define LIGHT_SANDYBROWN 0x00F4A460
# define LIGHT_BLUEVIOLET 0x008A2BE2
# define LIGHT_CRIMSON 0x00DC143C
# define LIGHT_FIREBRICK 0x00B22222
# define LIGHT_LIGHTGOLDENROD 0x00FFEC8B
# define LIGHT_LIGHTPINK 0x00FFB6C1
# define LIGHT_MEDIUMAQUAMARINE 0x0066CDAA
# define LIGHT_MEDIUMSPRINGGREEN 0x0000FA9A
# define LIGHT_MEDIUMTURQUOISE 0x0048D1CC
# define LIGHT_MEDIUMVIOLETRED 0x00C71585
# define LIGHT_ORCHID 0x00DA70D6
# define LIGHT_PALEGOLDENROD 0x00EEE8AA
# define LIGHT_PALEGREENYELLOW 0x00ADFF2F
# define LIGHT_ROYALBLUE 0x004169E1
# define LIGHT_SPRINGGREEN 0x0000FF7F
# define LIGHT_TURQUOISE 0x0040E0D0
# define LIGHT_YELLOWGREEN 0x009ACD32
# define LIGHT_BURLYWOOD 0x00DEB887
# define LIGHT_CORNSILK 0x00FFF8DC
# define LIGHT_DIMGRAY 0x00696969
# define LIGHT_GOLDENROD 0x00DAA520
# define LIGHT_HONEYDEW 0x00F0FFF0
# define LIGHT_IVORY 0x00FFFFF0
# define LIGHT_LAVENDERBLUSH 0x00FFF0F5
# define LIGHT_MINTCREAM 0x00F5FFFA
# define LIGHT_NAVY 0x00000080
# define LIGHT_OLDLACE 0x00FDF5E6
# define LIGHT_PALEGOLDENROD 0x00EEE8AA
# define LIGHT_PEACHPUFF2 0x00EECBAD
# define LIGHT_ROSYBROWN1 0x00FFC1C1
# define LIGHT_SEASHELL2 0x00EEE5DE
# define LIGHT_SNOW2 0x00EEE9E9
# define LIGHT_TAN2 0x00EE9A49
# define LIGHT_ALICEBLUE 0x00F0F8FF
# define LIGHT_CADETBLUE 0x005F9EA0
# define LIGHT_CHARTREUSE 0x007FFF00
# define LIGHT_DARKKHAKI 0x00BDB76B
# define LIGHT_GAINSBORO 0x00DCDCDC
# define LIGHT_HOTPINK 0x00FF69B4
# define LIGHT_LIGHTCORAL 0x00F08080
# define LIGHT_LIGHTSLATEGREY 0x00778899
# define LIGHT_MEDIUMBLUE 0x000000CD
# define LIGHT_MEDIUMORCHID2 0x00D15FEE
# define LIGHT_MEDIUMSLATEBLUE 0x007B68EE
# define LIGHT_MEDIUMVIOLETRED 0x00C71585
# define LIGHT_MIDNIGHTBLUE 0x00191970
# define LIGHT_NAVYBLUE 0x00000080
# define LIGHT_PALETURQUOISE 0x00AFEEEE
# define LIGHT_PALEVIOLETRED 0x00DB7093

# define MIDDLE_AQUA_BEIGE 0x00D0F9E0
# define MIDDLE_BEIGE_GOLD 0x00FFE1A8
# define MIDDLE_GOLD_LAVENDER 0x00FFD9ED
# define MIDDLE_LAVENDER_CORAL 0x00FFBED0
# define MIDDLE_CORAL_MAUVE 0x00FF9980
# define MIDDLE_MAUVE_OLIVE 0x00B0807F
# define MIDDLE_OLIVE_SILVER 0x00A0A040
# define MIDDLE_SILVER_RED 0x00C0C080
# define MIDDLE_RED_CYAN 0x00FF60E3
# define MIDDLE_CYAN_INDIGO 0x00AFC1F2
# define MIDDLE_INDIGO_GOLDENROD 0x009897A5
# define MIDDLE_GOLDENROD_SEAGREEN 0x0068D05A
# define MIDDLE_SEAGREEN_TAN 0x00506F3E
# define MIDDLE_TAN_CORNFLOWER 0x006F6E63
# define MIDDLE_CORNFLOWER_MEDIUMVIOLET 0x0060AAB7
# define MIDDLE_MEDIUMVIOLET_SALMON 0x00813877
# define MIDDLE_SALMON_SKYBLUE 0x00FFCC89
# define MIDDLE_SKYBLUE_LIME 0x0054F12D
# define MIDDLE_LIME_SLATEGRAY 0x00508045
# define MIDDLE_SLATEGRAY_VIOLET 0x009282AD
# define MIDDLE_VIOLET_SPRINGGREEN 0x007B9B95
# define MIDDLE_SPRINGGREEN_CORAL 0x007FFF65
# define MIDDLE_CORAL_ROYALBLUE 0x0063ACF9
# define MIDDLE_ROYALBLUE_MAROON 0x005F94C5
# define MIDDLE_MAROON_GREENYELLOW 0x00806F80
# define MIDDLE_GREENYELLOW_NAVAJOWHITE 0x00E5FF9D
# define MIDDLE_NAVAJOWHITE_CYANBLUE 0x005A94C8
# define MIDDLE_CYANBLUE_DARKORANGE 0x006E9994
# define MIDDLE_DARKORANGE_DARKSEAGREEN 0x007CA260
# define MIDDLE_DARKSEAGREEN_PEACHPUFF 0x00C1DDA2
# define MIDDLE_PEACHPUFF_SLATEBLUE 0x00E38EAC
# define MIDDLE_SLATEBLUE_CHOCOLATE 0x00A46987
# define MIDDLE_CHOCOLATE_PERU 0x00DA9561
# define MIDDLE_PERU_TOMATO 0x00E38E7C
# define MIDDLE_TOMATO_MEDIUMSEAGREEN 0x008F8449
# define MIDDLE_MEDIUMSEAGREEN_MEDIUMSLATEBLUE 0x0052617E
# define MIDDLE_MEDIUMSLATEBLUE_DARKTURQUOISE 0x0034A0A8
# define MIDDLE_DARKTURQUOISE_DARKGOLDENROD 0x005C7D99
# define MIDDLE_DARKGOLDENROD_MEDIUMORCHID 0x006F8468
# define MIDDLE_MEDIUMORCHID_LIGHTCORAL 0x00C5A3AF
# define MIDDLE_LIGHTCORAL_LIGHTGOLDENRODYELLOW 0x00EBEDCD
# define MIDDLE_LIGHTGOLDENRODYELLOW_LIGHTSKYBLUE 0x008CDBC7
# define MIDDLE_LIGHTSKYBLUE_LIGHTSLATEGRAY 0x00A5C4D4
# define MIDDLE_LIGHTSLATEGRAY_LIGHTSTEELBLUE 0x00B8C7D7
# define MIDDLE_LIGHTSTEELBLUE_LIGHTCYAN 0x00C5DBE8
# define MIDDLE_LIGHTCYAN_LIGHTGRAY 0x00D6D6D6
# define MIDDLE_LIGHTGRAY_LINEN 0x00F1EFEF
# define MIDDLE_LINEN_PEACH 0x00FFDDC1
# define MIDDLE_PEACH_PALEGOLDENROD 0x00FFE5C2
# define MIDDLE_PALEGOLDENROD_PALEGREEN 0x00D4F6A3
# define MIDDLE_PALEGREEN_PALETURQUOISE 0x00A3E1B8
# define MIDDLE_PALETURQUOISE_PALEVIOLETRED 0x00C5B5B8
# define MIDDLE_PALEVIOLETRED_PAPAYAWHIP 0x00FED8CC
# define MIDDLE_PAPAYAWHIP_ROSYBROWN 0x00F8A89E
# define MIDDLE_ROSYBROWN_SANDYBROWN 0x00DDBFA5
# define MIDDLE_SANDYBROWN_BLUEVIOLET 0x008C6A7E
# define MIDDLE_BLUEVIOLET_CRIMSON 0x00D77B8E
# define MIDDLE_CRIMSON_FIREBRICK 0x00B77976
# define MIDDLE_FIREBRICK_LIGHTGOLDENROD 0x00E56068
# define MIDDLE_LIGHTGOLDENROD_LIGHTPINK 0x00FFAFAF
# define MIDDLE_LIGHTPINK_MEDIUMAQUAMARINE 0x00ABD1C2
# define MIDDLE_MEDIUMAQUAMARINE_MEDIUMSPRINGGREEN 0x006ECCB1
# define MIDDLE_MEDIUMSPRINGGREEN_MEDIUMTURQUOISE 0x005EEFD2
# define MIDDLE_MEDIUMTURQUOISE_MEDIUMVIOLETRED 0x00B98B8B
# define MIDDLE_MEDIUMVIOLETRED_ORCHID 0x00C388AA
# define MIDDLE_ORCHID_PALEGOLDENROD 0x00DCC6A3
# define MIDDLE_PALEGOLDENROD_PALEGREENYELLOW 0x00DCECB1
# define MIDDLE_PALEGREENYELLOW_ROYALBLUE 0x0075CEC1
# define MIDDLE_ROYALBLUE_SPRINGGREEN 0x006AD3AC
# define MIDDLE_SPRINGGREEN_TURQUOISE 0x004ECCD5
# define MIDDLE_TURQUOISE_YELLOWGREEN 0x0070CF87
# define MIDDLE_YELLOWGREEN_BURLYWOOD 0x0096B682
# define MIDDLE_BURLYWOOD_CORNSILK 0x00E1CBAA
# define MIDDLE_CORNSILK_DIMGRAY 0x006A6A6A
# define MIDDLE_DIMGRAY_GOLDENROD 0x009F9F61
# define MIDDLE_GOLDENROD_HONEYDEW 0x00F1F1E1
# define MIDDLE_HONEYDEW_IVORY 0x00FFFFF5
# define MIDDLE_IVORY_LAVENDERBLUSH 0x00FFF0F2
# define MIDDLE_LAVENDERBLUSH_MINTCREAM 0x00FAFAF5
# define MIDDLE_MINTCREAM_NAVY 0x00000090
# define MIDDLE_NAVY_OLDLACE 0x00FDF5EB
# define MIDDLE_OLDLACE_PALEGOLDENROD 0x00F9EFD2
# define MIDDLE_PALEGOLDENROD_PEACHPUFF2 0x00F6E4C3
# define MIDDLE_PEACHPUFF2_ROSYBROWN1 0x00FFD1D1
# define MIDDLE_ROSYBROWN1_SEASHELL2 0x00F5ECEB
# define MIDDLE_SEASHELL2_SNOW2 0x00F5F0F0
# define MIDDLE_SNOW2_TAN2 0x00F5E3A9
# define MIDDLE_TAN2_ALICEBLUE 0x00E2F3F3
# define MIDDLE_ALICEBLUE_CADETBLUE 0x007FAFBF
# define MIDDLE_CADETBLUE_CHARTREUSE 0x003F7F7F
# define MIDDLE_CHARTREUSE_DARKKHAKI 0x00A99975
# define MIDDLE_DARKKHAKI_GAINSBORO 0x00999999
# define MIDDLE_GAINSBORO_HOTPINK 0x00FF9CBB
# define MIDDLE_HOTPINK_LIGHTCORAL 0x00FBB4B4

# define DARK_AQUA 0x00008080
# define DARK_BEIGE 0x00F5F5DC
# define DARK_GOLD 0x00B8860B
# define DARK_LAVENDER 0x00808080
# define DARK_CORAL 0x00CD5C5C
# define DARK_MAUVE 0x00800080
# define DARK_OLIVE 0x00808000
# define DARK_SILVER 0x00808080
# define DARK_RED 0x008B0000
# define DARK_CYAN 0x00008B8B
# define DARK_INDIGO 0x00008080
# define DARK_GOLDENROD 0x008B6508
# define DARK_SEAGREEN 0x00008B45
# define DARK_TAN 0x008B4513
# define DARK_CORNFLOWER 0x000080ED
# define DARK_MEDIUMVIOLET 0x008B008B
# define DARK_SALMON 0x00E9967A
# define DARK_SKYBLUE 0x0087CEEB
# define DARK_LIME 0x0000FF00
# define DARK_SLATEGRAY 0x002F4F4F
# define DARK_VIOLET 0x008A2BE2
# define DARK_SPRINGGREEN 0x0000FF7F
# define DARK_ROYALBLUE 0x001325CD
# define DARK_MAROON 0x00800080
# define DARK_GREENYELLOW 0x0055FF00
# define DARK_NAVAJOWHITE 0x00FFDEAD
# define DARK_CYANBLUE 0x004169E1
# define DARK_DARKORANGE 0x00FF4500
# define DARK_DARKSEAGREEN 0x002E8B57
# define DARK_PEACHPUFF 0x00FFDAB9
# define DARK_SLATEBLUE 0x00483D8B
# define DARK_CHOCOLATE 0x008B4513
# define DARK_PERU 0x008B4513
# define DARK_TOMATO 0x00FF6347
# define DARK_MEDIUMSEAGREEN 0x003CB371
# define DARK_MEDIUMSLATEBLUE 0x007B68EE
# define DARK_DARKTURQUOISE 0x0000CED1
# define DARK_DARKGOLDENROD 0x00B8860B
# define DARK_MEDIUMORCHID 0x00BA55D3
# define DARK_INDIANRED 0x00CD5C5C
# define DARK_KHAKI 0x00F0E68C
# define DARK_DODGERBLUE 0x001E90FF
# define DARK_SLATEGRAY 0x002F4F4F
# define DARK_STEELBLUE 0x004682B4
# define DARK_TEAL 0x00008080
# define DARK_GRAY50 0x007F7F7F
# define DARK_ANTIQUEWHITE 0x00FAEBD7
# define DARK_MIDNIGHTBLUE 0x00191970
# define DARK_NAVAJOWHITE 0x00FFDEAD
# define DARK_ORCHID 0x009932CC
# define DARK_SADDLEBROWN 0x008B4513
# define DARK_SEASHELL 0x00FFF5EE
# define DARK_SNOW 0x00FFFAFA
# define DARK_THISTLE 0x00D8BFD8
# define DARK_WHEAT 0x00F5DEB3
# define DARK_BLUEVIOLET 0x008A2BE2
# define DARK_CRIMSON 0x00DC143C
# define DARK_FIREBRICK 0x00B22222
# define DARK_LIGHTGOLDENROD 0x00FFEC8B
# define DARK_LIGHTPINK 0x00FFB6C1
# define DARK_MEDIUMAQUAMARINE 0x0066CDAA
# define DARK_MEDIUMSPRINGGREEN 0x0000FA9A
# define DARK_MEDIUMTURQUOISE 0x0048D1CC
# define DARK_MEDIUMVIOLETRED 0x00C71585
# define DARK_PALEGOLDENROD 0x00EEE8AA
# define DARK_PALEGREENYELLOW 0x00ADFF2F
# define DARK_SPRINGGREEN 0x0000FF7F
# define DARK_TURQUOISE 0x0040E0D0
# define DARK_YELLOWGREEN 0x009ACD32
# define DARK_BURLYWOOD 0x00DEB887
# define DARK_CORNSILK 0x00FFF8DC
# define DARK_DIMGRAY 0x00696969
# define DARK_HONEYDEW 0x00F0FFF0
# define DARK_IVORY 0x00FFFFF0
# define DARK_LAVENDERBLUSH 0x00FFF0F5
# define DARK_MINTCREAM 0x00F5FFFA
# define DARK_NAVY 0x00000080
# define DARK_OLDLACE 0x00FDF5E6
# define DARK_PALEGOLDENROD 0x00EEE8AA
# define DARK_PEACHPUFF2 0x00EECBAD
# define DARK_ROSYBROWN1 0x00FFC1C1
# define DARK_SEASHELL2 0x00EEE5DE
# define DARK_SNOW2 0x00EEE9E9
# define DARK_TAN2 0x00EE9A49
# define DARK_ALICEBLUE 0x00F0F8FF
# define DARK_CADETBLUE 0x005F9EA0
# define DARK_CHARTREUSE 0x007FFF00
# define DARK_DARKKHAKI 0x00BDB76B
# define DARK_GAINSBORO 0x00DCDCDC
# define DARK_HOTPINK 0x00FF69B4
# define DARK_LIGHTCORAL 0x00F08080
# define DARK_LIGHTSLATEGREY 0x00778899
# define DARK_MEDIUMBLUE 0x000000CD
# define DARK_MEDIUMORCHID2 0x00D15FEE
# define DARK_MEDIUMSLATEBLUE 0x007B68EE
# define DARK_MEDIUMVIOLETRED 0x00C71585
# define DARK_MIDNIGHTBLUE 0x00191970
# define DARK_NAVYBLUE 0x00000080
# define DARK_PALETURQUOISE 0x00AFEEEE
# define DARK_PALEVIOLETRED 0x00DB7093

typedef enum s_scale
{
	MAPSIZE,
	SCREEN
}	t_scale;

typedef enum s_ray
{
	VERTICAL,
	HORIZONTAL
}	t_ray;

typedef enum s_dir
{
	NO_DIR,
	NORTH,
	SOUTH,
	EAST,
	WEST,
	NORTH_EAST,
	NORTH_WEST,
	SOUTH_EAST,
	SOUTH_WEST
}	t_dir;

typedef enum s_move
{
	DOWN,
	UP,
	TURN_LEFT,
	TURN_RIGHT,
	STRAFE_RIGHT,
	STRAFE_LEFT
}	t_move;

typedef enum s_error
{
	SUCCESS,
	NO_WALL_HIT
}	t_error;

typedef struct s_dist
{
	float			y0;
	float			x0;
	float			x1;
	float			y1;
}	t_dist;

typedef struct s_img
{
	char			*addr;
	int				bpp;
	int				l_l;
	int				endian;
}	t_img;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
}	t_mlx;

typedef struct s_line
{
	float			x0;
	float			y0;
	float			x1;
	float			y1;
	float			x_step;
	float			y_step;
	int				direction;
	int				x_inc;
	int				y_inc;	
	int				wall_height;
	int				scale;
	int				length;
	int				neg_size;
	int				max;
	int				step;
}	t_line;

typedef struct s_player
{
	float			x_pos;
	float			y_pos;
	int				x_screen_pos;
	int				y_screen_pos;
	float			angle;
	float			x_dir;
	float			y_dir;
	int				direction;
	float			x_prev;
	float			y_prev;
}	t_player;

typedef struct s_raycast
{
	int					map_x;
	int					map_y;
	int					map_pos;
	int					max_depth;
	int					direction;
	float				reach_x;
	float				reach_y;
	float				angle;
	float				inc_x;
	float				inc_y;
	float				a_tan;
	float				n_tan;
	struct s_dist		dist;
}	t_raycast;

typedef struct s_txtr
{
	void			*img;
	char			*addr;
	int				bpp;
	int				l_l;
	int				endian;
	int				width;
	int				height;
	int				color;
}	t_txtr;



typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}				t_color;

typedef struct s_font_inner
{
	t_txtr	*letter;
	int		del;
}				t_font_inner;

typedef struct s_font
{
	t_font_inner	xl_font;
	t_font_inner	big_font;
	t_font_inner	medium_font;
	t_font_inner	small_font;
}				t_font;

typedef struct s_cords
{
	int	copy_x;
	int	copy_y;
	int	img_x;
	int	img_y;
}				t_cords;

typedef struct s_data t_data;

typedef struct s_button
{
	t_txtr	*img;
	int		del;
	int		curr;
	int		iden;
	int		active;
	int		activate;
	int		posx;
	int		posy;
	int		button_clicked;
	int		(*function)(t_data *, int i);
}				t_button;

typedef struct s_gif
{
	t_txtr	*img;
	t_txtr	*display;
	int		posx;
	int		posy;
	int		curr;
	int		del;
}				t_gif;


typedef struct s_font_setting
{
	int	x;
	int	y;
	int	color;
	int	identifier;
}				t_font_setting;



typedef struct s_data
{
	int					view_dir;
	int					ceiling_color;
	int					floor_color;
	int					map_width;
	int					map_height;
	int					map_size;
	int					win_width;
	int					win_height;
	int					line_color;
	float				line_height;
	float				line_offset;
	float				target_line_height;
	float				x_scale;
	float				y_scale;
	float				fisheye;
	float				min_distance;
	float				hit_pos;
	float				angle;
	int					hit;
	int					*map;
	int					gifs;
	int					button_index;
	int					clicked;
	struct s_txtr		pepe;
	struct s_txtr		walltest;
	struct s_txtr		brick;
	struct s_txtr		stone;
	struct s_txtr		wood;
	struct s_txtr		grass;
	struct s_txtr		metal;
	struct s_txtr		wall1;
	struct s_txtr		wall2;
	struct s_txtr		wall3;
	struct s_txtr		wall4;
	struct s_txtr		wall5;
	struct s_txtr		wall6;
	struct s_txtr		wall7;
	struct s_txtr		wall8;
	struct s_player		player;
	struct s_mlx		mlx;
	struct s_img		img;
	struct s_line		shortest_line;
	struct s_gif		**gif;
	struct s_button		**button;
	struct s_font		*font;
	struct s_cords		cords;
}	t_data;

//init
void	set_data_view(t_data *data);

//map
void	draw_map(t_data *data);
void	draw_player(t_data *data);
void	initialize_data(t_data *data);
int		isdirection(char c);
void	set_directions(t_data *data);

//raycaster
void	raycast(t_data *data);
void	get_3d_line(t_line *line1, int i, t_data *data);
void	adjust_vars(t_data *data, float angle);
void	init_vars_horizontal(t_raycast *h_ray, t_player *player, float angle);
void	get_line(t_line *line, t_raycast ray, t_data *data);
void	scan(t_raycast *ray, t_data *data, int max);
void	init_vars_vertical(t_raycast *v_ray, t_player *player, float angle);
void	draw_texture(t_data *data, int x, t_line line, t_txtr *texture);
bool	collision(t_data *data, float new_x, float new_y);
void	set_texture(t_data *data, t_txtr *texture);

//math_utils
void	normalize_angle(float *angle, float increment);
void	calculate_distance(t_data *data, t_line line1, t_line line2);
float	dist(t_line line);

//drawing_utils
void	put_pixel(t_data *data, int x, int y, int color);
t_line	draw_rays_horizontal(t_data *data, float angle);
void	draw_circle(t_data *data, int x, int y, int size);
void	draw_line(t_data *data, t_line line, int color, int size);
void	draw_background(t_data *data);

//memory management/mlx
void	start_games(t_data *data);
void	initialize_textures(t_data *data);
void	exit_failure(t_data *data, char *msg);
int		exit_success(t_data *data);
void	new_image(t_data *data);

//tests
int		*get_map(void);
int		print_test_raycasting(t_data *data, int loopbreak, int direction,
			t_raycast *ray);
// void	print_test(t_data *data, int color, int value, int x, int y);

//game
int		event(int key, t_data *data);
void	init_line(t_line *line, t_data *data, int length);




t_font			*font_init(void *mlx);
int				font_write(char *word, t_data *game, t_font_setting f_setting);
int				font_write_img(char *w, t_data *g, t_txtr *c, t_font_setting f);
t_font_setting	font_settings(int posx, int posy, int color, int identifier);
void			font_delete(t_data *game);

// image edit //
// void	image_edit(t_game *g, t_img *base, t_img to_copy, int identifier);


/*	Buttons	*/
int			*button_init(t_data *game, char *path, int (*f)(t_data *, int));
void		button_delete(t_data *game, void *mlx);
int			button_change_function(int (*f)(t_data *, int i), t_data *game, int i);
int			button_change_position(t_data *game, int posx, int posy, int iden);
int			button_switch(t_data *game, int i);
int			say(t_data *temp, int i);
int			int_exit(t_data *game, int i);
int			button_animation(void *data);
int			button_loop(t_data *game);

/*	Gif	*/
void		gif_loop(t_data *game);
void		gif_delete(t_data *game, void *mlx);
int			gif_init(t_data *game, char *path, int posx, int posy);

/*	Image edit	*/
void		image_edit(t_data *g, t_txtr *base, t_txtr to_copy, int identifier);

#endif