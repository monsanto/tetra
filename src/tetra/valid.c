
#include "tr.h"

EXPORT byte valid_string_index (struct tetraprogram * program, word index)
{
 if (index > program->string_pool_count)
  return 0;
 return 1;
}