var
  _, __, ___, ____ : longint;
  _____ : array[1..20,1..20] of longint;
  ______ : array[1..20] of boolean;
procedure ________(_________, __________ : longint);
var __ : longint;
begin
  if __________ >= ____ then exit;
  if (_________ = _+1) then
  begin
    if __________ < ____ then ____ := __________;
    exit;
  end;
  for __ := 1 to _ do
    if ______[__]=false then
    begin
      ______[__] := true;
      ________(_________+1, __________+_____[_________,__]);
      ______[__] := false;
    end;
end;
begin
  readln(_);
  for __ := 1 to _ do
  begin
    for ___ := 1 to _ do
    begin
      read(_____[__,___]);
      _____[__,___] := 2000 - _____[__,___];
    end;
  end;
  ____ := maxlongint;
  ________(1, 0);
  writeln(_*2000-____);
end.