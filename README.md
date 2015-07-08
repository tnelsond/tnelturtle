Tnelturtle
==========

This program is written in C using [SDL](https://www.libsdl.org/) and [Lua](http://lua.org).

To compile the program run: make

To run the program execute it from the command line with a .lua file as an argument.

*On Linux:
./tnelturtle.out demo.lua

*On Windows:
tnelturtle.out demo.lua

The commands that Tnelturtle accepts in the lua file are:

* fd(length)
 : Moves the turtle forward length number of pixels
* tr(degrees)
 : Turns the turtle clockwise by degrees
* turnto(degrees)
 : Turns the turtle clockwise by degrees from 0
* penup()
 : Makes the turtle stop writing
* pendown()
 : Makes the turtle start writing, turtle is writing by default
* growto(radius)
 : Changes the turtle's radius/size
* pencolor(color)
 : Changes the turtle's pencolor using a hexadecimal color (0xF9a103) as an argument
* delay(delayfactor)
 : Sets the turtle's delay in between commands by a delay factor
* moveto(x, y)
 : Moves the turtle to the position (x, y) on the screen. (0, 0) is the upper left hand corner
* move(x, y)
 : Move the turtle (x, y) relative to his current location
* angle()
 : Gets the current angle of the turtle
* loc()
 : Gets the current location of the turtle as (x, y)
