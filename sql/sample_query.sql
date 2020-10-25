/* sample query for entering a tick */

BEGIN;
    INSERT INTO ticks (num) VALUES (1);
    INSERT INTO ticks (num) VALUES (1);
    INSERT INTO ticks (num) VALUES (1);
    INSERT INTO ticks (num) VALUES (1);
COMMIT;

SELECT SUM(num)*0.9724 FROM TICKS * mm;
