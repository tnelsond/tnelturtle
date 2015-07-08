/* Copyright (C) 2011 Tnelsond */
/* read license.txt for more info */

#ifndef TDRAW
#define TDRAW

#define BITSPERPIXEL 32
#define TPI 3.14159265358979323846264
#define sq(a) (a) * (a)
#define MAX(a, b) (a > b) ? a : b
#define set_rect(rect, a, b, c, d) \
rect.x = a; \
rect.y = b; \
rect.w = c; \
rect.h = d
#define set_circle(circle, a, b, c) \
circle.x = a; \
circle.y = b; \
circle.r = c
#define t_OnScreen(x, y, width, height) !(x < 0 || x >= width || y < 0 || y >= height)
#define set_point(point, a, b) point.x = a; point.y = b

typedef struct t_Circle t_Circle;
struct t_Circle
{
	double x;
	double y;
	int r; /* Radius */
};


typedef struct t_Point t_Point;
struct t_Point
{
	double x;
	double y;
};

typedef struct t_Turtle t_Turtle;
struct t_Turtle
{
	t_Circle circle;
	t_Point oldpos;
	double angle; /* In Degrees */
	int iswriting;
	Uint32 writingcolor;
};

double t_cos(double angle);

double t_sin(double angle);

void t_SetPixel(SDL_Surface *surface, int x, int y, Uint32 color);

void t_DrawLine(SDL_Surface *surface, int x0, int y0, int x1, int y1, Uint32 color);

void t_FillCircle(SDL_Surface *surface, t_Circle *circle, Uint32 color);

void t_DrawTurtle(SDL_Surface *surface, t_Turtle *t);

#endif
