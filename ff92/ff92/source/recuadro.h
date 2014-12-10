/************************************************************************

 recuadros, archivo de cabecera

*************************************************************************/


#include "allegro.h"
#include "tadp.h"
#include "tadsala.h"
#include "files.h"



/***********************************************************

        Nombre: DibujaRecuadroC
        Tipo: void
        Par metros de entrada: doublebuffer, personaje, tiempo
        Descripcion: escribe en doublebuffer el tiempo restante y la vida
                     del personaje
************************************************************/

void DibujaRecuadroC (BITMAP *doublebuffer, TPERSONAJE personaje,int tiempo);



/***********************************************************

        Nombre: DibujaRecuadro
        Tipo: void
        Par metros de entrada: personaje, sala, doublebuffer
        Descripcion: dibuja en doublebuffer el cuadro inferior de la pantalla
                     durante el juego.
************************************************************/

void DibujaRecuadro (TPERSONAJE personaje, TSALA sala, BITMAP *doublebuffer,
                     BITMAP *foto);



/***********************************************************

        Nombre: DibujaRecuadorAtaque
        Tipo: void
        Par metros de entrada: doublebuffer, i
        Descripcion: dibuja el recuadro de seleccion de ataque
************************************************************/

void DibujaRecuadroAtaque (BITMAP *doublebuffer, int i);



/***********************************************************

        Nombre: DibujaRecuadroMove
        Tipo: void
        Par metros de entrada: doublebuffer, i
        Descripcion: dibuja el recuadro de seleccion de accion,
                     resaltando la opcion i.
************************************************************/

void DibujaRecuadroMove (BITMAP *doublebuffer, int i);



/***********************************************************

        Nombre: DibujaSlots
        Tipo: void
        Par metros de entrada: doublebuffer, k, j, array de partidas
                   grabadas
        Descripcion: dibuja en un recuadro el contenido de temp[k].
                     si k == j, lo har  en blanco, si no en gris.
************************************************************/

void DibujaSlots (BITMAP *doublebuffer,int k,int j,INFO temp[15]);
