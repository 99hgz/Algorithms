var
i,n,j,k,l,r,q:longint;
begin
randomize;
for i:=1 to 500000 do
 write(char(random(2)+ord('a')));
writeln;
n:=10000;
writeln(n);
for j:=1 to n do 
 begin
  for k:=1 to 5 do
   write(char(random(2)+ord('a')));
  writeln;
 end;
q:=500000;
writeln(q);
for i:=1 to q do begin
 l:=random(n)+1;
 r:=random(n-l+1)+l;
 write(l,' ',r,' ');
 l:=random(n)+1;
 r:=random(n-l+1)+l;
 writeln(l,' ',r,' ');
 end;
end.