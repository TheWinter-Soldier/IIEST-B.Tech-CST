--Creating table X
CREATE TABLE X(
    A NUMBER(2) PRIMARY KEY,
    B VARCHAR(25)
);


--Explicit CURSOR
DECLARE
    CURSOR MYCUR IS
        SELECT DEPTNO,DNAME
        FROM DEPT;
    A_M DEPT.DEPTNO%TYPE;
    B_M DEPT.DNAME%TYPE;

BEGIN
    OPEN MYCUR;
    IF MYCUR%ISOPEN THEN
        --DELETE FROM X;

        LOOP
            FETCH MYCUR INTO A_M, B_M;
            EXIT WHEN MYCUR%NOTFOUND;
            IF MYCUR%FOUND THEN
                INSERT INTO X VALUES(A_M,B_M);
            END IF;
        END LOOP;

        COMMIT;
    ELSE
        DBMS_OUTPUT.PUT_LINE('Unable to open cursor');
    END IF;

    CLOSE MYCUR;
END;