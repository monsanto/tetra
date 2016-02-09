
#include "tc.h"

void fp_add (word string)
{
 word index, i = 0;

 for (; i < tc.function_pool_entrys; i++)
  if (tc.function_pool[i].index == string)
  {
   yyerror ("Repeat function");
   break ;
  }
 
  index = tc.function_pool_entrys ++ ;
  tc.function_pool = (TCFUNCTION *)
   realloc(tc.function_pool, tc.function_pool_entrys * sizeof(TCFUNCTION)) ;
  tc.cur_func = &tc.function_pool[index] ;

  tc.cur_func->index = string ;
  tc.cur_func->args = 0;
  tc.cur_func->arg_count = 0;
  tc.cur_func->chunk = 0;
  tc.cur_func->allocated_size = 0;
  tc.cur_func->current_size = 0;
}

void fp_revert (void) 
{
 tc.cur_func = &tc.function_pool[0] ;
}

void fp_arg (word string)
{
 word index, i = 0 ;

 for (; i < tc.cur_func->arg_count; i++)
  if (tc.cur_func->args[i] == string)
  {
   yyerror("Repeat targ");
   break ;
  }

 index = tc.cur_func->arg_count ++ ;
 tc.cur_func->args = (word *) 
  realloc(tc.cur_func->args, tc.cur_func->arg_count * sizeof(word)) ;
 tc.cur_func->args[index] = string ;
}

void fp_delete ()
{
 word i = 0;

 if (!tc.function_pool)
  return ;

 for (; i < tc.function_pool_entrys; i++)
 {
  if (tc.function_pool[i].args)
   free(tc.function_pool[i].args);
  if (tc.function_pool[i].chunk)
   free(tc.function_pool[i].chunk);
 }

 free(tc.function_pool) ;
}