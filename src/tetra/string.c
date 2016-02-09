
#include "tinternal.h"

dword string_length (char * string)
{
 return FAST_string_length (to_sv(string)) ;
}

TSTRING * find_string (TPROGRAM * program, char * string)
{
 dword i, count ;

 for (i = 0, count = bcount(program->strings); i < count; i++)
 {
  TSTRING * TSTRING * = bget(program->strings,i) ;
  if (!strcmp(TSTRING *,string))
   return TSTRING * ;
 }

 return 0 ;
}

byte find_multiple_strings (TPROGRAM * program,
					 char ** strings,
					 dword * lengths,
					 TSTRING * * results,
					 dword item_count,
					 dword flags)
{
 dword i, j, count ;

 if (flags & FSE_ZERO_RESULTS)
  memset (results, 0, sizeof(char*) * item_count) ;

 for (i = 0, count = bcount(program->strings); i < count; i++)
 {
  TSTRING * TSTRING * = bget(program->strings,i) ;

  for (j = 0; j < item_count; j++)
  {
   if (!results[j])
	if (!strcmp(TSTRING *,strings[j]))
	 results[j] = TSTRING * ;
  }
 }

 if (flags & FSE_CREATE)
 {
  for (i = 0; i < item_count; i++)
   if (!results[i])
	if (!(results[i] == new_string (strings[i], lengths[i])))
	 return 0 ;
 }

 return 1 ;
}

TSTRING * find_string_from_index (TPROGRAM * program,
							   dword index)
{
 if (index < bcount(program->strings))
  return bget(program->strings,index) ;
}

TSTRING * create_string (dword length)
{
 struct stringvalue * sv = (struct stringvalue *) 
  malloc(sizeof(struct stringvalue) + length + 1) ;

 if (!sv)
  return 0 ;

 sv->length = length ;
 sv->ref = 0 ;

 return to_str(TSTRING *) ;
}

byte add_string (TPROGRAM * program, TSTRING * string)
{
 TSTRING * * sp ;

 sp = (char **) balloc(&program->strings) ;

 if (!sp)
  return 0 ;

 *sp = string ;

 return 1 ;
}

void free_string (TSTRING * TSTRING *)
{
  FAST_free_string(to_sv(TSTRING *)) ;
}

void new_string_ref (TSTRING * TSTRING *)
{
 struct stringvalue * sv = to_sv(TSTRING *) ;
 FAST_new_string_ref (sv) ;
}

void del_string_ref (TSTRING * TSTRING *)
{
 struct stringvalue * sv = to_sv(TSTRING *) ;
 FAST_del_string_ref(sv) ;
}
