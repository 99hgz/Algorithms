var  n,m,num,j,i:longint;
change:array[0..1 shl 22,0..1]of longint;
f:array[0..12,0..1 shl 13]of int64;
procedure swap(var a,b:longint);
var t:longint;
begin t:=a; a:=b; b:=t; end;
procedure init(d,go,from:longint);
begin
 if m<d then exit;
 if m=d then
  begin
   change[num,1]:=go;
   change[num,0]:=from;
   num:=num+1;
  end;
 init(d+1,(go<<1)+1,from<<1);
 init(d+1,go<<1,(from<<1)+1);
 init(d+2,go<<2,from<<2);
end;
begin
 read(n,m);
 while (n<>0)and(m<>0) do
  begin
   num:=0;
   if n<m then swap(n,m);
   init(0,0,0);
   fillchar(f,sizeof(f),0);
   f[0,0]:=1;
   for j:=1 to n do
    for i:=0 to num-1 do
     inc(f[j,change[i,1]],f[j-1,change[i,0]]);
   writeln(f[n,0]);
   read(n,m);
  end;
end.
