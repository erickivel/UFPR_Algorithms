program Ex085;
	uses math;
	const
		PI = 3.14;
	var
		diameter, volume, radius : real;
	begin
		read(diameter);
		radius := diameter/2;
		volume := (4*PI/3)*math.power(radius, 3);
		writeln(volume:0:2);
	end.
