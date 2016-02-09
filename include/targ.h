
TARG * ta_new (TPROGRAM * program) ;

#define ta_init(arg) (arg)->ref++

void free_arg (TPROGRAM * program, TARG * arg);

#define new_arg_ref(arg) (arg)->ref++ 

void del_arg_ref (TPROGRAM * program, TARG * arg) ;

void FAST_copy_arg (TARG * arg, TARG * arg2) ;
void copy_arg (TARG * arg, TARG * arg2) ;

#define tnum_setF(arg, number) \
 (arg)->type = TYPE_NUMBER ; \
 (arg)->number = number

void tnum_setF (TARG * arg, int number)  ;

#define treal_setF(arg, real) \
 (arg)->type = TYPE_REAL; \
 (arg)->number = real

void treal_set (TARG * arg, double real)  ;

#define tsv_setF(arg, sv) \
 (arg)->type = TYPE_STRING; \
 (arg)->string = sv ; \
 FAST_new_string_ref (sv) 
/* even if this is the fast version, skipping over the ref count
is inexcuseable. increment ref count no matter what. */

void set_sv (TARG * arg, TSTRING * string) ;

byte FAST_set_string (TARG * arg,
				 char * string,
				 dword length) ;

byte set_string (TARG * arg,
				 char * string,
				 dword length)  ;

byte FAST_set_resource (TARG * arg,
				   void * function_id,
				   void * resource,
				   CLEANUPFUNCTION cleanup_func)  ;

byte set_resource (TARG * arg,
				   void * function_id,
				   void * resource,
				   CLEANUPFUNCTION cleanup_func) ;
