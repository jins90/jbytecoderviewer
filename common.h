#ifndef COMMON_H
#define COMMON_H

#define ACC_PUBLIC       0x0001
#define ACC_PRIVATE      0x0002
#define ACC_PROTECTED    0x0004
#define ACC_STATIC       0x0008
#define ACC_FINAL        0x0010
#define ACC_SUPER        0x0020
#define ACC_VOLATILE     0x0040
#define ACC_TRANSIENT    0x0080
#define ACC_SYNTHETIC    0x1000
#define ACC_INTERFACE    0x0200
#define ACC_ABSTRACT     0x0400
#define ACC_ANNOTATION   0x2000
#define ACC_ENUM         0x4000
#define ACC_SYNCHRONIZED 0x0020
#define ACC_BRIDGE       0x0040
#define ACC_VARARGS      0x0080
#define ACC_NATIVE       0x0100
#define ACC_ABSTRACT     0x0400
#define ACC_STRICT       0x0800
#define ACC_SYNTHETIC    0x1000
  
typedef unsigned char u1;
typedef unsigned short u2;
typedef unsigned int u4;

typedef struct {
   u2 index;
} Class_Info;

typedef struct {
   u2 index;
   u2 nt_index;
} Field_Info;

typedef struct {
   u2 index;
   u2 nt_index;
} Method_Info;

typedef struct {
   u2 index;
   u2 nt_index;
} InterfaceMethod_Info;

typedef struct {
   u2 s_index;
} String_Info;

typedef struct {
   u4 bytes;
} Integer_Info;

typedef struct {
   u4 bytes;
} Float_Info;

typedef struct {
   u4 high_bytes;
   u4 low_bytes;
} Long_Info;

typedef struct {
   u4 high_bytes;
   u4 low_bytes;
} Double_Info;

typedef struct {
   u2 n_index;
   u2 d_index;
} NameAndType_Info;

typedef struct {
   u2 len;
   u1 *bytes;
} UTF8_Info;

typedef struct {
   u2 ref_kind;
   u2 ref_index;
} MethodHandle_Info;

typedef struct {
   u2 d_index;
} MethodType_Info;

typedef struct {
   u2 b_m_index;
   u2 nt_index;
} InvokeDynamic_Info;

typedef struct CP_Info_ {
   u1 tag;
   char *info;
    union {
      Class_Info c_info;
      Field_Info fld_info;
      Method_Info m_info;
      InterfaceMethod_Info IM_info;
      String_Info s_info;
      Integer_Info i_info;
      Float_Info f_info;
      Long_Info l_info;
      Double_Info d_info;
      NameAndType_Info nt_info;
      UTF8_Info u8_info;
      MethodHandle_Info mh_info;
      MethodType_Info mt_info;
      InvokeDynamic_Info id_info;
   } c_detail;
} CP_Info;

typedef struct Attribute_Info_ {
   u2 name_index;
   u4 length;
   u1 *info;
} Attribute_Info;

typedef struct Field_Detail_ {
   u2 access_flags;
   u2 name_index;
   u2 d_index;
   u2 a_count;
   Attribute_Info *attributes;
} Field_Detail;

typedef struct Method_Detail_ {
   u2 access_flags;
   u2 name_index;
   u2 d_index;
   u2 a_count;
   Attribute_Info *attributes;
} Method_Detail;

typedef struct ClassFile_ {
   u1 magic[4];
   u2 minor_version;
   u2 major_version;
   u2 c_pool_count;
   CP_Info *c_pool;
   u2 access_flag;
   u2 this_class;
   u2 super_class;
   u2 interface_count;
   u2 *interfaces;
   u2 field_count;
   Field_Detail *fields;
   u2 method_count;
   Method_Detail *methods;
   u2 attribute_count;
   Attribute_Info *attributes;
} ClassFile;


#endif
