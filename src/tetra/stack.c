 
#include "tinternal.h"

byte new_stack (TPROGRAM * program)
{
 program->current_stack = (struct tstack *) balloc (&program->stacks) ;

 if (!program->current_stack)
  return 0 ;

 if (!bpalloc(&program->current_stack->arg_stack,ARG_STACK_INCR))
  return 0;

 if (!bpalloc(&program->current_stack->local_vars, VAR_INCR))
  return 0 ;

 return 1 ;
}

byte free_stack (TPROGRAM * program) 
{
 dword i, count;

 for (i = 0, count = bcount(program->current_stack->local_vars); i < count; i++)
 {
  TARG * arg = ((TVARSTACK *)
   bget(program->current_stack->local_vars,i))->var ;
  del_arg_ref(program,arg) ;
 }

 bdelete(&program->current_stack->local_vars) ;
 bdelete(&program->current_stack->arg_stack) ;
 
 program->current_stack = bfree (&program->stacks);

 if (!program->current_stack)
  return 0 ;

 return 1 ;
}

byte push (TPROGRAM * program, TARG * arg)
{
 TARG ** stack_arg = (TARG **) 
  balloc(&program->current_stack->arg_stack) ;

 if (!stack_arg)
  return 0 ;

 *stack_arg = arg ;

 arg->ref++ ;

 return 1 ;
}

TARG * pop (TPROGRAM * program)
{
 TARG * arg = * (TARG **) 
  bfree (&program->current_stack->arg_stack) ;

 if (!arg)
  return 0 ;

 return arg ;
}

byte pop_multiple (TPROGRAM * program, dword arg_count, TARG ** args)
{
 dword i ;

 for (i = arg_count; i > 0; i--)
 {
  arg = * (TARG **) 
   bfree (&program->current_stack->arg_stack) ;

  if (!arg)
   return 0 ;

  if (!args)
   def_arg_ref (arg) ;
  else
   args[i-1] = arg ;
 }

 return 1 ;
}

byte set_args (TPROGRAM * program,
               struct ttfunction * tf,
               TARG ** args)
{
 byte i ; 

 if (!bpalloc (&program->current_stack->local_vars, code->arg_count))
  return 0;

 for ( i = 0 ; i < tf->arg_count ; i++ )
 {
  TVARSTACK * vs = (TVARSTACK *)
   bget(program->current_stack->local_vars,i) ;
  vs->name = tf->arguments[i] ;
  vs->var = args[i] ;
  args[i]->ref++ ;
 }

 return 1 ;
}