
#define TETRA_INTERNAL
#include <tetra.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include "bmem.h"

#ifdef _WIN32
#define alloca _alloca
#endif

#define IF_NOT_POP if (*binary != TPOP)
#define SKIP_POP *binary++
#define ELSE_SKIP_POP else SKIP_POP ;

/*
void _tetra_free_string (struct stringvalue * string) ;
void pop_string (struct stringvalue * string) ;
void _tetra_pop_resource (TETRARESOURCE * resource) ;
void _tetra_free_resource (TETRARESOURCE * resource) ;
TETRARESOURCE * _tetra_resource (void * resource,
								 TETRARESOURCEFUNC free_func) ;
byte _tetra_exec (TPROGRAM * program, byte * chunk, TARG * retval) ;
byte _tetra_push_stack (TPROGRAM * program) ;
byte _tetra_pop_stack (TPROGRAM * program) ;
byte _tetra_stack_set_args (TPROGRAM * program,
							ttfunction * function, 
							byte arg_count,
							TARG ** args) ;
byte _tetra_push (TPROGRAM * program, TARG * arg) ;
TARG * _tetra_pop (TPROGRAM * program) ;
struct stringvalue * _tetra_string (char * string, dword length);
struct stringvalue * _tetra_sp (TPROGRAM * program, char * string, dword length);
TARG * _tetra_get (TPROGRAM * program, char * name) ;
TARG * _tetra_arg (TPROGRAM * program) ;
void _tetra_default_catch (TPROGRAM * program, 
						   char * type,
						   char * msg,
						   byte level);
#define not_pop if (*program->chunk_ptr != TPOP) 
#define skip_pop *program->chunk_ptr++
#define else_skip_pop else skip_pop ;
void bulkinit (BULKALLOC * alloc, byte item_size, byte item_incr) ;
void * bulkadd (BULKALLOC * alloc);
void bulkdel (BULKALLOC * alloc) ;
void bulkinitto (BULKALLOC * alloc, dword how_many)  ;
#define bulkget(alloc,i) (((byte*)(alloc)->ptr)+i*(alloc)->item_size)
#define bulkgetlast(alloc) bulkget((alloc),((alloc)->amount_used-1))
*/
