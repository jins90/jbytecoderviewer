#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "class_type.h"
#include "util.h"
#include "c_pool.h"

/* read magic number CAFEBABY, if the magic number doesnt exist exit program */
void setMagic(ClassFile *cf, int fd)
{
   int size;

   jread(fd, cf->magic, 4, "Unable to read magic number");
   if(cf->magic[0] == 0xCA && cf->magic[1] == 0xFE &&
         cf->magic[2] == 0xBA && cf->magic[3] == 0xBE) {
   //   printf("Valid Magic Number\n");
   }
   else {
      printf("Not a valid Java Class File\n");
      exit(1);
   }
}

/* read Java class version */
void setVersion(ClassFile *cf, int fd)
{
   int size;
   u1 buff[2];
   
   jread(fd, buff, 2, "Unable to read minor version");
   cf->minor_version = convertShort(buff); 
   jread(fd, buff, 2, "Unable to read major version");
   cf->major_version = convertShort(buff);
}


/* Read access flag of class */
void setAccessFlag(ClassFile *cf, int fd)
{
   u1 buff[2];

   jread(fd, buff, 2, "Unable to read access flag");
   cf->access_flag = convertShort(buff);
}

/* set this.class of the class file */
void setThisClass(ClassFile *cf, int fd)
{
   u1 buff[2];

   jread(fd, buff, 2, "Unable to read this flag");
   cf->this_class = convertShort(buff);
}

/* set super.class of the class file */
void setSuperClass(ClassFile *cf, int fd)
{
   u1 buff[2];

   jread(fd, buff, 2, "Unable to read super flag");
   cf->super_class = convertShort(buff);
}

/* set the interface count of the class file, followed by the interfaces that map to the constant pool */
void setInterfaces(ClassFile *cf, int fd)
{
   u1 buff[2];
   int i;

   jread(fd, buff, 2, "Unable to read interface count");
   cf->interface_count = convertShort(buff);

   if(cf->interface_count > 0) {
      cf->interfaces = (u2 *)malloc(sizeof(u2) * cf->interface_count);
      for(i=0; i<cf->interface_count; i++) {
          jread(fd, buff, 2, "Unable to read interfaces");
          cf->interfaces[i] = convertShort(buff);
      }
   }   
}

/* set field detail */
void setFieldDetail(Field_Detail *field, int fd)
{
   u1 buff[2];
   int i;
   jread(fd, buff, 2, "Unable to read field access flag");
   field->access_flags = convertShort(buff);
   jread(fd, buff, 2, "Unable to read name index");
   field->name_index = convertShort(buff);
   jread(fd, buff, 2, "Unable to read descriptor index");
   field->d_index = convertShort(buff);
   jread(fd, buff, 2, "Unable to read attributes count");
   field->a_count = convertShort(buff);

   if(field->a_count > 0) {
      field->attributes = (Attribute_Info *)malloc(sizeof(Attribute_Info) * field->a_count);
      for(i=0; i<field->a_count; i++) {
         setAttributeDetail(&field->attributes[i], fd);
      }
   }
}

/* set the fields of the class file */
void setFields(ClassFile *cf,  int fd)
{
    u1 buff[2];
    int i;
   
    jread(fd, buff, 2, "Unable to read fields count");
    cf->field_count = convertShort(buff);
    
    if(cf->field_count > 0)  {
       cf->fields = (Field_Detail *)malloc(sizeof(Field_Detail) * cf->field_count);
       for(i=0; i<cf->field_count; i++) {
          setFieldDetail(&cf->fields[i], fd);
       }
    }
}

void setAttributes(ClassFile *cf, int fd)
{
    u1 buff[2];
    int i;
    
    jread(fd, buff, 2, "Unable to read attribute count");
    cf->attribute_count = convertShort(buff);
    
    if(cf->attribute_count > 0) {
       cf->attributes = (Attribute_Info *)malloc(sizeof(Attribute_Info) * cf->attribute_count);
       setAttributeDetail(&cf->attributes[i], fd);
    }
}

/* set attribute detail */
void setAttributeDetail(Attribute_Info *a, int fd)
{
   u1 buff[4];
   int i;

   jread(fd, buff, 2, "Unable to read attribute index");
   a->name_index = convertShort(buff);
   jread(fd, buff, 4, "Unable to read attribute length");
   a->length = convertInt(buff);
   a->info = (u1 *)malloc(sizeof(u1) * a->length); 
   for(i=0; i<a->length; i++) {
       jread(fd, &a->info[i], 1, "Unable to read attribute info");
   }
}

/* set method detail */
void setMethodDetail(Method_Detail *method, int fd)
{
   u1 buff[2];
   int i;
   jread(fd, buff, 2, "Unable to read field access flag");
   method->access_flags = convertShort(buff);
   jread(fd, buff, 2, "Unable to read name index");
   method->name_index = convertShort(buff);
   jread(fd, buff, 2, "Unable to read descriptor index");
   method->d_index = convertShort(buff);
   jread(fd, buff, 2, "Unable to read attributes count");
   method->a_count = convertShort(buff);

   if(method->a_count > 0) {
      method->attributes = (Attribute_Info *)malloc(sizeof(Attribute_Info) * method->a_count);
      for(i=0; i<method->a_count; i++) {
         setAttributeDetail(&method->attributes[i], fd);  
      }
   }
}

/* set methods of the class file */
void setMethods(ClassFile *cf, int fd)
{
    u1 buff[2];
    int i;
  
    jread(fd, buff, 2, "Unable to read method count");
    cf->method_count = convertShort(buff);
   
    if(cf->method_count > 0) {
       cf->methods = (Method_Detail *)malloc(sizeof(Method_Detail) * cf->method_count);
       for(i=0; i<cf->method_count; i++) {
          setMethodDetail(&cf->methods[i], fd);
       }
    }
}

/* read a Java Byte Class into ClassFile structure and return */
ClassFile *readClass(char file_name[])
{
   int fd = open(file_name, O_RDONLY);
   ClassFile *cf;
   char buff[2];

   cf = (ClassFile *)malloc(sizeof(ClassFile));
   if(fd == 1) {
      printf("Unable to open class file %s\n", file_name);
      exit(1);
   }
   setMagic(cf, fd);
   setVersion(cf, fd);
   setCPool(cf, fd);
   setAccessFlag(cf, fd);
   setThisClass(cf, fd);
   setSuperClass(cf, fd);
   setInterfaces(cf, fd);
   setFields(cf,  fd);
   setMethods(cf, fd);
   setAttributes(cf, fd);
   close(fd);
   
   return cf;
}
