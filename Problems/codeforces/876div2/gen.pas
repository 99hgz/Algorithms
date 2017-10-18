var
n,i:longint;
begin
randomize;
n:=random(20)+1;
writeln(n);
for i:=1 to n do 
 write(random(100),' ');
end.