function circle(diameter, fraction)
	local a = angle()
	local length = diameter * math.pi * fraction 
	local turn = 360 / length * fraction
	for i=1,length,1 do
		fd(1)
		tr(turn)
	end
	turnto(a + 360 * fraction)
end

sym = {} -- table to hold all our symbols and how to draw them

sym["a"] = function (size)
	diag = size * 2 / math.sqrt(3)
	tr(-60)
	fd(diag)
	tr(120)
	fd(diag/2)
	tr(120)
	fd(diag/2)
	fd(-diag/2)
	tr(-120)
	fd(diag/2)
	tr(-60)
end

sym["b"] = function (size)
	tr(-90)
	fd(size)
	tr(90)
	fd(size * .75)
	circle(size/2, 1/2)
	fd(size * .75)
	tr(180)
	fd(size * .75)
	circle(size/2, 1/2)
	fd(size * .75)
	tr(180)
end

sym["c"] = function (size)
	penup()
	fd(size)
	tr(180)
	pendown()
	fd(size/2)
	circle(size, 1/2)
	fd(size/2)
	tr(90)
end

sym["d"] = function (size)
	tr(-90)
	fd(size)
	tr(90)
	fd(size/2)
	circle(size, 1/2)
	fd(size/2)
	tr(180)
end

sym["e"] = function (size)
	tr(-90)
	fd(size)
	tr(90)
	fd(size)
	penup()
	tr(90)
	fd(size/2)
	pendown()
	tr(90)
	fd(size)
	tr(-90)
	fd(size/2)
	tr(-90)
	fd(size)
end

sym["f"] = function (size)
	tr(-90)
	fd(size)
	tr(90)
	fd(size)
	tr(90)
	penup()
	fd(size/2)
	tr(90)
	pendown()
	fd(size)
	tr(-90)
	fd(size/2)
	tr(-90)
end

sym["g"] = function (size)
	sym_c(size)
	tr(-90)
	fd(size/2)
	tr(-90)
	fd(size/2)
	tr(180)
end

sym["h"] = function (size)
	tr(-90)
	fd(size)
	tr(180)
	fd(size/2)
	tr(-90)
	fd(size)
	tr(-90)
	fd(size/2)
	fd(-size)
	tr(90)
end

sym["i"] = function (size)
	fd(size)
	fd(-size/2)
	tr(-90)
	fd(size)
	tr(-90)
	fd(size/2)
	fd(-size)
end

sym["j"] = function (size)
	penup()
	fd(size/2)
	tr(-90)
	fd(size/4)
	tr(180)
	pendown()
	halfc(size/2)
	tr(90)
	penup()
	fd(size/2)
	tr(-90)
	pendown()
	fd(size*.75)
	tr(-90)
	fd(size/2)
	fd(-size)
	tr(-90)
end

sym["k"] = function (size)
	tr(-90)
	fd(size)
	fd(-size/2)
	local angle = math.deg(math.atan(2))
	local diag = size * math.sqrt(5) / 2
	tr(angle)
	fd(diag)
	fd(-diag)
	tr(-2*angle + 180)
	fd(diag)
	tr(2*angle + 205)
end

sym["l"] = function (size)
	tr(-90)
	fd(size)
	fd(-size)
	tr(90)
	fd(size*3/4)
end

sym["m"] = function (size)
	tr(-90)
	fd(size)
	tr(150)
	local diag = size * 2 / math.sqrt(3)
	fd(diag)
	tr(-120)
	fd(diag)
	tr(150)
	fd(size)
	tr(-90)
end

sym["n"] = function (size)
	tr(-90)
	fd(size)
	tr(135)
	local diag = size * math.sqrt(2)
	fd(diag)
	tr(-135)
	fd(size)
	fd(-size)
	tr(90)
end

sym["o"] = function (size)
	penup()
	fd(size/2)
	tr(180)
	pendown()
	circle(size, 1)
	tr(180)
end

sym["p"] = function (size)
	tr(-90)
	fd(size)
	tr(90)
	fd(size*3/4)
	circle(size/2, 1/2)
	fd(size*3/4)
	tr(-90)
end

sym["q"] = function (size)
	sym["o"](size)
	tr(-135)
	fd(size / 2)
end

sym["r"] = function (size)
	sym["p"](size)
	local diag = size * math.sqrt(5) / 2
	local angle = math.deg(math.atan(2)) + 90
	tr(-angle)
	fd(diag)
end

sym["s"] = function (size)
	penup()
	fd(size * 3 / 4)
	tr(-90)
	fd(size/2)
	tr(-90)
	pendown()
	fd(size/2)
	circle(size/2, 1/2)
	fd(size/2)
	circle(size/2, 1/4)
	penup()
	fd(size/4)
	tr(-90)
	fd(-size/4)
	pendown()
	circle(size/2, 1/2)
	fd(size/2)
	circle(size/2, 1/4)
end

sym["t"] = function (size)
	penup()
	tr(-90)
	fd(size)
	pendown()
	tr(90)
	fd(size)
	fd(-size/2)
	tr(90)
	fd(size)
	tr(-90)
end

sym["u"] = function (size)
	penup()
	fd(size)
	tr(-90)
	pendown()
	sym["c"](size)
end

sym["v"] = function (size)
	local diag = size * 2 / math.sqrt(3)
	penup()
	tr(-90)
	fd(size)
	pendown()
	tr(150)
	fd(diag)
	tr(-120)
	fd(diag)
	tr(150)
end

sym["w"] = function (size)
	penup()
	fd(size)
	tr(-90)
	fd(size)
	tr(-90)
	pendown()
	sym["m"](size)
end

sym["x"] = function (size)
	local diag = math.sqrt(2) * size
	tr(-45)
	fd(diag)
	fd(-diag/2)
	tr(-90)
	fd(diag/2)
	fd(-diag)
	tr(135)
end

sym["y"] = function (size)
	local diag = math.sqrt(2) * size
	tr(-45)
	fd(diag)
	fd(-diag/2)
	tr(-90)
	fd(diag/2)
end

sym["z"] = function (size)
	local diag = math.sqrt(2) * size
	tr(-45)
	fd(diag)
	tr(-135)
	fd(size)
	penup()
	tr(-90)
	fd(size)
	tr(-90)
	pendown()
	fd(size)
end

sym["."] = function (size)
	penup()
	fd(size/2)
	tr(180)
	pendown()
	circle(size/4, 1)
	tr(180)
end

sym[","] = function (size)
	penup()
	fd(size/2)
	tr(-90)
	fd(size/2)
	tr(180)
	pendown()
	circle(size, 1/4)
	tr(180)
end

sym["1"] = function (size)
	fd(size/2)
	tr(-90)
	fd(size)
	tr(-135)
	fd(size/3)
	fd(-size/3)
	tr(135)
	fd(-size)
	tr(90)
	fd(size/2)
end

sym["3"] = function (size)
	penup()
	tr(-90)
	fd(size)
	tr(90)
	pendown()
	fd(size * .75)
	circle(size/2, 1/2)
	fd(size * .75)
	tr(180)
	fd(size * .75)
	circle(size/2, 1/2)
	fd(size * .75)
	tr(180)
end

sym["4"] = function (size)
	penup()
	tr(-90)
	fd(size)
	pendown()
	fd(-size/2)
	tr(90)
	fd(size)
	tr(-90)
	fd(size/2)
	fd(-size)
	tr(90)
end


sym["+"] = function (size)
	penup()
	tr(-90)
	fd(size/2)
	pendown()
	tr(90)
	fd(size)
	fd(-size/2)
	tr(-90)
	fd(size/2)
	fd(-size)
end

sym["="] = function (size)
	penup()
	tr(-90)
	fd(size/4)
	tr(90)
	pendown()
	fd(size)
	tr(-90)
	penup()
	fd(size/2)
	pendown()
	tr(90)
	fd(-size)
	fd(size)
end

sym["-"] = function (size)
	penup()
	tr(-90)
	fd(size/2)
	tr(90)
	pendown()
	fd(size)
end

function twrite(message, size)
	local x, y = loc()
	local theta = angle()
	local csym = 0
	message = tostring(message)
	message = message:lower()
	for i=0, message:len() + 1 do
		c = message:sub(i, i)
		if c == '\n' then 
			y = y + size * 1.5
			csym = i
		elseif(sym[c] ~= nil) then
			sym[c](size)
		end
		penup()
		local distance = (i - csym) * size * 3.0 / 2
		moveto(x + math.cos(math.rad(theta)) * distance, y + math.sin(math.rad(theta)) * distance)
		turnto(theta)
		fd(size/2)
		pendown()
	end
end