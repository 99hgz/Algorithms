{
 * @key word:哈希，除法散列，乘法散列
 * @已测试:http://www.yyhs.net.cn:801/JudgeOnline/problem.php?id=1600
 * @未测试:乘法散列(via. LHQ)
 * @h2超时，辣鸡‼
 * @Author: hgz 
 * @Date: 2017-04-23 12:27:40 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-04-23 12:27:40 
}
const max=1000000000*10000;ww=4194304;
var
    c:array[0..300000]of int64;
    q:array[1..1000000]of record sl,key:int64;end;
    next:array[1..1000000]of int64;
    a:array[1..1000]of int64;
    cs,a1,b1,c1,d1,p,n,tmp1,tmp,ans:int64;
    i,j:longint;
function h(k:int64):int64;
begin
    k:=abs(k);
    exit(k mod 225287);
end;

{function h2(k:int64):int64;
var 
    tmp:int64;
begin
        k:=k+max; k:=k and ww;
        tmp:=6180339*k;
        exit((tmp and ww) shr 2);
end;}

function h2(k:int64):int64;
var 
    tmp:double;
	res:int64;
begin
    tmp:=k*0.618034;
	res:=abs(trunc((1<<18)*(tmp-trunc(tmp))));
	//writeln(k,' ',res);
    exit(res);
end;

procedure add(t:int64);
var
    find:boolean;
    head:int64;
begin
    find:=false;
    head:=c[t];
    while (head<>0) do
        begin
        if q[head].key=tmp1 then begin find:=true;q[head].sl:=q[head].sl+1;break;end;
        head:=next[head];
        end;
    if find=false then
        begin
        cs:=cs+1;
        q[cs].key:=tmp1;
        q[cs].sl:=1;
        next[cs]:=c[t];
        c[t]:=cs;
        end;
end;
function search2(t:int64):int64;
var
    head:int64;
begin
    head:=c[t];
    while (head<>0) do
        begin
        if q[head].key=tmp then begin exit(q[head].sl);end;
        head:=next[head];
        end;
    exit(0);
end;
 
begin
    readln(a1,b1,c1,d1,p,n);
    for i:=1 to n do
        read(a[i]);
    for i:=1 to n do
        for j:=1 to n do
            begin
            tmp1:=a1*a[i]+b1*a[j];
            tmp:=h2(tmp1);
            if c[tmp]=0 then begin
                cs:=cs+1;
                q[cs].key:=tmp1;
                q[cs].sl:=1;
                c[tmp]:=cs;
            end else
            add(tmp);
        end;    
    for i:=1 to n do
        for j:=1 to n do
        begin
        tmp:=p-c1*a[i]-d1*a[j];
        ans:=ans+search2(h2(tmp));
        end;
    writeln(ans);
end.  