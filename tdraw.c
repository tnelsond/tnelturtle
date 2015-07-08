/* Copyright (C) 2011 Tnelsond */
/* read license.txt for more info */

#include <math.h>
#include "SDL.h"
#include "tdraw.h"

double t_cos(double angle)
{
	return cos(angle * TPI / 180.0); /* Used my own value of pi because it is more precise */
}

double t_sin(double angle)
{
	return sin(angle * TPI / 180.0);
}

void t_SetPixel(SDL_Surface *surface, int x, int y, Uint32 color)
{
	if (t_OnScreen(x, y, surface->w, surface->h))
	{
		Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * (BITSPERPIXEL / 8);
		*(Uint32 *)target_pixel = color;
	}
}

void t_DrawLine(SDL_Surface *surface, int x0, int y0, int x1, int y1, Uint32 color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	for ( ;; )
	{
		int e2 = 2 * err;
		t_SetPixel(surface, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break; /* It's the cleanest way to write this */
		if (e2 > -dy)
		{
			err = err - dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err = err + dx;
			y0 += sy;
		}

	}
}

/* Based off code from http://gpwiki.org/index.php/SDL:Tutorials:Drawing_and_Filling_Circles */
void t_FillCircle(SDL_Surface *surface, t_Circle *circle, Uint32 color)
{
	double r = circle->r;
	double dy;
	for (dy = 1; dy <= r; dy += 1)
	{
		double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
		int x = circle->x - dx;
		
		int t_y1 = ((int)(circle->y + r - dy));
		int t_y2 = ((int)(circle->y - r + dy));
		
		for (; x <= circle->x + dx; x++)
		{
			t_SetPixel(surface, x, t_y1, color);
			t_SetPixel(surface, x, t_y2, color);
		}
	}
}

/* Draws a cute little turtle. TODO: The code isn't cute, it's horrendous */
void t_DrawTurtle(SDL_Surface *surface, t_Turtle *t)
{
	int i; /* For drawing the spots on the turtle's shell */
	t_Circle temp;
	double angle_offset = 180/12.0;	
	
	/* Draws the head */
	set_circle(temp, t_cos(t->angle) * t->circle.r + t->circle.x, t_sin(t->angle) * t->circle.r + t->circle.y, t->circle.r/2);
	t_FillCircle(surface, &temp, 0x66BB00);
	/* Draw the Eyes */
	set_circle(temp, t_cos(t->angle + angle_offset) * t->circle.r * 1.2 + t->circle.x, t_sin(t->angle + angle_offset) * t->circle.r * 1.2 + t->circle.y, t->circle.r/9);
	t_FillCircle(surface, &temp, 0x000000);
	angle_offset = -angle_offset;
	set_circle(temp, t_cos(t->angle + angle_offset) * t->circle.r * 1.2 + t->circle.x, t_sin(t->angle + angle_offset) * t->circle.r * 1.2 + t->circle.y, t->circle.r/9);
	t_FillCircle(surface, &temp, 0x000000);
	/* Draw the legs and half the tail */
	angle_offset = 0;
	for (i = 0; i < 5; i++)
	{
		angle_offset += 60;
		set_circle(temp, t_cos(t->angle + angle_offset) * t->circle.r + t->circle.x, t_sin(t->angle + angle_offset) * t->circle.r + t->circle.y, t->circle.r/3);
		t_FillCircle(surface, &temp, 0x66BB00);
	}
	/* Draw the second half of the tail */
	angle_offset = 180;
	set_circle(temp, t_cos(t->angle + angle_offset) * (t->circle.r * 5 / 4) + t->circle.x, t_sin(t->angle + angle_offset) * (t->circle.r * 5 / 4) + t->circle.y, t->circle.r/5);
	t_FillCircle(surface, &temp, 0x66BB00);
	/* Draw the shell */
	t_FillCircle(surface, &t->circle, 0x998800);
	/* Draw the spots on the shell */
	angle_offset = 0;
	for (i = 0; i < 10; i++)
	{
		angle_offset += 36;
		set_circle(temp, t_cos(t->angle + angle_offset) * (t->circle.r/1.5) + t->circle.x, t_sin(t->angle + angle_offset) * (t->circle.r/1.5) + t->circle.y, t->circle.r/5);
		t_FillCircle(surface, &temp, 0x777700);
	}
	/* Draw the big spot on the shell */
	set_circle(temp, t->circle.x, t->circle.y, t->circle.r/3);
	t_FillCircle(surface, &temp, 0x777700);
}
