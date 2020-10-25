/* sample query for entering a tick */

BEGIN;
    /*
    INSERT INTO ticks (num) VALUES (1);
    INSERT INTO ticks (num) VALUES (1);
    INSERT INTO ticks (num) VALUES (1);
    INSERT INTO ticks (num) VALUES (1);
    */
    INSERT INTO ticks (num) VALUES (0.2794);
    INSERT INTO ticks (num) VALUES (0.2794);
    INSERT INTO ticks (num) VALUES (0.2794);
    INSERT INTO ticks (num) VALUES (0.2794);

COMMIT;

SELECT SUM(num) FROM TICKS;
