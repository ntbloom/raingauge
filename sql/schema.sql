/* schema.sql -- schema for the raingauge database */

BEGIN;
    DROP TABLE IF EXISTS gauge CASCADE;
    CREATE TABLE gauge(
        id INT PRIMARY KEY,
        shortname TEXT NOT NULL,
        mm_per_click NUMERIC DEFAULT 0.2794,
        description TEXT NOT NULL,
        created_at TIMESTAMPTZ DEFAULT current_timestamp
    );

    /* current location */
    INSERT INTO gauge (id, shortname, description)
        VALUES (
            1,
            'test', 
            'sitting on my desk, I wonder if it will ever see real rain'
        );

    /* count the ticks */
    DROP TABLE IF EXISTS ticks CASCADE;
    CREATE TABLE ticks (
        db_time TIMESTAMPTZ DEFAULT current_timestamp,
        gauge INT DEFAULT 1,
        num INT,
        FOREIGN KEY (gauge) REFERENCES gauge(id)
    );
COMMIT;
