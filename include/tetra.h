
#ifndef TETRA_H_INCLUDED
#define TETRA_H_INCLUDED

// tetra.h - THE definition for .t files

/*
 Format

 + Header
  - 0x01 (1 byte)
  - 'TE'(2 bytes)
  - Version Major (1 byte)
  - Version Minor (1 byte)
  - Contains debug information (1 byte) 
  - # of strings (2 bytes)
  - # of structures (2 bytes)
  - # of functions (2 bytes)
 + String Pool
  - Length of string (1 byte)
  - String (varying length)
 + Dependencies
  - 
 + Objects
  - String index (2 bytes)
  - # of fields (1 byte)
  + Members
   - String index (2 bytes)
 + Functions
  - String index (2 bytes)
  - # of args (1 byte)
  + Members
   - String index (2 bytes)
  - Length of chunk (4 bytes)
  - Chunk (varying length)
*/

// you need these for pretty much everything anyway...
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#define TAPI __stdcall
#else
#define TAPI
#endif

#include <tconfig.h> // Tetra build configuration
#include <tinst.h> // Tetra bytecode instructions 

#include <tdef.h> // Tetra structure definitions

#include <tprogram.h> // Base functions and macros
#include <tthread.h> // Threading functions and macros

#include <targ.h> // Scalar/targ functions and macros
#include <tstring.h> // String functions and macros
#include <tresource.h> // Resources functions and macros
#include <tarray.h> // Array functions and macros
#include <tobject.h> // Object functions and macros

//#include <toperators.h> // Functions which use arguments
//#include <tcast.h> // Converts arguments to C primitives

#include <tmacro.h> // General macros.

/*

EXPORT TPROGRAM * tetra_load (char * filename) ;

#define TL_FILE_NOT_FOUND   (TPROGRAM*) 0
#define TL_FILE_NOT_TETRA   (TPROGRAM*) -1
#define TL_MEMORY           (TPROGRAM*) -2
#define TL_INVALID_FILE     (TPROGRAM*) -3

// only use this if you are defining your own file format...
// otherwise use tetra_load
EXPORT TPROGRAM * tetra_new_program (byte debug_enabled,
										 byte register_count,
										 word string_count,
										 word object_count,
										 word function_count) ;

// reset all variables/etc without freeing program.
// good if you want to use a program several times
// w/o the overhead of tetra_load
EXPORT void tetra_reset (TPROGRAM * program) ;

EXPORT void tetra_unload (TPROGRAM * program) ;
EXPORT byte tetra_valid_index (TPROGRAM * program, word index) ;

EXPORT byte tetra_add_function (TPROGRAM * program,
										   char * name,
										   TETRAFUNC func) ;

EXPORT byte tetra_call (TPROGRAM * program, 
						char * name,
						byte arg_count,
						TARG ** args,
						TARG * retval) ;

#define TS_START 0
#define TS_CURRENT 1
#define TS_RETRIEVE 2
EXPORT dword tetra_seek (TPROGRAM * program, dword position, byte how) ;

#define TC_NOSUCH 0
#define TC_RETURN 1
#define TC_EXIT    2 // success, but exit application
#define TC_ARG_COUNT_WRONG 3
#define TC_MEMORY 4
#define TC_STACK_UNDERFLOW 5
#define TC_STACK_OVERFLOW 6 // reserved constant.. not in use currently

#define TE_RETURN 1
#define TE_EXIT    2 // success, but exit application...
#define TE_INVALID_INSTRUCTION 3
#define TE_ERROR 4

typedef void (*TETRACATCHFUNC) (TPROGRAM * program, char * type, char * msg, byte level) ;

EXPORT TETRACATCHFUNC tetra_catch (TPROGRAM * program, 
						 TETRACATCHFUNC func) ;
EXPORT byte tetra_throw (TPROGRAM * program, 
						 char * type,
						 char * msg,
						 byte level) ;
#define LEVEL_WARNING 0
#define LEVEL_ERROR   1
#define LEVEL_FATAL   2

#include "tops.h"
#include "targ.h"
#include "tcast.h"
#include "tutil.h"
#include "tmacro.h"
*/

// unless you know what you are doing.. don't mess with these :/
/*
// you can get current location by doing tetra_seek(program,0)
dword tetra_seek (TPROGRAM * program, dword pos) ; 

// almost all of the tetra_debug_* functions 
// return 1 if program has debugging information and 0 if they dont

// notes about this function:

 tetra_debug_set_lowlevel enables debugging on a low level (for tetra anyway..) 
 which means: 
 tetra_debug_break and tetra_debug_resume will work on bytecode commands,
 not lines.

 if you use tetra_debug_set_walker, your walker function will be called
 every time a new command comes up in the byte code.. (alot of times..)

 tetra_debug_get_info acts as if there was no debugging enabled in lowlevel.

 one last note, all the functions that would return 1 for debug on will return
 2 for lowlevel.

byte tetra_debug_set_lowlevel (TPROGRAM * program, byte on) ; 
byte tetra_debug_enabled (TPROGRAM * program) ;
byte tetra_debug_break (TPROGRAM * program) ; 
byte tetra_debug_resume (TPROGRAM * program) ;
byte tetra_debug_set_walker (TPROGRAM * program, TETRAWALKER walker) ;
TETRAWALKER tetra_debug_get_walker (TPROGRAM * program) ;

// this returns a pointer to the tdi tetra is currently using...
TETRADEBUGINFO * tetra_debug_get_info (TPROGRAM * program) ;

// you should only use tetra_add_function on the base TPROGRAM ...


inline TPROGRAM * tetra_call_thread (TPROGRAM * program,
										  char * name,
										  byte arg_count,
										  TARG ** args,
										  TARG * retval) 
{
 return tetra_call_thread_from_struct (program, 
  tetra_function_from_name(program,name), arg_count, args, retval) ;
}

TPROGRAM * tetra_call_thread_from_struct (TPROGRAM * program,
										  ttfunction * function,
										  byte arg_count,
										  TARG ** args,
										  TARG * retval) ;

TPROGRAM * tetra_get_thread_parent (TPROGRAM * thread) ;
TPROGRAM * tetra_get_thread_base (TPROGRAM * thread) ;
byte tetra_is_thread (TPROGRAM * program) ;

// don't use this for terminating base programs!
// threads and base programs allocate different memory.
byte tetra_terminate (TPROGRAM * thread) ;
*/
#endif 