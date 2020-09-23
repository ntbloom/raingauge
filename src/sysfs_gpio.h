#ifndef SYSFS_GPIO_H
#define SYSFS_GPIO_H

#define OUT "out"
#define IN "in"
#define SYSFS "/sys/class/gpio/"
#define EXPORT "/sys/class/gpio/export"
#define UNEXPORT "/sys/class/gpio/unexport"
#define HIGH "1"
#define LOW "0"

struct Pin {
  const char* num;
  const char* fdesc;
  const char* direction;
  const char* value;
};

int _write_to_file(const char* msg, const char* fdesc);
char* _read_file(const char* fdesc);

int create_pin(struct Pin pin);
int remove_pin(struct Pin pin);
const char* get_direction(struct Pin pin);
int set_direction(struct Pin pin, const char* direction);

#endif
