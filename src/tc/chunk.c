
#include "tc.h"

// returns position for later writing ;]
dword chunk_write (byte instruction, dword param, byte size)
{
 return chunk_write_ptr (instruction,&param,size) ;
}

dword chunk_write_ptr (byte instruction, void * param, byte size) 
{
 dword position = tc.cur_func->current_size ;

 tc.cur_func->current_size += size + 1 ;

 if (tc.cur_func->allocated_size < tc.cur_func->current_size)
 {
  tc.cur_func->allocated_size += 128 ;
  tc.cur_func->chunk = (char *) 
   realloc(tc.cur_func->chunk,tc.cur_func->allocated_size) ;
 }

 tc.cur_func->chunk[position++] = instruction ;
 memcpy (tc.cur_func->chunk+position,param,size);

 return position ;
}

dword chunk_get ()
{
 return tc.cur_func->current_size ;
}

void chunk_writeat (dword at, dword param, byte size)
{
 memcpy (tc.cur_func->chunk+at,&param,size);
}