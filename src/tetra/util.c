
#include "tinternal.h"

EXPORT byte tetra_is_real_str (char * TSTRING *)
{
 if (strchr(TSTRING *,'.'))
  return 1 ;
 else
  return 0 ;
}