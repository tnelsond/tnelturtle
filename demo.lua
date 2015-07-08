dofile("text.lua")

delay(0)
pencolor(0xcccc00)
moveto(320, 160)
numsides = 24
for i=1, numsides do
	penup()
	fd(20)
	tr(360/numsides)
	pendown()
	local x, y = loc()
	tr(-90)
	twrite(" sunshine", 8 + 3 * (i % 2))
	tr(90)
	moveto(x, y)
end

pencolor(0x00cc00)
moveto(0, 480)
turnto(45)
for j=1, 2 do
	for i=1, 40 do
		tr(-90)
		fd(20)
		tr(90)
		fd(20)
	end
end	

moveto(320, 240)
