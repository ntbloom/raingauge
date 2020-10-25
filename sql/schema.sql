/* schema.sql -- schema for the raingauge database */
SET CLIENT_MIN_MESSAGES to WARNING;
BEGIN;
    DROP TABLE IF EXISTS gauge CASCADE;
    CREATE TABLE gauge(
        id INT PRIMARY KEY,
        shortname TEXT NOT NULL,
        mm_per_click NUMERIC DEFAULT 0.2794,
        description TEXT NOT NULL,
        created_at TIMESTAMPTZ DEFAULT current_timestamp,
        UNIQUE(shortname)
    );

    DROP TABLE IF EXISTS ticks CASCADE;
    CREATE TABLE ticks (
        db_time TIMESTAMPTZ DEFAULT current_timestamp,
        gauge INT DEFAULT 1,
        num NUMERIC NOT NULL,
        FOREIGN KEY (gauge) REFERENCES gauge(id)
    );
COMMIT;
