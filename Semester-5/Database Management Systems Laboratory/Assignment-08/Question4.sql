create table ACCT_MSTR(
    acct_no number(5) primary key,
    type char(2),
    curbal number(8,2),
    status char(1));


--Inserting values into the ACCT_MSTR table
INSERT into ACCT_MSTR values(41239,'CA',45000,'A');
INSERT into ACCT_MSTR values(41246,'SB',115000,'S');
INSERT into ACCT_MSTR values(42567,'SB',20429.5,'A');
INSERT into ACCT_MSTR values(51264,'SB',303045.5,'A');
INSERT into ACCT_MSTR values(54666,'CA',675.8,'A');
INSERT into ACCT_MSTR values(57001,'CA',24500,'A');
INSERT into ACCT_MSTR values(58903,'SB',120000,'A');
INSERT into ACCT_MSTR values(59011,'CA',0,'T');
INSERT into ACCT_MSTR values(70048,'SB',788.4,'A');
INSERT into ACCT_MSTR values(71619,'CA',916,'A');
INSERT into ACCT_MSTR values(74342,'SB',0,'T');
INSERT into ACCT_MSTR values(85327,'SB',89557.3,'A');
INSERT into ACCT_MSTR values(86864,'CA',5160,'A');


--Operations
DECLARE
acctno number(5);
balance number(8,2);
Min_bal number(4) := 1000;

BEGIN
acctno := &acctno;

select curbal into balance from ACCT_MSTR
where acct_no = acctno;
            
if balance < Min_bal
then
   UPDATE ACCT_MSTR
   set curbal = balance - 100
   where acct_no = acctno;
end if;

END;