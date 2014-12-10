/************************************************************************

 combates, archivo de cabecera

*************************************************************************/


#include "allegro.h"
#include "tadmalo.h"
#include "tadp.h"
#include "tadsala.h"
#include "videos.h"

#include <string.h>



/***********************************************************

        Nombre: HayCombate
        Tipo: entero
        Par metros de entrada: sala
        Descripci¢n: determina de manera aleatoria si ha de producirse un
                     combate. Devuelve cero o el c¢digo de un enemigo de la
                     sala.
************************************************************/

int HayCombate (TSALA sala);



/***********************************************************

        Nombre: Combate
        Tipo: void
        Par metros de entrada: sala en que se desarrolla el combate.
                   personaje. m, c¢digo del malo con el que luchar.
                   musicC, nombre del fichero con la m£sica para el combate.
                   doublebuffer, BITMAP.
        Descripci¢n: carga lo necesario para el combate, y llama a CombateEnSi

************************************************************/

void Combate (TSALA sala, TPERSONAJE *personaje,int m,char musicC[13],
              BITMAP *doublebuffer);



/***********************************************************

        Nombre: CombateFinal
        Tipo: void
        Par metros de entrada: personaje. m, c¢digo del malo con el que luchar.
                   doublebuffer, BITMAP. C¢digo de la pantalla actual.
        Descripci¢n: carga lo necesario para el combate con el enemigo final
                     de pantalla, y llama a CombateEnSi

************************************************************/

void CombateFinal (TPERSONAJE *personaje,BITMAP *doublebuffer,int codActual);
