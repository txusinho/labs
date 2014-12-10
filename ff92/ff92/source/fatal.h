/************************************************************************

 cabecera que no sabemos qu‚ es, pero venia con las listas.
Lo unico que hace es definir unas macros.

*************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#define Error( Str )        FatalError( Str )
#define FatalError( Str )   fprintf( stderr, "%s\n", Str ), exit( 1 )
