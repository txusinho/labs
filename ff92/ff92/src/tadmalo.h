/************************************************************************

 enemigos, fichero de cabecera

*************************************************************************/


#include <stdio.h>

#ifndef _malo

typedef struct        // Tipo de dato: Magia
        {
         int tiene;
         char fot[13];
         int tiempo;
        }TMAGIA;

typedef struct       // Tipo de dato: enemigo
        {
         int codigo;
         char nombre[21];
         char fotogramas[4];
         int carac[5];
         TMAGIA magias[6];
        }TMALO;

#define _malo
#endif


/**************************************************************

        Nombre: CargaMalo
        Tipo: TMALO
        Parametros de entrada: codigo
        Descripcion: mediante llamadas a CargaMaloSiguiente, devuelve
                     el enemigo del codigo solicitado.

**************************************************************/

TMALO CargaMalo(int codigo);


