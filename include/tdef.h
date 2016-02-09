
#define TA_NUMBER 0
#define TA_STRING 1
#define TA_REAL 2
#define TA_ARRAY 3
#define TA_OBJECT 4
#define TA_RESOURCE 5

#ifdef NO_ARG_CHUNK
#define TA_UNALLOC 255
#endif

#define TF_NATIVE 0
#define TF_TETRA 1

// Prototypes. Damned compilers. :/

// new primitives. please don't change these to uppercase!
typedef unsigned char byte ;
typedef unsigned short word ;
typedef unsigned long dword ;

#ifndef TDEFINE_STRUCT
#define TDEFINE_STRUCT(name) typedef struct _##name name
#endif

TDEFINE_STRUCT(TSTRING) ;
TDEFINE_STRUCT(TOBJECTDEF) ;
TDEFINE_STRUCT(TOBJECT) ;
TDEFINE_STRUCT(TARRAY) ;
TDEFINE_STRUCT(TFUNCTION) ;
TDEFINE_STRUCT(TRESOURCE) ;
TDEFINE_STRUCT(TARG) ;
TDEFINE_STRUCT(TPROGRAM) ;
TDEFINE_STRUCT(TDEBUGINFO) ;

typedef byte TAPI (*TCFUNCTION) (TPROGRAM *, byte, TARG **, TARG *) ;
typedef void TAPI (*TCLEANUPFUNCTION) (void *) ;
typedef void TAPI (*TDEBUGHANDLER) (TPROGRAM *, TDEBUGINFO *); 