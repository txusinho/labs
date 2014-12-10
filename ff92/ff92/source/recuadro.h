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
        Descripci¢n: escribe en doublebuffer el tiempo restante y la vida
                     del personaje
************************************************************/

void DibujaRecuadroC (BITMAP *doublebuffer, TPERSONAJE personaje,int tiempo);



/***********************************************************

        Nombre: DibujaRecuadro
        Tipo: void
        Par metros de entrada: personaje, sala, doublebuffer
        Descripci¢n: dibuja en doublebuffer el cuadro inferior de la pantalla
                     durante el juego.
************************************************************/

void DibujaRecuadro (TPERSONAJE personaje, TSALA sala, BITMAP *doublebuffer,
                     BITMAP *foto);



/***********************************************************

        Nombre: DibujaRecuadorAtaque
        Tipo: void
        Par metros de entrada: doublebuffer, i
        Descripci¢n: dibuja el recuadro de selecci¢n de ataque
************************************************************/

void DibujaRecuadroAtaque (BITMAP *doublebuffer, int i);



/***********************************************************

        Nombre: DibujaRecuadroMove
        Tipo: void
        Par metros de entrada: doublebuffer, i
        Descripci¢n: dibuja el recuadro de selecci¢n de acci¢n,
                     resaltando la opci¢n i.
************************************************************/

void DibujaRecuadroMove (BITMAP *doublebuffer, int i);



/***********************************************************

        Nombre: DibujaSlots
        Tipo: void
        Par metros de entrada: doublebuffer, k, j, array de partidas
                   grabadas
        Descripci¢n: dibuja en un recuadro el contenido de temp[k].
                     si k == j, lo har  en blanco, si no en gris.
************************************************************/

void DibujaSlots (BITMAP *doublebuffer,int k,int j,INFO temp[15]);
