program Ex089;
	var
		grossPrice : integer;
		finalPrice : real;
begin
	read(grossPrice);
	finalPrice := ((grossPrice*1.28)+(grossPrice*0.45));
	writeln(trunc(finalPrice));
end.
