program Ex025;
	var day, month, year, age : integer;
begin
	read(day, month, year);
	if (month > 4) then
			age := (2021 - year - 1)
	else if (month = 4) then
		if (day > 29) then
			age := (2021 - year - 1)
		else
			age := (2021 - year)
	else
			age := (2021 - year);
	writeln(age);
end.
