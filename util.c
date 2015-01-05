#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "util.h"

inline u2 convertShort(char buff[])
{
    return ((buff[0] << 8) & 0xFF00) | (buff[1] & 0xFF);
}

inline u4 convertInt(char buff[])
{
    return ((buff[0] << 24) & 0xFF000000) | ((buff[1] << 16) & 0xFF0000) | ((buff[2] << 8) & 0xFF00) | (buff[3] & 0xFF); 
}

void jread(int fd, void *buff, int s, char *error)
{
    int size;
  
    size = read(fd, buff, s);
    if(size != s) {
       printf("%s\n", error);
       exit(1);
    }
      
}
