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
# include "libft/libft.h"
# include "vm.h"
# include <ncurses.h>
# ifdef __MACH__
#  include <mach/clock.h>
#  include <mach/mach.h>
# endif
# define _POSIX_C_SOURCE >= 199309L
# define GREEN_PAIR 1
# define YELLOW__PAIR 2
# define WORLD_WIDTH 254
# define WORLD_HEIGHT 68
# define APP_REFRESH_RATE 500
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
	int					offsetx;
	int					offsety ;
	int					max_y;
	int					max_x;
	short				line_colors[3];
	short				title_colors[3];
	int					margin_x;
	int					margin_y;
	bool				graphics_end;
	int					i;
	int					j;
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
	DWORD				sleep_time;
}						t_graphics;

void					Graphics_Start(t_graphics *g);
void					Graphics_End(t_graphics *g);
void					Render_Start(t_graphics *g);
void					Render_End(t_graphics *g);
void					graphics_print_message(t_graphics *g, char *str);

bool					keyboard_event();
void					get_keyboard_event(t_graphics *g);
void					update_app(t_graphics *g, t_env *e);
void					display_app(t_graphics *g, t_env *e);
void					graphics_loop(t_env *e);

DWORD					GetTickCount();
void					Render_Board(t_graphics *g, t_env *e);
void					Render_Log(t_graphics *g, t_env *e);
void					Render_Player(t_graphics *g, t_env *e);
void					Render_Process(t_graphics *g, t_env *e);
void					Render_Stats(t_graphics *g, t_env *e);
#endif