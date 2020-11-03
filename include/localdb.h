#ifndef LOCALDB_H
#define LOCALDB_H

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

#define LOCALDB "/home/pi/rain/local.db"

/* Creates a sqlite database file.  Schema is embedded within the function for simplicity over
 * extensibility */
int create_db(const char*);

/* Connect to a database that already exists and has a schema. Returns a pointer to the db struct */
sqlite3* db_connect(const char*);

/* Adds a click to the database object */
int db_add_click(sqlite3*);

#endif
