#ifndef UTIL_H
#define UTIL_H

#include "common.h"

u2 convertShort(char buff[]);
u4 convertInt(char buff[]);
void jread(int fd, void *buff, int s, char *error);

#endif
