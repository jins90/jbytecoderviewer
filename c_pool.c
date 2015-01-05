#include <stdio.h>
#include <stdlib.h>
#include "c_pool.h"
#include "util.h"
#include "common.h"

/* set the class_info type constant pool */
void setClassInfo(Class_Info *c_info, int fd)
{
   u1 buff[2];
   
   jread(fd, buff, 2, "Unable to read Class Info");
   c_info->index = convertShort(buff);
}


/* set the method_info type constant pool */
void setMethodInfo(Method_Info *m_info, int fd)
{
   u1 buff[2];
  
   jread(fd, buff, 2, "Unable to read Method Info Index");
   m_info->index = convertShort(buff);
   jread(fd, buff, 2, "Unable to read Method Info NIndex");
   m_info->nt_index = convertShort(buff);
}

/* read UTF8 String */
void setUTF8Info(UTF8_Info *u_info, int fd) 
{
   u1 buff[2];

   jread(fd, buff, 2, "Unable to read UTF8 Length");
   u_info->len = convertShort(buff);
   u_info->bytes = (u1 *)malloc(sizeof(u1) * u_info->len+1);
   u_info->bytes[u_info->len +1] = '\0';
   jread(fd, u_info->bytes, u_info->len, "Unable to read UTF8");
}


/* set name and type */
void setNameTypeInfo(NameAndType_Info *nt_info, int fd)
{
   u1 buff[2];
  
   jread(fd, buff, 2, "Unable to read NameAndType Info");
   nt_info->n_index = convertShort(buff);
   jread(fd, buff, 2, "Unable to read NameAndType Info");
   nt_info->d_index = convertShort(buff);
}

/* read integer */
void setIntInfo(Integer_Info *i_info, int fd)
{
   u1 buff[4];
   jread(fd, buff, 4, "Unable to read Integer");
   i_info->bytes = convertInt(buff);
}

/* read float */
void setFloatInfo(Float_Info *f_info, int fd)
{
   u1 buff[4];
   jread(fd, buff, 4, "Unable to read Integer");
   f_info->bytes = convertInt(buff);
}


/* set field ref info */
void setFieldRefInfo(Field_Info *fld_info, int fd)
{
   char buff[2];
  
   jread(fd, buff, 2, "Unable to read field info index\n");
   fld_info->index = convertShort(buff);
   jread(fd, buff, 2, "Unable to read field into nt_index\n");
   fld_info->nt_index = convertShort(buff);
}

/* set the string information*/
void setStringInfo(String_Info *s_info, int fd)
{
   u1 buff[2];
  
   jread(fd, buff, 2, "Unable to read string index");
   s_info->s_index = convertShort(buff);
}

/* read constant pool detail */
void setCPoolDetail(CP_Info *cp, int fd, int cindex)
{
   u1 buff[2];

   jread(fd, &cp->tag, 1, "Unable to read CP flag");
   switch(cp->tag) {
      case UTF8:
        setUTF8Info(&cp->c_detail.u8_info, fd);
        break;
      case INT:
        setIntInfo(&cp->c_detail.i_info, fd);
        break;
      case FLOAT:
        setFloatInfo(&cp->c_detail.f_info, fd);   
      case CLASS:
        setClassInfo(&cp->c_detail.c_info, fd); 
        break; 
      case STRING: 
        setStringInfo(&cp->c_detail.s_info, fd);
        break;
      case FIELDREF:
        setFieldRefInfo(&cp->c_detail.fld_info, fd);
        break;
      case METHODREF:
        setMethodInfo(&cp->c_detail.m_info, fd);
        break;
      case NAMEANDTYPE:
        setNameTypeInfo(&cp->c_detail.nt_info, fd); 
        break;
      default:
         printf("Unable to handle %d\n", cp->tag);
         exit(1);
   }
}

/* read the constant pool information */
void setCPool(ClassFile *cf, int fd)
{
   u1 buff[2];
   int i;

   jread(fd, buff, 2, "Unable to read cpool count");
   cf->c_pool_count = convertShort(buff);
   cf->c_pool = (CP_Info *)malloc(sizeof(CP_Info) * (1 + cf->c_pool_count));

   for(i=1; i<cf->c_pool_count; i++) {
       setCPoolDetail(&cf->c_pool[i], fd, i); 
   }
}


