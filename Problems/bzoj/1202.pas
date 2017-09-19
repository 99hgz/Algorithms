var  
        n,m,i,j,k,x,y,d,ans,zs,w,t:longint; 
        flag:boolean;	
        father,r:array[0..110] of longint;  
function getfather(x:longint):longint;  
var
		fx:longint;
begin  
        if father[x]=x then exit(x);
		fx:=getfather(father[x]);  
		r[x]:=(r[x]+r[father[x]]);
        father[x]:=fx;
        exit(father[x]);  
end;  
function he(x,y,w:longint):boolean;
var  
        fx,fy:longint;  
begin  
        fx:=getfather(x);  
        fy:=getfather(y);  
		if (fx=fy) then begin
			if ((r[y]-r[x]))<>w then exit(true) else exit(false);
		end else 
			begin
			father[fy]:=fx;
			r[fy]:=w+r[x]-r[y];
			end;
		exit(false);
end;  
begin
readln(t);
while not(eof) do
		begin
        readln(n,m);  
		for i:=0 to n do 
			father[i]:=i;
		fillchar(r,sizeof(r),0);
		ans:=0;
        flag:=false;
		for i:=1 to m do 
		begin
			readln(x,y,w);
			if (flag=false) then if (he(x-1,y,w)) then flag:=true;
		end;
		if (flag) then writeln('false') else writeln('true');
		end;
end.