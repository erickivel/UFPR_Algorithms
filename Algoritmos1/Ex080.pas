program Ex080;
	var
		x, y, solution : real;
	begin
		read(x, y);
		solution := (x/y) + (y/x);
		writeln(solution:0:3);
	end.
