{
 * @key word: 并查集，懒惰标记
 * @已测试:POJ	- 2492
 * @Author: hgz 
 * @Date: 2017-04-24 20:51:39 
 * @Last Modified by:   hgz 
 * @Last Modified time: 2017-04-24 20:51:39 
}
var  
    n,m,i,j,k,x,y,d,ans,zs,t:longint; 	
    father,r:array[0..2001] of longint;  
function getfather(x:longint):longint;  
var
	fx:longint;
begin  
    if father[x]=x then exit(x);
    fx:=getfather(father[x]);  
    r[x]:=(r[x]+r[father[x]])mod 2;
    father[x]:=fx;
    exit(father[x]);  
end;  
function he(x,y:longint):boolean;
var  
    fx,fy:longint;  
begin  
    fx:=getfather(x);  
    fy:=getfather(y);  
    if (fx=fy) then begin
        if ((r[y]+r[x])mod 2)=0 then exit(true) else exit(false);
        end;
    father[fy]:=fx;  
    r[fy]:=(r[y]+r[x]+1)mod 2;
    exit(false);
end;  
function i2s(a:longint):string;
begin
    str(a,i2s);
end;
begin  
    readln(t);
	for zs:=1 to t do
		begin
        readln(n,m);  
		for i:=1 to n do 
			father[i]:=i;
		fillchar(r,sizeof(r),0);
		ans:=0;
		for i:=1 to m do 
		    begin
			readln(x,y);
			if (ans=0)and(he(x,y))then ans:=ans+1;
		    end;
		writeln('Scenario #'+i2s(zs)+':');
		if ans=1 then writeln('Suspicious bugs found!') else writeln('No suspicious bugs found!');
		writeln;
	    end;
end.