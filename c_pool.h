#ifndef C_POOL_H
#define C_POOL_H
#include "common.h"

#define UTF8        1
#define INT         3
#define FLOAT       4
#define LONG        5
#define DOUBLE      6
#define CLASS       7
#define STRING      8
#define FIELDREF    9
#define METHODREF   10
#define IMETHODREF  11
#define NAMEANDTYPE 12
#define MHANDLE     15
#define MTYPE       16
#define IDYNAMIC    18


void setCPool(ClassFile *cf, int fd);
void setCPoolDetail(CP_Info *cp, int fd, int cindex);
void setNameTypeInfo(NameAndType_Info *nt_info, int fd);
void setUTF8Info(UTF8_Info *u_info, int fd);
void setMethodInfo(Method_Info *m_info, int fd);
void setClassInfo(Class_Info *c_info, int fd);
void setStringInfo(String_Info *s_info, int fd);
void setIntInfo(Integer_Info *i_info, int fd);
void setFloatInfo(Float_Info *f_info, int fd);
void setFieldRefInfo(Field_Info *fld_info, int fd);


#endif
