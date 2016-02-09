
#include "tinternal.h"

// this only returns global variables. C interface doesnt need to mess
// with the stacks
TARG * get_variable (TPROGRAM * program, TSTRING * name)
{
 TVARSTACK * vs ;
 dword i, count ;

 for (i = 0, count = bcount(program->global_vars); i < count; i++)
 {
  vs = (TVARSTACK *) 
   bget (program->global_vars,i) ;
  if (!strcmpi(vs->name,name))
   return vs->var ;
 }

 vs = (TVARSTACK *) balloc (&program->global_vars) ;

 vs->name = name ;
 new_string_ref(name) ;
 vs->var = ta_new (program) ;

 return vs->var ;
}

TARG * get_local_variable (TPROGRAM * program, TSTRING * name)
{
 TVARSTACK * vs ;
 dword i, count ;

 for (i = 0, count = bcount(program->current_stack->local_vars); i < count; i++)
 {
  vs = (TVARSTACK *) 
   bget (program->current_stack->local_vars,i) ;
  if (!strcmpi(vs->name,name))
   return vs->var ;
 }

 vs = (TVARSTACK *) balloc (&program->current_stack->local_vars) ;

 vs->name = name ;
 new_string_ref(name) ;
 vs->var = ta_new (program) ;

 return vs->var ;
}