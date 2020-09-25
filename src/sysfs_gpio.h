#ifndef SYSFS_GPIO_H
#define SYSFS_GPIO_H

#define OUT "out"
#define IN "in"
#define SYSFS "/sys/class/gpio/"
#define EXPORT "/sys/class/gpio/export"
#define UNEXPORT "/sys/class/gpio/unexport"
#define HIGH "1"
#define LOW "0"
#define TIMEOUT 5

struct Pin {
    const char* num;
    const char* fdesc;
    const char* direction;
    const char* value;
};

int _write_to_file(const char*, const char*);
char* _read_file(const char*);

int create_pin(struct Pin);
int remove_pin(struct Pin);
const char* get_direction(struct Pin);
int set_direction(struct Pin, const char*);
int set_value(struct Pin, const char*);
const char* get_value(struct Pin);

#endif
