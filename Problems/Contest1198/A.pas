var
    a,f:array[0..100001]of int64;
    i:longint;
    n,last,j:int64;
  
function binary_search(x:int64):int64;
    var l,r,mid:int64;
    begin
    l:=0; r:=last;
    while l<r do
        begin
        mid:=(l+r) div 2;
        if f[mid]<x then l:=mid+1 else r:=mid;
        end;
    end;
  
begin
read(n);
for i:=1 to n do
    readln(a[i]);
for i:=n downto 1 do
    begin
    if a[i]>=f[last] then
        begin
        last:=last+1;
        f[last]:=a[i];
    end
    else
    begin
    j:=binary_search(a[i]);
    if f[j]>a[i] then f[j]:=a[i];
    end;
end;
write(last);
end.