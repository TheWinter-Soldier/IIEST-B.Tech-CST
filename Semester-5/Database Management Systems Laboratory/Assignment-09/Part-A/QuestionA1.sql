--Creating table Y
CREATE TABLE Y(
    C1 NUMBER PRIMARY KEY,
    C2 VARCHAR(15)
);


--Filling values in Y TABLE
INSERT INTO Y VALUES(1,'Jokes');
INSERT INTO Y VALUES(2,'Humor');
INSERT INTO Y VALUES(3,'Death');


--Implicit CURSOR
DECLARE
    AFFECTED CHAR(4);
BEGIN
    DELETE FROM Y
    WHERE (C1 = 1 OR C1 = 2);

    AFFECTED:=TO_CHAR(SQL%ROWCOUNT);
    DBMS_OUTPUT.PUT_LINE(AFFECTED);
END;