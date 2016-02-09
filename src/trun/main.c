
#include <tetra.h>
#include <windows.h>

int main(int argc, char **argv)
{
 struct tprogram * program ;
 LARGE_INTEGER freq, time1, time2 ;
 double dfreq, dtime ;
 char * boo ;

 if (!QueryPerformanceFrequency(&freq))
 {
  puts("Your hardware doesn't support high-resolution timers...");
  return 1;
 }
 
 boo = argv[1] ;

 dfreq = (double) freq.QuadPart ;

 

 program = tetra_load(boo) ;
 if (program == TL_FILE_NOT_FOUND)
  puts("file not found");
 else if (program == TL_FILE_NOT_TETRA)
  puts("file not tetra");
 else if (program == TL_MEMORY)
  puts("memory error");
 else if (program == TL_INVALID_FILE)
  puts ("invalid/corrupted tetra file") ;
 else 
 {
  tetra_com_install(program,INSTALL_ALL) ;
  QueryPerformanceCounter(&time1);
  tetra_start(program) ;
 QueryPerformanceCounter(&time2);
  tetra_unload(program) ;
 }

 dtime = (double) (time2.QuadPart-time1.QuadPart) ;

 printf("\nTime taken: about %f seconds\n", dtime/dfreq);
}