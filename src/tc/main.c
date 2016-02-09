
#include "tc.h"

FILE * yyin, * yyout;
TC tc = { 0 } ;

void display_help () 
{
 puts ("Syntax: tc (input_file | -stdin) (output_file | -stdout) [-d] [-i]") ;
 puts ("-stdin\tRead from standard input") ;
 puts ("-stdout\tRead from standard output") ;
 puts ("-d\tAdd debugging information") ;
 puts ("-r\tForce N number of registers to be allocated") ;
 puts ("-b\tForce Tetra to use N as the entry point function") ;
 puts ("-i\tIgnore warnings") ;
}

int main (int argc, char ** argv)
{
 int i = 0;
 byte mode = 0;

 argc-- ; argv++ ;

 if (argc < 2) 
 {
  display_help () ;
  return 1 ;
 }

 yyin = fopen(argv[0],"r");

 if (!yyin)
 {
  printf ("Couldn't open input file %s\n", argv[0]) ;
  return 1 ;
 }

 yyout = fopen(argv[1],"w+b") ;

 if (!yyout)
 {
  printf ("Couldn't open output file %s\n", argv[1]) ;
  fclose (yyin) ;
  return 1;
 }

 printf ("Compiling %s\n", argv[0]) ;

 yyparse();

 fclose(yyin) ;

 compile () ;

 fclose (yyout) ;

 fp_delete();
 sp_delete ();
 lp_delete () ;
// sm_dump(0) ;
 return 0;
}

yyerror(char * msg)
{
   extern long yypos;

   printf("Error on line %i: %s\n", yypos, msg);
}

yywrap()
{
   return 1;
}