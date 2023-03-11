--Question 1
CREATE TRIGGER TR1 AFTER
    UPDATE ON DEPT FOR EACH ROW

DECLARE
    CURSOR CUR3 IS
        SELECT MAX(SAL)
        FROM EMP
        WHERE SAL<(
                SELECT MAX(SAL)
                FROM EMP
            );
    SAL_M EMP.SAL%TYPE;

BEGIN
    OPEN CUR3;
    IF CUR3%ISOPEN THEN
        FETCH CUR3 INTO SAL_M;
        DBMS_OUTPUT.PUT_LINE('After updation, the Second highest salary in EMP table is ' || TO_CHAR(SAL_M));
    ELSE
        DBMS_OUTPUT.PUT_LINE('Unable to open Cursor');
    END IF;
    CLOSE CUR3;
END;


--Updating the DEPT table
DECLARE
    TOTAL_ROWS NUMBER(2);
BEGIN
    UPDATE DEPT
    SET LOC = 'Kolkata'
    WHERE(DEPTNO = 20 OR DEPTNO = 30);
    IF SQL%NOTFOUND THEN 
        DBMS_OUTPUT.PUT_LINE('No rows were updated.');
    ELSIF SQL%FOUND THEN
        TOTAL_ROWS := SQL%ROWCOUNT;
        DBMS_OUTPUT.PUT_LINE( TOTAL_ROWS || ' rows were updated.');
    END IF;
END;