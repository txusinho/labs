/************************************************************************

 cabecera que no sabemos qu‚ es, pero ven¡a con las listas.
Lo £nico que hace es definir unas macros.

*************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#define Error( Str )        FatalError( Str )
#define FatalError( Str )   fprintf( stderr, "%s\n", Str ), exit( 1 )
