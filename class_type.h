#ifndef CLASSFILE_H
#define CLASSFILE_H
#include "c_pool.h"
#include "common.h"

void setMagic(ClassFile *cf, int fd);
void setVersion(ClassFile *cf, int fd);
void setAccessFlag(ClassFile *cf, int fd);
void setThisClass(ClassFile *cf, int fd);
void setSuperClass(ClassFile *cf, int fd);
void setInterfaces(ClassFile *cf, int fd);
void setFields(ClassFile *cf, int fd);
void setFieldDetail(Field_Detail *field, int fd);
void setMethods(ClassFile *cf, int fd);
void setMethodDetail(Method_Detail *method, int fd);
void setAttributeDetail(Attribute_Info *a, int fd);
void setAttributes(ClassFile *cf, int fd);
ClassFile *readClass(char file_name[]);

#endif
