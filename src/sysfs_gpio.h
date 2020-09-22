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

int _write_to_file(const char* msg, const char* fdesc);

int create_pin(struct Pin pin);
int remove_pin(struct Pin pin);
const char* get_direction(struct Pin pin);
int set_direction(struct Pin pin, const char* dir);

#endif
