#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <stdio.h>
#include "libpq-fe.h"

PGconn* dbconnect(const char*);

#endif
