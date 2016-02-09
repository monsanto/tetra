
#include "tinternal.h"

/* I use goto here. Bite me. I'm not going to repeat the same
code over and over. */
TPROGRAM * new_program (dword flags,
                              byte register_count,
							  dword string_count,
							  dword object_count,
							  dword function_count,
							  dword native_function_count)
{
 TPROGRAM * program ;

 program = (TPROGRAM *) 
  malloc(sizeof(TPROGRAM)) ;

 if (!program)
  return 0 ;

 program->flags = flags ;

 if (register_count)
 {
  program->registers = (TARG **) 
   malloc (register_count * sizeof(TARG *)) ;

  if (!program->registers)
   goto end ;

  memset(program->registers, 0, 
   register_count * sizeof(TARG *)) ;
 }

 program->register_count = register_count ;

 program->strings = (TSTRING * *) 
   bnew (sizeof(TSTRING *), STRING_INCR) ;

 if (!program->strings)
  goto end2 ;

 if (string_count)
  if (!bpalloc((void**)&program->strings, string_count))
   goto end2 ;

 if (flags & PF_OBJECTS)
 {
  program->objects = (struct objectdef **) 
   bnew (sizeof(struct objectdef *), OBJECT_INCR) ;

  if (!program->objects)
   goto end3 ;

  if (object_count)
   if (!bpalloc((void**)&program->objects, object_count))
	goto end3 ;
 }

 if (flags & PF_FUNCTIONS)
 {
  program->functions = (struct ttfunction *) 
   bnew (sizeof(struct ttfunction), FUNCTION_INCR) ;

  if (!program->functions)
   goto end4 ;

  if (function_count)
   if (!bpalloc(&program->functions,function_count))
	goto end4 ;
 }

 if (flags & PF_STACKS)
  {
  program->stacks = (struct tstack *)
   bnew(sizeof(struct tstack), FUNCTION_STACK_INCR) ;

  if (!program->stacks)
   goto end5 ;

  program->current_stack = 0 ;
  
  program->global_vars = (TVARSTACK *)
   bnew(sizeof(TVARSTACK),VAR_INCR) ;

  if (!program->global_vars)
   goto end6 ;
  }

 if (flags & PF_NATIVE_FUNCTIONS)
 {
  program->native_functions = (struct tnfunction *) 
   bnew (sizeof(struct ttfunction), FUNCTION_INCR) ;

  if (!program->native_functions)
   goto end7 ;

  if (native_function_count)
   if (!bpalloc((void**)&program->functions,function_count))
	goto end7 ;
 }

 program->chunk_ptr = 0 ;
 program->chunk_start = 0 ;

#ifndef NO_ARG_CHUNK
 program->arg_chunk_first = 0 ;
#endif

 set_catch_handler(program,default_catch_handler) ;
 return program;

 // rollback!
 // not like walmart though, so shush
end7:
 if (flags & PF_STACKS)
 {
  bdelete (&program->global_vars) ;
end6:
  bdelete (&program->stacks) ;
 }
end5:
 if (flags & PF_FUNCTIONS)
  bdelete (&program->functions) ;
end4:
 if (flags & PF_OBJECTS)
  bdelete (&program->objects) ;
end3:
 bdelete(&program->strings) ;
end2:
 if (register_count)
  free (program->registers) ;
end:
 free (program) ;
 return 0 ;
}

void reset_program (TPROGRAM * program)
{
 // coming later! 
}

void free_program (TPROGRAM * program)
{
 dword i, count ;

#ifndef NO_ARG_CHUNK
 TCHUNK * chunk = program->arg_chunk_first ;
#endif

 if (program->flags & PF_STACKS)
 {
  for (i = 0, count = bcount(program->global_vars); i < count; i++)
  {
   TARG * arg = ((TVARSTACK *)
	bget(program->global_vars,i))->var ;

   free_arg (program, arg) ;
  }

  bdelete (&program->global_vars) ;
 }

#ifndef NO_ARG_CHUNK
 while (chunk)
 {
  TCHUNK * next = chunk->next ;
  free(chunk->chunk) ;
  free(chunk);
  chunk = next ;
 }
#endif

 for (i = 0, count = bcount(program->strings); i < count; i++ )
  free_string ((TSTRING *)bget(program->strings, i)) ;

 bdelete (&program->strings) ;

 //for (i = 0; i < program->object_pool_count; i++ )
 //free (program->object_pool[i].members) ;

 if (program->flags & PF_FUNCTIONS)
 {
  for (i = 0, count = bcount(program->functions); i < count; i++ )
  {
   struct ttfunction * tf = (struct ttfunction *)
	bget (program->functions, i) ;

   free_codeblock (tf->code) ;
  }
  bdelete (&program->functions) ;
 }

 if (program->flags & PF_NATIVE_FUNCTIONS)
  bdelete (&program->native_functions) ;

 if (program->register_count)
  free (program->registers) ;

 free (program) ;
}
