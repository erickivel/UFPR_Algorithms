program Ex092;
	var
		P1, P2, P3: integer;
		mean : real;
begin
	read(P1, P2, P3);
	mean := (P1 + 2*P2 + 3*P3)/6;
	writeln(mean:0:0);
end.
