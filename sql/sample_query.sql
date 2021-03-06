/* sample query for entering a tick */

BEGIN;

    /* location */
    INSERT INTO gauge (id, shortname, description)
        VALUES (
            1,
            'test', 
            'sitting on my desk, I wonder if it will ever see real rain'
        );

    INSERT INTO ticks (gauge, num) SELECT 1, mm_per_click FROM gauge WHERE id = 1;
    INSERT INTO ticks (gauge, num) SELECT 1, mm_per_click FROM gauge WHERE id = 1;
    INSERT INTO ticks (gauge, num) SELECT 1, mm_per_click FROM gauge WHERE id = 1;
    INSERT INTO ticks (gauge, num) SELECT 1, mm_per_click FROM gauge WHERE id = 1;
    INSERT INTO ticks (gauge, num) SELECT 1, mm_per_click FROM gauge WHERE id = 1;
    INSERT INTO ticks (gauge, num) SELECT 1, mm_per_click FROM gauge WHERE id = 1;
COMMIT;

SELECT SUM(num) FROM ticks AS total_rain;
SELECT COUNT(num) FROM ticks as clicks;
