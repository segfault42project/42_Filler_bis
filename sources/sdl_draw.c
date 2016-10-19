#include "../include/filler.h"

static void	draw_square(SDL_Renderer *render, int width_x, int width_y, int pos_x, int pos_y)
{
	int x;
	int y;

	y = pos_y;
	while (y < width_y + pos_y)
	{
		x = pos_x;
		while (x < width_x + pos_x)
		{
			SDL_RenderDrawPoint(render, x, y);
			++x;
		}
		++y;
	}
}

static void	draw_grille(t_env *env, t_win *win, int	map_x, int map_y)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	SDL_SetRenderDrawColor(win->render, 0, 0, 0, 255);
	SDL_SetRenderDrawColor(win->render2, 0, 0, 0, 255);
	while (y < map_y)
	{
		SDL_RenderDrawLine(win->render, 0, y, map_x, y);
		SDL_RenderDrawLine(win->render2, 0, y, map_x, y);
		y += win->size_plateau;
	}
	while (x < map_x)
	{
		SDL_RenderDrawLine(win->render, x, 0, x, map_y);
		SDL_RenderDrawLine(win->render2, x, 0, x, map_y);
		x += win->size_plateau;
	}
}


void	sdl_init(t_win *win, t_env *env, char *argv)
{
	win->loop = 1;
	if (env->size_map_x < 25 )
		win->size_plateau = 30;
	else if (env->size_map_x >= 25 && env->size_map_x < 70)
		win->size_plateau = 20;
	else
		win->size_plateau = 8;
	win->size_piece = win->size_plateau;
	init_window(env->size_map_x * win->size_plateau,
						  env->size_map_y * win->size_plateau, win);
	if (argv != NULL && ft_strstr(argv, "s") != NULL)
	{
		SDL_Init(SDL_INIT_AUDIO);
		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
		win->music = Mix_LoadMUS("./media/sound/Music2.mp3");
		Mix_PlayMusic(win->music, -1);
		Mix_AllocateChannels(1);
		Mix_Volume(1, MIX_MAX_VOLUME);
		win->plop = Mix_LoadWAV("./media/sound/plop.wav");
	}
}

int	event(t_env *env, t_bonus *bonus, t_win *win, char *argv)
{
	SDL_Event	event;

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			quit_filler(env, bonus, win, argv);
		if (event.key.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			if (event.key.keysym.sym == SDLK_SPACE)
				SDL_Delay(2000);
			if (event.key.keysym.sym == SDLK_ESCAPE)
				quit_filler(env, bonus, win, argv);
		}
	}
	return (0);
}

static void	draw_piece(t_win *win, t_env *env)
{
	int	x;
	int	y;

	y = 0;
	while (y < env->size_form_y)
	{
		x = 0;
		while (x < env->size_form_x)
		{
			SDL_SetRenderDrawColor(win->render2, 100, 100, 100, 255);
			if (env->piece[y][x] == '.')
				draw_square(win->render2, win->size_piece, win->size_piece,
									(x * win->size_piece),
									(y * win->size_piece));
			else if (env->piece[y][x] == '*')
			{
				SDL_SetRenderDrawColor(win->render2, 156, 100, 200, 255);
				draw_square(win->render2, win->size_piece, win->size_piece,
									(x * win->size_piece),
									(y * win->size_piece));
			}
			++x;
		}
		++y;
	}
	/*SDL_SetWindowSize(win->win2, x * win->size_piece, y * win->size_piece);*/
}

void	draw(t_win *win, t_env *env)
{
	int	x;
	int	y;

	y = 0;
	sdl_clear(win);
	while (y < env->size_map_y)
	{
		x = 0;
		while (x < env->size_map_x)
		{
			SDL_SetRenderDrawColor(win->render, 100, 100, 100, 255);
			if (env->map[y][x] == '.')
				draw_square(win->render, win->size_plateau, win->size_plateau,
									 x * win->size_plateau, y * win->size_plateau);
			else if (env->map[y][x] == 'X' || env->map[y][x] == 'x')
			{
				SDL_SetRenderDrawColor(win->render, 255, 0, 0, 255);
				draw_square(win->render, win->size_plateau, win->size_plateau,
									 x * win->size_plateau, y * win->size_plateau);
			}
			else if (env->map[y][x] == 'O' || env->map[y][x] == 'o')
			{
				SDL_SetRenderDrawColor(win->render, 0, 255, 0, 255);
				draw_square(win->render, win->size_plateau, win->size_plateau,
									 x * win->size_plateau, y * win->size_plateau);
			}
			++x;
		}
		++y;
	}
	draw_piece(win, env);
	draw_grille(env, win, env->size_map_x * win->size_plateau, env->size_map_y * win->size_plateau);
	draw_grille(env, win, (env->size_map_x * win->size_plateau) * 2, (env->size_map_y * win->size_plateau));
	SDL_RenderPresent(win->render);
	SDL_RenderPresent(win->render2);
}

