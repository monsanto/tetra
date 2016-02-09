
#include "tcommon.h"

byte tf_print (struct tprogram * program, byte arg_count, 
			   struct targ ** args, struct targ * retval)
{
 byte i ;

 if (!arg_count)
  return TC_ARG_COUNT_WRONG ;
 for (i = 0; i < arg_count; i++)
  fputs(tetra_to_string(args[i],0,0),stdout) ;

 return TC_RETURN ;
}

byte tf_input (struct tprogram * program, byte arg_count,
			   struct targ ** args, struct targ * retval)
{
 dword len = 1024, str_len = 0, actual_len;
 char * TSV, * read_str ;
 if (arg_count >= 1)
  TSV = tetra_to_string(args[0],0,&str_len);
 if (arg_count >= 2)
  len = tetra_to_number(args[1],0) ;
 if (arg_count >= 3)
  return TC_ARG_COUNT_WRONG ;
 if (str_len)
  printf("%s ", TSV) ;
 read_str = (char*) malloc(len+1) ;
 fgets(read_str,len,stdin) ;
 actual_len = strlen(read_str) - 1 ;
 read_str[actual_len] = 0 ;
 tetra_set_string(retval,read_str,actual_len) ;
 free(read_str) ;
 return TC_RETURN ;
}