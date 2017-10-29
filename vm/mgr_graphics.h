/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgr_graphics.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoung-w <byoung-w@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:26:46 by byoung-w          #+#    #+#             */
/*   Updated: 2017/10/19 15:32:45 by byoung-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MGR_GRAPHICS_H
# define MGR_GRAPHICS_H
# include "matrix.h"
# include "libft/libft.h"
# include "vm.h"
# include <time.h>
# include <stdlib.h>
# include <ncurses.h>
# ifdef __MACH__
#  include <mach/clock.h>
#  include <mach/mach.h>
# endif
# define _POSIX_C_SOURCE >= 199309L
# define WHITE_PAIR 1
# define GREEN_PAIR 2
# define YELLOW_PAIR 3
# define RED_PAIR 4
# define MAGENTA_PAIR 5
# define MA_PAIR 5
# define WORLD_WIDTH 254
# define WORLD_HEIGHT 68
# define APP_REFRESH_RATE 10
# define MAT_REFRESH_RATE 50
# define FRAMES_PER_SECOND 60
# define SKIP_TICKS 1000 / FRAMES_PER_SECOND
# define APP_KEY_UP 65
# define APP_KEY_DOWN 66
# define APP_KEY_LEFT 68
# define APP_KEY_RIGHT 67
# define APP_KEY_SPACE 32
# define APP_KEY_SPECIAL 91
# define APP_KEY_ESC 27
# define APP_KEY_INVALID -1
# define BOARD_WIDTH 64
# define BOARD_SPACING 1
# define BOARD_HEIGHT 64
# define BOARD_CELL_LENGTH 2

#ifdef WIN32
#else
typedef long					DWORD;
typedef unsigned long			UWORD;
typedef unsigned short			WORD;
typedef unsigned int			UNINT32;
#endif

typedef struct			s_graphics
{
	WINDOW				*game_window;
	WINDOW				*border_window;
	WINDOW				*background_window;
	int					offsetx;
	int					offsety ;
	int					max_y;
	int					max_x;
	int					margin_x;
	int					margin_y;
	bool				graphics_end;
	int					i;
	int					j;
	int					flag;
	t_matrix			*mat;
	struct s_column		*col;
	int					window_x;
	int					window_y;
	int					window_index;
	bool				app_is_running;
	int					key_pressed;
	DWORD				start_time;
	DWORD				next_app_tick;
	DWORD				current;
	DWORD				elapsed;
	DWORD				seconds;
	DWORD				seconds2;
	DWORD				sleep_time;
	char				hex[3];
	char				*buffer;
}						t_graphics;

void					graphics_start(t_graphics *g);
void					graphics_end(t_graphics *g);
void					render_start(t_graphics *g);
void					render_end(t_graphics *g);
void					graphics_print_message(t_graphics *g, char *str);

bool					keyboard_event();
void					get_keyboard_event(t_graphics *g);
void					update_app(t_graphics *g, t_env *e);
void					display_app(t_graphics *g, t_env *e);
void					graphics_loop(t_env *e);

DWORD					GetTickCount();
void					render_board(t_graphics *g, t_env *e);
void					render_log(t_graphics *g, t_env *e);
void					render_player(t_graphics *g, t_env *e);
void					render_process(t_graphics *g, t_env *e);
void					render_stats(t_graphics *g, t_env *e);
#endif