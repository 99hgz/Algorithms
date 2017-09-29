
Var 
  n,i,j: longint;
  map: array[1..100,1..100] Of longint;
  f: array[1..100,1..100,1..100] Of longint;
vis: array[1..100,1..100,1..100] Of boolean;

function min(a,b:longint):longint;
begin
    if a<b then exit(a) else exit(b);
end;

Function find(a,b,c:longint): longint;
var
i:longint;

Procedure swap(Var a,b,c:longint);

Procedure swap2(Var a,b:longint);

Var 
  c: longint;
Begin
  c := a;
  a := b;
  b := c;
End;
Begin
  If (b>a) Then
    Begin
      swap2(a,b);
    End;
  If (c>a) Then
    Begin
      swap2(a,c);
    End;
  If (c>b) Then
    Begin
      swap2(b,c);
    End;
End;
Begin
  swap(a,b,c);
  if (a=n) then begin
      exit(0);
  end;
  if (vis[a,b,c]) then begin
      exit(f[a,b,c]);
  end;
  vis[a,b,c]:=true;
  f[a,b,c]:=maxlongint;
  f[a,b,c]:=min(f[a,b,c],map[a,a+1]+find(a+1,b,c));
  for i:=b+1 to min(n,a+1) Do
     f[a,b,c]:=min(f[a,b,c],map[b,i]+find(a,i,c));
  for i:=c+1 to min(n,a+1) do 
     f[a,b,c]:=min(f[a,b,c],map[c,i]+find(a,b,i));
  { find(point+1,point+1,b,c,cost+map[a,point+1]);
  find(point+1,a,point+1,c,cost+map[b,point+1]);
  find(point+1,a,b,point+1,cost+map[c,point+1]);}
  exit (f[a,b,c]);
End;
Begin
  readln(n);
  For i:=1 To n Do
    For j:=i+1 To n Do
      read(map[i,j]);
  writeln(find(1,1,1));
End.
