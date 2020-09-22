#ifndef SYSFS_GPIO_H
#define SYSFS_GPIO_H

struct Pin {
  const char* num;
  const char* fname;
  const char* fexport;
  const char* funexport;
  const char* fdirection;
  const char* fvalue;
};

int create_pin(struct Pin pin);
int remove_pin(struct Pin pin);

#endif
