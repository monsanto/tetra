
// bulkmemory preheader
typedef struct bulkmem
{
 byte item_size ;
 byte item_incr ;
 dword amount_used ;
 dword max_avail ;
} BULKMEM ;

#ifdef _WIN32
#include <pshpack1.h>
#endif
typedef struct tfileheader
{
 byte binary_byte ; // should be 0x01
 word signature ; // should be 'TE'
 byte versionmajor ;
 byte versionminor ;
 byte debug_enabled ;
 byte register_count ;
 word string_count ;
 word object_count ;
 word function_count ;
} TFILEHEADER ;
#ifdef _WIN32
#include <poppack.h>
#endif

typedef struct _TSTRING
{
 dword length ;
 byte ref ;
} TSTRING ; // string follows this..

typedef struct _TOBJECTDEF
{
 TSTRING * name ;
 TSTRING ** members ;
 byte member_count ;
} OBJECTDEF ;

typedef struct _TFUNCTION
{
 TSTRING * name ;
 byte type ;
 byte ref ;
} TFUNCTION ;

typedef struct _TTFUNCTION
{
 TFUNCTION header ;
 dword length ;
 byte arg_count ;
 TSTRING ** arguments ;
 // binary follows
} TTFUNCTION ;

typedef struct _TCFUNCTION
{
 TTFUNCTION header ;
 TARG * self ;
} TCFUNCTION ;

typedef struct _TNFUNCTION
{
 TFUNCTION header ;
 TNATIVEFUNCTION function ;
} TNFUNCTION ;

typedef struct _TRESOURCE
{
 void * function_id ;
 void * resource ;
 TCLEANUPFUNCTION cleanup_func ;
 byte ref ;
} TRESOURCE ;

typedef struct _TDEBUGINFO
{
 TSTRING * name ;
 dword position ; // line number on debug, position on not debug.
                  // always function address if !is_tetra
 TDEBUGHANDLER catch_handler ;
} TDEBUGINFO ;

typedef struct _TARG
{
 byte type ;
 byte ref  ; 
#ifndef NO_ARG_CHUNK
 TCHUNK * arg_chunk ;
#endif
 union 
 {
  long number ;
  TSTRING * string ;
  double real ;
  struct tresource * resource ;
//  TETRAOBJECT * object ;
 } ;
} TARG ;

typedef struct _TVARSTACK
{
 TSTRING *  name ;
 TARG * var ;
} TVARSTACK ;

typedef struct _TSTACK
{
 TARG ** arg_stack ; // b
 TVARSTACK * local_vars ; // b
} TSTACK ;

#ifndef TCONFIG_NO_CHUNK
typedef struct _TCHUNK
{
 TARG * chunk ;
 byte amount_avail ;
 byte first_avail ;
 TCHUNK * next ;
} TCHUNK ;
#endif

typedef TPROGRAM
{
 dword flags ;

 TARG ** registers ;
 byte register_count ;

 TSTRING ** strings ; // b
 TOBJECTDEF ** objects ; // b
 TFUNCTION ** functions ; // b
 TPROGRAM ** modules ; // b
 
 TSTACK * stacks ; // b
 TSTACK * current_stack ;

 TVARSTACK * global_vars ; // b

 TDEBUGINFO debug_info ;

#ifndef TCONFIG_NO_CHUNK
 TCHUNK arg_chunk_first ;
#endif
} TPROGRAM ;
