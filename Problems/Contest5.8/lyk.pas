
Var 
  n,i,t,j,k,m,tmp1,tmp,tmp2,ans: longint;
  a,f: array[-1..101000] Of longint;


Function lowbit(i:longint): longint;
Begin
  exit((i)and(-i));
End;

Procedure add(i,c:longint);
Begin
  While (i<=n) Do
    Begin
      f[i] := f[i]+c;
      i := i+lowbit(i);
    End;
End;

Function get(i:longint): longint;

Var 
  ans: longint;
Begin
  ans := 0;
  While (i>0) Do
    Begin
      ans := ans+f[i];
      i := i-lowbit(i);
    End;
  exit(ans);
End;

Begin

  read(n);
  For i:=1 To n Do
    read(a[i]);
  For i:=n Downto 1 Do
    Begin
      ans :=( ans+get(a[i])) Mod 2;
      add(a[i],1);
      //writeln(ans);
    End;
  readln(m);
  ans := ans Mod 2;
  For t:=1 To m Do
    Begin
      read(i,j);
      If i<>j Then ans := ans xor 1;
      writeln(ans);
    End;

End.
