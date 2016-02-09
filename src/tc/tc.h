
#include <tetra.h>

typedef struct tcstring
{
 byte length ;
 char * string  ;
} TCSTRING ;

typedef struct tcfunction
{
 word index ;
 word * args ;
 byte arg_count ;

 char * chunk ;
 dword allocated_size ;
 dword current_size ;
} TCFUNCTION ;

typedef struct tcloop
{
 dword begin_pos ;
 dword end_pos ;
 dword * trace_points ;
 word trace_point_count ;
} TCLOOP ;

typedef struct tc
{
 TCSTRING * string_pool ;
 word string_pool_entrys ;
 TCFUNCTION * function_pool ;
 TCFUNCTION * cur_func ;
 word function_pool_entrys ;
 TCLOOP * loop_pool ;
 TCLOOP * cur_loop ;
 word loop_pool_entrys ;
} TC ;

extern TC tc ;

typedef union tcarg {
  word index ;
  long number ;
  double real ;
} TCARG ;

word sp_add (char * string, dword length) ;
void sp_delete () ;

void fp_add (word string) ;
void fp_revert (void) ;
void fp_arg (word string);
void fp_delete ();

TCLOOP * lp_add () ;
TCLOOP * lp_get (word i) ;
void lp_add_trace (TCLOOP * loop, dword position) ;
void lp_end () ;
void lp_delete () ;

dword chunk_write (byte instruction, dword param, byte size) ;
dword chunk_write_ptr (byte instruction, void * param, byte size) ;
dword chunk_get () ;
void chunk_writeat (dword at, dword param, byte size) ;

void compile () ;

extern FILE * yyout ;

#define YYSTYPE TCARG 