
#include <tetra.h>

void init_genrand(unsigned long s) ;

byte tf_fopen (struct tetraprogram * program, byte arg_count, 
			   struct argument ** args, struct argument * retval);
byte tf_fread (struct tetraprogram * program, byte arg_count, 
			   struct argument ** args, struct argument * retval);
byte tf_fwrite (struct tetraprogram * program, byte arg_count, 
			   struct argument ** args, struct argument * retval);
byte tf_fclose (struct tetraprogram * program, byte arg_count, 
			   struct argument ** args, struct argument * retval);
byte tf_print (struct tetraprogram * program, byte arg_count, 
			   struct argument ** args, struct argument * retval);
byte tf_input (struct tetraprogram * program, byte arg_count,
			   struct argument ** args, struct argument * retval);
byte tf_rand  (struct tetraprogram * program, byte arg_count,
			   struct argument ** args, struct argument * retval);
byte tf_randf  (struct tetraprogram * program, byte arg_count,
			   struct argument ** args, struct argument * retval);
byte tf_srand (struct tetraprogram * program, byte arg_count,
			   struct argument ** args, struct argument * retval) ;
