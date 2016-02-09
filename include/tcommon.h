
#define INSTALL_SCREEN 0x01
#define INSTALL_IO     0x02
#define INSTALL_RAND   0x04
#define INSTALL_ALL    INSTALL_SCREEN|INSTALL_IO|INSTALL_RAND

EXPORT byte tetra_com_install (TPROGRAM * program, dword mask) ;
