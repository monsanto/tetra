
#include "tinternal.h"

byte load_standard_file (TPROGRAM * program, 
						 FILE * file,
						 word string_count, 
						 word object_count, 
						 word function_count)
{
 dword i, j ;

 for (i = 0; i < string_count; i++)
 {
  TSTRING * string ;
  byte length ;

  if (!fread(&length,1,1,file))
   return 0;

  string = reserve_string (program, length) ;

  if (!string)
   return (byte) -1 ;

  string[length] = 0 ;

  if (length)
  {
   if (!fread(string,length,1,file))
	return 0;
  }
 }

 /*for (i = 0, count = bcount(; i < program->object_pool_count; i++)
 {
 word index ;
 byte length ;
 struct stringvalue ** members ;

 if (!fread(&index,2,1,file))
 return 0;

 if (!tetra_valid_index(program,index))
 return 0;

 program->object_pool[i].name = program->string_pool[index] ;
 program->object_pool[i].name->ref++ ;

 if (!fread(&length,1,1,file))
 return 0;

 program->object_pool[i].length = length ;

 if (length)
 {
 members = (struct stringvalue**) malloc(length * sizeof(struct stringvalue**)) ;

 program->object_pool[i].members = members ;

 (*obj_alloc)++ ;

 if (!members)
 return (byte) -1 ;

 for (j = 0; j < length; j++)
 {
 if (!fread(&index,2,1,file))
 return 0;

 if (!tetra_valid_index(program,index))
 return 0;

 members[j] = program->string_pool[index];
 members[j]->ref++ ;
 }
 }
 }*/

 for (i = 0; i < function_count; i++)
 {
  word index ;
  TSTRING * * args, name ;
  byte arg_count, ** binary ;
  dword binary_length ;
  struct codeblock * code ;

  if (!fread(&index,2,1,file))
   return 0;

  name = find_string_from_index (program, index) ;

  if (!name)
   return 0 ;

  if (!fread(&arg_count,1,1,file))
   return 0 ;

  if (arg_count)
  {
   args = (TSTRING * *) malloc (arg_count * sizeof(TSTRING *)) ;

   if (!args)
	return (byte) -1 ;

   for (j = 0; j < arg_count; j++)
   {
	if (!fread(&index,2,1,file))
	 return 0;

	args[j] = find_string_from_index (program, index) ;

	if (!args[j])
	{
	 free (args) ;
	 return 0 ;
	}
   }
  }
  else
   args = 0 ;

  if (!fread(&binary_length,4,1,file))
   return 0;

  if (!binary_length)
  {
   if (args) 
	free (args);
   return 0 ;
  }

  code = new_codeblock (&binary, binary_length, arg_count, args) ;

  if (!code)
  {
   if (args)
	free (args) ;
   return (byte) -1;
  }

  if (!fread(*binary,binary_length,1,file))
  {
   free_codeblock(code) ;
   return 0;
  }

  if (!add_function (program, name, code))
  {
   free_codeblock (code) ;
   return (byte) -1;
  }
 }

 return 1 ;
}

TPROGRAM * load_program (char * name) 
{
 FILE * file ;
 TPROGRAM * program ;
 
#ifdef _WIN32
 file = fopen (name, "rbS") ; /*
							  Windows optimization hinting that 
							  we are reading in seq. order.
							  */
#else
 file = fopen (name, "rb") ;
#endif

 if (!file)
  return LP_FILE_NOT_FOUND ;

 program = load_program_from_file (file, 0) ;

 fclose (file) ;

 return program ;
}

TPROGRAM * load_program_from_file (FILE * file, dword flags)
{
 struct fileheader fh ;
 TPROGRAM * program ;
 dword pflags = PF_ALL ;

 byte ret ;

 if (flags & LPF_NO_SIGNATURE)
 {
  // i shouldnt do this, should i? cheap hack. fix later, k?
  if (!fread (((byte*)&fh)+3, sizeof(struct fileheader)-3, 1, file))
   return LP_FILE_NOT_TETRA ;
 }
 else
 {
  if (!fread (&fh, sizeof(struct fileheader), 1, file))
   return LP_FILE_NOT_TETRA ;

  if (fh.binary_byte != 1 || fh.signature != 'TE')
   return LP_FILE_NOT_TETRA ;
 }

 if (fh.debug_enabled)
  pflags |= PF_DEBUG_ENABLED ;

 program = new_program (pflags, fh.register_count,
  fh.string_count, fh.object_count, fh.function_count, 0) ;

 if (!program)
  return LP_MEMORY ;

 ret = load_standard_file (program, file, fh.string_count, 
  fh.object_count, fh.function_count) ;

 if (ret != 1)
 {
  free_program (program) ;

  if (!ret)
   return LP_INVALID_FILE;
  else
   return LP_MEMORY ;
 }

 return program ;
}