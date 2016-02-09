
#include "tcommon.h"

void tf_fclose_func (FILE * file)
{
 fclose(file) ;
}

byte tf_fopen (struct tprogram * program, byte arg_count, 
			   struct targ ** args, struct targ * retval)
{
 FILE * file ;
 if (arg_count != 2)
  return TC_ARG_COUNT_WRONG ;
 file = fopen(tetra_to_string(args[0],0,0),tetra_to_string(args[1],0,0)) ;
 if (file && retval)
  tetra_set_resource(retval,file,tf_fclose_func) ;
 return TC_RETURN; 
}

byte tf_fwrite (struct tprogram * program, byte arg_count, 
			    struct targ ** args, struct targ * retval)
{
 FILE * file ;
 dword len = 0;
 byte i ;

 if (arg_count < 2)
  return TC_ARG_COUNT_WRONG ;

 file = tetra_to_resource(args[0]) ;

 if (!file)
  return TC_RETURN ;

 for (i = 1; i < arg_count; i++)
 {
  char * TSV ;
  dword arg_len, write_len ;
  TSV = tetra_to_string(args[i],0,&arg_len) ;
  write_len = fwrite(TSV,1,arg_len,file) ;
  len += write_len ;
  if (write_len != arg_len)
   break ;
 }

 if (retval)
  tetra_set_number(retval,len) ;

 return TC_RETURN; 
}

byte tf_fread (struct tprogram * program, byte arg_count, 
			   struct targ ** args, struct targ * retval)
{
 FILE * file ;
 char * TSV ;
 dword len ;
 dword size ;

 if (arg_count != 2)
  return TC_ARG_COUNT_WRONG ;

 file = tetra_to_resource(args[0]) ;

 if (!file)
  return TC_RETURN ;

  len = tetra_to_number(args[1],0) ;
 TSV = (char*)malloc(len+1) ;
 size = fread(TSV,1,len,file) ;
 TSV[size] = 0 ;
 if (retval)
  tetra_set_string(retval,TSV,size) ;
 free(TSV) ;
 return TC_RETURN; 
}

byte tf_fclose (struct tprogram * program, byte arg_count, 
			   struct targ ** args, struct targ * retval)
{
 FILE * file ;
 if (arg_count != 1)
  return TC_ARG_COUNT_WRONG ;
 file = tetra_to_resource(args[0]) ;
 if (!file)
  return TC_RETURN ;
 fclose(file) ;
 return TC_RETURN ;
}