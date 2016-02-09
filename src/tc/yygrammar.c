#line 2 "parser.acc"

 #include "tc.h"
 #pragma warning(disable:4013)
 #pragma warning(disable:4716)
 #pragma warning(disable:4715)

# line 9 "yygrammar.c"
#include "yygrammar.h"

YYSTART ()
{
   switch(yyselect()) {
   case 102: {
      program();
      get_lexval();
      } break;
   }
}

program ()
{
   switch(yyselect()) {
   case 1: {
#line 14 "parser.acc"

  fp_add(sp_add("$",1)); 
 
# line 30 "yygrammar.c"
      while (1) {
         switch (yyselect()) {
         case 103: {
            statement();
            } break;
         case 104: {
            function_def();
            } break;
         default: goto yy1;
         }
      }
      yy1: ;
#line 18 "parser.acc"

  chunk_write(TPUSH1,0,1) ; chunk_write(TRETURN,0,0) ; 
 
# line 47 "yygrammar.c"
      } break;
   }
}

function_def ()
{
   YYSTYPE name;
   switch(yyselect()) {
   case 2: {
      get_lexval();
      get_lexval();
      name = yylval;
#line 24 "parser.acc"
 fp_add(name.index); 
# line 62 "yygrammar.c"
      switch (yyselect()) {
      case 105: {
         } break;
      case 107: {
         get_lexval();
         function_def_arg();
         while (1) {
            switch (yyselect()) {
            case 106: {
               get_lexval();
               function_def_arg();
               } break;
            default: goto yy2;
            }
         }
         yy2: ;
         } break;
      case 108: {
         get_lexval();
         } break;
      default: printf("???\n"); exit(1);
      }
      content();
#line 26 "parser.acc"
 chunk_write(TPUSH1,0,1) ; chunk_write(TRETURN,0,0) ; fp_revert() ; 
# line 88 "yygrammar.c"
      } break;
   }
}

function_def_arg ()
{
   YYSTYPE arg;
   switch(yyselect()) {
   case 3: {
      get_lexval();
      arg = yylval;
#line 30 "parser.acc"
 fp_arg(arg.index); 
# line 102 "yygrammar.c"
      } break;
   }
}

content ()
{
   switch(yyselect()) {
   case 4: {
      get_lexval();
      statements();
      get_lexval();
      } break;
   case 5: {
      statement();
      } break;
   }
}

statements ()
{
   switch(yyselect()) {
   case 6: {
      statement();
      while (1) {
         switch (yyselect()) {
         case 109: {
            statement();
            } break;
         default: goto yy3;
         }
      }
      yy3: ;
      } break;
   }
}

statement ()
{
   switch(yyselect()) {
   case 7: {
      exp0();
      get_lexval();
#line 43 "parser.acc"
 chunk_write (TPOP, 0, 0) ; 
# line 147 "yygrammar.c"
      } break;
   case 8: {
      if_statement();
      } break;
   case 9: {
      while_statement();
      } break;
   case 10: {
      infinity_statement();
      } break;
   case 11: {
      continue_statement();
      get_lexval();
      } break;
   case 12: {
      break_statement();
      get_lexval();
      } break;
   case 13: {
      return_statement();
      get_lexval();
      } break;
   case 14: {
      get_lexval();
      } break;
   }
}

continue_statement ()
{
   YYSTYPE n;
#line 54 "parser.acc"

  TCLOOP * loop ;
 
# line 183 "yygrammar.c"
   switch(yyselect()) {
   case 15: {
      get_lexval();
#line 57 "parser.acc"

  loop = lp_get(0) ;
  if (!loop) 
   yyerror("No loop to continue") ;
  else
   chunk_write(TGOTO,loop->begin_pos,sizeof(dword)) ;  
 
# line 195 "yygrammar.c"
      } break;
   case 16: {
      get_lexval();
      get_lexval();
      n = yylval;
#line 64 "parser.acc"

  loop = lp_get(n.number-1) ;
  if (!loop) 
   yyerror("No loop to continue") ;
  else
   chunk_write(TGOTO,loop->begin_pos,sizeof(dword)) ; 
 
# line 209 "yygrammar.c"
      } break;
   }
}

break_statement ()
{
   YYSTYPE n;
#line 74 "parser.acc"

  TCLOOP * loop ;
 
# line 221 "yygrammar.c"
   switch(yyselect()) {
   case 17: {
      get_lexval();
#line 77 "parser.acc"

  loop = lp_get(0) ;
  if (!loop) 
   yyerror("No loop to break out of") ;
  else
   lp_add_trace(loop,chunk_write(TGOTO,0,4)) ;
 
# line 233 "yygrammar.c"
      } break;
   case 18: {
      get_lexval();
      get_lexval();
      n = yylval;
#line 84 "parser.acc"

  loop = lp_get(n.number-1) ;
  if (!loop) 
   yyerror("No loop to break out of") ;
  else
   lp_add_trace(loop,chunk_write(TGOTO,0,4)) ;
 
# line 247 "yygrammar.c"
      } break;
   }
}

if_statement ()
{
#line 94 "parser.acc"

  dword if_location, goto_location, else_location, end_location ;
 
# line 258 "yygrammar.c"
   switch(yyselect()) {
   case 19: {
      get_lexval();
      get_lexval();
      exp0();
      get_lexval();
#line 99 "parser.acc"

  if_location = chunk_write(TIF,0,4) ;
 
# line 269 "yygrammar.c"
      content();
      switch (yyselect()) {
      case 110: {
#line 103 "parser.acc"

  end_location = chunk_get() ;
  chunk_writeat(if_location,end_location,4) ;
 
# line 278 "yygrammar.c"
         } break;
      case 111: {
#line 106 "parser.acc"

  goto_location = chunk_write(TGOTO,0,4) ;
  else_location = chunk_get() ;
 
# line 286 "yygrammar.c"
         get_lexval();
         content();
#line 109 "parser.acc"

  end_location = chunk_get() ;
  chunk_writeat(if_location,else_location,4) ;
  chunk_writeat(goto_location, end_location, 4) ;
 
# line 295 "yygrammar.c"
         } break;
      default: printf("???\n"); exit(1);
      }
      } break;
   }
}

while_statement ()
{
#line 117 "parser.acc"

  TCLOOP * loop = lp_add () ;
  dword if_location ;
  loop->begin_pos = chunk_get() ;
 
# line 311 "yygrammar.c"
   switch(yyselect()) {
   case 20: {
      get_lexval();
      get_lexval();
      exp0();
      get_lexval();
#line 124 "parser.acc"

  if_location = chunk_write(TIF,0,4) ;
 
# line 322 "yygrammar.c"
      content();
#line 128 "parser.acc"

  loop = lp_get(0) ; // everything has a reason, trust me
  chunk_write(TGOTO,loop->begin_pos,4) ;
  loop->end_pos = chunk_get () ;
  chunk_writeat(if_location,loop->end_pos,4) ;
  lp_end () ;
 
# line 332 "yygrammar.c"
      } break;
   }
}

infinity_statement ()
{
#line 139 "parser.acc"

  TCLOOP * loop = lp_add () ;
  loop->begin_pos = chunk_get() ;
 
# line 344 "yygrammar.c"
   switch(yyselect()) {
   case 21: {
      get_lexval();
      content();
#line 145 "parser.acc"

  loop = lp_get(0) ;
  chunk_write(TGOTO,loop->begin_pos,4) ;
  loop->end_pos = chunk_get() ;
  lp_end () ;
 
# line 356 "yygrammar.c"
      } break;
   }
}

return_statement ()
{
   switch(yyselect()) {
   case 22: {
      get_lexval();
      exp0();
#line 154 "parser.acc"
 chunk_write (TRETURN, 0, 0) ; 
# line 369 "yygrammar.c"
      } break;
   case 23: {
      get_lexval();
#line 155 "parser.acc"
 chunk_write (TPUSH1, 0, 1) ; chunk_write (TRETURN, 0, 0) ; 
# line 375 "yygrammar.c"
      } break;
   }
}

exp0 ()
{
   switch(yyselect()) {
   case 24: {
      exp1();
      get_lexval();
      exp0();
#line 159 "parser.acc"
 chunk_write (TSET, 0, 0) ; 
# line 389 "yygrammar.c"
      } break;
   case 25: {
      exp1();
      get_lexval();
      get_lexval();
      exp0();
#line 160 "parser.acc"
 chunk_write (TSETADD, 0, 0) ; 
# line 398 "yygrammar.c"
      } break;
   case 26: {
      exp1();
      get_lexval();
      get_lexval();
      exp0();
#line 161 "parser.acc"
 chunk_write (TSETSUB, 0, 0) ; 
# line 407 "yygrammar.c"
      } break;
   case 27: {
      exp1();
      get_lexval();
      get_lexval();
      exp0();
#line 162 "parser.acc"
 chunk_write (TSETMUL, 0, 0) ; 
# line 416 "yygrammar.c"
      } break;
   case 28: {
      exp1();
      get_lexval();
      get_lexval();
      exp0();
#line 163 "parser.acc"
 chunk_write (TSETDIV, 0, 0) ; 
# line 425 "yygrammar.c"
      } break;
   case 29: {
      exp1();
      get_lexval();
      get_lexval();
      exp0();
#line 164 "parser.acc"
 chunk_write (TSETMOD, 0, 0) ; 
# line 434 "yygrammar.c"
      } break;
   case 30: {
      exp1();
      get_lexval();
      get_lexval();
      exp0();
#line 165 "parser.acc"
 chunk_write (TSETAND, 0, 0) ; 
# line 443 "yygrammar.c"
      } break;
   case 31: {
      exp1();
      get_lexval();
      get_lexval();
      exp0();
#line 166 "parser.acc"
 chunk_write (TSETOR, 0, 0) ; 
# line 452 "yygrammar.c"
      } break;
   case 32: {
      exp1();
      get_lexval();
      get_lexval();
      exp0();
#line 167 "parser.acc"
 chunk_write (TSETXOR, 0, 0) ; 
# line 461 "yygrammar.c"
      } break;
   case 33: {
      exp1();
      get_lexval();
      get_lexval();
      get_lexval();
      exp0();
#line 168 "parser.acc"
 chunk_write (TSETSRIGHT, 0, 0) ; 
# line 471 "yygrammar.c"
      } break;
   case 34: {
      exp1();
      get_lexval();
      get_lexval();
      get_lexval();
      exp0();
#line 169 "parser.acc"
 chunk_write (TSETSLEFT, 0, 0) ; 
# line 481 "yygrammar.c"
      } break;
   case 35: {
      exp1();
      } break;
   }
}

exp1 ()
{
   switch(yyselect()) {
   case 36: {
      exp1();
      get_lexval();
      exp2();
      get_lexval();
      exp2();
#line 174 "parser.acc"
 yyerror("?: not supported yet") ; 
# line 500 "yygrammar.c"
      } break;
   case 37: {
      exp2();
      } break;
   }
}

exp2 ()
{
   switch(yyselect()) {
   case 38: {
      exp2();
      get_lexval();
      get_lexval();
      exp3();
#line 179 "parser.acc"
 chunk_write (TLOR, 0, 0) ; 
# line 518 "yygrammar.c"
      } break;
   case 39: {
      exp3();
      } break;
   }
}

exp3 ()
{
   switch(yyselect()) {
   case 40: {
      exp3();
      get_lexval();
      get_lexval();
      exp4();
#line 184 "parser.acc"
 chunk_write (TLAND, 0, 0) ; 
# line 536 "yygrammar.c"
      } break;
   case 41: {
      exp4();
      } break;
   }
}

exp4 ()
{
   switch(yyselect()) {
   case 42: {
      exp4();
      get_lexval();
      exp5();
#line 189 "parser.acc"
 chunk_write (TOR, 0, 0) ; 
# line 553 "yygrammar.c"
      } break;
   case 43: {
      exp5();
      } break;
   }
}

exp5 ()
{
   switch(yyselect()) {
   case 44: {
      exp5();
      get_lexval();
      exp6();
#line 194 "parser.acc"
 chunk_write (TXOR, 0, 0) ; 
# line 570 "yygrammar.c"
      } break;
   case 45: {
      exp6();
      } break;
   }
}

exp6 ()
{
   switch(yyselect()) {
   case 46: {
      exp6();
      get_lexval();
      exp7();
#line 199 "parser.acc"
 chunk_write (TAND, 0, 0) ; 
# line 587 "yygrammar.c"
      } break;
   case 47: {
      exp7();
      } break;
   }
}

exp7 ()
{
   switch(yyselect()) {
   case 48: {
      exp7();
      get_lexval();
      get_lexval();
      exp8();
#line 204 "parser.acc"
 chunk_write (TEQ, 0, 0) ; 
# line 605 "yygrammar.c"
      } break;
   case 49: {
      exp7();
      get_lexval();
      get_lexval();
      exp8();
#line 205 "parser.acc"
 chunk_write (TNQ, 0, 0) ; 
# line 614 "yygrammar.c"
      } break;
   case 50: {
      exp8();
      } break;
   }
}

exp8 ()
{
   switch(yyselect()) {
   case 51: {
      exp8();
      get_lexval();
      exp9();
#line 210 "parser.acc"
 chunk_write (TGT, 0, 0) ; 
# line 631 "yygrammar.c"
      } break;
   case 52: {
      exp8();
      get_lexval();
      exp9();
#line 211 "parser.acc"
 chunk_write (TLT, 0, 0) ; 
# line 639 "yygrammar.c"
      } break;
   case 53: {
      exp8();
      get_lexval();
      get_lexval();
      exp9();
#line 212 "parser.acc"
 chunk_write (TGTEQ, 0, 0) ; 
# line 648 "yygrammar.c"
      } break;
   case 54: {
      exp8();
      get_lexval();
      get_lexval();
      exp9();
#line 213 "parser.acc"
 chunk_write (TLTEQ, 0, 0) ; 
# line 657 "yygrammar.c"
      } break;
   case 55: {
      exp9();
      } break;
   }
}

exp9 ()
{
   switch(yyselect()) {
   case 56: {
      exp9();
      get_lexval();
      get_lexval();
      exp10();
#line 218 "parser.acc"
 chunk_write (TSLEFT, 0, 0) ; 
# line 675 "yygrammar.c"
      } break;
   case 57: {
      exp9();
      get_lexval();
      get_lexval();
      exp10();
#line 219 "parser.acc"
 chunk_write (TSRIGHT, 0, 0) ; 
# line 684 "yygrammar.c"
      } break;
   case 58: {
      exp10();
      } break;
   }
}

exp10 ()
{
   switch(yyselect()) {
   case 59: {
      exp10();
      get_lexval();
      exp11();
#line 224 "parser.acc"
 chunk_write (TADD, 0, 0) ; 
# line 701 "yygrammar.c"
      } break;
   case 60: {
      exp10();
      get_lexval();
      exp11();
#line 225 "parser.acc"
 chunk_write (TSUB, 0, 0) ; 
# line 709 "yygrammar.c"
      } break;
   case 61: {
      exp10();
      get_lexval();
      exp11();
#line 226 "parser.acc"
 chunk_write (TCAT,0,0) ; 
# line 717 "yygrammar.c"
      } break;
   case 62: {
      exp11();
      } break;
   }
}

exp11 ()
{
   switch(yyselect()) {
   case 63: {
      exp11();
      get_lexval();
      exp12();
#line 231 "parser.acc"
 chunk_write (TMUL, 0, 0) ; 
# line 734 "yygrammar.c"
      } break;
   case 64: {
      exp11();
      get_lexval();
      exp12();
#line 232 "parser.acc"
 chunk_write (TDIV, 0, 0) ; 
# line 742 "yygrammar.c"
      } break;
   case 65: {
      exp11();
      get_lexval();
      exp12();
#line 233 "parser.acc"
 chunk_write (TMOD, 0, 0) ; 
# line 750 "yygrammar.c"
      } break;
   case 66: {
      exp12();
      } break;
   }
}

exp12 ()
{
   switch(yyselect()) {
   case 67: {
      exp12();
      get_lexval();
      get_lexval();
      exp13();
#line 238 "parser.acc"
 chunk_write (TPOW,0,0) ; 
# line 768 "yygrammar.c"
      } break;
   case 68: {
      exp13();
      } break;
   }
}

exp13 ()
{
   YYSTYPE id;
   switch(yyselect()) {
   case 69: {
      get_lexval();
      get_lexval();
      exp13();
      get_lexval();
#line 243 "parser.acc"
 chunk_write (TCASTSTRING, 0, 0) ; 
# line 787 "yygrammar.c"
      } break;
   case 70: {
      get_lexval();
      get_lexval();
      exp13();
      get_lexval();
#line 244 "parser.acc"
 chunk_write (TCASTNUMBER, 0, 0) ; 
# line 796 "yygrammar.c"
      } break;
   case 71: {
      get_lexval();
      get_lexval();
      exp13();
      get_lexval();
#line 245 "parser.acc"
 chunk_write (TCASTREAL, 0, 0) ; 
# line 805 "yygrammar.c"
      } break;
   case 72: {
      get_lexval();
      get_lexval();
      id = yylval;
#line 246 "parser.acc"
 chunk_write(TPUSHSTR, id.index, 2) ; chunk_write (TNEW, 0, 0) ; 
# line 813 "yygrammar.c"
      } break;
   case 73: {
      get_lexval();
      get_lexval();
      exp13();
      get_lexval();
#line 247 "parser.acc"
 chunk_write (TNEW, 0, 0) ; 
# line 822 "yygrammar.c"
      } break;
   case 74: {
      get_lexval();
      exp13();
      } break;
   case 75: {
      get_lexval();
      exp13();
#line 249 "parser.acc"
 chunk_write (TNEG, 0, 0) ; 
# line 833 "yygrammar.c"
      } break;
   case 76: {
      get_lexval();
      exp13();
#line 250 "parser.acc"
 chunk_write (TNOT, 0, 0) ; 
# line 840 "yygrammar.c"
      } break;
   case 77: {
      get_lexval();
      exp13();
#line 251 "parser.acc"
 chunk_write (TINV, 0, 0) ; 
# line 847 "yygrammar.c"
      } break;
   case 78: {
      get_lexval();
      get_lexval();
      exp13();
#line 252 "parser.acc"
 chunk_write (TINC, 0, 0) ; 
# line 855 "yygrammar.c"
      } break;
   case 79: {
      get_lexval();
      get_lexval();
      exp13();
#line 253 "parser.acc"
 chunk_write (TDEC, 0, 0) ; 
# line 863 "yygrammar.c"
      } break;
   case 80: {
      exp13();
      get_lexval();
      get_lexval();
#line 254 "parser.acc"
 chunk_write (TPINC, 0, 0) ; 
# line 871 "yygrammar.c"
      } break;
   case 81: {
      exp13();
      get_lexval();
      get_lexval();
#line 255 "parser.acc"
 chunk_write (TPDEC, 0, 0) ; 
# line 879 "yygrammar.c"
      } break;
   case 82: {
      exp14();
      } break;
   }
}

exp14 ()
{
   switch(yyselect()) {
   case 83: {
      function_call();
      } break;
   case 84: {
      member_call();
      } break;
   case 85: {
      exp14();
      get_lexval();
      exp0();
      get_lexval();
#line 262 "parser.acc"
 chunk_write (TARRAY, 0, 0) ; 
# line 903 "yygrammar.c"
      } break;
   case 86: {
      get_lexval();
      exp0();
      get_lexval();
      } break;
   case 87: {
      literals();
      } break;
   }
}

function_call ()
{
   byte arg_count;
#line 268 "parser.acc"

  arg_count = 0;
  
# line 923 "yygrammar.c"
   switch(yyselect()) {
   case 88: {
      function_call_syntax(&arg_count);
#line 272 "parser.acc"
 chunk_write (TCALL, arg_count, 1) ; 
# line 929 "yygrammar.c"
      } break;
   }
}

function_call_syntax (arg_count)
   byte *arg_count;
{
   YYSTYPE id;
   switch(yyselect()) {
   case 89: {
      get_lexval();
      id = yylval;
      get_lexval();
      function_call_args(arg_count);
      get_lexval();
#line 276 "parser.acc"
 chunk_write (TPUSHSTR, id.index, 2) ; 
# line 947 "yygrammar.c"
      } break;
   case 90: {
      get_lexval();
      get_lexval();
      exp0();
      get_lexval();
      get_lexval();
      function_call_args(arg_count);
      get_lexval();
      } break;
   }
}

function_call_args (arg_count)
   byte *arg_count;
{
   switch(yyselect()) {
   case 91: {
      } break;
   case 92: {
      function_call_arg(arg_count);
      while (1) {
         switch (yyselect()) {
         case 112: {
            get_lexval();
            function_call_arg(arg_count);
            } break;
         default: goto yy4;
         }
      }
      yy4: ;
      } break;
   }
}

function_call_arg (arg_count)
   byte *arg_count;
{
   switch(yyselect()) {
   case 93: {
      exp0();
#line 285 "parser.acc"
 *arg_count += 1; 
# line 991 "yygrammar.c"
      } break;
   }
}

member_call ()
{
   switch(yyselect()) {
   case 94: {
      exp14();
      get_lexval();
      get_lexval();
      member_suffix();
      } break;
   }
}

member_suffix ()
{
   YYSTYPE id;
   byte arg_count;
#line 293 "parser.acc"

  arg_count = 0;
 
# line 1016 "yygrammar.c"
   switch(yyselect()) {
   case 95: {
      switch (yyselect()) {
      case 113: {
         get_lexval();
         id = yylval;
#line 297 "parser.acc"
 chunk_write(TPUSHSTR,id.index,2) ; 
# line 1025 "yygrammar.c"
         } break;
      case 114: {
         get_lexval();
         get_lexval();
         exp0();
         get_lexval();
         } break;
      default: printf("???\n"); exit(1);
      }
#line 297 "parser.acc"
 chunk_write(TMEMBER,0,0) ; 
# line 1037 "yygrammar.c"
      } break;
   case 96: {
      function_call_syntax(&arg_count);
#line 298 "parser.acc"
 chunk_write(TCCALL,arg_count,1) ; 
# line 1043 "yygrammar.c"
      } break;
   }
}

literals ()
{
   YYSTYPE n;
   YYSTYPE s;
   YYSTYPE r;
   YYSTYPE id;
   switch(yyselect()) {
   case 97: {
      get_lexval();
      n = yylval;
#line 302 "parser.acc"

  if ((dword)n.number <= 0xff)
   chunk_write(TPUSH1,n.number,1) ;
  else if ((dword)n.number <= 0xffff)
   chunk_write(TPUSH2,n.number,2) ;
  else if ((dword)n.number <= 0xffffffff)
   chunk_write(TPUSH4,n.number,4) ;
  else
   yyerror("tetra does not support 64 bit+ integers yet") ;
 
# line 1069 "yygrammar.c"
      } break;
   case 98: {
      get_lexval();
      s = yylval;
#line 312 "parser.acc"

   chunk_write(TPUSHSTR,s.index, 2) ;
 
# line 1078 "yygrammar.c"
      } break;
   case 99: {
      get_lexval();
      r = yylval;
#line 315 "parser.acc"

   chunk_write_ptr(TPUSHREAL,&r.real, 8) ;
 
# line 1087 "yygrammar.c"
      } break;
   case 100: {
      get_lexval();
      id = yylval;
#line 318 "parser.acc"

   chunk_write(TPUSHSTR,id.index,2) ;
   chunk_write(TPUSHVAR,0,0) ;
 
# line 1097 "yygrammar.c"
      } break;
   case 101: {
      get_lexval();
      get_lexval();
      id = yylval;
#line 322 "parser.acc"

   chunk_write(TPUSHSTR,id.index,2) ;
   chunk_write(TPUSHGLOBALVAR,0,0) ;
 
# line 1108 "yygrammar.c"
      } break;
   }
}

extern YYSTYPE yylval;
YYSTYPE yylval;
extern long yypos;

typedef struct LEXELEMSTRUCT {
   YYSTYPE val;
   long pos;
   struct LEXELEMSTRUCT *next;
} LEXELEM;
   
LEXELEM *first_lexelem, *cur_lexelem;

init_lexelem()
{
   cur_lexelem = first_lexelem;
}

first_lexval () {
   LEXELEM *p;
   p = (LEXELEM *)malloc(sizeof(LEXELEM));
   if (! p) yymallocerror();
   p->val = yylval;
   p->pos = yypos;
   p->next = 0;
   cur_lexelem = p;
   first_lexelem = p;
}

next_lexval() {
   LEXELEM *p;
   p = (LEXELEM *)malloc(sizeof(LEXELEM));
   if (! p) yymallocerror();
   cur_lexelem-> next = p;
   p->val = yylval;
   p->pos = yypos;
   p->next = 0;
   cur_lexelem = p;
}

get_lexval() {
   yylval = cur_lexelem->val;
   yypos = cur_lexelem->pos;
   cur_lexelem = cur_lexelem->next;
}

extern int c_length;
int c_length = 633;
extern int yygrammar[];
int yygrammar[] = {
0,
/* 1 */ 0,
/* 2 */ 6,
/* 3 */ 50000,
/* 4 */ -1,
/* 5 */ 102,
/* 6 */ 0,
/* 7 */ 10,
/* 8 */ -6,
/* 9 */ 1,
/* 10 */ 15,
/* 11 */ 79,
/* 12 */ 10,
/* 13 */ -10,
/* 14 */ 103,
/* 15 */ 20,
/* 16 */ 23,
/* 17 */ 10,
/* 18 */ -10,
/* 19 */ 104,
/* 20 */ 0,
/* 21 */ -10,
/* 22 */ 115,
/* 23 */ 0,
/* 24 */ 50260,
/* 25 */ 50259,
/* 26 */ 30,
/* 27 */ 56,
/* 28 */ -23,
/* 29 */ 2,
/* 30 */ 33,
/* 31 */ -30,
/* 32 */ 105,
/* 33 */ 39,
/* 34 */ 50058,
/* 35 */ 52,
/* 36 */ 43,
/* 37 */ -30,
/* 38 */ 107,
/* 39 */ 0,
/* 40 */ 50058,
/* 41 */ -30,
/* 42 */ 108,
/* 43 */ 49,
/* 44 */ 50044,
/* 45 */ 52,
/* 46 */ 43,
/* 47 */ -43,
/* 48 */ 106,
/* 49 */ 0,
/* 50 */ -43,
/* 51 */ 116,
/* 52 */ 0,
/* 53 */ 50259,
/* 54 */ -52,
/* 55 */ 3,
/* 56 */ 62,
/* 57 */ 50123,
/* 58 */ 66,
/* 59 */ 50125,
/* 60 */ -56,
/* 61 */ 4,
/* 62 */ 0,
/* 63 */ 79,
/* 64 */ -56,
/* 65 */ 5,
/* 66 */ 0,
/* 67 */ 79,
/* 68 */ 71,
/* 69 */ -66,
/* 70 */ 6,
/* 71 */ 76,
/* 72 */ 79,
/* 73 */ 71,
/* 74 */ -71,
/* 75 */ 109,
/* 76 */ 0,
/* 77 */ -71,
/* 78 */ 117,
/* 79 */ 84,
/* 80 */ 172,
/* 81 */ 50059,
/* 82 */ -79,
/* 83 */ 7,
/* 84 */ 88,
/* 85 */ 133,
/* 86 */ -79,
/* 87 */ 8,
/* 88 */ 92,
/* 89 */ 150,
/* 90 */ -79,
/* 91 */ 9,
/* 92 */ 96,
/* 93 */ 158,
/* 94 */ -79,
/* 95 */ 10,
/* 96 */ 101,
/* 97 */ 115,
/* 98 */ 50059,
/* 99 */ -79,
/* 100 */ 11,
/* 101 */ 106,
/* 102 */ 124,
/* 103 */ 50059,
/* 104 */ -79,
/* 105 */ 12,
/* 106 */ 111,
/* 107 */ 163,
/* 108 */ 50059,
/* 109 */ -79,
/* 110 */ 13,
/* 111 */ 0,
/* 112 */ 50059,
/* 113 */ -79,
/* 114 */ 14,
/* 115 */ 119,
/* 116 */ 50271,
/* 117 */ -115,
/* 118 */ 15,
/* 119 */ 0,
/* 120 */ 50271,
/* 121 */ 50257,
/* 122 */ -115,
/* 123 */ 16,
/* 124 */ 128,
/* 125 */ 50268,
/* 126 */ -124,
/* 127 */ 17,
/* 128 */ 0,
/* 129 */ 50268,
/* 130 */ 50257,
/* 131 */ -124,
/* 132 */ 18,
/* 133 */ 0,
/* 134 */ 50264,
/* 135 */ 50040,
/* 136 */ 172,
/* 137 */ 50041,
/* 138 */ 56,
/* 139 */ 142,
/* 140 */ -133,
/* 141 */ 19,
/* 142 */ 145,
/* 143 */ -142,
/* 144 */ 110,
/* 145 */ 0,
/* 146 */ 50275,
/* 147 */ 56,
/* 148 */ -142,
/* 149 */ 111,
/* 150 */ 0,
/* 151 */ 50267,
/* 152 */ 50040,
/* 153 */ 172,
/* 154 */ 50041,
/* 155 */ 56,
/* 156 */ -150,
/* 157 */ 20,
/* 158 */ 0,
/* 159 */ 50278,
/* 160 */ 56,
/* 161 */ -158,
/* 162 */ 21,
/* 163 */ 168,
/* 164 */ 50265,
/* 165 */ 172,
/* 166 */ -163,
/* 167 */ 22,
/* 168 */ 0,
/* 169 */ 50265,
/* 170 */ -163,
/* 171 */ 23,
/* 172 */ 178,
/* 173 */ 254,
/* 174 */ 50061,
/* 175 */ 172,
/* 176 */ -172,
/* 177 */ 24,
/* 178 */ 185,
/* 179 */ 254,
/* 180 */ 50043,
/* 181 */ 50061,
/* 182 */ 172,
/* 183 */ -172,
/* 184 */ 25,
/* 185 */ 192,
/* 186 */ 254,
/* 187 */ 50045,
/* 188 */ 50061,
/* 189 */ 172,
/* 190 */ -172,
/* 191 */ 26,
/* 192 */ 199,
/* 193 */ 254,
/* 194 */ 50042,
/* 195 */ 50061,
/* 196 */ 172,
/* 197 */ -172,
/* 198 */ 27,
/* 199 */ 206,
/* 200 */ 254,
/* 201 */ 50047,
/* 202 */ 50061,
/* 203 */ 172,
/* 204 */ -172,
/* 205 */ 28,
/* 206 */ 213,
/* 207 */ 254,
/* 208 */ 50037,
/* 209 */ 50061,
/* 210 */ 172,
/* 211 */ -172,
/* 212 */ 29,
/* 213 */ 220,
/* 214 */ 254,
/* 215 */ 50038,
/* 216 */ 50061,
/* 217 */ 172,
/* 218 */ -172,
/* 219 */ 30,
/* 220 */ 227,
/* 221 */ 254,
/* 222 */ 50124,
/* 223 */ 50061,
/* 224 */ 172,
/* 225 */ -172,
/* 226 */ 31,
/* 227 */ 234,
/* 228 */ 254,
/* 229 */ 50094,
/* 230 */ 50061,
/* 231 */ 172,
/* 232 */ -172,
/* 233 */ 32,
/* 234 */ 242,
/* 235 */ 254,
/* 236 */ 50060,
/* 237 */ 50060,
/* 238 */ 50061,
/* 239 */ 172,
/* 240 */ -172,
/* 241 */ 33,
/* 242 */ 250,
/* 243 */ 254,
/* 244 */ 50062,
/* 245 */ 50062,
/* 246 */ 50061,
/* 247 */ 172,
/* 248 */ -172,
/* 249 */ 34,
/* 250 */ 0,
/* 251 */ 254,
/* 252 */ -172,
/* 253 */ 35,
/* 254 */ 262,
/* 255 */ 254,
/* 256 */ 50063,
/* 257 */ 266,
/* 258 */ 50058,
/* 259 */ 266,
/* 260 */ -254,
/* 261 */ 36,
/* 262 */ 0,
/* 263 */ 266,
/* 264 */ -254,
/* 265 */ 37,
/* 266 */ 273,
/* 267 */ 266,
/* 268 */ 50124,
/* 269 */ 50124,
/* 270 */ 277,
/* 271 */ -266,
/* 272 */ 38,
/* 273 */ 0,
/* 274 */ 277,
/* 275 */ -266,
/* 276 */ 39,
/* 277 */ 284,
/* 278 */ 277,
/* 279 */ 50038,
/* 280 */ 50038,
/* 281 */ 288,
/* 282 */ -277,
/* 283 */ 40,
/* 284 */ 0,
/* 285 */ 288,
/* 286 */ -277,
/* 287 */ 41,
/* 288 */ 294,
/* 289 */ 288,
/* 290 */ 50124,
/* 291 */ 298,
/* 292 */ -288,
/* 293 */ 42,
/* 294 */ 0,
/* 295 */ 298,
/* 296 */ -288,
/* 297 */ 43,
/* 298 */ 304,
/* 299 */ 298,
/* 300 */ 50094,
/* 301 */ 308,
/* 302 */ -298,
/* 303 */ 44,
/* 304 */ 0,
/* 305 */ 308,
/* 306 */ -298,
/* 307 */ 45,
/* 308 */ 314,
/* 309 */ 308,
/* 310 */ 50038,
/* 311 */ 318,
/* 312 */ -308,
/* 313 */ 46,
/* 314 */ 0,
/* 315 */ 318,
/* 316 */ -308,
/* 317 */ 47,
/* 318 */ 325,
/* 319 */ 318,
/* 320 */ 50061,
/* 321 */ 50061,
/* 322 */ 336,
/* 323 */ -318,
/* 324 */ 48,
/* 325 */ 332,
/* 326 */ 318,
/* 327 */ 50033,
/* 328 */ 50061,
/* 329 */ 336,
/* 330 */ -318,
/* 331 */ 49,
/* 332 */ 0,
/* 333 */ 336,
/* 334 */ -318,
/* 335 */ 50,
/* 336 */ 342,
/* 337 */ 336,
/* 338 */ 50060,
/* 339 */ 366,
/* 340 */ -336,
/* 341 */ 51,
/* 342 */ 348,
/* 343 */ 336,
/* 344 */ 50062,
/* 345 */ 366,
/* 346 */ -336,
/* 347 */ 52,
/* 348 */ 355,
/* 349 */ 336,
/* 350 */ 50060,
/* 351 */ 50061,
/* 352 */ 366,
/* 353 */ -336,
/* 354 */ 53,
/* 355 */ 362,
/* 356 */ 336,
/* 357 */ 50062,
/* 358 */ 50061,
/* 359 */ 366,
/* 360 */ -336,
/* 361 */ 54,
/* 362 */ 0,
/* 363 */ 366,
/* 364 */ -336,
/* 365 */ 55,
/* 366 */ 373,
/* 367 */ 366,
/* 368 */ 50060,
/* 369 */ 50060,
/* 370 */ 384,
/* 371 */ -366,
/* 372 */ 56,
/* 373 */ 380,
/* 374 */ 366,
/* 375 */ 50062,
/* 376 */ 50062,
/* 377 */ 384,
/* 378 */ -366,
/* 379 */ 57,
/* 380 */ 0,
/* 381 */ 384,
/* 382 */ -366,
/* 383 */ 58,
/* 384 */ 390,
/* 385 */ 384,
/* 386 */ 50043,
/* 387 */ 406,
/* 388 */ -384,
/* 389 */ 59,
/* 390 */ 396,
/* 391 */ 384,
/* 392 */ 50045,
/* 393 */ 406,
/* 394 */ -384,
/* 395 */ 60,
/* 396 */ 402,
/* 397 */ 384,
/* 398 */ 50046,
/* 399 */ 406,
/* 400 */ -384,
/* 401 */ 61,
/* 402 */ 0,
/* 403 */ 406,
/* 404 */ -384,
/* 405 */ 62,
/* 406 */ 412,
/* 407 */ 406,
/* 408 */ 50042,
/* 409 */ 428,
/* 410 */ -406,
/* 411 */ 63,
/* 412 */ 418,
/* 413 */ 406,
/* 414 */ 50047,
/* 415 */ 428,
/* 416 */ -406,
/* 417 */ 64,
/* 418 */ 424,
/* 419 */ 406,
/* 420 */ 50037,
/* 421 */ 428,
/* 422 */ -406,
/* 423 */ 65,
/* 424 */ 0,
/* 425 */ 428,
/* 426 */ -406,
/* 427 */ 66,
/* 428 */ 435,
/* 429 */ 428,
/* 430 */ 50042,
/* 431 */ 50042,
/* 432 */ 439,
/* 433 */ -428,
/* 434 */ 67,
/* 435 */ 0,
/* 436 */ 439,
/* 437 */ -428,
/* 438 */ 68,
/* 439 */ 446,
/* 440 */ 50261,
/* 441 */ 50060,
/* 442 */ 439,
/* 443 */ 50062,
/* 444 */ -439,
/* 445 */ 69,
/* 446 */ 453,
/* 447 */ 50262,
/* 448 */ 50060,
/* 449 */ 439,
/* 450 */ 50062,
/* 451 */ -439,
/* 452 */ 70,
/* 453 */ 460,
/* 454 */ 50263,
/* 455 */ 50060,
/* 456 */ 439,
/* 457 */ 50062,
/* 458 */ -439,
/* 459 */ 71,
/* 460 */ 465,
/* 461 */ 50276,
/* 462 */ 50259,
/* 463 */ -439,
/* 464 */ 72,
/* 465 */ 472,
/* 466 */ 50276,
/* 467 */ 50040,
/* 468 */ 439,
/* 469 */ 50041,
/* 470 */ -439,
/* 471 */ 73,
/* 472 */ 477,
/* 473 */ 50043,
/* 474 */ 439,
/* 475 */ -439,
/* 476 */ 74,
/* 477 */ 482,
/* 478 */ 50045,
/* 479 */ 439,
/* 480 */ -439,
/* 481 */ 75,
/* 482 */ 487,
/* 483 */ 50033,
/* 484 */ 439,
/* 485 */ -439,
/* 486 */ 76,
/* 487 */ 492,
/* 488 */ 50126,
/* 489 */ 439,
/* 490 */ -439,
/* 491 */ 77,
/* 492 */ 498,
/* 493 */ 50043,
/* 494 */ 50043,
/* 495 */ 439,
/* 496 */ -439,
/* 497 */ 78,
/* 498 */ 504,
/* 499 */ 50045,
/* 500 */ 50045,
/* 501 */ 439,
/* 502 */ -439,
/* 503 */ 79,
/* 504 */ 510,
/* 505 */ 439,
/* 506 */ 50043,
/* 507 */ 50043,
/* 508 */ -439,
/* 509 */ 80,
/* 510 */ 516,
/* 511 */ 439,
/* 512 */ 50045,
/* 513 */ 50045,
/* 514 */ -439,
/* 515 */ 81,
/* 516 */ 0,
/* 517 */ 520,
/* 518 */ -439,
/* 519 */ 82,
/* 520 */ 524,
/* 521 */ 545,
/* 522 */ -520,
/* 523 */ 83,
/* 524 */ 528,
/* 525 */ 587,
/* 526 */ -520,
/* 527 */ 84,
/* 528 */ 535,
/* 529 */ 520,
/* 530 */ 50091,
/* 531 */ 172,
/* 532 */ 50093,
/* 533 */ -520,
/* 534 */ 85,
/* 535 */ 541,
/* 536 */ 50040,
/* 537 */ 172,
/* 538 */ 50041,
/* 539 */ -520,
/* 540 */ 86,
/* 541 */ 0,
/* 542 */ 613,
/* 543 */ -520,
/* 544 */ 87,
/* 545 */ 0,
/* 546 */ 549,
/* 547 */ -545,
/* 548 */ 88,
/* 549 */ 556,
/* 550 */ 50259,
/* 551 */ 50040,
/* 552 */ 566,
/* 553 */ 50041,
/* 554 */ -549,
/* 555 */ 89,
/* 556 */ 0,
/* 557 */ 50260,
/* 558 */ 50060,
/* 559 */ 172,
/* 560 */ 50062,
/* 561 */ 50040,
/* 562 */ 566,
/* 563 */ 50041,
/* 564 */ -549,
/* 565 */ 90,
/* 566 */ 569,
/* 567 */ -566,
/* 568 */ 91,
/* 569 */ 0,
/* 570 */ 583,
/* 571 */ 574,
/* 572 */ -566,
/* 573 */ 92,
/* 574 */ 580,
/* 575 */ 50044,
/* 576 */ 583,
/* 577 */ 574,
/* 578 */ -574,
/* 579 */ 112,
/* 580 */ 0,
/* 581 */ -574,
/* 582 */ 118,
/* 583 */ 0,
/* 584 */ 172,
/* 585 */ -583,
/* 586 */ 93,
/* 587 */ 0,
/* 588 */ 520,
/* 589 */ 50045,
/* 590 */ 50062,
/* 591 */ 594,
/* 592 */ -587,
/* 593 */ 94,
/* 594 */ 598,
/* 595 */ 602,
/* 596 */ -594,
/* 597 */ 95,
/* 598 */ 0,
/* 599 */ 549,
/* 600 */ -594,
/* 601 */ 96,
/* 602 */ 606,
/* 603 */ 50259,
/* 604 */ -602,
/* 605 */ 113,
/* 606 */ 0,
/* 607 */ 50277,
/* 608 */ 50040,
/* 609 */ 172,
/* 610 */ 50041,
/* 611 */ -602,
/* 612 */ 114,
/* 613 */ 617,
/* 614 */ 50257,
/* 615 */ -613,
/* 616 */ 97,
/* 617 */ 621,
/* 618 */ 50256,
/* 619 */ -613,
/* 620 */ 98,
/* 621 */ 625,
/* 622 */ 50258,
/* 623 */ -613,
/* 624 */ 99,
/* 625 */ 629,
/* 626 */ 50259,
/* 627 */ -613,
/* 628 */ 100,
/* 629 */ 0,
/* 630 */ 50036,
/* 631 */ 50259,
/* 632 */ -613,
/* 633 */ 101,
0
};
extern int yyannotation[];
int yyannotation[] = {
0,
/* 1 */ 0,
/* 2 */ -1,
/* 3 */ 50000,
/* 4 */ -1,
/* 5 */ 0,
/* 6 */ 0,
/* 7 */ -1,
/* 8 */ -6,
/* 9 */ -1,
/* 10 */ 15,
/* 11 */ -1,
/* 12 */ -1,
/* 13 */ -10,
/* 14 */ -1,
/* 15 */ 20,
/* 16 */ -1,
/* 17 */ -1,
/* 18 */ -10,
/* 19 */ -1,
/* 20 */ 0,
/* 21 */ -10,
/* 22 */ -1,
/* 23 */ 0,
/* 24 */ 50260,
/* 25 */ 50259,
/* 26 */ -1,
/* 27 */ -1,
/* 28 */ -23,
/* 29 */ -1,
/* 30 */ 33,
/* 31 */ -30,
/* 32 */ -1,
/* 33 */ 39,
/* 34 */ 50058,
/* 35 */ -1,
/* 36 */ -1,
/* 37 */ -30,
/* 38 */ -1,
/* 39 */ 0,
/* 40 */ 50058,
/* 41 */ -30,
/* 42 */ -1,
/* 43 */ 49,
/* 44 */ 50044,
/* 45 */ -1,
/* 46 */ -1,
/* 47 */ -43,
/* 48 */ -1,
/* 49 */ 0,
/* 50 */ -43,
/* 51 */ -1,
/* 52 */ 0,
/* 53 */ 50259,
/* 54 */ -52,
/* 55 */ -1,
/* 56 */ 62,
/* 57 */ 50123,
/* 58 */ -1,
/* 59 */ 50125,
/* 60 */ -56,
/* 61 */ -1,
/* 62 */ 0,
/* 63 */ -1,
/* 64 */ -56,
/* 65 */ -1,
/* 66 */ 0,
/* 67 */ -1,
/* 68 */ -1,
/* 69 */ -66,
/* 70 */ -1,
/* 71 */ 76,
/* 72 */ -1,
/* 73 */ -1,
/* 74 */ -71,
/* 75 */ -1,
/* 76 */ 0,
/* 77 */ -71,
/* 78 */ -1,
/* 79 */ 84,
/* 80 */ -1,
/* 81 */ 50059,
/* 82 */ -79,
/* 83 */ -1,
/* 84 */ 88,
/* 85 */ -1,
/* 86 */ -79,
/* 87 */ -1,
/* 88 */ 92,
/* 89 */ -1,
/* 90 */ -79,
/* 91 */ -1,
/* 92 */ 96,
/* 93 */ -1,
/* 94 */ -79,
/* 95 */ -1,
/* 96 */ 101,
/* 97 */ -1,
/* 98 */ 50059,
/* 99 */ -79,
/* 100 */ -1,
/* 101 */ 106,
/* 102 */ -1,
/* 103 */ 50059,
/* 104 */ -79,
/* 105 */ -1,
/* 106 */ 111,
/* 107 */ -1,
/* 108 */ 50059,
/* 109 */ -79,
/* 110 */ -1,
/* 111 */ 0,
/* 112 */ 50059,
/* 113 */ -79,
/* 114 */ -1,
/* 115 */ 119,
/* 116 */ 50271,
/* 117 */ -115,
/* 118 */ -1,
/* 119 */ 0,
/* 120 */ 50271,
/* 121 */ 50257,
/* 122 */ -115,
/* 123 */ -1,
/* 124 */ 128,
/* 125 */ 50268,
/* 126 */ -124,
/* 127 */ -1,
/* 128 */ 0,
/* 129 */ 50268,
/* 130 */ 50257,
/* 131 */ -124,
/* 132 */ -1,
/* 133 */ 0,
/* 134 */ 50264,
/* 135 */ 50040,
/* 136 */ -1,
/* 137 */ 50041,
/* 138 */ -1,
/* 139 */ -1,
/* 140 */ -133,
/* 141 */ -1,
/* 142 */ 145,
/* 143 */ -142,
/* 144 */ -1,
/* 145 */ 0,
/* 146 */ 50275,
/* 147 */ -1,
/* 148 */ -142,
/* 149 */ -1,
/* 150 */ 0,
/* 151 */ 50267,
/* 152 */ 50040,
/* 153 */ -1,
/* 154 */ 50041,
/* 155 */ -1,
/* 156 */ -150,
/* 157 */ -1,
/* 158 */ 0,
/* 159 */ 50278,
/* 160 */ -1,
/* 161 */ -158,
/* 162 */ -1,
/* 163 */ 168,
/* 164 */ 50265,
/* 165 */ -1,
/* 166 */ -163,
/* 167 */ -1,
/* 168 */ 0,
/* 169 */ 50265,
/* 170 */ -163,
/* 171 */ -1,
/* 172 */ 178,
/* 173 */ -1,
/* 174 */ 50061,
/* 175 */ -1,
/* 176 */ -172,
/* 177 */ -1,
/* 178 */ 185,
/* 179 */ -1,
/* 180 */ 50043,
/* 181 */ 50061,
/* 182 */ -1,
/* 183 */ -172,
/* 184 */ -1,
/* 185 */ 192,
/* 186 */ -1,
/* 187 */ 50045,
/* 188 */ 50061,
/* 189 */ -1,
/* 190 */ -172,
/* 191 */ -1,
/* 192 */ 199,
/* 193 */ -1,
/* 194 */ 50042,
/* 195 */ 50061,
/* 196 */ -1,
/* 197 */ -172,
/* 198 */ -1,
/* 199 */ 206,
/* 200 */ -1,
/* 201 */ 50047,
/* 202 */ 50061,
/* 203 */ -1,
/* 204 */ -172,
/* 205 */ -1,
/* 206 */ 213,
/* 207 */ -1,
/* 208 */ 50037,
/* 209 */ 50061,
/* 210 */ -1,
/* 211 */ -172,
/* 212 */ -1,
/* 213 */ 220,
/* 214 */ -1,
/* 215 */ 50038,
/* 216 */ 50061,
/* 217 */ -1,
/* 218 */ -172,
/* 219 */ -1,
/* 220 */ 227,
/* 221 */ -1,
/* 222 */ 50124,
/* 223 */ 50061,
/* 224 */ -1,
/* 225 */ -172,
/* 226 */ -1,
/* 227 */ 234,
/* 228 */ -1,
/* 229 */ 50094,
/* 230 */ 50061,
/* 231 */ -1,
/* 232 */ -172,
/* 233 */ -1,
/* 234 */ 242,
/* 235 */ -1,
/* 236 */ 50060,
/* 237 */ 50060,
/* 238 */ 50061,
/* 239 */ -1,
/* 240 */ -172,
/* 241 */ -1,
/* 242 */ 250,
/* 243 */ -1,
/* 244 */ 50062,
/* 245 */ 50062,
/* 246 */ 50061,
/* 247 */ -1,
/* 248 */ -172,
/* 249 */ -1,
/* 250 */ 0,
/* 251 */ -1,
/* 252 */ -172,
/* 253 */ -1,
/* 254 */ 262,
/* 255 */ -1,
/* 256 */ 50063,
/* 257 */ -1,
/* 258 */ 50058,
/* 259 */ -1,
/* 260 */ -254,
/* 261 */ -1,
/* 262 */ 0,
/* 263 */ -1,
/* 264 */ -254,
/* 265 */ -1,
/* 266 */ 273,
/* 267 */ -1,
/* 268 */ 50124,
/* 269 */ 50124,
/* 270 */ -1,
/* 271 */ -266,
/* 272 */ -1,
/* 273 */ 0,
/* 274 */ -1,
/* 275 */ -266,
/* 276 */ -1,
/* 277 */ 284,
/* 278 */ -1,
/* 279 */ 50038,
/* 280 */ 50038,
/* 281 */ -1,
/* 282 */ -277,
/* 283 */ -1,
/* 284 */ 0,
/* 285 */ -1,
/* 286 */ -277,
/* 287 */ -1,
/* 288 */ 294,
/* 289 */ -1,
/* 290 */ 50124,
/* 291 */ -1,
/* 292 */ -288,
/* 293 */ -1,
/* 294 */ 0,
/* 295 */ -1,
/* 296 */ -288,
/* 297 */ -1,
/* 298 */ 304,
/* 299 */ -1,
/* 300 */ 50094,
/* 301 */ -1,
/* 302 */ -298,
/* 303 */ -1,
/* 304 */ 0,
/* 305 */ -1,
/* 306 */ -298,
/* 307 */ -1,
/* 308 */ 314,
/* 309 */ -1,
/* 310 */ 50038,
/* 311 */ -1,
/* 312 */ -308,
/* 313 */ -1,
/* 314 */ 0,
/* 315 */ -1,
/* 316 */ -308,
/* 317 */ -1,
/* 318 */ 325,
/* 319 */ -1,
/* 320 */ 50061,
/* 321 */ 50061,
/* 322 */ -1,
/* 323 */ -318,
/* 324 */ -1,
/* 325 */ 332,
/* 326 */ -1,
/* 327 */ 50033,
/* 328 */ 50061,
/* 329 */ -1,
/* 330 */ -318,
/* 331 */ -1,
/* 332 */ 0,
/* 333 */ -1,
/* 334 */ -318,
/* 335 */ -1,
/* 336 */ 342,
/* 337 */ -1,
/* 338 */ 50060,
/* 339 */ -1,
/* 340 */ -336,
/* 341 */ -1,
/* 342 */ 348,
/* 343 */ -1,
/* 344 */ 50062,
/* 345 */ -1,
/* 346 */ -336,
/* 347 */ -1,
/* 348 */ 355,
/* 349 */ -1,
/* 350 */ 50060,
/* 351 */ 50061,
/* 352 */ -1,
/* 353 */ -336,
/* 354 */ -1,
/* 355 */ 362,
/* 356 */ -1,
/* 357 */ 50062,
/* 358 */ 50061,
/* 359 */ -1,
/* 360 */ -336,
/* 361 */ -1,
/* 362 */ 0,
/* 363 */ -1,
/* 364 */ -336,
/* 365 */ -1,
/* 366 */ 373,
/* 367 */ -1,
/* 368 */ 50060,
/* 369 */ 50060,
/* 370 */ -1,
/* 371 */ -366,
/* 372 */ -1,
/* 373 */ 380,
/* 374 */ -1,
/* 375 */ 50062,
/* 376 */ 50062,
/* 377 */ -1,
/* 378 */ -366,
/* 379 */ -1,
/* 380 */ 0,
/* 381 */ -1,
/* 382 */ -366,
/* 383 */ -1,
/* 384 */ 390,
/* 385 */ -1,
/* 386 */ 50043,
/* 387 */ -1,
/* 388 */ -384,
/* 389 */ -1,
/* 390 */ 396,
/* 391 */ -1,
/* 392 */ 50045,
/* 393 */ -1,
/* 394 */ -384,
/* 395 */ -1,
/* 396 */ 402,
/* 397 */ -1,
/* 398 */ 50046,
/* 399 */ -1,
/* 400 */ -384,
/* 401 */ -1,
/* 402 */ 0,
/* 403 */ -1,
/* 404 */ -384,
/* 405 */ -1,
/* 406 */ 412,
/* 407 */ -1,
/* 408 */ 50042,
/* 409 */ -1,
/* 410 */ -406,
/* 411 */ -1,
/* 412 */ 418,
/* 413 */ -1,
/* 414 */ 50047,
/* 415 */ -1,
/* 416 */ -406,
/* 417 */ -1,
/* 418 */ 424,
/* 419 */ -1,
/* 420 */ 50037,
/* 421 */ -1,
/* 422 */ -406,
/* 423 */ -1,
/* 424 */ 0,
/* 425 */ -1,
/* 426 */ -406,
/* 427 */ -1,
/* 428 */ 435,
/* 429 */ -1,
/* 430 */ 50042,
/* 431 */ 50042,
/* 432 */ -1,
/* 433 */ -428,
/* 434 */ -1,
/* 435 */ 0,
/* 436 */ -1,
/* 437 */ -428,
/* 438 */ -1,
/* 439 */ 446,
/* 440 */ 50261,
/* 441 */ 50060,
/* 442 */ -1,
/* 443 */ 50062,
/* 444 */ -439,
/* 445 */ -1,
/* 446 */ 453,
/* 447 */ 50262,
/* 448 */ 50060,
/* 449 */ -1,
/* 450 */ 50062,
/* 451 */ -439,
/* 452 */ -1,
/* 453 */ 460,
/* 454 */ 50263,
/* 455 */ 50060,
/* 456 */ -1,
/* 457 */ 50062,
/* 458 */ -439,
/* 459 */ -1,
/* 460 */ 465,
/* 461 */ 50276,
/* 462 */ 50259,
/* 463 */ -439,
/* 464 */ -1,
/* 465 */ 472,
/* 466 */ 50276,
/* 467 */ 50040,
/* 468 */ -1,
/* 469 */ 50041,
/* 470 */ -439,
/* 471 */ -1,
/* 472 */ 477,
/* 473 */ 50043,
/* 474 */ -1,
/* 475 */ -439,
/* 476 */ -1,
/* 477 */ 482,
/* 478 */ 50045,
/* 479 */ -1,
/* 480 */ -439,
/* 481 */ -1,
/* 482 */ 487,
/* 483 */ 50033,
/* 484 */ -1,
/* 485 */ -439,
/* 486 */ -1,
/* 487 */ 492,
/* 488 */ 50126,
/* 489 */ -1,
/* 490 */ -439,
/* 491 */ -1,
/* 492 */ 498,
/* 493 */ 50043,
/* 494 */ 50043,
/* 495 */ -1,
/* 496 */ -439,
/* 497 */ -1,
/* 498 */ 504,
/* 499 */ 50045,
/* 500 */ 50045,
/* 501 */ -1,
/* 502 */ -439,
/* 503 */ -1,
/* 504 */ 510,
/* 505 */ -1,
/* 506 */ 50043,
/* 507 */ 50043,
/* 508 */ -439,
/* 509 */ -1,
/* 510 */ 516,
/* 511 */ -1,
/* 512 */ 50045,
/* 513 */ 50045,
/* 514 */ -439,
/* 515 */ -1,
/* 516 */ 0,
/* 517 */ -1,
/* 518 */ -439,
/* 519 */ -1,
/* 520 */ 524,
/* 521 */ -1,
/* 522 */ -520,
/* 523 */ -1,
/* 524 */ 528,
/* 525 */ -1,
/* 526 */ -520,
/* 527 */ -1,
/* 528 */ 535,
/* 529 */ -1,
/* 530 */ 50091,
/* 531 */ -1,
/* 532 */ 50093,
/* 533 */ -520,
/* 534 */ -1,
/* 535 */ 541,
/* 536 */ 50040,
/* 537 */ -1,
/* 538 */ 50041,
/* 539 */ -520,
/* 540 */ -1,
/* 541 */ 0,
/* 542 */ -1,
/* 543 */ -520,
/* 544 */ -1,
/* 545 */ 0,
/* 546 */ -1,
/* 547 */ -545,
/* 548 */ -1,
/* 549 */ 556,
/* 550 */ 50259,
/* 551 */ 50040,
/* 552 */ -1,
/* 553 */ 50041,
/* 554 */ -549,
/* 555 */ -1,
/* 556 */ 0,
/* 557 */ 50260,
/* 558 */ 50060,
/* 559 */ -1,
/* 560 */ 50062,
/* 561 */ 50040,
/* 562 */ -1,
/* 563 */ 50041,
/* 564 */ -549,
/* 565 */ -1,
/* 566 */ 569,
/* 567 */ -566,
/* 568 */ -1,
/* 569 */ 0,
/* 570 */ -1,
/* 571 */ -1,
/* 572 */ -566,
/* 573 */ -1,
/* 574 */ 580,
/* 575 */ 50044,
/* 576 */ -1,
/* 577 */ -1,
/* 578 */ -574,
/* 579 */ -1,
/* 580 */ 0,
/* 581 */ -574,
/* 582 */ -1,
/* 583 */ 0,
/* 584 */ -1,
/* 585 */ -583,
/* 586 */ -1,
/* 587 */ 0,
/* 588 */ -1,
/* 589 */ 50045,
/* 590 */ 50062,
/* 591 */ -1,
/* 592 */ -587,
/* 593 */ -1,
/* 594 */ 598,
/* 595 */ -1,
/* 596 */ -594,
/* 597 */ -1,
/* 598 */ 0,
/* 599 */ -1,
/* 600 */ -594,
/* 601 */ -1,
/* 602 */ 606,
/* 603 */ 50259,
/* 604 */ -602,
/* 605 */ -1,
/* 606 */ 0,
/* 607 */ 50277,
/* 608 */ 50040,
/* 609 */ -1,
/* 610 */ 50041,
/* 611 */ -602,
/* 612 */ -1,
/* 613 */ 617,
/* 614 */ 50257,
/* 615 */ -613,
/* 616 */ -1,
/* 617 */ 621,
/* 618 */ 50256,
/* 619 */ -613,
/* 620 */ -1,
/* 621 */ 625,
/* 622 */ 50258,
/* 623 */ -613,
/* 624 */ -1,
/* 625 */ 629,
/* 626 */ 50259,
/* 627 */ -613,
/* 628 */ -1,
/* 629 */ 0,
/* 630 */ 50036,
/* 631 */ 50259,
/* 632 */ -613,
/* 633 */ -1,
0
};
extern int yycoordinate[];
int yycoordinate[] = {
0,
/* 1 */ 9999,
/* 2 */ 13008,
/* 3 */ 9999,
/* 4 */ 9999,
/* 5 */ 13008,
/* 6 */ 9999,
/* 7 */ 17002,
/* 8 */ 9999,
/* 9 */ 14002,
/* 10 */ 9999,
/* 11 */ 17004,
/* 12 */ 17012,
/* 13 */ 9999,
/* 14 */ 17012,
/* 15 */ 9999,
/* 16 */ 17016,
/* 17 */ 17027,
/* 18 */ 9999,
/* 19 */ 17027,
/* 20 */ 9999,
/* 21 */ 9999,
/* 22 */ 17027,
/* 23 */ 9999,
/* 24 */ 9999,
/* 25 */ 9999,
/* 26 */ 25002,
/* 27 */ 26002,
/* 28 */ 9999,
/* 29 */ 24009,
/* 30 */ 9999,
/* 31 */ 9999,
/* 32 */ 25004,
/* 33 */ 9999,
/* 34 */ 9999,
/* 35 */ 25010,
/* 36 */ 25027,
/* 37 */ 9999,
/* 38 */ 25006,
/* 39 */ 9999,
/* 40 */ 9999,
/* 41 */ 9999,
/* 42 */ 25055,
/* 43 */ 9999,
/* 44 */ 9999,
/* 45 */ 25033,
/* 46 */ 25029,
/* 47 */ 9999,
/* 48 */ 25029,
/* 49 */ 9999,
/* 50 */ 9999,
/* 51 */ 25029,
/* 52 */ 9999,
/* 53 */ 9999,
/* 54 */ 9999,
/* 55 */ 30003,
/* 56 */ 9999,
/* 57 */ 9999,
/* 58 */ 34006,
/* 59 */ 9999,
/* 60 */ 9999,
/* 61 */ 34002,
/* 62 */ 9999,
/* 63 */ 35004,
/* 64 */ 9999,
/* 65 */ 35012,
/* 66 */ 9999,
/* 67 */ 39002,
/* 68 */ 39012,
/* 69 */ 9999,
/* 70 */ 39010,
/* 71 */ 9999,
/* 72 */ 39015,
/* 73 */ 39023,
/* 74 */ 9999,
/* 75 */ 39023,
/* 76 */ 9999,
/* 77 */ 9999,
/* 78 */ 39023,
/* 79 */ 9999,
/* 80 */ 43002,
/* 81 */ 9999,
/* 82 */ 9999,
/* 83 */ 43005,
/* 84 */ 9999,
/* 85 */ 44004,
/* 86 */ 9999,
/* 87 */ 44015,
/* 88 */ 9999,
/* 89 */ 45004,
/* 90 */ 9999,
/* 91 */ 45018,
/* 92 */ 9999,
/* 93 */ 46004,
/* 94 */ 9999,
/* 95 */ 46021,
/* 96 */ 9999,
/* 97 */ 47004,
/* 98 */ 9999,
/* 99 */ 9999,
/* 100 */ 47021,
/* 101 */ 9999,
/* 102 */ 48004,
/* 103 */ 9999,
/* 104 */ 9999,
/* 105 */ 48018,
/* 106 */ 9999,
/* 107 */ 49004,
/* 108 */ 9999,
/* 109 */ 9999,
/* 110 */ 49019,
/* 111 */ 9999,
/* 112 */ 9999,
/* 113 */ 9999,
/* 114 */ 50004,
/* 115 */ 9999,
/* 116 */ 9999,
/* 117 */ 9999,
/* 118 */ 57009,
/* 119 */ 9999,
/* 120 */ 9999,
/* 121 */ 9999,
/* 122 */ 9999,
/* 123 */ 64011,
/* 124 */ 9999,
/* 125 */ 9999,
/* 126 */ 9999,
/* 127 */ 77006,
/* 128 */ 9999,
/* 129 */ 9999,
/* 130 */ 9999,
/* 131 */ 9999,
/* 132 */ 84008,
/* 133 */ 9999,
/* 134 */ 9999,
/* 135 */ 9999,
/* 136 */ 98009,
/* 137 */ 9999,
/* 138 */ 102002,
/* 139 */ 103002,
/* 140 */ 9999,
/* 141 */ 98003,
/* 142 */ 9999,
/* 143 */ 9999,
/* 144 */ 103004,
/* 145 */ 9999,
/* 146 */ 9999,
/* 147 */ 109009,
/* 148 */ 9999,
/* 149 */ 106006,
/* 150 */ 9999,
/* 151 */ 9999,
/* 152 */ 9999,
/* 153 */ 123012,
/* 154 */ 9999,
/* 155 */ 127002,
/* 156 */ 9999,
/* 157 */ 123006,
/* 158 */ 9999,
/* 159 */ 9999,
/* 160 */ 144002,
/* 161 */ 9999,
/* 162 */ 143009,
/* 163 */ 9999,
/* 164 */ 9999,
/* 165 */ 154009,
/* 166 */ 9999,
/* 167 */ 154007,
/* 168 */ 9999,
/* 169 */ 9999,
/* 170 */ 9999,
/* 171 */ 155009,
/* 172 */ 9999,
/* 173 */ 159002,
/* 174 */ 9999,
/* 175 */ 159011,
/* 176 */ 9999,
/* 177 */ 159005,
/* 178 */ 9999,
/* 179 */ 160004,
/* 180 */ 9999,
/* 181 */ 9999,
/* 182 */ 160017,
/* 183 */ 9999,
/* 184 */ 160007,
/* 185 */ 9999,
/* 186 */ 161004,
/* 187 */ 9999,
/* 188 */ 9999,
/* 189 */ 161017,
/* 190 */ 9999,
/* 191 */ 161007,
/* 192 */ 9999,
/* 193 */ 162004,
/* 194 */ 9999,
/* 195 */ 9999,
/* 196 */ 162017,
/* 197 */ 9999,
/* 198 */ 162007,
/* 199 */ 9999,
/* 200 */ 163004,
/* 201 */ 9999,
/* 202 */ 9999,
/* 203 */ 163017,
/* 204 */ 9999,
/* 205 */ 163007,
/* 206 */ 9999,
/* 207 */ 164004,
/* 208 */ 9999,
/* 209 */ 9999,
/* 210 */ 164017,
/* 211 */ 9999,
/* 212 */ 164007,
/* 213 */ 9999,
/* 214 */ 165004,
/* 215 */ 9999,
/* 216 */ 9999,
/* 217 */ 165017,
/* 218 */ 9999,
/* 219 */ 165007,
/* 220 */ 9999,
/* 221 */ 166004,
/* 222 */ 9999,
/* 223 */ 9999,
/* 224 */ 166017,
/* 225 */ 9999,
/* 226 */ 166007,
/* 227 */ 9999,
/* 228 */ 167004,
/* 229 */ 9999,
/* 230 */ 9999,
/* 231 */ 167017,
/* 232 */ 9999,
/* 233 */ 167007,
/* 234 */ 9999,
/* 235 */ 168004,
/* 236 */ 9999,
/* 237 */ 9999,
/* 238 */ 9999,
/* 239 */ 168021,
/* 240 */ 9999,
/* 241 */ 168007,
/* 242 */ 9999,
/* 243 */ 169004,
/* 244 */ 9999,
/* 245 */ 9999,
/* 246 */ 9999,
/* 247 */ 169021,
/* 248 */ 9999,
/* 249 */ 169007,
/* 250 */ 9999,
/* 251 */ 170004,
/* 252 */ 9999,
/* 253 */ 170007,
/* 254 */ 9999,
/* 255 */ 174002,
/* 256 */ 9999,
/* 257 */ 174011,
/* 258 */ 9999,
/* 259 */ 174020,
/* 260 */ 9999,
/* 261 */ 174005,
/* 262 */ 9999,
/* 263 */ 175004,
/* 264 */ 9999,
/* 265 */ 175007,
/* 266 */ 9999,
/* 267 */ 179002,
/* 268 */ 9999,
/* 269 */ 9999,
/* 270 */ 179015,
/* 271 */ 9999,
/* 272 */ 179005,
/* 273 */ 9999,
/* 274 */ 180004,
/* 275 */ 9999,
/* 276 */ 180007,
/* 277 */ 9999,
/* 278 */ 184002,
/* 279 */ 9999,
/* 280 */ 9999,
/* 281 */ 184015,
/* 282 */ 9999,
/* 283 */ 184005,
/* 284 */ 9999,
/* 285 */ 185004,
/* 286 */ 9999,
/* 287 */ 185007,
/* 288 */ 9999,
/* 289 */ 189002,
/* 290 */ 9999,
/* 291 */ 189011,
/* 292 */ 9999,
/* 293 */ 189005,
/* 294 */ 9999,
/* 295 */ 190004,
/* 296 */ 9999,
/* 297 */ 190007,
/* 298 */ 9999,
/* 299 */ 194002,
/* 300 */ 9999,
/* 301 */ 194011,
/* 302 */ 9999,
/* 303 */ 194005,
/* 304 */ 9999,
/* 305 */ 195004,
/* 306 */ 9999,
/* 307 */ 195007,
/* 308 */ 9999,
/* 309 */ 199002,
/* 310 */ 9999,
/* 311 */ 199011,
/* 312 */ 9999,
/* 313 */ 199005,
/* 314 */ 9999,
/* 315 */ 200004,
/* 316 */ 9999,
/* 317 */ 200007,
/* 318 */ 9999,
/* 319 */ 204002,
/* 320 */ 9999,
/* 321 */ 9999,
/* 322 */ 204015,
/* 323 */ 9999,
/* 324 */ 204005,
/* 325 */ 9999,
/* 326 */ 205004,
/* 327 */ 9999,
/* 328 */ 9999,
/* 329 */ 205017,
/* 330 */ 9999,
/* 331 */ 205007,
/* 332 */ 9999,
/* 333 */ 206004,
/* 334 */ 9999,
/* 335 */ 206007,
/* 336 */ 9999,
/* 337 */ 210002,
/* 338 */ 9999,
/* 339 */ 210011,
/* 340 */ 9999,
/* 341 */ 210005,
/* 342 */ 9999,
/* 343 */ 211004,
/* 344 */ 9999,
/* 345 */ 211013,
/* 346 */ 9999,
/* 347 */ 211007,
/* 348 */ 9999,
/* 349 */ 212004,
/* 350 */ 9999,
/* 351 */ 9999,
/* 352 */ 212017,
/* 353 */ 9999,
/* 354 */ 212007,
/* 355 */ 9999,
/* 356 */ 213004,
/* 357 */ 9999,
/* 358 */ 9999,
/* 359 */ 213017,
/* 360 */ 9999,
/* 361 */ 213007,
/* 362 */ 9999,
/* 363 */ 214004,
/* 364 */ 9999,
/* 365 */ 214007,
/* 366 */ 9999,
/* 367 */ 218002,
/* 368 */ 9999,
/* 369 */ 9999,
/* 370 */ 218015,
/* 371 */ 9999,
/* 372 */ 218005,
/* 373 */ 9999,
/* 374 */ 219004,
/* 375 */ 9999,
/* 376 */ 9999,
/* 377 */ 219017,
/* 378 */ 9999,
/* 379 */ 219007,
/* 380 */ 9999,
/* 381 */ 220004,
/* 382 */ 9999,
/* 383 */ 220008,
/* 384 */ 9999,
/* 385 */ 224002,
/* 386 */ 9999,
/* 387 */ 224012,
/* 388 */ 9999,
/* 389 */ 224006,
/* 390 */ 9999,
/* 391 */ 225004,
/* 392 */ 9999,
/* 393 */ 225014,
/* 394 */ 9999,
/* 395 */ 225008,
/* 396 */ 9999,
/* 397 */ 226004,
/* 398 */ 9999,
/* 399 */ 226014,
/* 400 */ 9999,
/* 401 */ 226008,
/* 402 */ 9999,
/* 403 */ 227004,
/* 404 */ 9999,
/* 405 */ 227008,
/* 406 */ 9999,
/* 407 */ 231002,
/* 408 */ 9999,
/* 409 */ 231012,
/* 410 */ 9999,
/* 411 */ 231006,
/* 412 */ 9999,
/* 413 */ 232004,
/* 414 */ 9999,
/* 415 */ 232014,
/* 416 */ 9999,
/* 417 */ 232008,
/* 418 */ 9999,
/* 419 */ 233004,
/* 420 */ 9999,
/* 421 */ 233014,
/* 422 */ 9999,
/* 423 */ 233008,
/* 424 */ 9999,
/* 425 */ 234004,
/* 426 */ 9999,
/* 427 */ 234008,
/* 428 */ 9999,
/* 429 */ 238002,
/* 430 */ 9999,
/* 431 */ 9999,
/* 432 */ 238016,
/* 433 */ 9999,
/* 434 */ 238006,
/* 435 */ 9999,
/* 436 */ 239004,
/* 437 */ 9999,
/* 438 */ 239008,
/* 439 */ 9999,
/* 440 */ 9999,
/* 441 */ 9999,
/* 442 */ 243018,
/* 443 */ 9999,
/* 444 */ 9999,
/* 445 */ 243012,
/* 446 */ 9999,
/* 447 */ 9999,
/* 448 */ 9999,
/* 449 */ 244020,
/* 450 */ 9999,
/* 451 */ 9999,
/* 452 */ 244014,
/* 453 */ 9999,
/* 454 */ 9999,
/* 455 */ 9999,
/* 456 */ 245018,
/* 457 */ 9999,
/* 458 */ 9999,
/* 459 */ 245012,
/* 460 */ 9999,
/* 461 */ 9999,
/* 462 */ 9999,
/* 463 */ 9999,
/* 464 */ 246006,
/* 465 */ 9999,
/* 466 */ 9999,
/* 467 */ 9999,
/* 468 */ 247012,
/* 469 */ 9999,
/* 470 */ 9999,
/* 471 */ 247006,
/* 472 */ 9999,
/* 473 */ 9999,
/* 474 */ 248008,
/* 475 */ 9999,
/* 476 */ 248004,
/* 477 */ 9999,
/* 478 */ 9999,
/* 479 */ 249008,
/* 480 */ 9999,
/* 481 */ 249004,
/* 482 */ 9999,
/* 483 */ 9999,
/* 484 */ 250008,
/* 485 */ 9999,
/* 486 */ 250004,
/* 487 */ 9999,
/* 488 */ 9999,
/* 489 */ 251008,
/* 490 */ 9999,
/* 491 */ 251004,
/* 492 */ 9999,
/* 493 */ 9999,
/* 494 */ 9999,
/* 495 */ 252012,
/* 496 */ 9999,
/* 497 */ 252004,
/* 498 */ 9999,
/* 499 */ 9999,
/* 500 */ 9999,
/* 501 */ 253012,
/* 502 */ 9999,
/* 503 */ 253004,
/* 504 */ 9999,
/* 505 */ 254004,
/* 506 */ 9999,
/* 507 */ 9999,
/* 508 */ 9999,
/* 509 */ 254008,
/* 510 */ 9999,
/* 511 */ 255004,
/* 512 */ 9999,
/* 513 */ 9999,
/* 514 */ 9999,
/* 515 */ 255008,
/* 516 */ 9999,
/* 517 */ 256004,
/* 518 */ 9999,
/* 519 */ 256008,
/* 520 */ 9999,
/* 521 */ 260002,
/* 522 */ 9999,
/* 523 */ 260014,
/* 524 */ 9999,
/* 525 */ 261004,
/* 526 */ 9999,
/* 527 */ 261014,
/* 528 */ 9999,
/* 529 */ 262004,
/* 530 */ 9999,
/* 531 */ 262014,
/* 532 */ 9999,
/* 533 */ 9999,
/* 534 */ 262008,
/* 535 */ 9999,
/* 536 */ 9999,
/* 537 */ 263008,
/* 538 */ 9999,
/* 539 */ 9999,
/* 540 */ 263004,
/* 541 */ 9999,
/* 542 */ 264004,
/* 543 */ 9999,
/* 544 */ 264011,
/* 545 */ 9999,
/* 546 */ 272002,
/* 547 */ 9999,
/* 548 */ 272021,
/* 549 */ 9999,
/* 550 */ 9999,
/* 551 */ 9999,
/* 552 */ 276013,
/* 553 */ 9999,
/* 554 */ 9999,
/* 555 */ 276003,
/* 556 */ 9999,
/* 557 */ 9999,
/* 558 */ 9999,
/* 559 */ 277017,
/* 560 */ 9999,
/* 561 */ 9999,
/* 562 */ 277030,
/* 563 */ 9999,
/* 564 */ 9999,
/* 565 */ 277011,
/* 566 */ 9999,
/* 567 */ 9999,
/* 568 */ 281002,
/* 569 */ 9999,
/* 570 */ 281004,
/* 571 */ 281033,
/* 572 */ 9999,
/* 573 */ 281020,
/* 574 */ 9999,
/* 575 */ 9999,
/* 576 */ 281039,
/* 577 */ 281035,
/* 578 */ 9999,
/* 579 */ 281035,
/* 580 */ 9999,
/* 581 */ 9999,
/* 582 */ 281035,
/* 583 */ 9999,
/* 584 */ 285002,
/* 585 */ 9999,
/* 586 */ 285005,
/* 587 */ 9999,
/* 588 */ 289002,
/* 589 */ 9999,
/* 590 */ 9999,
/* 591 */ 289016,
/* 592 */ 9999,
/* 593 */ 289006,
/* 594 */ 9999,
/* 595 */ 297002,
/* 596 */ 9999,
/* 597 */ 297002,
/* 598 */ 9999,
/* 599 */ 298004,
/* 600 */ 9999,
/* 601 */ 298023,
/* 602 */ 9999,
/* 603 */ 9999,
/* 604 */ 9999,
/* 605 */ 297005,
/* 606 */ 9999,
/* 607 */ 9999,
/* 608 */ 9999,
/* 609 */ 297063,
/* 610 */ 9999,
/* 611 */ 9999,
/* 612 */ 297057,
/* 613 */ 9999,
/* 614 */ 9999,
/* 615 */ 9999,
/* 616 */ 302007,
/* 617 */ 9999,
/* 618 */ 9999,
/* 619 */ 9999,
/* 620 */ 312009,
/* 621 */ 9999,
/* 622 */ 9999,
/* 623 */ 9999,
/* 624 */ 315007,
/* 625 */ 9999,
/* 626 */ 9999,
/* 627 */ 9999,
/* 628 */ 318005,
/* 629 */ 9999,
/* 630 */ 9999,
/* 631 */ 9999,
/* 632 */ 9999,
/* 633 */ 322004,
0
};
/* only for BIGHASH (see art.c)
extern int DHITS[];
int DHITS[635];
*/
int TABLE[119][280];
init_dirsets() {
TABLE[102][0] = 1;
TABLE[102][260] = 1;
TABLE[102][59] = 1;
TABLE[102][264] = 1;
TABLE[102][267] = 1;
TABLE[102][278] = 1;
TABLE[102][271] = 1;
TABLE[102][268] = 1;
TABLE[102][265] = 1;
TABLE[102][261] = 1;
TABLE[102][262] = 1;
TABLE[102][263] = 1;
TABLE[102][276] = 1;
TABLE[102][43] = 1;
TABLE[102][45] = 1;
TABLE[102][33] = 1;
TABLE[102][126] = 1;
TABLE[102][40] = 1;
TABLE[102][257] = 1;
TABLE[102][256] = 1;
TABLE[102][258] = 1;
TABLE[102][259] = 1;
TABLE[102][36] = 1;
TABLE[1][0] = 1;
TABLE[1][59] = 1;
TABLE[1][260] = 1;
TABLE[1][265] = 1;
TABLE[1][268] = 1;
TABLE[1][271] = 1;
TABLE[1][278] = 1;
TABLE[1][267] = 1;
TABLE[1][264] = 1;
TABLE[1][126] = 1;
TABLE[1][33] = 1;
TABLE[1][45] = 1;
TABLE[1][43] = 1;
TABLE[1][276] = 1;
TABLE[1][263] = 1;
TABLE[1][262] = 1;
TABLE[1][261] = 1;
TABLE[1][40] = 1;
TABLE[1][36] = 1;
TABLE[1][259] = 1;
TABLE[1][258] = 1;
TABLE[1][256] = 1;
TABLE[1][257] = 1;
TABLE[103][59] = 1;
TABLE[103][264] = 1;
TABLE[103][267] = 1;
TABLE[103][278] = 1;
TABLE[103][271] = 1;
TABLE[103][268] = 1;
TABLE[103][265] = 1;
TABLE[103][261] = 1;
TABLE[103][262] = 1;
TABLE[103][263] = 1;
TABLE[103][276] = 1;
TABLE[103][43] = 1;
TABLE[103][45] = 1;
TABLE[103][33] = 1;
TABLE[103][126] = 1;
TABLE[103][40] = 1;
TABLE[103][257] = 1;
TABLE[103][256] = 1;
TABLE[103][258] = 1;
TABLE[103][259] = 1;
TABLE[103][36] = 1;
TABLE[103][260] = 1;
TABLE[104][260] = 1;
TABLE[115][0] = 1;
TABLE[2][260] = 1;
TABLE[105][123] = 1;
TABLE[105][59] = 1;
TABLE[105][265] = 1;
TABLE[105][268] = 1;
TABLE[105][271] = 1;
TABLE[105][278] = 1;
TABLE[105][267] = 1;
TABLE[105][264] = 1;
TABLE[105][126] = 1;
TABLE[105][33] = 1;
TABLE[105][45] = 1;
TABLE[105][43] = 1;
TABLE[105][276] = 1;
TABLE[105][263] = 1;
TABLE[105][262] = 1;
TABLE[105][261] = 1;
TABLE[105][40] = 1;
TABLE[105][36] = 1;
TABLE[105][259] = 1;
TABLE[105][258] = 1;
TABLE[105][256] = 1;
TABLE[105][257] = 1;
TABLE[105][260] = 1;
TABLE[107][58] = 1;
TABLE[108][58] = 1;
TABLE[106][44] = 1;
TABLE[116][123] = 1;
TABLE[116][59] = 1;
TABLE[116][265] = 1;
TABLE[116][268] = 1;
TABLE[116][271] = 1;
TABLE[116][278] = 1;
TABLE[116][267] = 1;
TABLE[116][264] = 1;
TABLE[116][126] = 1;
TABLE[116][33] = 1;
TABLE[116][45] = 1;
TABLE[116][43] = 1;
TABLE[116][276] = 1;
TABLE[116][263] = 1;
TABLE[116][262] = 1;
TABLE[116][261] = 1;
TABLE[116][40] = 1;
TABLE[116][36] = 1;
TABLE[116][259] = 1;
TABLE[116][258] = 1;
TABLE[116][256] = 1;
TABLE[116][257] = 1;
TABLE[116][260] = 1;
TABLE[3][259] = 1;
TABLE[4][123] = 1;
TABLE[5][59] = 1;
TABLE[5][264] = 1;
TABLE[5][267] = 1;
TABLE[5][278] = 1;
TABLE[5][271] = 1;
TABLE[5][268] = 1;
TABLE[5][265] = 1;
TABLE[5][261] = 1;
TABLE[5][262] = 1;
TABLE[5][263] = 1;
TABLE[5][276] = 1;
TABLE[5][43] = 1;
TABLE[5][45] = 1;
TABLE[5][33] = 1;
TABLE[5][126] = 1;
TABLE[5][40] = 1;
TABLE[5][257] = 1;
TABLE[5][256] = 1;
TABLE[5][258] = 1;
TABLE[5][259] = 1;
TABLE[5][36] = 1;
TABLE[5][260] = 1;
TABLE[6][59] = 1;
TABLE[6][264] = 1;
TABLE[6][267] = 1;
TABLE[6][278] = 1;
TABLE[6][271] = 1;
TABLE[6][268] = 1;
TABLE[6][265] = 1;
TABLE[6][261] = 1;
TABLE[6][262] = 1;
TABLE[6][263] = 1;
TABLE[6][276] = 1;
TABLE[6][43] = 1;
TABLE[6][45] = 1;
TABLE[6][33] = 1;
TABLE[6][126] = 1;
TABLE[6][40] = 1;
TABLE[6][257] = 1;
TABLE[6][256] = 1;
TABLE[6][258] = 1;
TABLE[6][259] = 1;
TABLE[6][36] = 1;
TABLE[6][260] = 1;
TABLE[109][59] = 1;
TABLE[109][264] = 1;
TABLE[109][267] = 1;
TABLE[109][278] = 1;
TABLE[109][271] = 1;
TABLE[109][268] = 1;
TABLE[109][265] = 1;
TABLE[109][261] = 1;
TABLE[109][262] = 1;
TABLE[109][263] = 1;
TABLE[109][276] = 1;
TABLE[109][43] = 1;
TABLE[109][45] = 1;
TABLE[109][33] = 1;
TABLE[109][126] = 1;
TABLE[109][40] = 1;
TABLE[109][257] = 1;
TABLE[109][256] = 1;
TABLE[109][258] = 1;
TABLE[109][259] = 1;
TABLE[109][36] = 1;
TABLE[109][260] = 1;
TABLE[117][125] = 1;
TABLE[7][126] = 1;
TABLE[7][33] = 1;
TABLE[7][45] = 1;
TABLE[7][43] = 1;
TABLE[7][276] = 1;
TABLE[7][263] = 1;
TABLE[7][262] = 1;
TABLE[7][261] = 1;
TABLE[7][40] = 1;
TABLE[7][36] = 1;
TABLE[7][259] = 1;
TABLE[7][258] = 1;
TABLE[7][256] = 1;
TABLE[7][257] = 1;
TABLE[7][260] = 1;
TABLE[8][264] = 1;
TABLE[9][267] = 1;
TABLE[10][278] = 1;
TABLE[11][271] = 1;
TABLE[12][268] = 1;
TABLE[13][265] = 1;
TABLE[14][59] = 1;
TABLE[15][271] = 1;
TABLE[16][271] = 1;
TABLE[17][268] = 1;
TABLE[18][268] = 1;
TABLE[19][264] = 1;
TABLE[110][59] = 1;
TABLE[110][260] = 1;
TABLE[110][265] = 1;
TABLE[110][268] = 1;
TABLE[110][271] = 1;
TABLE[110][278] = 1;
TABLE[110][267] = 1;
TABLE[110][264] = 1;
TABLE[110][126] = 1;
TABLE[110][33] = 1;
TABLE[110][45] = 1;
TABLE[110][43] = 1;
TABLE[110][276] = 1;
TABLE[110][263] = 1;
TABLE[110][262] = 1;
TABLE[110][261] = 1;
TABLE[110][40] = 1;
TABLE[110][36] = 1;
TABLE[110][259] = 1;
TABLE[110][258] = 1;
TABLE[110][256] = 1;
TABLE[110][257] = 1;
TABLE[110][0] = 1;
TABLE[110][125] = 1;
TABLE[110][275] = 1;
TABLE[111][275] = 1;
TABLE[20][267] = 1;
TABLE[21][278] = 1;
TABLE[22][265] = 1;
TABLE[23][265] = 1;
TABLE[24][261] = 1;
TABLE[24][262] = 1;
TABLE[24][263] = 1;
TABLE[24][276] = 1;
TABLE[24][43] = 1;
TABLE[24][45] = 1;
TABLE[24][33] = 1;
TABLE[24][126] = 1;
TABLE[24][40] = 1;
TABLE[24][257] = 1;
TABLE[24][256] = 1;
TABLE[24][258] = 1;
TABLE[24][259] = 1;
TABLE[24][36] = 1;
TABLE[24][260] = 1;
TABLE[25][261] = 1;
TABLE[25][262] = 1;
TABLE[25][263] = 1;
TABLE[25][276] = 1;
TABLE[25][43] = 1;
TABLE[25][45] = 1;
TABLE[25][33] = 1;
TABLE[25][126] = 1;
TABLE[25][40] = 1;
TABLE[25][257] = 1;
TABLE[25][256] = 1;
TABLE[25][258] = 1;
TABLE[25][259] = 1;
TABLE[25][36] = 1;
TABLE[25][260] = 1;
TABLE[26][261] = 1;
TABLE[26][262] = 1;
TABLE[26][263] = 1;
TABLE[26][276] = 1;
TABLE[26][43] = 1;
TABLE[26][45] = 1;
TABLE[26][33] = 1;
TABLE[26][126] = 1;
TABLE[26][40] = 1;
TABLE[26][257] = 1;
TABLE[26][256] = 1;
TABLE[26][258] = 1;
TABLE[26][259] = 1;
TABLE[26][36] = 1;
TABLE[26][260] = 1;
TABLE[27][261] = 1;
TABLE[27][262] = 1;
TABLE[27][263] = 1;
TABLE[27][276] = 1;
TABLE[27][43] = 1;
TABLE[27][45] = 1;
TABLE[27][33] = 1;
TABLE[27][126] = 1;
TABLE[27][40] = 1;
TABLE[27][257] = 1;
TABLE[27][256] = 1;
TABLE[27][258] = 1;
TABLE[27][259] = 1;
TABLE[27][36] = 1;
TABLE[27][260] = 1;
TABLE[28][261] = 1;
TABLE[28][262] = 1;
TABLE[28][263] = 1;
TABLE[28][276] = 1;
TABLE[28][43] = 1;
TABLE[28][45] = 1;
TABLE[28][33] = 1;
TABLE[28][126] = 1;
TABLE[28][40] = 1;
TABLE[28][257] = 1;
TABLE[28][256] = 1;
TABLE[28][258] = 1;
TABLE[28][259] = 1;
TABLE[28][36] = 1;
TABLE[28][260] = 1;
TABLE[29][261] = 1;
TABLE[29][262] = 1;
TABLE[29][263] = 1;
TABLE[29][276] = 1;
TABLE[29][43] = 1;
TABLE[29][45] = 1;
TABLE[29][33] = 1;
TABLE[29][126] = 1;
TABLE[29][40] = 1;
TABLE[29][257] = 1;
TABLE[29][256] = 1;
TABLE[29][258] = 1;
TABLE[29][259] = 1;
TABLE[29][36] = 1;
TABLE[29][260] = 1;
TABLE[30][261] = 1;
TABLE[30][262] = 1;
TABLE[30][263] = 1;
TABLE[30][276] = 1;
TABLE[30][43] = 1;
TABLE[30][45] = 1;
TABLE[30][33] = 1;
TABLE[30][126] = 1;
TABLE[30][40] = 1;
TABLE[30][257] = 1;
TABLE[30][256] = 1;
TABLE[30][258] = 1;
TABLE[30][259] = 1;
TABLE[30][36] = 1;
TABLE[30][260] = 1;
TABLE[31][261] = 1;
TABLE[31][262] = 1;
TABLE[31][263] = 1;
TABLE[31][276] = 1;
TABLE[31][43] = 1;
TABLE[31][45] = 1;
TABLE[31][33] = 1;
TABLE[31][126] = 1;
TABLE[31][40] = 1;
TABLE[31][257] = 1;
TABLE[31][256] = 1;
TABLE[31][258] = 1;
TABLE[31][259] = 1;
TABLE[31][36] = 1;
TABLE[31][260] = 1;
TABLE[32][261] = 1;
TABLE[32][262] = 1;
TABLE[32][263] = 1;
TABLE[32][276] = 1;
TABLE[32][43] = 1;
TABLE[32][45] = 1;
TABLE[32][33] = 1;
TABLE[32][126] = 1;
TABLE[32][40] = 1;
TABLE[32][257] = 1;
TABLE[32][256] = 1;
TABLE[32][258] = 1;
TABLE[32][259] = 1;
TABLE[32][36] = 1;
TABLE[32][260] = 1;
TABLE[33][261] = 1;
TABLE[33][262] = 1;
TABLE[33][263] = 1;
TABLE[33][276] = 1;
TABLE[33][43] = 1;
TABLE[33][45] = 1;
TABLE[33][33] = 1;
TABLE[33][126] = 1;
TABLE[33][40] = 1;
TABLE[33][257] = 1;
TABLE[33][256] = 1;
TABLE[33][258] = 1;
TABLE[33][259] = 1;
TABLE[33][36] = 1;
TABLE[33][260] = 1;
TABLE[34][261] = 1;
TABLE[34][262] = 1;
TABLE[34][263] = 1;
TABLE[34][276] = 1;
TABLE[34][43] = 1;
TABLE[34][45] = 1;
TABLE[34][33] = 1;
TABLE[34][126] = 1;
TABLE[34][40] = 1;
TABLE[34][257] = 1;
TABLE[34][256] = 1;
TABLE[34][258] = 1;
TABLE[34][259] = 1;
TABLE[34][36] = 1;
TABLE[34][260] = 1;
TABLE[35][261] = 1;
TABLE[35][262] = 1;
TABLE[35][263] = 1;
TABLE[35][276] = 1;
TABLE[35][43] = 1;
TABLE[35][45] = 1;
TABLE[35][33] = 1;
TABLE[35][126] = 1;
TABLE[35][40] = 1;
TABLE[35][257] = 1;
TABLE[35][256] = 1;
TABLE[35][258] = 1;
TABLE[35][259] = 1;
TABLE[35][36] = 1;
TABLE[35][260] = 1;
TABLE[36][261] = 1;
TABLE[36][262] = 1;
TABLE[36][263] = 1;
TABLE[36][276] = 1;
TABLE[36][43] = 1;
TABLE[36][45] = 1;
TABLE[36][33] = 1;
TABLE[36][126] = 1;
TABLE[36][40] = 1;
TABLE[36][257] = 1;
TABLE[36][256] = 1;
TABLE[36][258] = 1;
TABLE[36][259] = 1;
TABLE[36][36] = 1;
TABLE[36][260] = 1;
TABLE[37][126] = 1;
TABLE[37][33] = 1;
TABLE[37][45] = 1;
TABLE[37][43] = 1;
TABLE[37][276] = 1;
TABLE[37][263] = 1;
TABLE[37][262] = 1;
TABLE[37][261] = 1;
TABLE[37][40] = 1;
TABLE[37][36] = 1;
TABLE[37][259] = 1;
TABLE[37][258] = 1;
TABLE[37][256] = 1;
TABLE[37][257] = 1;
TABLE[37][260] = 1;
TABLE[38][126] = 1;
TABLE[38][33] = 1;
TABLE[38][45] = 1;
TABLE[38][43] = 1;
TABLE[38][276] = 1;
TABLE[38][263] = 1;
TABLE[38][262] = 1;
TABLE[38][261] = 1;
TABLE[38][40] = 1;
TABLE[38][36] = 1;
TABLE[38][259] = 1;
TABLE[38][258] = 1;
TABLE[38][256] = 1;
TABLE[38][257] = 1;
TABLE[38][260] = 1;
TABLE[39][261] = 1;
TABLE[39][262] = 1;
TABLE[39][263] = 1;
TABLE[39][276] = 1;
TABLE[39][43] = 1;
TABLE[39][45] = 1;
TABLE[39][33] = 1;
TABLE[39][126] = 1;
TABLE[39][40] = 1;
TABLE[39][257] = 1;
TABLE[39][256] = 1;
TABLE[39][258] = 1;
TABLE[39][259] = 1;
TABLE[39][36] = 1;
TABLE[39][260] = 1;
TABLE[40][261] = 1;
TABLE[40][262] = 1;
TABLE[40][263] = 1;
TABLE[40][276] = 1;
TABLE[40][43] = 1;
TABLE[40][45] = 1;
TABLE[40][33] = 1;
TABLE[40][126] = 1;
TABLE[40][40] = 1;
TABLE[40][257] = 1;
TABLE[40][256] = 1;
TABLE[40][258] = 1;
TABLE[40][259] = 1;
TABLE[40][36] = 1;
TABLE[40][260] = 1;
TABLE[41][126] = 1;
TABLE[41][33] = 1;
TABLE[41][45] = 1;
TABLE[41][43] = 1;
TABLE[41][276] = 1;
TABLE[41][263] = 1;
TABLE[41][262] = 1;
TABLE[41][261] = 1;
TABLE[41][40] = 1;
TABLE[41][36] = 1;
TABLE[41][259] = 1;
TABLE[41][258] = 1;
TABLE[41][256] = 1;
TABLE[41][257] = 1;
TABLE[41][260] = 1;
TABLE[42][126] = 1;
TABLE[42][33] = 1;
TABLE[42][45] = 1;
TABLE[42][43] = 1;
TABLE[42][276] = 1;
TABLE[42][263] = 1;
TABLE[42][262] = 1;
TABLE[42][261] = 1;
TABLE[42][40] = 1;
TABLE[42][36] = 1;
TABLE[42][259] = 1;
TABLE[42][258] = 1;
TABLE[42][256] = 1;
TABLE[42][257] = 1;
TABLE[42][260] = 1;
TABLE[43][261] = 1;
TABLE[43][262] = 1;
TABLE[43][263] = 1;
TABLE[43][276] = 1;
TABLE[43][43] = 1;
TABLE[43][45] = 1;
TABLE[43][33] = 1;
TABLE[43][126] = 1;
TABLE[43][40] = 1;
TABLE[43][257] = 1;
TABLE[43][256] = 1;
TABLE[43][258] = 1;
TABLE[43][259] = 1;
TABLE[43][36] = 1;
TABLE[43][260] = 1;
TABLE[44][261] = 1;
TABLE[44][262] = 1;
TABLE[44][263] = 1;
TABLE[44][276] = 1;
TABLE[44][43] = 1;
TABLE[44][45] = 1;
TABLE[44][33] = 1;
TABLE[44][126] = 1;
TABLE[44][40] = 1;
TABLE[44][257] = 1;
TABLE[44][256] = 1;
TABLE[44][258] = 1;
TABLE[44][259] = 1;
TABLE[44][36] = 1;
TABLE[44][260] = 1;
TABLE[45][126] = 1;
TABLE[45][33] = 1;
TABLE[45][45] = 1;
TABLE[45][43] = 1;
TABLE[45][276] = 1;
TABLE[45][263] = 1;
TABLE[45][262] = 1;
TABLE[45][261] = 1;
TABLE[45][40] = 1;
TABLE[45][36] = 1;
TABLE[45][259] = 1;
TABLE[45][258] = 1;
TABLE[45][256] = 1;
TABLE[45][257] = 1;
TABLE[45][260] = 1;
TABLE[46][126] = 1;
TABLE[46][33] = 1;
TABLE[46][45] = 1;
TABLE[46][43] = 1;
TABLE[46][276] = 1;
TABLE[46][263] = 1;
TABLE[46][262] = 1;
TABLE[46][261] = 1;
TABLE[46][40] = 1;
TABLE[46][36] = 1;
TABLE[46][259] = 1;
TABLE[46][258] = 1;
TABLE[46][256] = 1;
TABLE[46][257] = 1;
TABLE[46][260] = 1;
TABLE[47][261] = 1;
TABLE[47][262] = 1;
TABLE[47][263] = 1;
TABLE[47][276] = 1;
TABLE[47][43] = 1;
TABLE[47][45] = 1;
TABLE[47][33] = 1;
TABLE[47][126] = 1;
TABLE[47][40] = 1;
TABLE[47][257] = 1;
TABLE[47][256] = 1;
TABLE[47][258] = 1;
TABLE[47][259] = 1;
TABLE[47][36] = 1;
TABLE[47][260] = 1;
TABLE[48][261] = 1;
TABLE[48][262] = 1;
TABLE[48][263] = 1;
TABLE[48][276] = 1;
TABLE[48][43] = 1;
TABLE[48][45] = 1;
TABLE[48][33] = 1;
TABLE[48][126] = 1;
TABLE[48][40] = 1;
TABLE[48][257] = 1;
TABLE[48][256] = 1;
TABLE[48][258] = 1;
TABLE[48][259] = 1;
TABLE[48][36] = 1;
TABLE[48][260] = 1;
TABLE[49][261] = 1;
TABLE[49][262] = 1;
TABLE[49][263] = 1;
TABLE[49][276] = 1;
TABLE[49][43] = 1;
TABLE[49][45] = 1;
TABLE[49][33] = 1;
TABLE[49][126] = 1;
TABLE[49][40] = 1;
TABLE[49][257] = 1;
TABLE[49][256] = 1;
TABLE[49][258] = 1;
TABLE[49][259] = 1;
TABLE[49][36] = 1;
TABLE[49][260] = 1;
TABLE[50][126] = 1;
TABLE[50][33] = 1;
TABLE[50][45] = 1;
TABLE[50][43] = 1;
TABLE[50][276] = 1;
TABLE[50][263] = 1;
TABLE[50][262] = 1;
TABLE[50][261] = 1;
TABLE[50][40] = 1;
TABLE[50][36] = 1;
TABLE[50][259] = 1;
TABLE[50][258] = 1;
TABLE[50][256] = 1;
TABLE[50][257] = 1;
TABLE[50][260] = 1;
TABLE[51][126] = 1;
TABLE[51][33] = 1;
TABLE[51][45] = 1;
TABLE[51][43] = 1;
TABLE[51][276] = 1;
TABLE[51][263] = 1;
TABLE[51][262] = 1;
TABLE[51][261] = 1;
TABLE[51][40] = 1;
TABLE[51][36] = 1;
TABLE[51][259] = 1;
TABLE[51][258] = 1;
TABLE[51][256] = 1;
TABLE[51][257] = 1;
TABLE[51][260] = 1;
TABLE[52][126] = 1;
TABLE[52][33] = 1;
TABLE[52][45] = 1;
TABLE[52][43] = 1;
TABLE[52][276] = 1;
TABLE[52][263] = 1;
TABLE[52][262] = 1;
TABLE[52][261] = 1;
TABLE[52][40] = 1;
TABLE[52][36] = 1;
TABLE[52][259] = 1;
TABLE[52][258] = 1;
TABLE[52][256] = 1;
TABLE[52][257] = 1;
TABLE[52][260] = 1;
TABLE[53][126] = 1;
TABLE[53][33] = 1;
TABLE[53][45] = 1;
TABLE[53][43] = 1;
TABLE[53][276] = 1;
TABLE[53][263] = 1;
TABLE[53][262] = 1;
TABLE[53][261] = 1;
TABLE[53][40] = 1;
TABLE[53][36] = 1;
TABLE[53][259] = 1;
TABLE[53][258] = 1;
TABLE[53][256] = 1;
TABLE[53][257] = 1;
TABLE[53][260] = 1;
TABLE[54][126] = 1;
TABLE[54][33] = 1;
TABLE[54][45] = 1;
TABLE[54][43] = 1;
TABLE[54][276] = 1;
TABLE[54][263] = 1;
TABLE[54][262] = 1;
TABLE[54][261] = 1;
TABLE[54][40] = 1;
TABLE[54][36] = 1;
TABLE[54][259] = 1;
TABLE[54][258] = 1;
TABLE[54][256] = 1;
TABLE[54][257] = 1;
TABLE[54][260] = 1;
TABLE[55][261] = 1;
TABLE[55][262] = 1;
TABLE[55][263] = 1;
TABLE[55][276] = 1;
TABLE[55][43] = 1;
TABLE[55][45] = 1;
TABLE[55][33] = 1;
TABLE[55][126] = 1;
TABLE[55][40] = 1;
TABLE[55][257] = 1;
TABLE[55][256] = 1;
TABLE[55][258] = 1;
TABLE[55][259] = 1;
TABLE[55][36] = 1;
TABLE[55][260] = 1;
TABLE[56][261] = 1;
TABLE[56][262] = 1;
TABLE[56][263] = 1;
TABLE[56][276] = 1;
TABLE[56][43] = 1;
TABLE[56][45] = 1;
TABLE[56][33] = 1;
TABLE[56][126] = 1;
TABLE[56][40] = 1;
TABLE[56][257] = 1;
TABLE[56][256] = 1;
TABLE[56][258] = 1;
TABLE[56][259] = 1;
TABLE[56][36] = 1;
TABLE[56][260] = 1;
TABLE[57][261] = 1;
TABLE[57][262] = 1;
TABLE[57][263] = 1;
TABLE[57][276] = 1;
TABLE[57][43] = 1;
TABLE[57][45] = 1;
TABLE[57][33] = 1;
TABLE[57][126] = 1;
TABLE[57][40] = 1;
TABLE[57][257] = 1;
TABLE[57][256] = 1;
TABLE[57][258] = 1;
TABLE[57][259] = 1;
TABLE[57][36] = 1;
TABLE[57][260] = 1;
TABLE[58][126] = 1;
TABLE[58][33] = 1;
TABLE[58][45] = 1;
TABLE[58][43] = 1;
TABLE[58][276] = 1;
TABLE[58][263] = 1;
TABLE[58][262] = 1;
TABLE[58][261] = 1;
TABLE[58][40] = 1;
TABLE[58][36] = 1;
TABLE[58][259] = 1;
TABLE[58][258] = 1;
TABLE[58][256] = 1;
TABLE[58][257] = 1;
TABLE[58][260] = 1;
TABLE[59][126] = 1;
TABLE[59][33] = 1;
TABLE[59][45] = 1;
TABLE[59][43] = 1;
TABLE[59][276] = 1;
TABLE[59][263] = 1;
TABLE[59][262] = 1;
TABLE[59][261] = 1;
TABLE[59][40] = 1;
TABLE[59][36] = 1;
TABLE[59][259] = 1;
TABLE[59][258] = 1;
TABLE[59][256] = 1;
TABLE[59][257] = 1;
TABLE[59][260] = 1;
TABLE[60][126] = 1;
TABLE[60][33] = 1;
TABLE[60][45] = 1;
TABLE[60][43] = 1;
TABLE[60][276] = 1;
TABLE[60][263] = 1;
TABLE[60][262] = 1;
TABLE[60][261] = 1;
TABLE[60][40] = 1;
TABLE[60][36] = 1;
TABLE[60][259] = 1;
TABLE[60][258] = 1;
TABLE[60][256] = 1;
TABLE[60][257] = 1;
TABLE[60][260] = 1;
TABLE[61][126] = 1;
TABLE[61][33] = 1;
TABLE[61][45] = 1;
TABLE[61][43] = 1;
TABLE[61][276] = 1;
TABLE[61][263] = 1;
TABLE[61][262] = 1;
TABLE[61][261] = 1;
TABLE[61][40] = 1;
TABLE[61][36] = 1;
TABLE[61][259] = 1;
TABLE[61][258] = 1;
TABLE[61][256] = 1;
TABLE[61][257] = 1;
TABLE[61][260] = 1;
TABLE[62][261] = 1;
TABLE[62][262] = 1;
TABLE[62][263] = 1;
TABLE[62][276] = 1;
TABLE[62][43] = 1;
TABLE[62][45] = 1;
TABLE[62][33] = 1;
TABLE[62][126] = 1;
TABLE[62][40] = 1;
TABLE[62][257] = 1;
TABLE[62][256] = 1;
TABLE[62][258] = 1;
TABLE[62][259] = 1;
TABLE[62][36] = 1;
TABLE[62][260] = 1;
TABLE[63][261] = 1;
TABLE[63][262] = 1;
TABLE[63][263] = 1;
TABLE[63][276] = 1;
TABLE[63][43] = 1;
TABLE[63][45] = 1;
TABLE[63][33] = 1;
TABLE[63][126] = 1;
TABLE[63][40] = 1;
TABLE[63][257] = 1;
TABLE[63][256] = 1;
TABLE[63][258] = 1;
TABLE[63][259] = 1;
TABLE[63][36] = 1;
TABLE[63][260] = 1;
TABLE[64][261] = 1;
TABLE[64][262] = 1;
TABLE[64][263] = 1;
TABLE[64][276] = 1;
TABLE[64][43] = 1;
TABLE[64][45] = 1;
TABLE[64][33] = 1;
TABLE[64][126] = 1;
TABLE[64][40] = 1;
TABLE[64][257] = 1;
TABLE[64][256] = 1;
TABLE[64][258] = 1;
TABLE[64][259] = 1;
TABLE[64][36] = 1;
TABLE[64][260] = 1;
TABLE[65][261] = 1;
TABLE[65][262] = 1;
TABLE[65][263] = 1;
TABLE[65][276] = 1;
TABLE[65][43] = 1;
TABLE[65][45] = 1;
TABLE[65][33] = 1;
TABLE[65][126] = 1;
TABLE[65][40] = 1;
TABLE[65][257] = 1;
TABLE[65][256] = 1;
TABLE[65][258] = 1;
TABLE[65][259] = 1;
TABLE[65][36] = 1;
TABLE[65][260] = 1;
TABLE[66][126] = 1;
TABLE[66][33] = 1;
TABLE[66][45] = 1;
TABLE[66][43] = 1;
TABLE[66][276] = 1;
TABLE[66][263] = 1;
TABLE[66][262] = 1;
TABLE[66][261] = 1;
TABLE[66][40] = 1;
TABLE[66][36] = 1;
TABLE[66][259] = 1;
TABLE[66][258] = 1;
TABLE[66][256] = 1;
TABLE[66][257] = 1;
TABLE[66][260] = 1;
TABLE[67][126] = 1;
TABLE[67][33] = 1;
TABLE[67][45] = 1;
TABLE[67][43] = 1;
TABLE[67][276] = 1;
TABLE[67][263] = 1;
TABLE[67][262] = 1;
TABLE[67][261] = 1;
TABLE[67][40] = 1;
TABLE[67][36] = 1;
TABLE[67][259] = 1;
TABLE[67][258] = 1;
TABLE[67][256] = 1;
TABLE[67][257] = 1;
TABLE[67][260] = 1;
TABLE[68][261] = 1;
TABLE[68][262] = 1;
TABLE[68][263] = 1;
TABLE[68][276] = 1;
TABLE[68][43] = 1;
TABLE[68][45] = 1;
TABLE[68][33] = 1;
TABLE[68][126] = 1;
TABLE[68][40] = 1;
TABLE[68][257] = 1;
TABLE[68][256] = 1;
TABLE[68][258] = 1;
TABLE[68][259] = 1;
TABLE[68][36] = 1;
TABLE[68][260] = 1;
TABLE[69][261] = 1;
TABLE[70][262] = 1;
TABLE[71][263] = 1;
TABLE[72][276] = 1;
TABLE[73][276] = 1;
TABLE[74][43] = 1;
TABLE[75][45] = 1;
TABLE[76][33] = 1;
TABLE[77][126] = 1;
TABLE[78][43] = 1;
TABLE[79][45] = 1;
TABLE[80][261] = 1;
TABLE[80][262] = 1;
TABLE[80][263] = 1;
TABLE[80][276] = 1;
TABLE[80][43] = 1;
TABLE[80][45] = 1;
TABLE[80][33] = 1;
TABLE[80][126] = 1;
TABLE[80][40] = 1;
TABLE[80][257] = 1;
TABLE[80][256] = 1;
TABLE[80][258] = 1;
TABLE[80][259] = 1;
TABLE[80][36] = 1;
TABLE[80][260] = 1;
TABLE[81][261] = 1;
TABLE[81][262] = 1;
TABLE[81][263] = 1;
TABLE[81][276] = 1;
TABLE[81][43] = 1;
TABLE[81][45] = 1;
TABLE[81][33] = 1;
TABLE[81][126] = 1;
TABLE[81][40] = 1;
TABLE[81][257] = 1;
TABLE[81][256] = 1;
TABLE[81][258] = 1;
TABLE[81][259] = 1;
TABLE[81][36] = 1;
TABLE[81][260] = 1;
TABLE[82][40] = 1;
TABLE[82][36] = 1;
TABLE[82][259] = 1;
TABLE[82][258] = 1;
TABLE[82][256] = 1;
TABLE[82][257] = 1;
TABLE[82][260] = 1;
TABLE[83][260] = 1;
TABLE[83][259] = 1;
TABLE[84][40] = 1;
TABLE[84][257] = 1;
TABLE[84][256] = 1;
TABLE[84][258] = 1;
TABLE[84][259] = 1;
TABLE[84][36] = 1;
TABLE[84][260] = 1;
TABLE[85][40] = 1;
TABLE[85][36] = 1;
TABLE[85][259] = 1;
TABLE[85][258] = 1;
TABLE[85][256] = 1;
TABLE[85][257] = 1;
TABLE[85][260] = 1;
TABLE[86][40] = 1;
TABLE[87][257] = 1;
TABLE[87][256] = 1;
TABLE[87][258] = 1;
TABLE[87][259] = 1;
TABLE[87][36] = 1;
TABLE[88][259] = 1;
TABLE[88][260] = 1;
TABLE[89][259] = 1;
TABLE[90][260] = 1;
TABLE[91][41] = 1;
TABLE[92][261] = 1;
TABLE[92][262] = 1;
TABLE[92][263] = 1;
TABLE[92][276] = 1;
TABLE[92][43] = 1;
TABLE[92][45] = 1;
TABLE[92][33] = 1;
TABLE[92][126] = 1;
TABLE[92][40] = 1;
TABLE[92][257] = 1;
TABLE[92][256] = 1;
TABLE[92][258] = 1;
TABLE[92][259] = 1;
TABLE[92][36] = 1;
TABLE[92][260] = 1;
TABLE[112][44] = 1;
TABLE[118][41] = 1;
TABLE[93][126] = 1;
TABLE[93][33] = 1;
TABLE[93][45] = 1;
TABLE[93][43] = 1;
TABLE[93][276] = 1;
TABLE[93][263] = 1;
TABLE[93][262] = 1;
TABLE[93][261] = 1;
TABLE[93][40] = 1;
TABLE[93][36] = 1;
TABLE[93][259] = 1;
TABLE[93][258] = 1;
TABLE[93][256] = 1;
TABLE[93][257] = 1;
TABLE[93][260] = 1;
TABLE[94][40] = 1;
TABLE[94][36] = 1;
TABLE[94][259] = 1;
TABLE[94][258] = 1;
TABLE[94][256] = 1;
TABLE[94][257] = 1;
TABLE[94][260] = 1;
TABLE[95][259] = 1;
TABLE[95][277] = 1;
TABLE[96][259] = 1;
TABLE[96][260] = 1;
TABLE[113][259] = 1;
TABLE[114][277] = 1;
TABLE[97][257] = 1;
TABLE[98][256] = 1;
TABLE[99][258] = 1;
TABLE[100][259] = 1;
TABLE[101][36] = 1;
}

extern int yydirset();
int yydirset(i,j)
   int i,j;
{
   return TABLE[i][j];
}
char * yyprintname(n)
   int n;
{
   if (n <= 50000)
      switch(n) {
         case 1: return "YYSTART"; break;
         case 6: return "program"; break;
         case 10: return "Subphrase"; break;
         case 23: return "function_def"; break;
         case 30: return "Subphrase"; break;
         case 43: return "Subphrase"; break;
         case 52: return "function_def_arg"; break;
         case 56: return "content"; break;
         case 66: return "statements"; break;
         case 71: return "Subphrase"; break;
         case 79: return "statement"; break;
         case 115: return "continue_statement"; break;
         case 124: return "break_statement"; break;
         case 133: return "if_statement"; break;
         case 142: return "Subphrase"; break;
         case 150: return "while_statement"; break;
         case 158: return "infinity_statement"; break;
         case 163: return "return_statement"; break;
         case 172: return "exp0"; break;
         case 254: return "exp1"; break;
         case 266: return "exp2"; break;
         case 277: return "exp3"; break;
         case 288: return "exp4"; break;
         case 298: return "exp5"; break;
         case 308: return "exp6"; break;
         case 318: return "exp7"; break;
         case 336: return "exp8"; break;
         case 366: return "exp9"; break;
         case 384: return "exp10"; break;
         case 406: return "exp11"; break;
         case 428: return "exp12"; break;
         case 439: return "exp13"; break;
         case 520: return "exp14"; break;
         case 545: return "function_call"; break;
         case 549: return "function_call_syntax"; break;
         case 566: return "function_call_args"; break;
         case 574: return "Subphrase"; break;
         case 583: return "function_call_arg"; break;
         case 587: return "member_call"; break;
         case 594: return "member_suffix"; break;
         case 602: return "Subphrase"; break;
         case 613: return "literals"; break;
   }
   else 
      switch(n-50000) {
         case 279: return "REGISTER"; break;
         case 278: return "INFINITY"; break;
         case 277: return "MEMBER"; break;
         case 276: return "NEW"; break;
         case 275: return "ELSE"; break;
         case 274: return "DEFAULT"; break;
         case 273: return "UNTIL"; break;
         case 272: return "WITH"; break;
         case 271: return "CONTINUE"; break;
         case 270: return "CASE"; break;
         case 269: return "SWITCH"; break;
         case 268: return "BREAK"; break;
         case 267: return "WHILE"; break;
         case 266: return "FOR"; break;
         case 265: return "RETURN"; break;
         case 264: return "IF"; break;
         case 263: return "CAST_REAL"; break;
         case 262: return "CAST_NUMBER"; break;
         case 261: return "CAST_STRING"; break;
         case 260: return "FUNCTION"; break;
         case 259: return "ID"; break;
         case 258: return "REAL"; break;
         case 257: return "NUMBER"; break;
         case 256: return "STRING"; break;
   }
   return "<character>";
}
