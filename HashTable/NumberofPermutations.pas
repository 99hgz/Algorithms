{
 * @key word:排列数
 * @已测试:http://192.68.1.212/JudgeOnline/problem.php?id=1161
 * @Author: hgz 
 * @Date: 2017-04-25 14:41:20 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-04-25 14:41:20 
}
var
    p:array[1..9]of longint=(40320,5040,720,120,24,6,2,1,0);
    ex:array[0..362880]of boolean;
    q:array[0..362880]of record v,cs:longint;end;
    head,tail,i,n,csmax:longint;
    find:boolean;
    _st,st:string;
function h(a:longint):longint;
    var
    cz:array[1..9]of boolean;
    sz:array[1..9]of longint;
    wz,i,sl,j:longint;
    begin
    h:=0;
    fillchar(cz,sizeof(cz),0);
    for wz:=9 downto 1 do
        begin
        sz[wz]:=a mod 10;
        a:=a div 10;
        end;
    for i:=1 to 9 do
        begin
        sl:=0;
        for j:=1 to sz[i]-1 do
            if cz[j]=false then sl:=sl+1;
        cz[sz[i]]:=true;
        h:=h*10+sl;
        end;
    end;
function hn(a:longint):longint;
    var
    cz:array[1..9]of boolean;
    sz:array[1..9]of longint;
    wz,i,sl,j:longint;
    begin
    hn:=0;
    fillchar(cz,sizeof(cz),0);
    for wz:=9 downto 1 do
        begin
        sz[wz]:=(a mod 10)+1;
        a:=a div 10;
        end;
    for i:=1 to 9 do
        begin
        sl:=0;
        for j:=1 to 9 do
            if cz[j]=false then
                begin
                sl:=sl+1;
                if sl=sz[i] then break;
                end;
        cz[j]:=true;
        hn:=hn*10+j;
        end;
    end;
function a2n(a:longint):longint;
var
    wz:longint;
    sz:array[1..9]of longint;
begin
    a2n:=0;
    for wz:=9 downto 1 do
        begin
        sz[wz]:=(a mod 10);
        a:=a div 10;
        end;
    for wz:=1 to 9 do
        a2n:=a2n+sz[wz]*p[wz];
end;    
function a2nn(a:longint):longint;
var
    wz:longint;
    sz:array[1..9]of longint;
 
begin
    a2nn:=0;
    for wz:=9 downto 1 do
        begin
        sz[wz]:=(a mod (11-wz));
        a:=a div (11-wz);
        end;
    for wz:=1 to 9 do
        begin
        writeln(sz[wz]);
        a2nn:=a2nn*10+sz[wz];
        end;
end;
function turn(a,b,c,d,e:longint;st:string):string;
var _st:string;t:char;
begin
    _st:=st;
    t:=_st[a];
    case e of
    1:begin _st[a]:=_st[c];_st[c]:=_st[d];_st[d]:=_st[b];_st[b]:=t;end;
    2:begin _st[a]:=_st[d];_st[d]:=t;t:=_st[b];_st[b]:=_st[c];_st[c]:=t;end;
    3:begin _st[a]:=_st[b];_st[b]:=_st[d];_st[d]:=_st[c];_st[c]:=t;end;
    end;
    exit(_st);
end;
function s2i(st:string):longint;
begin
    val(st,s2i);
end;
procedure push(st:string);
begin
    //writeln(st);
    if st='123456789' then begin find:=true;exit;end;
    if ex[a2n(h(s2i(st)))] then exit;
    tail:=tail+1;
    q[tail].v:=s2i(st);
    q[tail].cs:=q[head].cs+1;
    ex[a2n(h(s2i(st)))]:=true;
end;
begin
    {writeln(h(123456798));
    writeln(a2n(h(123456798)));}
    //writeln(hn(a2nn(24)));
readln(n);
for i:=1 to n do
begin
    readln(st);
    find:=false;
    fillchar(ex,sizeof(ex),0);
    head:=0;
    tail:=1;
    q[tail].v:=s2i(copy(st,2,length(st)-1));
    csmax:=s2i(copy(st,1,1));
    q[tail].cs:=0;
    while head<tail do
        begin
        head:=head+1;
        if (q[head].cs)=csmax then begin writeln(-1);break;end;
        str(q[head].v,_st);
        {for i:=1 to 3 do 
            for j:=1 to 3 do 
                jz[i,j]:=_st[i*3-3+j];}
        push(turn(1,2,4,5,1,_st));
        //push(turn(1,2,4,5,2,_st));
        push(turn(1,2,4,5,3,_st));
        push(turn(2,3,5,6,1,_st));
        //push(turn(2,3,5,6,2,_st));
        push(turn(2,3,5,6,3,_st));
        push(turn(4,5,7,8,1,_st));
        //push(turn(4,5,7,8,2,_st));
        push(turn(4,5,7,8,3,_st));
        push(turn(5,6,8,9,1,_st));
        //push(turn(5,6,8,9,2,_st));
        push(turn(5,6,8,9,3,_st));
        if find then begin writeln(q[head].cs+1);break;end;
        end;
    end;
end.