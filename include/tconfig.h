
// ARG_CHUNK_SIZE 
/*
 This is a constant which reflects how much tetra will allocate 
 for each chunk. Specfically, the higher this value is...

 Less calls to tmalloc and tfree.
 More time spent searching for new values in chunks.
 More time spent initalizing memory.
 More memory allocated on arg chunks, HOWEVER, less total chunks.
 Less time is spent looping through chunks.
 Less memory is allocated on chunk indexing.

 On the other hand, the less this value is...

 More calls to tmalloc and tfree.
 Less time spent searching for new values in chunks.
 Less time spent initalizing memory.
 Less memory allocated on arg chunks, HOWEVER, more total chunks.
 More time is spent looping through chunks.
 More memory is allocated on chunk indexing.

 You'll want to find a mix between both for optimal performance.
 -----------------
 You can turn off chunks by defining NO_ARG_CHUNK, however this will
 call tmalloc and tfree on EVERY tetra_arg and tetra_free_arg call.
 This uses less memory total, but it may fragment memory in long
 programs.
 -----------------

 * Using chunks adds 5 bytes (32bit systems) or 9 bytes (64bit systems) to
 every targ.

 * ARG_CHUNK_SIZE CANNOT BE MORE THAN 255.
 * SHOULDNT BE LESS THAN 2, THIS PROVIDES NO ADVANTAGE OVER NON-CHUNKING
   AND ACTUALLY HURTS PERFORMANCE.
*/

//#define NO_ARG_CHUNK 
#define ARG_CHUNK_SIZE 16

#if ARG_CHUNK_SIZE > 255 || ARG_CHUNK_SIZE < 2
#error ARG_CHUNK_SIZE HAS TO BE <= 255 && >= 2.
#endif

// * Note: The *_INCR constants do not have the same benefits/losses
// as ARG_CHUNK_SIZE! These use bulk* while the others use a special
// tmalloc system so memory pointers arent changed.

// This defines how many strings have to be allocated
// before tetra allocates more memory.
// Havent figured out a way to pool the actual strings...
#define STRING_INCR 4

// How many objects before reallocation...
#define OBJECT_INCR 4

// How many functions before reallocation...
#define FUNCTION_INCR 4

// This defines how many nested functions have to be called 
// before tetra allocates more memory.
#define FUNCTION_STACK_INCR 4

// This defines how many variables have to be made
// before tetra allocates more memory.

// Variables ALWAYS malloc unless the var name is in the string pool.
// (it almost always is.)

// Global variables and local variables do not share the same count;
// they DO share the same INCR amount though.
#define VAR_INCR 8

// This defines how many arguments have to be nested
// before tetra allocates more memory...
#define ARG_STACK_INCR 4