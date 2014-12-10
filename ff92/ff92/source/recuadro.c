/************************************************************************

 recuadros

*************************************************************************/


#include "recuadro.h"



/***********************************************************

        Nombre: EscribeOpcion
        Tipo: void
        Par metros de entrada: doublebuffer, i
        Descripcion: escribe en doublebuffer la opcion i.
************************************************************/

void EscribeOpcion(BITMAP *doublebuffer, int i)
{
 switch (i)
 {
  case (1): textprintf (doublebuffer,font,80,424,215," <- Ataque base -> ");
            break;
  case (2): textprintf (doublebuffer,font,80,424,215,"   <- Curacion ->  ");
            break;
  case (3): textprintf (doublebuffer,font,80,424,215,"<- Ataque bestia ->");
            break;
  case (4): textprintf (doublebuffer,font,80,424,215,"    <- Rayo ->     ");
            break;
  case (5): textprintf (doublebuffer,font,80,424,215,"    <- Fuego ->    ");
            break;
  case (6): textprintf (doublebuffer,font,80,424,215,"   <- Bahamut ->   ");
            break;
 }

 return;
}



/***********************************************************

        Nombre: DibujaRecuadroC
        Tipo: void
        Par metros de entrada: doublebuffer, personaje, tiempo
        Descripcion: escribe en doublebuffer el tiempo restante y la vida
                     del personaje
************************************************************/

void DibujaRecuadroC (BITMAP *doublebuffer, TPERSONAJE personaje,int tiempo)
{
 rect (doublebuffer,0,381,639,479,215);
 rectfill (doublebuffer,1,382,638,478,10);
 textprintf (doublebuffer, font, 74,404,215, "%s",personaje.nombre);
 textprintf (doublebuffer, font, 500,404,215,"HP: %d/%d" ,
             personaje.carac[3], personaje.carac[4]);
 rectfill (doublebuffer, 500,424,602,446,86);
 rectfill (doublebuffer, 501,425,501+personaje.carac[3]*100/personaje.carac[4],
          445,69); //dibujamos en el rect ngulo de vida el tanto por ciento que
                   //tenemos sobre el total
 textprintf (doublebuffer,font,500,465,215,"%d",tiempo);

 return;
}



/***********************************************************

        Nombre: DibujaRecuadro
        Tipo: void
        Par metros de entrada: personaje, sala, doublebuffer
        Descripcion: dibuja en doublebuffer el cuadro inferior de la pantalla
                     durante el juego.
************************************************************/

void DibujaRecuadro (TPERSONAJE personaje, TSALA sala, BITMAP *doublebuffer,
                     BITMAP *foto)

{
 rect (doublebuffer,0,381,639,479,215);
 rectfill (doublebuffer,1,382,638,478,10);
 draw_sprite(doublebuffer, foto, 4,384);
 textprintf (doublebuffer, font, 74,404,215, "%s",personaje.nombre);
 textprintf (doublebuffer, font, 74,424,215, "%s",sala.nombre );
 textprintf (doublebuffer, font, 500,404,215,"HP: %d/%d" ,
             personaje.carac[3], personaje.carac[4]);

 rectfill (doublebuffer, 500,424,602,446,86);
 rectfill (doublebuffer, 501,425,501+personaje.carac[3]*100/personaje.carac[4],
          445,69); //dibujamos en el rect ngulo de vida el tanto por ciento que
                   //tenemos sobre el total

 return;
}



/***********************************************************

        Nombre: DibujaRecuadorAtaque
        Tipo: void
        Par metros de entrada: doublebuffer, i
        Descripcion: dibuja el recuadro de seleccion de ataque
************************************************************/

void DibujaRecuadroAtaque (BITMAP *doublebuffer,int i)
{
 rect (doublebuffer,0,381,639,479,215);
 rectfill (doublebuffer,1,382,638,478,10);
 EscribeOpcion (doublebuffer,i);

 return;
}



/***********************************************************

        Nombre: DibujaRecuadroMove
        Tipo: void
        Par metros de entrada: doublebuffer, i
        Descripcion: dibuja el recuadro de seleccion de accion,
                     resaltando la opcion i.
************************************************************/

void DibujaRecuadroMove (BITMAP *doublebuffer, int i)
{
 rect (doublebuffer,0,381,639,479,215);
 rectfill (doublebuffer,1,382,638,478,10);
 textprintf (doublebuffer,font,80,404,(i==0)?215:86,"Atacar");
 textprintf (doublebuffer,font,80,424,(i==1)?215:86,"Esperar");
 textprintf (doublebuffer,font,80,444,(i==2)?215:86,"Salir");

 return;
}



/***********************************************************

        Nombre: DibujaSlots
        Tipo: void
        Par metros de entrada: doublebuffer, k, j, array de partidas
                   grabadas
        Descripcion: dibuja en un recuadro el contenido de temp[k].
                     si k == j, lo har  en blanco, si no en gris.
************************************************************/

void DibujaSlots (BITMAP *doublebuffer,int k,int j,INFO temp[15])

{
 rect (doublebuffer,0,k*30+20,639,k*30+49,(k==j)?215:86);
 rectfill (doublebuffer,1,k*30+21,638,k*30+48,10);
 if (temp[k].codActual) // Si hay informacion la escribimos
    textprintf (doublebuffer,font,10,k*30+27,(k==j)?215:86,"%d %s %s",
                temp[k].codActual,temp[k].nPlayer,temp[k].nSala);
 else textprintf (doublebuffer,font,10,k*30+27,(k==j)?215:86,"VACIO");

 return;
}
