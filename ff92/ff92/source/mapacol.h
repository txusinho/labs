/************************************************************************

 colisiones, fichero de cabecera

*************************************************************************/

#include "list.h"
#include "allegro.h"
#include "tadsala.h"


/**************************************************************

        Nombre: RellenaMapa
        Tipo: void
        Par metros de entrada: mapa de colisiones, coordenadas de inicio y
                               final del espacio a rellenar del mapa y
                               codigo con el que rellenar ese espacio
        Descripcion: Modifica el mapa de colisiones, rellenando el espacio
                     especificado por las corrdenas con el codigo dado en n.

**************************************************************/

void RellenaMapa (char mapaColisiones[640][380],int x1,int y1,int x2,int y2,
                  int n);



/**************************************************************

        Nombre: CreaMapaColisiones
        Tipo: void
        Par metros de entrada: sala, mapa de colisiones, lista de objetos
        Descripcion: Crea el mapa de colisiones de la sala especificada
                     para la lista de objetos que le pasamos.

**************************************************************/

void CreaMapaColisiones (TSALA sala,char mapaColisiones[640][380],List objetos);




/**************************************************************

        Nombre: Colision
        Tipo: char
        Par metros de entrada: mapa de colisiones, coordenadas iniciales y
                               finales.
        Descripcion: Devuelve el primer codigo distinto de cero presente en
                     el recinto especificado del mapa de colisiones, o cero
                     si no lo hay.

**************************************************************/

char Colision(char mapaColisiones[640][380], int x1, int y1,int x2, int y2);
