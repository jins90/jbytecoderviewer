#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "class_type.h"
#include "common.h"

#define BSIZE   256
#define CSIZE   128
#define ROOT    0
#define CPOOL   1
#define METHODS 2
#define FIELDS  3

int path = ROOT;

void printClassInfo(ClassFile *cf)
{
     CP_Info *class_index = &cf->c_pool[cf->this_class];
     CP_Info *superc_index = &cf->c_pool[cf->super_class];
     CP_Info *str = &cf->c_pool[class_index->c_detail.c_info.index];
     char buff[200];

     printf("[%s extends ", str->c_detail.u8_info.bytes);
     str = &cf->c_pool[superc_index->c_detail.c_info.index];
     printf("%s] ", str->c_detail.u8_info.bytes); 

     buff[0] = '(';
     buff[1] = '\0';
     if(cf->access_flag & ACC_PUBLIC) {
          strcat(buff, "public, ");
     }
     if(cf->access_flag & ACC_FINAL) {
          strcat(buff, "final, ");
     }
     if(cf->access_flag & ACC_SUPER) {
          strcat(buff, "super, ");
     }
     if(cf->access_flag & ACC_INTERFACE) {
          strcat(buff, "interface, ");
     }
     if(cf->access_flag & ACC_ABSTRACT) {
          strcat(buff, "abstract, ");
     }
     if(cf->access_flag & ACC_SYNTHETIC) {
          strcat(buff, "Synthetic, ");
     }
     if(cf->access_flag & ACC_ANNOTATION) {
          strcat(buff, "Annotation, ");
     }
     if(cf->access_flag & ACC_ENUM) {
          strcat(buff, "Enum, ");
     }
     buff[strlen(buff) - 2] = '\0';
     strcat(buff, ")");
     printf("%s\n", buff);

}

void printRoot(ClassFile *cf)
{
     printClassInfo(cf);
     printf("  cpool\n");
     printf("  methods\n");
     printf("  fields\n");   
}

void printCPoolDetail(ClassFile *cf, int index)
{
   CP_Info *cp = &cf->c_pool[index];
   int cindex = 0;
   int ntindex = 0;
 
   switch(cp->tag) {
      case UTF8:
        printf("[%3d] UTF8 = %s\n", index, cp->c_detail.u8_info.bytes);  
        break;
      case INT:
        printf("[%3d] INT = %d\n", index, cp->c_detail.i_info.bytes);
        break;
      case CLASS:
        cindex = cp->c_detail.c_info.index;
        printf("[%3d] CLASS = (index = %d, value = %s)\n", index, cindex, cf->c_pool[cindex].c_detail.u8_info.bytes);
        break;  
      case STRING:
        cindex = cp->c_detail.s_info.s_index;
        printf("[%3d] STRING = (index = %d, value = %s)\n", index, cindex, cf->c_pool[cindex].c_detail.u8_info.bytes);
        break;
      case FIELDREF:
        cindex = cp->c_detail.fld_info.index;
        ntindex = cp->c_detail.fld_info.nt_index;
        printf("[%3d] FIELD REF = (class_index = %d, nt_index = %d)\n", index, cindex, ntindex);
        break;
      case METHODREF:
        cindex = cp->c_detail.m_info.index;
        ntindex = cp->c_detail.m_info.nt_index;
        printf("[%3d] METHOD REF = (class_index = %d, nt_index = %d)\n", index, cindex, ntindex);
        break;
      case NAMEANDTYPE:
        cindex = cp->c_detail.nt_info.n_index;
        ntindex = cp->c_detail.nt_info.d_index;
        printf("[%3d] NAME AND TYPE = (name_index = %d, desc_index = %d)\n", index, cindex, ntindex);
        break;
      default:
         printf("Unable to handle %d\n", cp->tag);
         exit(1);
   }
     
}

/* print the contant pool information */
void printCPool(ClassFile *cf)
{
     int i;

     printf("Constant Pool size = %d\n", cf->c_pool_count); 
     for(i=1; i<cf->c_pool_count; i++) {
         printCPoolDetail(cf, i);
     }
}

void printMethodDetail(ClassFile *cf, int index)
{
     int nindex = cf->methods[index].name_index;
     int dindex = cf->methods[index].d_index;
     char buff[200];

     printf(" [%3d] Name = %s ", index, cf->c_pool[nindex].c_detail.u8_info.bytes);     
     printf("(%s)  ", cf->c_pool[dindex].c_detail.u8_info.bytes);
     buff[0] = '[';
     buff[1] = '\0';
     if(cf->methods[index].access_flags & ACC_PUBLIC) {
          strcat(buff, "Public, ");
     }
     else if(cf->methods[index].access_flags & ACC_PRIVATE) {
          strcat(buff, "Private, ");
     }
     else if(cf->methods[index].access_flags & ACC_PROTECTED) {
          strcat(buff, "Protected, ");
     }

     if(cf->methods[index].access_flags & ACC_STATIC) {
          strcat(buff, "Static, ");
     }
     if(cf->methods[index].access_flags & ACC_FINAL) {
          strcat(buff, "Final, ");
     }
     if(cf->methods[index].access_flags & ACC_SYNCHRONIZED) {
          strcat(buff, "Synchronized, ");
     }
     if(cf->methods[index].access_flags & ACC_BRIDGE) {
          strcat(buff, "Bridge, ");
     }
     if(cf->methods[index].access_flags & ACC_VARARGS) {
          strcat(buff, "Varargs, "); 
     }  
     if(cf->methods[index].access_flags & ACC_NATIVE) {
          strcat(buff, "Native, ");
     }
     if(cf->methods[index].access_flags & ACC_ABSTRACT) {
          strcat(buff, "Abstract, ");
     }
     if(cf->methods[index].access_flags & ACC_STRICT) {
          strcat(buff, "Strict, " );
     }
     if(cf->methods[index].access_flags & ACC_SYNTHETIC) {
          strcat(buff, "Synthetic, ");
     }
     buff[strlen(buff) - 2] = '\0';
     strcat(buff, "]");
     printf("%s\n", buff);

}

/* print a list of methods */
void printMethods(ClassFile *cf)
{
     int i;
     
     printf("Number of methods = %d\n", cf->method_count);
     for(i=0; i<cf->method_count; i++) {
         printMethodDetail(cf, i);
     }
}

void printFieldDetail(ClassFile *cf, int index)
{
     int nindex = cf->fields[index].name_index;
     int dindex = cf->fields[index].d_index;
     char buff[200];

     printf("[%3d] Name = %s ", index, cf->c_pool[nindex].c_detail.u8_info.bytes);
     printf("(%s)  ", cf->c_pool[dindex].c_detail.u8_info.bytes); 
     buff[0] = '[';
     buff[1] = '\0'; 
     if(cf->fields[index].access_flags & ACC_PUBLIC) {
          strcat(buff, "Public, ");
     }
     else if(cf->fields[index].access_flags & ACC_PRIVATE) {
          strcat(buff, "Private, ");
     }
     else if(cf->fields[index].access_flags & ACC_PROTECTED) {
          strcat(buff, "Protected, ");
     }

     if(cf->fields[index].access_flags & ACC_STATIC) {
          strcat(buff, "Static, ");
     }
     if(cf->fields[index].access_flags & ACC_FINAL) {
          strcat(buff, "Final, ");
     }
     if(cf->fields[index].access_flags & ACC_VOLATILE) {
          strcat(buff, "Volatile, ");
     }
     if(cf->fields[index].access_flags & ACC_TRANSIENT) {
          strcat(buff, "Transient, "); 
     }
     if(cf->fields[index].access_flags & ACC_SYNTHETIC) {
          strcat(buff, "Synthetic, ");
     }
     if(cf->fields[index].access_flags & ACC_ENUM) {
          strcat(buff, "Enum, ");
     }
     buff[strlen(buff) - 2] = '\0';
     strcat(buff, "]");
     printf("%s\n", buff);
}

/* print a list of fields */
void printFields(ClassFile *cf)
{
     int i;

     printf("Number of fields = %d\n", cf->field_count);
     for(i=0; i<cf->field_count; i++) {
         printFieldDetail(cf, i);
     }
}


/* ls command */
void executeLS(ClassFile *cf)
{
     switch(path) {
         case ROOT:
            printRoot(cf);          
            break;
         case CPOOL:
            printCPool(cf); 
            break;
         case METHODS:
            printMethods(cf);
            break;
         case FIELDS:
            printFields(cf); 
            break;
     }

}

/* cd command */
void executeCD(char param[])
{
     if(strlen(param) == 0) {
         return;
     }
     switch(path) {
         case ROOT:
            if(strcmp(param, "cpool") == 0) {
                 path = CPOOL;
            }
            else if(strcmp(param, "methods") == 0) {
                 path = METHODS;
            }
            else if(strcmp(param, "fields") == 0) {
                 path = FIELDS;
            }
            else {
                 printf("Path %s not found\n", param);
            }
            break;
         case CPOOL:
            if(strcmp(param, "..") == 0) {
                 path = ROOT;
            } 
            else {
                 printf("Path %s not found\n", param);
            }
            break;
         case METHODS:
            if(strcmp(param, "..") == 0) {
                 path = ROOT;
            } 
            else {
                 printf("Path %s not found\n", param);
            }
            break;
         case FIELDS:
            if(strcmp(param, "..") == 0) {
                 path = ROOT;
            }
            else {
                 printf("Path %s not found\n", param);
            }
            break;
         default:
            printf("ERROR\n");
            break;
     }
}


void executeCAT(ClassFile *cf, char param[])
{
     int nindex;
     int i;
     int j;
     Method_Detail *m_detail;
     Attribute_Info *attrib;
     UTF8_Info *utf8_info;


     if(strlen(param) == 0) {
         return;
     }

     for(i=0; i<cf->method_count; i++) {
         m_detail = &cf->methods[i];
         nindex = m_detail->name_index;
         if(strcmp(cf->c_pool[nindex].c_detail.u8_info.bytes, param) == 0) {
              for(j=0; j<m_detail->a_count; j++) {
                  attrib = &m_detail->attributes[j];
                  utf8_info = &cf->c_pool[attrib->name_index].c_detail.u8_info;
                  if(strcmp("Code", utf8_info->bytes) == 0) {
                        printOpcode(&attrib->info[4]);
                  }
              }              
         }
     }
}

/* handle the appropriate command */
void execute(char command[], char param[], ClassFile *cf)
{
     if(strcmp(command, "ls") == 0) {
         executeLS(cf); 
     }
     else if(strcmp(command, "cd") == 0) {
         executeCD(param);
     }
     else if(strcmp(command, "clear") == 0) {
         system("clear");
     }
     else if(strcmp(command, "exit") == 0) {
         return;
     }
     else if(path == METHODS && strcmp(command, "cat") == 0) {
         executeCAT(cf, param); 
     }
     else {
         printf("Command not found\n");
     }
}

/* parse line into a command and a single argument */
void processCommand(char buff[], ClassFile *cf)
{
     char *sp = buff;
     char command[CSIZE];
     char param[CSIZE]; 
     int cindex = 0;
     int pindex = 0;

     while(isspace(*sp)) {
         sp++;
     }
     while(!isspace(*sp) && *sp != '\0') {
         command[cindex++] = *sp;
         sp++;
     }
     command[cindex] = '\0';
     if(*sp == '\0') {
        param[0] = '\0';
        execute(command, param, cf);
        return;
     }     
     while(isspace(*sp)) {
         sp++;
     }
     while(!isspace(*sp) && *sp != '\0') {
         param[pindex++] = *sp;
         sp++;
     }
     param[pindex] = '\0';
     execute(command, param, cf);
}


/* read a line from standard input until user enters exit */
void readCommands(ClassFile *cf)
{
     char buff[BSIZE];
     int len;

     do {
        printf("(bytereader) ");
        fgets(buff, BSIZE, stdin);
        len = strlen(buff);
        buff[len-1] = '\0';
        processCommand(buff, cf);
     }  while( strcmp(buff, "exit") != 0);
     printf("Good Bye\n");
}

int main(int argc, char *argv[])
{
     ClassFile *cf;

     if(argc < 1) {
        printf("Input class file not provided\n");
        printf("Example: ./bytereader Test.class\n");
        exit(1);
     }
     cf = readClass(argv[1]);
     readCommands(cf);
}

