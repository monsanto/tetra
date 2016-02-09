
#include "tinternal.h"

INLINE byte _tetra_situation_real(TARG * arg1, TARG * arg2)
{
 if (arg1->type == TYPE_REAL || arg2->type == TYPE_REAL)
  return 1 ;
 else if (arg1->type == TYPE_STRING)
 {
  if (tetra_is_real_str(arg1->string->string))
   return 1;
 }
 else if (arg2->type == TYPE_STRING)
 {
  if (tetra_is_real_str(arg2->string->string))
   return 1;
 }
 
 return 0 ;
}

EXPORT void tetra_add (TARG * arg1, TARG * arg2, 
					   TARG * result)
{
 if (_tetra_situation_real(arg1,arg2))
 {
  result->type = TYPE_REAL ;
  result->real = tetra_to_real(arg1,0) + tetra_to_real(arg2,0) ;
 }
 else
 {
  result->type = TYPE_NUMBER ;
  result->number = tetra_to_number(arg1,0) + tetra_to_number(arg2,0) ;
 }
}

EXPORT void tetra_sub (TARG * arg1, TARG * arg2, 
					   TARG * result) 
{
 if (_tetra_situation_real(arg1,arg2))
 {
  result->type = TYPE_REAL ;
  result->real = tetra_to_real(arg1,0) - tetra_to_real(arg2,0) ;
 }
 else
 {
  result->type = TYPE_NUMBER ;
  result->number = tetra_to_number(arg1,0) - tetra_to_number(arg2,0) ;
 }
}

EXPORT void tetra_mul (TARG * arg1, TARG * arg2, 
					   TARG * result) 
{
 if (_tetra_situation_real(arg1,arg2))
 {
  result->type = TYPE_REAL ;
  result->real = tetra_to_real(arg1,0) * tetra_to_real(arg2,0) ;
 }
 else
 {
  result->type = TYPE_NUMBER ;
  result->number = tetra_to_number(arg1,0) * tetra_to_number(arg2,0) ;
 }
}

EXPORT void tetra_div (TARG * arg1, TARG * arg2, 
					   TARG * result) 
{
 if (_tetra_situation_real(arg1,arg2))
 {
  result->type = TYPE_REAL ;
  result->real = tetra_to_real(arg1,0) / tetra_to_real(arg2,0) ;
 }
 else
 {
  result->type = TYPE_NUMBER ;
  result->number = tetra_to_number(arg1,0) / tetra_to_number(arg2,0) ;
 }
}

EXPORT void tetra_pow (TARG * arg1, TARG * arg2, 
					   TARG * result) 
{
 double n = pow(tetra_to_real(arg1,0),tetra_to_real(arg2,0)) ;
 if (_tetra_situation_real(arg1,arg2))
 {
  result->type = TYPE_REAL ;
  result->real = n ;
 }
 else
 {
  result->type = TYPE_NUMBER ;
  result->number = (long)n ;
 }
}

EXPORT void tetra_mod (TARG * arg1, TARG * arg2, 
					   TARG * result) 
{
 if (_tetra_situation_real(arg1,arg2))
 {
  result->type = TYPE_REAL ;
  result->real = fmod(tetra_to_real(arg1,0),tetra_to_real(arg2,0)) ;
 }
 else
 {
  result->type = TYPE_NUMBER ;
  result->number = tetra_to_number(arg1,0) % tetra_to_number(arg2,0) ;
 }
}

EXPORT byte tetra_cat (TARG * arg1, TARG * arg2, TARG * result)
{
 dword len1, len2, lenresult ;
 char * str1, * str2, * strresult ; 
 char buffer1[16], buffer2[16] ; // since we call tetra_to_string twice,
                                 // we need our own buffers
 struct stringvalue * tstr ;

 str1 = tetra_to_string(arg1,buffer1,&len1) ;
 str2 = tetra_to_string(arg2,buffer2,&len2) ;
 lenresult = len1+len2 ;
 strresult = (char *) malloc(lenresult+1) ;
 if (!strresult) 
  return 0 ;
 strcpy(strresult,str1) ;
 strcat(strresult,str2) ;
 tstr = _tetra_new_string(strresult,lenresult) ;
 if (!tstr)
 {
  free(strresult);
  return 0;
 }
 result->type = TYPE_STRING ;
 result->string = tstr ;
 return 1 ;
}

INLINE byte _tetra_situation_string (TARG * arg1, TARG * arg2)
{
 if (arg1->type == TYPE_STRING && arg2->type == TYPE_STRING)
  return 1 ;
 return 0 ;
}

EXPORT void tetra_eq (TARG * arg1, TARG * arg2, 
					  TARG * result) 
{
 result->type = TYPE_NUMBER ;
 if (_tetra_situation_string(arg1,arg2))
  // screw tetra_to_string here, we KNOW its a string.
  result->number = !strcmp(arg1->string->string,arg2->string->string) ;
 else if (_tetra_situation_real(arg1,arg2))
 {
  byte exact ;
  double number1, number2 ;
  number1 = tetra_to_real(arg1,&exact) ;
  if (!exact)
  {
   result->number = 0 ;
   return ;
  }
  number2 = tetra_to_real(arg2,&exact) ;
  if (!exact)
  {
   result->number = 0 ;
   return ;
  }
  result->number = number1 == number2 ;
 }
 else
 {
  byte exact ;
  long number1, number2 ;
  number1 = tetra_to_number(arg1,&exact) ;
  if (!exact)
  {
   result->number = 0 ;
   return ;
  }
  number2 = tetra_to_number(arg2,&exact) ;
  if (!exact)
  {
   result->number = 0 ;
   return ;
  }
  result->number = number1 == number2 ;
 }
}

EXPORT void tetra_nq (TARG * arg1, TARG * arg2, 
					  TARG * result) 
{
 result->type = TYPE_NUMBER ;
 if (_tetra_situation_string(arg1,arg2))
  // screw tetra_to_string here, we KNOW its a string.
  result->number = !!strcmp(arg1->string->string,arg2->string->string) ;
 else if (_tetra_situation_real(arg1,arg2))
 {
  byte exact ;
  double number1, number2 ;
  number1 = tetra_to_real(arg1,&exact) ;
  if (!exact)
  {
   result->number = 1 ;
   return ;
  }
  number2 = tetra_to_real(arg2,&exact) ;
  if (!exact)
  {
   result->number = 1 ;
   return ;
  }
  result->number = number1 != number2 ;
 }
 else
 {
  byte exact ;
  long number1, number2 ;
  number1 = tetra_to_number(arg1,&exact) ;
  if (!exact)
  {
   result->number = 1 ;
   return ;
  }
  number2 = tetra_to_number(arg2,&exact) ;
  if (!exact)
  {
   result->number = 1 ;
   return ;
  }
  result->number = number1 != number2 ;
 }
}

// i hated writing all of this...
EXPORT void tetra_lt (TARG * arg1, TARG * arg2, TARG * result)
{
 char buffer1[16], buffer2[16], * buf1, * buf2 ;
 result->type = TYPE_NUMBER ;
 if (_tetra_situation_string(arg1,arg2))
  // screw tetra_to_string here, we KNOW its a string.
  result->number = strcmp(arg1->string->string,arg2->string->string) > 0 ;
 else if (_tetra_situation_real(arg1,arg2))
 {
  byte exact ;
  double number1, number2 ;
  number1 = tetra_to_real(arg1,&exact) ;
  if (!exact)
   goto string_cmp ;
  number2 = tetra_to_real(arg2,&exact) ;
  if (!exact)
   goto string_cmp ;
  result->number = number1 > number2 ;
 }
 else
 {
  byte exact ;
  long number1, number2 ;

  number1 = tetra_to_number(arg1,&exact) ;
  if (!exact)
   goto string_cmp ;
  number2 = tetra_to_number(arg2,&exact) ;
  if (!exact)
   goto string_cmp ;
  result->number = number1 > number2 ;
 }

 return ;

string_cmp:
 buf1 = tetra_to_string(arg1,buffer1,0) ;
 buf2 = tetra_to_string(arg2,buffer2,0) ;
 result->number = strcmp(buf1,buf2) > 0 ;
}

EXPORT void tetra_gt (TARG * arg1, TARG * arg2, TARG * result)
{
 char buffer1[16], buffer2[16], * buf1, * buf2 ;
 result->type = TYPE_NUMBER ;
 if (_tetra_situation_string(arg1,arg2))
  // screw tetra_to_string here, we KNOW its a string.
  result->number = strcmp(arg1->string->string,arg2->string->string) < 0 ;
 else if (_tetra_situation_real(arg1,arg2))
 {
  byte exact ;
  double number1, number2 ;
  number1 = tetra_to_real(arg1,&exact) ;
  if (!exact)
   goto string_cmp ;
  number2 = tetra_to_real(arg2,&exact) ;
  if (!exact)
   goto string_cmp ;
  result->number = number1 < number2 ;
 }
 else
 {
  byte exact ;
  long number1, number2 ;

  number1 = tetra_to_number(arg1,&exact) ;
  if (!exact)
   goto string_cmp ;
  number2 = tetra_to_number(arg2,&exact) ;
  if (!exact)
   goto string_cmp ;
  result->number = number1 < number2 ;
 }

 return ;

string_cmp:
 buf1 = tetra_to_string(arg1,buffer1,0) ;
 buf2 = tetra_to_string(arg2,buffer2,0) ;
 result->number = strcmp(buf1,buf2) < 0 ;
}

EXPORT void tetra_lteq (TARG * arg1, TARG * arg2, TARG * result)
{
 char buffer1[16], buffer2[16], * buf1, * buf2 ;
 result->type = TYPE_NUMBER ;
 if (_tetra_situation_string(arg1,arg2))
  // screw tetra_to_string here, we KNOW its a string.
  result->number = strcmp(arg1->string->string,arg2->string->string) >= 0 ;
 else if (_tetra_situation_real(arg1,arg2))
 {
  byte exact ;
  double number1, number2 ;
  number1 = tetra_to_real(arg1,&exact) ;
  if (!exact)
   goto string_cmp ;
  number2 = tetra_to_real(arg2,&exact) ;
  if (!exact)
   goto string_cmp ;
  result->number = number1 >= number2 ;
 }
 else
 {
  byte exact ;
  long number1, number2 ;

  number1 = tetra_to_number(arg1,&exact) ;
  if (!exact)
   goto string_cmp ;
  number2 = tetra_to_number(arg2,&exact) ;
  if (!exact)
   goto string_cmp ;
  result->number = number1 >= number2 ;
 }

 return ;

string_cmp:
 buf1 = tetra_to_string(arg1,buffer1,0) ;
 buf2 = tetra_to_string(arg2,buffer2,0) ;
 result->number = strcmp(buf1,buf2) >= 0 ;
}

EXPORT void tetra_gteq (TARG * arg1, TARG * arg2, TARG * result)
{
 char buffer1[16], buffer2[16], * buf1, * buf2 ;
 result->type = TYPE_NUMBER ;
 if (_tetra_situation_string(arg1,arg2))
  // screw tetra_to_string here, we KNOW its a string.
  result->number = strcmp(arg1->string->string,arg2->string->string) <= 0 ;
 else if (_tetra_situation_real(arg1,arg2))
 {
  byte exact ;
  double number1, number2 ;
  number1 = tetra_to_real(arg1,&exact) ;
  if (!exact)
   goto string_cmp ;
  number2 = tetra_to_real(arg2,&exact) ;
  if (!exact)
   goto string_cmp ;
  result->number = number1 <= number2 ;
 }
 else
 {
  byte exact ;
  long number1, number2 ;

  number1 = tetra_to_number(arg1,&exact) ;
  if (!exact)
   goto string_cmp ;
  number2 = tetra_to_number(arg2,&exact) ;
  if (!exact)
   goto string_cmp ;
  result->number = number1 <= number2 ;
 }

 return ;

string_cmp:
 buf1 = tetra_to_string(arg1,buffer1,0) ;
 buf2 = tetra_to_string(arg2,buffer2,0) ;
 result->number = strcmp(buf1,buf2) <= 0 ;
}
