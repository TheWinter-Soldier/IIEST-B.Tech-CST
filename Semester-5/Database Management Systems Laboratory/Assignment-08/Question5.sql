create table areas(
    Radius number(2) primary key,
    Area number(14,2));


--To process and enter the values
DECLARE
r number(2);
area number(14,2);
pi constant number(4,2) := 3.14;

BEGIN
r:=3;

while r<=7
loop
area := pi*power(r,2);
insert into areas values(r,area);
r := r+1;
end loop;

END;


--To check the table
SELECT * 
from areas;