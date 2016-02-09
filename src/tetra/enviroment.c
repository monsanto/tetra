
#include "tr.h"

EXPORT struct enviroment * create_enviroment (byte debug_enabled,
											  byte register_count,
											  word string_count,
											  word object_count, 
											  word function_count, 
											  word native_function_count)
{
 struct enviroment * env = (struct enviroment *)
  malloc (sizeof(struct enviroment)) ;

 if (!env)
  return 0 ;

 env->debug_enabled = debug_enabled ;

 if (register_count)
 {
  env->registers = (struct argument **) 
   malloc (register_count * sizeof(struct argument*)) ;

  if (!env->registers)
   goto end ;
 }

 env->register_count = register_count ;

 if (string_count)
 {
  env->registers = (struct argument **) 
   malloc (register_count * sizeof(struct argument*)) ;

  if (!env->registers)
   goto end ;
 }

 bulkinit(&env->strings,sizeof(struct stringvalue **),STRING_INCV) ;


end:
 free (env) ;
 return 0 ;
}