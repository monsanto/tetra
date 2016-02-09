
#include "tinternal.h"
#include <ctype.h>

// cast functions. just to encourage 
// function to accept both numbers and strings.

// oh what the hell, every system has 16 bytes to share.
// this is useful anyway.
char cast_from_number[16] ;

char * to_string (TARG * arg, char * buffer, dword * length)
{
 char * data ;
 dword len ;
 if (!buffer)
  data = cast_from_number ;
 else
  data = buffer ;
 switch(arg->type)
 {
 case TYPE_NUMBER:
  len = sprintf(data,"%i",arg->number) ;
  break ;
 case TYPE_REAL:
  len = sprintf(data,"%g",arg->real) ;
  break ;
 case TYPE_RESOURCE:
  len = sprintf(data,"0x%x",(int)arg->resource->resource) ;
  break ;
 case TYPE_STRING: // special case g
  if (length)
   *length = arg->string->length ;
  return arg->string->string ; // screw buffer.
 }
 if (length)
  *length = len ;
 return data;
}

dword to_buffer (TARG * arg, char * buffer, dword max_len)
{
 char * string ;
 dword length ;

 string = to_string(arg,buffer,&length) ;

 if (string != buffer) // was our arg already a string?
  strncpy(buffer,string,max_len) ;

 return length ;
}

long to_number (TARG * arg, byte * exact)
{
 switch (arg->type)
 {
 case TYPE_NUMBER:
  if (exact) 
   *exact = 1 ;
  return arg->number ;
 case TYPE_REAL:
  if (exact) 
   *exact = 1 ;
  return (long) arg->real ;
 case TYPE_RESOURCE:
  if (exact) 
   *exact = 1 ;
  return (long)arg->resource->resource ;
 case TYPE_STRING:
  {
   char * check_exact ;
   long ret = strtol(arg->string->string,&check_exact,10) ;
   if (exact) 
	*exact = !*check_exact ;
   return ret;
  }
 }
 if (exact) 
  *exact = 0 ;
 return 0 ;
}

double to_real (TARG * arg, byte * exact)
{
 switch (arg->type)
 {
 case TYPE_NUMBER:
  if (exact) 
   *exact = 1 ;
  return (double)arg->number;
 case TYPE_REAL:
  if (exact) 
   *exact = 1 ;
  return arg->real ;
 case TYPE_STRING:
  {
   char * check_exact ;
   double ret = strtod(arg->string->string,&check_exact) ;
   if (exact) 
	*exact = !*check_exact ;
   return ret;
  }
 case TYPE_RESOURCE:
  if (exact) 
   *exact = 1 ;
  return (double)(long)arg->resource->resource ;
 }
 if (exact) 
  *exact = 0 ;
 return 0 ;
}

byte to_bool (TARG * arg)
{
 switch (arg->type)
 {
 case TYPE_NUMBER:
  return (arg->number) ? 1 : 0 ;
 case TYPE_REAL:
  return (arg->real) ? 1 : 0 ;
 case TYPE_STRING:
  return (arg->string->length) ? 1 : 0 ;
 case TYPE_RESOURCE:
  return (arg->resource->resource) ? 1 : 0 ;
 }
 return 0 ;
}

// This is strict. There is no casting between resources.
// Programs expect the resource they set, not some half-assed cast.
void * to_resource (TARG * arg, void * function_id)
{
 if (arg->type == TYPE_RESOURCE)
 {
  if (arg->resource->function_id == function_id)
   return arg->resource->resource ;
 }
 return 0 ;
}