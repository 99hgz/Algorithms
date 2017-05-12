var
    st:string;
    i,j,ans_min,len:longint;
    f:array[0..110,0..110]of longint;
function min(a,b:longint):longint;
begin
    if a>b then exit(b) else exit(a);
end;
begin
    readln(st);
    len:=length(st);
    f[1,1]:=1;
    for i:=2 to len do
        begin
            for j := 1 to i-1 do
                if st[i]=st[j] then
                    f[i,j]:=f[i-1,j] else 
                    f[i,j]:=f[i-1,j]+1;
            f[i,i]:=maxlongint;
            for j:=1 to i-1 do
                f[i,i]:=min(f[i,i],f[i,j]);
        end;
    writeln(f[len,len]);
    readln;
end.