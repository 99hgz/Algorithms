var n,num,i,l,r,x,operate:longint;
head,tail,tag:array[0..1000]of longint;
block,a,b:array[0..100000]of longint;
    procedure sort(l,r: longint);
      var
         i,j,x,y: longint;
      begin

         i:=l;
         j:=r;
         x:=b[(l+r) div 2];
         repeat
           while b[i]<x do
            inc(i);
           while x<b[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=b[i];
                b[i]:=b[j];
                b[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;
function binary(l,r,x:longint):longint;
var ll,rr,mid:longint;
f:boolean;
begin
 ll:=l; rr:=r;
 f:=false;
 while (rr-ll)>1 do
  begin
   mid:=(ll+rr) div 2;
   if b[mid]<x then begin rr:=mid; f:=true; end
    else ll:=mid;
  end;
  if f=true then exit(rr)
   else exit(-1);
end;
procedure add(l,r,x:longint);
var i:longint;
begin
	for i:=l to tail[block[l]] do
	 begin
	  a[i]:=a[i]+x;
	  b[i]:=a[i];
	 end;
	sort(l,tail[block[l]]);
	for i:=head[block[r]] to r do
	 begin
	  a[i]:=a[i]+x;
	  b[i]:=a[i];
	 end;
	sort(head[block[r]],r);
	for i:=block[l]+1 to block[r]-1 do tag[i]:=tag[i]+x;

end;
function search(l,r,x:longint):longint;
var xx,max,i:longint;
begin
  max:=-1;
  for i:=l to tail[block[l]] do
	if (a[i]>max)and(a[i]<x) then max:=a[i];
  for i:=head[block[r]] to r do
    if (a[i]>max)and(a[i]<x) then max:=a[i];
  for i:=block[l]+1 to block[r]-1 do
   begin
    xx:=(binary(head[i],tail[i],x-tag[i]));
	if xx>max then max:=xx;
   end;
  exit(max);
end;
begin
assign(input,'cjy.in');reset(input);
assign(output,'cjy.out');rewrite(output);
 readln(n);
 num:=trunc(sqrt(n));
 for i:=1 to num do
  begin
   head[i]:=(i-1)*num+1;
   tail[i]:=i*num;
  end;
 if num<>sqrt(n) then
  begin
   num:=num+1;
   head[num]:=tail[num-1]+1;
   tail[num]:=n;
  end;
 //head[i],tail[i] 表示第i个块的头和尾 这个序列共分成num个块
 for i:=1 to n do
  begin
   read(a[i]);
   block[i]:=(i-1) div trunc(sqrt(n))+1;  //block指的是第i个数的所属块
   b[i]:=a[i];
  end;
 for i:=1 to num do
  sort(head[i],tail[i]);
 //先把原有的数据按块排序存在b数组。
 for i:=1 to n do
  begin
   read(operate,l,r,x);
   if operate=0 then
    add(l,r,x)
	 else
	  writeln(search(l,r,x));
  end;
  close(input);
  close(output);
end.
