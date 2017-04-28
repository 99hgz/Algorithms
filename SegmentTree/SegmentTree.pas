{
 * @key word:线段树
 * @已测试:HDU - 1166
 * @Author: hgz 
 * @Date: 2017-04-24 19:12:50 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-04-24 19:12:50 
}
const maxn=50000;
var
tree:array[1..maxn*6]of longint;
a:array[1..maxn]of longint;
n,wz,i,r1,r2,sl,j:longint;
ch:char;
st:string;

procedure build(v,l,r:longint);
var
mid:longint;
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

procedure modify(v,i,l,r,val:longint);
var
mid:longint;
begin
	if l=r then begin
		tree[v]:=tree[v]+val;
		exit;
		end;
	mid:=(l+r)div 2;
	if mid>=i then
		modify(v+v,i,l,mid,val)
		else
		modify(v+v+1,i,mid+1,r,val);
	tree[v]:=tree[v+v]+tree[v+v+1];
end;

function query(v,l,r,x,y:longint):longint;
var
mid:longint;
begin
	if (l=x)and(r=y) then 
		exit(tree[v]);
	mid:=(l+r)div 2;
	if (y<=mid) then 
		exit(query(v+v,l,mid,x,y))
		else
	if (x>mid) then 
		exit(query(v+v+1,mid+1,r,x,y));
	exit(query(v+v,l,mid,x,mid)+query(v+v+1,mid+1,r,mid+1,y));
end;

begin
readln(sl);
for j:=1 to sl do
begin
	fillchar(tree,sizeof(tree),0);
	readln(n);
	for i:=1 to n do 
		read(a[i]);
	readln;
	build(1,1,n);
	writeln('Case ',j,':');
	while true do 
	begin
		readln(st);
		if st[1]='E' then break;
		ch:=st[1];
		wz:=pos(' ',st);
		delete(st,1,wz);
		wz:=pos(' ',st);
		val(copy(st,1,wz-1),r1);
		delete(st,1,wz);
		val(st,r2);
		if ch='Q' then 
			writeln(query(1,1,n,r1,r2))
			else 
		if ch='S' then 
			modify(1,r1,1,n,-r2)
			else
		if ch='A' then 
			modify(1,r1,1,n,r2);
	end;
end;
end.