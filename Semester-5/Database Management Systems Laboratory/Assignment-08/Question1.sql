DECLARE
a NUMBER(5);
b NUMBER(5);
c NUMBER(5);
    
BEGIN
a := &a;
b := &b;
c := &c;
    
IF a >= b AND a >= c 
THEN
    dbms_output.Put_line('Among, '||a||','||b||' and '||c||', the greatest number is '||a||'.');
ELSIF b >= a AND b >= c 
THEN
    dbms_output.Put_line('Among '||a||','||b||' and '||c||', the greatest number is '||b||'.');
ELSE
    dbms_output.Put_line('Among, '||a||','||b||' and '||c||', the greatest number is '||c||'.');
END IF;

IF a <= b AND a <= c 
THEN
    dbms_output.Put_line('Also, the lowest number is '||a||'.');
ELSIF b <= a AND b <= c 
THEN
    dbms_output.Put_line('Also, the lowest number is '||b||'.');
ELSE
    dbms_output.Put_line('Also, the lowest number is '||c||'.');
END IF;

END;