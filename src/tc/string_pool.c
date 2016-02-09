
#include "tc.h"

word sp_add (char * string, dword length) // while we only accept bytes...
                 // we need to be able to detect if something is over 255
{
 word index, i = 0 ;

 for (; i < tc.string_pool_entrys; i++)
  if (!strcmp(tc.string_pool[i].string, string))
   return i;

 index = tc.string_pool_entrys ++ ;

 tc.string_pool = (TCSTRING *) 
  realloc (tc.string_pool, tc.string_pool_entrys * sizeof(TCSTRING)) ;
 
 tc.string_pool[index].string = strdup (string) ;

 if (length > 255)
 {
  yyerror("String pool entry over 255 characters.. truncating.") ;
  tc.string_pool[index].length = 255 ;
  tc.string_pool[index].string[255] = 0;
 }
 else
  tc.string_pool[index].length = (byte) length ;

 return index ;
}

void sp_delete ()
{
 word i  ;

 if (!tc.string_pool)
  return ;

 for (i = 0; i < tc.string_pool_entrys; i++)
  free(tc.string_pool[i].string) ;

 free(tc.string_pool);
}
