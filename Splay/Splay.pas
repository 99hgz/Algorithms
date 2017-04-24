{
 * @key word:Splay
 * @已测试:POJ - 3481
 * @Author: hgz 
 * @Date: 2017-04-24 19:28:52 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-04-24 19:28:52 
}
var num,key,n,root,top,temp,x,y,keynum:longint;
    tr_left,tr_right,tr_size,tr_num,tr_key:array[0..1000000] of longint;
procedure right_rot(var x:longint);
begin
  y:=tr_left[x];
  tr_left[x]:=tr_right[y];
  tr_right[y]:=x;
  tr_size[y]:=tr_size[x];
  tr_size[x]:=tr_size[tr_left[x]]+tr_size[tr_right[x]]+1;
  x:=y;
end;
procedure left_rot(var x:longint);
begin
  y:=tr_right[x];
  tr_right[x]:=tr_left[y];
  tr_left[y]:=x;
  tr_size[y]:=tr_size[x];
  tr_size[x]:=tr_size[tr_left[x]]+tr_size[tr_right[x]]+1;
  x:=y;
end;
procedure maintain(var x:longint; f:boolean);
begin
  if f=false then
   begin
     if  tr_size[tr_left[tr_left[x]]]>tr_size[tr_right[x]] then
       right_rot(x)
     else
     if  tr_size[tr_right[tr_left[x]]]>tr_size[tr_right[x]] then
     begin
       left_rot(tr_left[x]);
       right_rot(x)
     end
     else exit;
   end
  else
   begin
     if  tr_size[tr_right[tr_right[x]]]>tr_size[tr_left[x]] then
       left_rot(x)
     else
     if  tr_size[tr_left[tr_right[x]]]>tr_size[tr_left[x]] then
     begin
       right_rot(tr_right[x]);
       left_rot(x)
     end
     else exit;

   end;
  maintain(tr_left[x],false);
  maintain(tr_right[x],true);
  maintain(x,true);
  maintain(x,false);
end;
procedure insert(var x:longint; key,num:longint);
begin
  if x=0 then
   begin
     inc(top); x:=top;
     tr_left[x]:=0; tr_right[x]:=0;
     tr_size[x]:=1;
     tr_key[x]:=key;
     tr_num[x]:=num;
   end
  else
   begin
    inc(tr_size[x]);
    if key<tr_key[x] then insert(tr_left[x],key,num)
                     else insert(tr_right[x],key,num);
    maintain(x,key>=tr_key[x]);
   end;
end;
function remove(var x:longint; key:longint):longint;
begin
   dec(tr_size[x]);
   if (key>tr_key[x]) then
    remove(tr_right[x],key)
   else
    if (key<tr_key[x]) then remove(tr_left[x],key)
   else
    begin
      if (tr_left[x]<>0) and (tr_right[x]=0) then
       begin
         temp:=x;
         x:=tr_left[x];
         exit(temp);
       end
       else
       if (tr_left[x]=0) and (tr_right[x]<>0) then
       begin
         temp:=x;
         x:=tr_right[x];
         exit(temp);
       end
       else
       if (tr_left[x]=0) and (tr_right[x]=0) then
       begin
         temp:=x;
         x:=0;
         exit(temp);
       end
       else
       begin
         temp:=tr_right[x];
         while (tr_left[temp]<>0) do temp:=tr_left[temp];
         tr_key[x]:=tr_key[temp];
         remove(tr_right[x],tr_key[temp]);
       end;

    end;
end;
function getmin(x:longint):longint;
begin
  while (tr_left[x]<>0) do x:=tr_left[x];
  exit(x);
end;
function getmax(x:longint):longint;
begin
  while (tr_right[x]<>0) do x:=tr_right[x];
  exit(x);
end;
begin
  n:=1;
  while (n<>0) do
   begin
     read(n);
     case n of
      1:begin readln(num,key); insert(root,key,num); end;
      2:begin
              x:=getmax(root);
              writeln(tr_num[x]);
              remove(root,tr_key[x]);
        end;
      3:begin
              x:=getmin(root);
              writeln(tr_num[x]);
              remove(root,tr_key[x]);
        end;
     end;

   end;
end.