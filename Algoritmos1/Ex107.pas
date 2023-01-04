program Ex107;
var 
  number : longint;
begin
  read(number);
  if number mod 3 = 0 then
    writeln('SIM')
  else
    writeln('NAO');
end.
