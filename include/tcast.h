
// rules about tetra_to_string:
/*
 char *TSTRING *, buffer[16] ; // buffers should always be at least 16 bytes!
 dword length ;
 TSTRING * = tetra_to_string (arg,buffer,&length) ;
 puts(TSTRING *) ;

 *** NOTES:
 -ALWAYS- use the RETURN value from tetra_to_string. if tetra
 finds that arg is already a string, it will return the string
 it already has instead of copying it again.

 dont use strlen on your new string, use the length parameter.
 most of the time this will allow you to work with binary data
 as well as ascii.

 if you pass 0 as buffer, tetra_to_string will use an internal
 buffer. you have to use your data before you call tetra_to_string
 again.

 *** /end notes

 IF YOU ABSOLUTELY -MUST- NEED THE STRING STRCPYED TO BUFFER NO MATTER
 WHAT, USE tetra_copy_string (copy always).

*/
char * to_string (TARG * arg, char * buffer, dword * length) ;

// for performance reasons, use tetra_to_string. this is only
// useful if you MUST have the data copyed in buffer. make sure
// you allocated enough! *returns string length*

// ** note: this calls tetra_to_string.
// ** #2 note: max_len and sizeof(buffer) must be >= 16!
dword tetra_copy_string (TARG * arg, char * buffer, dword max_len) ;
long tetra_to_number (TARG * arg, byte * exact) ;
double tetra_to_real (TARG * arg, byte * exact) ;
byte tetra_to_bool (TARG * arg) ;
void * tetra_to_resource (TARG * arg) ;
