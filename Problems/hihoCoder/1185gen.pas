var
n,m,i,u,v:longint;
found:boolean;
dis:array[0..1000,0..1000]of boolean;
begin
randomize;
n:=random(20);
repeat
m:=random(n*n);
until (m<=((n*n) div 2))and(m<=100000);
writeln(n,' ',m);
for i:=1 to n do
 write(random(10000),' ');
writeln;
for i:=1 to m do 
 begin
 found:=false;
 while (found=false) do
 begin
 u:=random(n)+1;
 v:=random(n)+1;
 if (u<>v)and(dis[u,v]=false) then begin 
  dis[u,v]:=true;
  found:=true;
  writeln(u,' ',v);
  end;
  end;
 end;
end.