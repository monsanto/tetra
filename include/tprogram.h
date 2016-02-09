
#define PF_DEBUG_ENABLED 1

// for no registers, just put 0 for register_count.

// there is no PF_STRINGS. why? you need the string table for all other
// module functions...

#define PF_OBJECTS 2
#define PF_FUNCTIONS 4
#define PF_NATIVE_FUNCTIONS 8
#define PF_STACKS 16

// does not include debug_enabled...
#define PF_ALL (PF_OBJECTS | PF_FUNCTIONS | PF_NATIVE_FUNCTIONS | PF_STACKS)

TPROGRAM * new_program (dword flags,
                              byte register_count,
							  dword string_count,
							  dword object_count,
							  dword function_count,
							  dword native_function_count) ;

void free_program (TPROGRAM * program) ;

#define LP_FILE_NOT_FOUND   (TPROGRAM*) 0
#define LP_FILE_NOT_TETRA   (TPROGRAM*) -1
#define LP_INVALID_FILE     (TPROGRAM*) -2
#define LP_MEMORY           (TPROGRAM*) -3

#define LPF_NO_SIGNATURE 1

TPROGRAM * load_program (char * name)  ;
TPROGRAM * load_program_from_file (FILE * file, dword flags) ;
