var
n,m,q,i,j,len:longint;
begin
    randomize;
    n:=11;
    m:=200;
    q:=10000;
    writeln(n,' ',m,' ',q);
    {for i:=2 to n do
        writeln(random(i-1)+1,' ',i,' ',chr(ord('a')+random(2)));}
writeln('7 9 m');
writeln('3 9 x');
writeln('9 1 v');
writeln('9 10 q');
writeln('6 7 b');
writeln('8 5 f');
writeln('2 5 x');
writeln('5 7 s');
writeln('4 1 x');
writeln('11 4 z');

    for i:=1 to m do 
        begin
            len:=random(500)+1;
            for j:=1 to len do 
                write(chr(ord('a')+random(26)));
            writeln;
        end;
    for i:=1 to q do 
        writeln(random(n)+1,' ',random(n)+1,' ',random(m)+1);
end.