

#include "tinternal.h"

void default_catch_handler (TPROGRAM * program, 
						   char * type,
						   char * msg,
						   byte level)
{
 printf("Exception %s raised, details: %s\n",type,msg) ;
}

DEBUGHANDLER set_catch_handler (TPROGRAM * program, 
						           DEBUGHANDLER handler)
{
 DEBUGHANDLER old_handler = program->debug_info.catch_handler ;
 if (handler) /* this allows you to call tetra_catch(program,0) to 
		   get the catch handler */
		   program->debug_info.catch_handler = handler ;
 return old_handler ;
}

byte throw_exception (TPROGRAM * program, 
						 char * type,
						 char * msg,
						 byte level) 
{
 program->debug_info.catch_handler (program,type,msg,level) ;
 return 0 ;
}