--Question 3
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
        DBMS_OUTPUT.PUT_LINE(TO_CHAR(SAL_M));
    ELSE
        DBMS_OUTPUT.PUT_LINE('Unable to open Cursor');
    END IF;
    CLOSE CUR3;
END;