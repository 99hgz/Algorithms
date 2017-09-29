
Var n,i,j,p,q,yhq,sta: longint;
  f: array[0..33000] Of double;
  t: array[0..33000,0..20] Of double;
  are: array[0..33000] Of longint;
  pre: array[0..20,0..20] Of double;
  price,area: array[0..20] Of longint;
  max: double;
Function min(a,b:double): double;
Begin
  If a<b Then exit(a)
  Else exit(b);
End;
Begin
  readln(n);
  While n<>0 Do
    Begin
      For i:=0 To 20 Do
        For j:=0 To 20 Do
          pre[i,j] := 1;
      For i:=1 To n Do
        Begin
          read(price[i],area[i]);
          read(yhq);
          For j:=1 To yhq Do
            Begin
              read(p,q);
              pre[i,p] := pre[i,p]*(100-q)/100;
            End;
        End;
      readln;
      For i:=0 To 33000 Do
        For j:=0 To 20 Do
          t[i,j] := 1;
      For sta:=0 To (1<<n)-1 Do
        Begin
          are[sta] := 0;
          For i:=1 To n Do
            If (sta And (1<<(i-1)))>0 Then
              are[sta] := are[sta]+area[i]
            Else
              For j:=1 To n Do
                If (sta And (1<<(j-1)))>0 Then
                  t[sta,i] := t[sta,i]*pre[j,i];
        End;
      f[0] := 0;
      max := maxlongint;
      For sta:=1 To (1<<n)-1 Do
        Begin
          f[sta] := maxlongint;
          For i:=1 To n Do
            If (sta And (1 shl (i-1)) )>0 Then
              f[sta] := min(f[sta xor (1<< (i-1) )]+t[sta xor (1<< (i-1) ),i]*
                        price[i],f[sta]);
          If are[sta]*max>f[sta] Then max := f[sta]/are[sta];
        End;
      writeln(max:0:4);
      readln(n);
    End;
End.
