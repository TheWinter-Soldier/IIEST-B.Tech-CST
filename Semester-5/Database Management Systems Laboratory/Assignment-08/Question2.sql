DECLARE
fac number(8);
n number(2);

BEGIN
n := &n;
fac := 1;

while n > 0 
loop
    fac := n*fac;
    n := n-1;
end loop;
   
dbms_output.put_line(fac);

END;