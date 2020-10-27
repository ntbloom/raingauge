#ifndef RAINGAUGE_H
#define RAINGAUGE_H

#include <stdlib.h>
#include "../include/constants.h"
#include "../include/dbconnect.h"
#include "../include/pin.h"
#include "../include/poll.h"
#include "../include/sysfs.h"

/* startup pins, allocate memory, connect to the database */
int start(void);

/* close pins, deallocate memory, disconnect from the database */
int stop(void);

#endif
