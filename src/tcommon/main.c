
#include "tcommon.h"

EXPORT byte tetra_com_install (struct tprogram * program, dword mask)
{
 if (mask & INSTALL_SCREEN)
 {
  tetra_add_function(program,"print",tf_print) ;
  tetra_add_function(program,"input",tf_input) ;
 }
 if (mask & INSTALL_IO)
 {
  tetra_add_function(program,"fopen",tf_fopen) ;
  tetra_add_function(program,"fwrite",tf_fwrite) ;
  tetra_add_function(program,"fread",tf_fread) ;
  tetra_add_function(program,"fclose",tf_fclose) ;
 }
 if (mask & INSTALL_RAND)
 {
  init_genrand(time(0)) ;
  tetra_add_function(program,"rand",tf_rand) ;
  tetra_add_function(program,"randf",tf_randf) ;
  tetra_add_function(program,"srand",tf_srand) ;
 }
 return 1 ;
}