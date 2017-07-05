var
n,q,i:longint;
begin
    randomize;
    n:=random(10)+1;
    q:=random(10)+1;
    writeln(n,' ',q);
    for i:=1 to n-1 do 
        begin
            writeln(random(i));
        end;
    for i:=1 to q do 
        begin
            writeln(random(n div 2),' ',random(n div 2)+(n div 2),' ',random(n));
        end;
end.