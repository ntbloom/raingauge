/* schema.sql -- schema for local sqlite file */
DROP TABLE IF EXISTS gauge CASCADE;
CREATE TABLE gauge(
    id INT PRIMARY KEY,
    shortname TEXT NOT NULL,
    mm_per_click REAL DEFAULT 0.2794,
    description TEXT NOT NULL,
    created_at TEXT, /* timestamp */
    UNIQUE(shortname)
);

DROP TABLE IF EXISTS ticks CASCADE;
CREATE TABLE ticks (
    db_time TEXT, /* current_timestamp */
    gauge INT DEFAULT 1,
    num REAL NOT NULL,
    FOREIGN KEY (gauge) REFERENCES gauge(id)
);
