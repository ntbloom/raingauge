#ifndef RAINGAUGE_H
#define RAINGAUGE_H

#include <stdlib.h>
#include "constants.h"
#include "pin.h"
#include "poll.h"
#include "sysfs.h"

/* startup pins, allocate memory, connect to the database */
int start(void);

/* close pins, deallocate memory, disconnect from the database */
int stop(void);

#endif
