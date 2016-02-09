
#include "tc.h"

TCLOOP * lp_add ()
{
 word index, i = 0;

 index = tc.loop_pool_entrys ++ ;
 tc.loop_pool = (TCLOOP *)
  realloc(tc.loop_pool, tc.loop_pool_entrys * sizeof(TCLOOP)) ;
 tc.cur_loop = &tc.loop_pool[index] ;
 tc.cur_loop->begin_pos = 0;
 tc.cur_loop->end_pos = 0;
 tc.cur_loop->trace_point_count = 0;
 tc.cur_loop->trace_points = 0;
 return tc.cur_loop ;
}

TCLOOP * lp_get (word i) 
{
 long /* notice how this isnt unsigned! */ get = tc.loop_pool_entrys-1 ;
 if (i > get)
  return 0;
 return &tc.loop_pool[get-i] ;
}

void lp_add_trace (TCLOOP * loop, dword position)
{
 word index = loop->trace_point_count ++ ;
 loop->trace_points = (dword*) 
  realloc(loop->trace_points, loop->trace_point_count * sizeof(dword)) ;
 loop->trace_points[index] = position ;
}

void lp_end ()
{
 word i, index;
 if (tc.cur_loop->trace_point_count)
 {
  for (i = 0; i < tc.cur_loop->trace_point_count; i++)
   chunk_writeat(tc.cur_loop->trace_points[i],tc.cur_loop->end_pos,4) ;
  free(tc.cur_loop->trace_points);
 }
 index = -- tc.loop_pool_entrys - 1;
 if (tc.loop_pool_entrys != 0)
 {
 tc.loop_pool = (TCLOOP *)
  realloc(tc.loop_pool, tc.loop_pool_entrys * sizeof(TCLOOP)) ;
 tc.cur_loop = &tc.loop_pool[index] ;
 }
 else
  free(tc.loop_pool) ;
}

void lp_delete () 
{
 word i;
 if (tc.loop_pool_entrys)
 {
  for (i = 0; i < tc.loop_pool_entrys; i++)
   free(tc.loop_pool[i].trace_points) ;
  free(tc.loop_pool) ;
 }
}