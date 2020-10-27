#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libpq-fe.h"

PGconn* dbconnect(const char*);
int add_tick(PGconn*, int);
double all_ticks(PGconn*, int);

#endif
