program Ex093;
	var
		number, predecessor, sucessor : integer;
	begin
		read(number);
		predecessor := number - 1;
		sucessor := number + 1;
		writeln(sucessor, ' ', predecessor);
	end.
