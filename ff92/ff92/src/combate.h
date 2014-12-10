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
        Parametros de entrada: sala
        Descripcion: determina de manera aleatoria si ha de producirse un
                     combate. Devuelve cero o el codigo de un enemigo de la
                     sala.
************************************************************/

int HayCombate (TSALA sala);



/***********************************************************

        Nombre: Combate
        Tipo: void
        Parametros de entrada: sala en que se desarrolla el combate.
                   personaje. m, codigo del malo con el que luchar.
                   musicC, nombre del fichero con la musica para el combate.
                   doublebuffer, BITMAP.
        Descripcion: carga lo necesario para el combate, y llama a CombateEnSi

************************************************************/

void Combate (TSALA sala, TPERSONAJE *personaje,int m,char musicC[13],
              BITMAP *doublebuffer);



/***********************************************************

        Nombre: CombateFinal
        Tipo: void
        Parametros de entrada: personaje. m, codigo del malo con el que luchar.
                   doublebuffer, BITMAP. Codigo de la pantalla actual.
        Descripcion: carga lo necesario para el combate con el enemigo final
                     de pantalla, y llama a CombateEnSi

************************************************************/

void CombateFinal (TPERSONAJE *personaje,BITMAP *doublebuffer,int codActual);
