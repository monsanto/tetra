
#include "tinternal.h"

struct tfunction * find_function (TPROGRAM * program, char * name)  
{
 dword i, count ;

 for (i = 0, count = bcount(program->functions); i < count; i++)
 {
  struct tfunction * fd = (struct tfunction *)
   bget (program->functions, i) ;

  if (strcmpi(fd->name, name) == 0)
   return fd ;
 }

 return 0;
}

byte add_function (TPROGRAM * program,
				   struct tfunction * function)
{
 struct tfunction ** fd ;

 if (!(program->flags & PF_FUNCTIONS)) 
  return 0;

 fd = (struct tfunction **)
  balloc(&program->functions) ;

 if (!fd)
  return 0 ; 

 *fd = function ;

 new_function_ref(function) ;

 return 1 ;
}

byte call_function (TPROGRAM * program, 
					struct tfunction * function,
					byte arg_count,
                    TARG ** args,
                    TARG * retval)
{

 if (function->type == FUNCTION_TETRA)
 {
  struct ttfunction * tf = (struct ttfunction *) function ;
  byte ret ;

  if (tf->arg_count != arg_count)
   return EC_ARG_COUNT_WRONG ;

  if (!new_stack (program)) ;
  return EC_MEMORY ;

  if (!set_args (program, tf, args))
   return EC_MEMORY ; // TODO: Add memory cleanup.. memory errors are rare anyway

  ret = execute_binary (program, to_binary(code), retval) ;

  free_stack (program) ;

  return ret ;
 }
 else
 {
  struct tnfunction * nf = (struct tnfunction *) function ;
  return nf->function (program, arg_count, args, retval) ;
 }
}

struct tfunction * new_function (TSTRING * name, byte ** binary, dword length, 
 byte arg_count, TSTRING * * arguments)
{
 byte i ;
 struct ttfunction * tf = (struct ttfunction *)
  malloc (sizeof(struct ttfunction) + length) ;
 
 if (!tf)
  return 0 ;

 tf->header.name = name ;
 tf->header.type = FUNCTION_TETRA ;
 tf->header.ref = 0 ;

 tf->length = length ;
 tf->arg_count = arg_count ;
 tf->arguments = arguments ;

 new_string_ref (name) ;

 for (i = 0; i < arg_count; i++)
  new_string_ref (arguments[i]) ;

 *binary = to_binary (tf) ;

 return (struct tfunction *) tf ;
}

struct tfunction * new_native_function (TSTRING * name, FUNCTIONPOINTER function)
{
 struct tnfunction * nf = (struct tnfunction *)
  malloc(sizeof(struct tnfunction)) ;

 if (!nf)
  return 0 ;

 nf->header.name = name ;
 nf->header.type = FUNCTION_NATIVE ;
 nf->header.ref = 0 ;

 nf->function = function ;

 new_string_ref(name) ;

 return (struct tfunction *) nf ;
}

#define new_function_ref(function) (function)->ref++

void del_function_ref (struct tfunction * function)
{
 function->ref -- ;
 if (!function->ref)
  free_function (function) ;
}

void free_function (struct tfunction * function)
{
 if (function->type == FUNCTION_TETRA)
 {
  byte i ;
  struct ttfunction * tf = (struct ttfunction *) function ;

  if (tf->arguments)
  {
   for (i = 0; i < tf->arg_count; i++)
	del_string_ref(tf->arguments[i]) ;
   free (tf->arguments) ;
  }
 }

 free(function) ;
}