/* Copyright (C) 2011 Tnelsond */
/* read license.txt for more info */

#include "SDL.h"
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "tdraw.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

lua_State *l; /* Lua */
Uint32 bgcolor;

t_Turtle turtle;
SDL_Surface *screen, *drawingboard;
unsigned int time_delay;
int running;
SDL_Event event;

void t_cleanupandexit()
{
		SDL_FreeSurface(drawingboard);
		SDL_Quit();
		exit(0);
}

void t_Draw()
{
		SDL_BlitSurface(drawingboard, NULL, screen, NULL);
		t_DrawTurtle(screen, &turtle);
		SDL_Flip(screen);
}

/* 0 means stop running, 1 means keep running */
void t_Process(int timemultiplier)
{	
		Uint32 next_time = SDL_GetTicks() + time_delay * abs(timemultiplier);
		int diff_time;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				t_cleanupandexit();	
		}
		t_Draw();
		diff_time = next_time - SDL_GetTicks();
		if (diff_time > 0)
		{
			SDL_Delay(diff_time);
		}
}

int tl_delay(lua_State *l)
{
	if (lua_gettop(l) >= 0)
	{
		time_delay = (int) lua_tonumber(l, -1);
	}
	return 0;
}

int tl_fd(lua_State *l)
{
	double length;
	if (lua_gettop(l) >= 0)
	{
		length = lua_tonumber(l, -1);
		set_point(turtle.oldpos, turtle.circle.x, turtle.circle.y);
		turtle.circle.x += t_cos(turtle.angle) * length;
		turtle.circle.y += t_sin(turtle.angle) * length;
		if (turtle.iswriting)
			t_DrawLine(drawingboard, (int)(turtle.oldpos.x + .5), (int)(turtle.oldpos.y + .5), (int)(turtle.circle.x + .5), (int)(turtle.circle.y + .5), turtle.writingcolor);
	}
	t_Process(length);
	return 0;
}

int tl_tr(lua_State *l)
{
	double old_angle = turtle.angle;
	if (lua_gettop(l) >= 0)
	{
		if (lua_isnumber(l, -1))
			turtle.angle += lua_tonumber(l, -1);
	}
	t_Process(turtle.angle - old_angle);
	return 0;
}

int tl_penup(lua_State *l)
{
	turtle.iswriting = 0;
	return 0;
}

int tl_pendown(lua_State *l)
{
	turtle.iswriting = 1;
	return 0;
}

int tl_growto(lua_State *l)
{
	int old_size = turtle.circle.r;
	if (lua_gettop(l) >= 0 && lua_isnumber(l, -1))
			turtle.circle.r = lua_tonumber(l, -1);
	t_Process(turtle.circle.r - old_size);
	return 0;
}

int tl_setpencolor(lua_State *l)
{
	if (lua_gettop(l) >= 0 && lua_isnumber(l, -1))
			turtle.writingcolor = lua_tonumber(l, -1);
	return 0;
}

int tl_moveto(lua_State *l)
{
	if(lua_gettop(l) >= 1 && lua_isnumber(l, -1) && lua_isnumber(l, -2))
	{
			turtle.circle.x = lua_tonumber(l, -2);
			turtle.circle.y = lua_tonumber(l, -1);
	}
	return 0;
}

int tl_move(lua_State *l)
{
	if(lua_gettop(l) >= 1 && lua_isnumber(l, -1) && lua_isnumber(l, -2))
	{
			turtle.circle.x += lua_tonumber(l, -2);
			turtle.circle.y += lua_tonumber(l, -1);
	}
	return 0;
}

int tl_turnto(lua_State *l)
{
	if(lua_gettop(l) >= 1 && lua_isnumber(l, -1))
			turtle.angle = lua_tonumber(l, -1);
	return 0;
}

int tl_angle(lua_State *l)
{
	lua_pushnumber(l, turtle.angle);
	return 1;
}

int tl_loc(lua_State *l)
{
	lua_pushnumber(l, turtle.circle.x);
	lua_pushnumber(l, turtle.circle.y);
	return 2;
}

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		bgcolor = 0xEEEEDD;
		turtle.writingcolor = 0x00aaFF;
		running = 1;
		turtle.iswriting = 1;
		if (SDL_Init(SDL_INIT_VIDEO) == -1)
			return -1;
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, BITSPERPIXEL, SDL_SWSURFACE | SDL_DOUBLEBUF);
		if (screen == NULL)
			return -2;
	
		drawingboard = SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h, BITSPERPIXEL, 0, 0, 0, 0);
		SDL_FillRect(drawingboard, NULL, bgcolor);
		SDL_WM_SetCaption("TnelTurtle", NULL);
	
		l = luaL_newstate();
		luaL_openlibs(l);

		lua_register(l, "fd", tl_fd);
		lua_register(l, "tr", tl_tr);
		lua_register(l, "turnto", tl_turnto);
		lua_register(l, "penup", tl_penup);
		lua_register(l, "pendown", tl_pendown);
		lua_register(l, "growto", tl_growto);
		lua_register(l, "pencolor", tl_setpencolor);
		lua_register(l, "delay", tl_delay);
		lua_register(l, "moveto", tl_moveto);
		lua_register(l, "move", tl_move);
		lua_register(l, "angle", tl_angle);
		lua_register(l, "loc", tl_loc);

		turtle.angle = 0;
		set_circle(turtle.circle, screen->w / 2, screen->h / 2, 20);
		time_delay = 3;
		t_Draw();
		SDL_Delay(500);

		if(luaL_dofile(l, argv[1]))
			error(l, "cannot run lua script: %s", lua_tostring(l, -1));
		lua_close(l);
		printf("Closed lua\n");

		time_delay = 500;
		while (running)
			t_Process(1);
			
	}
	else
		fprintf(stderr, "%s must be called followed by a lua file as an argument.\n", argv[0]);

	return 0;
}
