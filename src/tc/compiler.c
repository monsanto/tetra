
#include "tc.h"

void compile () 
{
 TETRAHEADER th ;
 word i = 0;

 th.binary_byte = 0x01 ;
 th.signature = 'TE' ;
 th.versionmajor = 1 ;
 th.versionminor = 0 ;
 th.debug_enabled = 0; // for now
 th.register_count = 0;
 th.string_count = tc.string_pool_entrys ;
 th.object_count = 0; // for now
 th.function_count = tc.function_pool_entrys ;

 fwrite(&th,sizeof(TETRAHEADER),1,yyout) ;

 for (; i < tc.string_pool_entrys; i++)
 {
  fwrite(&tc.string_pool[i].length,1,1,yyout) ;
  fwrite(tc.string_pool[i].string,tc.string_pool[i].length,1,yyout) ;
 }

 for (i = 0; i < tc.function_pool_entrys; i++)
 {
  byte j = 0;
  fwrite(&tc.function_pool[i].index,2,1,yyout) ;
  fwrite(&tc.function_pool[i].arg_count,1,1,yyout) ; 
  for (;j < tc.function_pool[i].arg_count; j++)
   fwrite(&tc.function_pool[i].args[j],2,1,yyout) ; 
  fwrite(&tc.function_pool[i].current_size,4,1,yyout) ;
  fwrite(tc.function_pool[i].chunk,tc.function_pool[i].current_size,1,yyout) ;
 }
}
