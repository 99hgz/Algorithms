{
 * @key word:线段树，懒惰标记
 * @已测试:HDU 1698 
 * @Author: hgz 
 * @Date: 2017-04-24 19:19:25 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-04-24 19:19:25 
}
var
    tree,mark:array[1..100000*4]of int64;
    a:array[1..100000]of int64;
    n,wz,r1,r2,sl,m,r3:int64;
    i,j:longint;
    ch:char;
    st:string;
procedure build(v,l,r:int64);
var
    mid:int64;
begin
    if l=r then begin
        tree[v]:=a[l];
        exit;
        end;
    mid:=(l+r)div 2;
    build(v+v,l,mid);
    build(v+v+1,mid+1,r);
    tree[v]:=tree[v+v]+tree[v+v+1];
end;
procedure modify(v,l,r,x,y,val:int64);
var
    mid:int64;
begin
    if (l=x)and(r=y) then begin
        mark[v]:=val;
        exit;
        end;
    if mark[v]>0 then mark[v+v]:=mark[v];
    if mark[v]>0 then mark[v+v+1]:=mark[v];
    mark[v]:=0;
    mid:=(l+r)div 2;
    if (y<=mid) then 
        modify(v+v,l,mid,x,y,val)
    else if (x>mid) then 
        modify(v+v+1,mid+1,r,x,y,val)
    else begin
        modify(v+v,l,mid,x,mid,val);
        modify(v+v+1,mid+1,r,mid+1,y,val);
        end;
end;
function query(v,l,r:int64):int64;
var
    mid:int64;
begin
	if mark[v]<>0 then exit(mark[v]*(r-l+1));
	mid:=(l+r)div 2;
	exit(query(v+v,l,mid)+query(v+v+1,mid+1,r));
end;
begin
readln(sl);
for j:=1 to sl do
    begin
    fillchar(tree,sizeof(tree),0);
    readln(n);
    modify(1,1,n,1,n,1);
    readln(m);
    for i:=1 to m do 
    begin
       readln(r1,r2,r3);
       modify(1,1,n,r1,r2,r3);
    end;
    writeln('Case ',j,': The total value of the hook is ',(query(1,1,n)),'.');
    end;
end.