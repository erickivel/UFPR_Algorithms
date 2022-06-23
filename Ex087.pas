program Ex087;
	var width, length, area, totalEnergy : integer;
begin
	read(width, length);
	area := width*length;
	totalEnergy := area*18;
	writeln(area, ' ', totalEnergy);
end.

