#ifndef LOCALDB_H
#define LOCALDB_H

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

#define LOCALDB "/home/pi/rain/local.db"

sqlite3* dbconnect(const char*);

#endif
