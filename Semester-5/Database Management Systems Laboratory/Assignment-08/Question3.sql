DECLARE
str  varchar(40);
len  number;
str1 varchar(40);
    
BEGIN
str := &str;

len := Length(str);
FOR i IN REVERSE 1..len 
LOOP
   str1 := str1||Substr(str,i,1);
END LOOP;
    
dbms_output.Put_line('Reverse of the given string is '||str1||'.');

END;