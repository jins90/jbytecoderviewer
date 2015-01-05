* HOW TO USE BYTE CODER

COMMANDS -
  ls 
  cat - only able to use cat inside methods.  cat "method_name" will print the byte code instruction of the method
  cd 

EXAMPLE -

jhkim@jhkim-ThinkPad-T430:~/refjvmbyte$ ./bytereader Go.class
(bytereader) ls
[Go extends java/lang/Object] (public, super)
  cpool
  methods
  fields
(bytereader) cd cpool
(bytereader) ls
Constant Pool size = 54
[  1] METHOD REF = (class_index = 14, nt_index = 34)
[  2] FIELD REF = (class_index = 11, nt_index = 35)
[  3] FIELD REF = (class_index = 11, nt_index = 36)
[  4] FIELD REF = (class_index = 11, nt_index = 37)
[  5] CLASS = (index = 38, value = java/util/HashMap)
[  6] METHOD REF = (class_index = 5, nt_index = 34)
[  7] FIELD REF = (class_index = 11, nt_index = 39)
[  8] STRING = (index = 40, value = HELLO)
[  9] FIELD REF = (class_index = 41, nt_index = 42)
[ 10] METHOD REF = (class_index = 43, nt_index = 44)
[ 11] CLASS = (index = 45, value = Go)
[ 12] METHOD REF = (class_index = 11, nt_index = 34)
[ 13] METHOD REF = (class_index = 11, nt_index = 46)
[ 14] CLASS = (index = 47, value = java/lang/Object)
[ 15] UTF8 = x
[ 16] UTF8 = I
[ 17] UTF8 = j
[ 18] UTF8 = k
[ 19] UTF8 = Ljava/lang/Integer;
[ 20] UTF8 = m
[ 21] UTF8 = Ljava/util/Map;
[ 22] UTF8 = Signature
[ 23] UTF8 = Ljava/util/Map<Ljava/lang/String;Ljava/lang/String;>;
[ 24] UTF8 = <init>
[ 25] UTF8 = ()V
[ 26] UTF8 = Code
[ 27] UTF8 = LineNumberTable
[ 28] UTF8 = hello
[ 29] UTF8 = (II)V
[ 30] UTF8 = main
[ 31] UTF8 = ([Ljava/lang/String;)V
[ 32] UTF8 = SourceFile
[ 33] UTF8 = Go.java
[ 34] NAME AND TYPE = (name_index = 24, desc_index = 25)
[ 35] NAME AND TYPE = (name_index = 15, desc_index = 16)
[ 36] NAME AND TYPE = (name_index = 17, desc_index = 16)
[ 37] NAME AND TYPE = (name_index = 18, desc_index = 19)
[ 38] UTF8 = java/util/HashMap
[ 39] NAME AND TYPE = (name_index = 20, desc_index = 21)
[ 40] UTF8 = HELLO
[ 41] CLASS = (index = 48, value = java/lang/System)
[ 42] NAME AND TYPE = (name_index = 49, desc_index = 50)
[ 43] CLASS = (index = 51, value = java/io/PrintStream)
[ 44] NAME AND TYPE = (name_index = 52, desc_index = 53)
[ 45] UTF8 = Go
[ 46] NAME AND TYPE = (name_index = 28, desc_index = 29)
[ 47] UTF8 = java/lang/Object
[ 48] UTF8 = java/lang/System
[ 49] UTF8 = out
[ 50] UTF8 = Ljava/io/PrintStream;
[ 51] UTF8 = java/io/PrintStream
[ 52] UTF8 = println
[ 53] UTF8 = (I)V
(bytereader) cd ..
(bytereader) ls
[Go extends java/lang/Object] (public, super)
  cpool
  methods
  fields
(bytereader) cd methods
(bytereader) ls
Number of methods = 3
 [  0] Name = <init> (()V)  [Public]
 [  1] Name = hello ((II)V)  [Public]
 [  2] Name = main (([Ljava/lang/String;)V)  [Public, Static]
(bytereader) cat hello
  [   0] ldc 8, 
  [   1] astore_3 
  [   2] aload_0 
  [   3] bipush 30, 
  [   4] putfield 0, 2, 
  [   5] aload_0 
  [   6] aload_0 
  [   7] getfield 0, 2, 
  [   8] iconst_5 
  [   9] iadd 
  [  10] putfield 0, 2, 
  [  11] bipush 10, 
  [  12] istore_1 
  [  13] bipush 50, 
  [  14] istore_2 
  [  15] getstatic 0, 9, 
  [  16] iload_2 
  [  17] invokevirtual 0, 10, 
  [  18] return 
(bytereader) cat main
  [   0] new 0, 11, 
  [   1] dup 
  [   2] invokespecial 0, 12, 
  [   3] astore_1 
  [   4] aload_1 
  [   5] bipush 20, 
  [   6] bipush 30, 
  [   7] invokevirtual 0, 13, 
  [   8] return 
(bytereader) cd .. 
(bytereader) ls
[Go extends java/lang/Object] (public, super)
  cpool
  methods
  fields
(bytereader) cd fields
(bytereader) ls
Number of fields = 4
[  0] Name = x (I)  [Public]
[  1] Name = j (I)  [Private]
[  2] Name = k (Ljava/lang/Integer;)  []
[  3] Name = m (Ljava/util/Map;)  []
(bytereader) exit
Good Bye

