program Ex082;
	var
		seconds : longint;
		minutes, hours : real;
begin
	minutes := 0;
	hours := 0;
	read(seconds);
	if (seconds >= 60) then
		minutes := seconds/60;
		seconds := seconds mod 60;
	if (minutes >= 60) then
		hours := minutes/60;
		minutes := trunc(minutes) mod 60;
	writeln(trunc(hours), ':', trunc(minutes), ':', seconds);
end.
