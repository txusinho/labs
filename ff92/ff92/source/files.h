/************************************************************************

 ficheros de partidas grabadas, fichero de cabecera

*************************************************************************/


#include <stdio.h>

#ifndef _INFO

        typedef struct // Registro de informaci¢n para partidas grabadas
                {
                 int codActual,x,y;
                 char nPlayer[21], nSala[21], fPlayer[13], fPantalla[13];
                } INFO;

        #define _INFO
#endif


/**************************************************************

        Nombre: ActualizaSaved
        Tipo: void
        Par metros de entrada: array de elementos INFO
        Descripci¢n: graba el array en el archivo saved.dat

**************************************************************/

void ActualizaSaved (INFO temp[15]);


/**************************************************************

        Nombre: CargaSaved
        Tipo: void
        Par metros de entrada: array de elementos INFO
        Descripci¢n: carga en el array el archivo saved.dat

**************************************************************/

void CargaSaved (INFO temp[15]);
