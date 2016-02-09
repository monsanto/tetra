
#include "tinternal.h"

#ifndef NO_ARG_CHUNK
TARG * find_arg_in_chunk (TCHUNK * chunk)
{
 TARG * arg ;
 byte i ;
 if (!chunk->amount_avail)
  return 0 ;
 arg = &chunk->chunk[chunk->first_avail] ;
 chunk->amount_avail-- ;
 if (chunk->amount_avail)
 {
  for (i = chunk->first_avail+1 ; i < ARG_CHUNK_SIZE ; i++)
  {
   if (chunk->chunk[i].type == TYPE_UNALLOC)
   {
	chunk->first_avail = i ;
	break ;
   }
  }
 }
 return arg ;
}

byte new_arg_chunk (TPROGRAM * program) 
{
 byte i ;
 TCHUNK * chunk = (TCHUNK *)
   malloc(sizeof(TCHUNK)) ;
 if (!chunk)
  return 0 ;
 chunk->chunk = (TARG*) 
  malloc(ARG_CHUNK_SIZE*sizeof(TARG)) ;
 if (!chunk->chunk)
 {
  free(chunk) ;
  return 0 ;
 }
 for (i = 0; i < ARG_CHUNK_SIZE; i++)
 {
  chunk->chunk[i].type = TYPE_UNALLOC ;
  chunk->chunk[i].arg_chunk = chunk ;
  chunk->chunk[i].position = i ;
 }
 if (program->arg_chunk_first)
  program->arg_chunk_first->next = chunk ;
 program->arg_chunk_first = chunk ;
 chunk->next = 0 ;
 chunk->amount_avail = ARG_CHUNK_SIZE ;
 chunk->first_avail = 0 ;
 return 1 ;
}
#endif

TARG * get_arg (TPROGRAM * program)
{
 TARG * arg ;
#ifdef NO_ARG_CHUNK
 arg = (TARG *) malloc(sizeof(TARG)) ;
 if (!arg)
  return 0 ;
 arg->ref = 0 ;
 return arg ;
#else
 TCHUNK * chunk = program->arg_chunk_first ;
 while (chunk)
 {
  if (arg = find_arg_in_chunk(chunk))
   return arg ;

  chunk = chunk->next ;
 }
 new_arg_chunk (program) ;
 arg = find_arg_in_chunk (program->arg_chunk_first) ;
 arg->ref = 0;
 return arg ;
#endif
}

TARG * TAPI targ_new_num (TPROGRAM * program, int num)
{
 TARG * arg = get_arg (program) ;
 arg->type = TYPE_NUMBER ;
 arg->number = num ;
 return arg ; 
}

void targ_free (TPROGRAM * program, TARG * arg)
{
#ifdef NO_ARG_CHUNK
 free(arg) ;
#else
 TCHUNK * chunk = arg->arg_chunk ;
 chunk->amount_avail++ ;
 if (chunk->first_avail > arg->position) 
  chunk->first_avail = arg->position ;
 arg->type = TYPE_UNALLOC ;
#endif
}

void TAPI targ_preparechange (TARG * arg)
{
 if (arg->type == TYPE_STRING)
  tstr_dec_ref (arg->string) ;
 else if (arg->type == TYPE_RESOURCE)
  tres_dec_ref (arg->resource) ;
}

void TAPI targ_dec_ref (TPROGRAM * program, TARG * arg) 
{
 if (!--arg->ref)
 {
  targ_preparechange (arg) ; 
  targ_free (program, arg) ;
 }
}

// this is too big to be a macro.
void TAPI targ_copyF (TARG * arg, TARG * arg2)
{
 switch (arg->type = arg2->type)
 {
 case TYPE_NUMBER:
  arg->number = arg2->number ;
  break ;
 case TYPE_REAL:
  arg->real = arg2->real ;
  break ;
 case TYPE_STRING:
  arg->string = arg2->string ;
  new_string_ref (arg->string) ;
  break ;
 case TYPE_RESOURCE:
  arg->resource = arg2->resource ;
  new_resource_ref (arg->resource) ;
 }
}

void TAPI targ_copy (TARG * arg, TARG * arg2)
{
 del_arg_member_ref (arg) ; 
 FAST_copy_arg (arg,arg2) ;
}

#define tres_set(arg,res) \
 ((arg)->type = TYPE_RESOURCE, (arg)->resource = res) ;

