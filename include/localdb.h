#ifndef LOCALDB_H
#define LOCALDB_H

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

/* define the schema for a simple on-disk sqlite database */
#define SCHEMA                                 \
    "BEGIN;"                                   \
    "DROP TABLE IF EXISTS gauge;"              \
    "CREATE TABLE gauge("                      \
    "id INT PRIMARY KEY,"                      \
    "shortname TEXT NOT NULL,"                 \
    "mm_per_click REAL NOT NULL,"              \
    "description TEXT NOT NULL,"               \
    "created_at TEXT NOT NULL,"                \
    "UNIQUE(shortname)"                        \
    ");"                                       \
    "DROP TABLE IF EXISTS ticks;"              \
    "CREATE TABLE ticks ("                     \
    "db_time TEXT,"                            \
    "gauge INT DEFAULT 1,"                     \
    "num REAL NOT NULL,"                       \
    "FOREIGN KEY (gauge) REFERENCES gauge(id)" \
    ");"                                       \
    "COMMIT;"
#define NEWGAUGE                                                                     \
    "BEGIN;"                                                                         \
    "INSERT INTO gauge (id, shortname, mm_per_click, description, created_at)"       \
    "VALUES ("                                                                       \
    "1,"                                                                             \
    "'test',"                                                                        \
    "0.2794,"                                                                        \
    "'Argent Data Systems Magnetic Reed Switch, 0.011 inch or 0.2794 mm per click'," \
    "DateTime('now')"                                                                \
    ");"                                                                             \
    "COMMIT;"

#define LOCALDB "/home/pi/rain/local.db"
#define INSERTCLICK "INSERT INTO ticks (gauge, num) SELECT 1, mm_per_click FROM gauge WHERE id = "

/* Creates a sqlite database file.  Schema is embedded within the function for simplicity over
 * extensibility */
int create_db(const char*);

/* Creates sample raingauge. Used for testing and development mostly */
int create_sample_gauge(sqlite3*);

/* Connect to a database that already exists and has a schema. Returns a pointer to the db struct */
sqlite3* db_connect(const char*);

/* Adds a tick to the database object */
int db_add_tick(sqlite3*, int);

/* Prints all ticks from the database object */
void db_print_ticks(sqlite3*, int);

#endif
