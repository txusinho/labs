/************************************************************************

 colisiones

*************************************************************************/


#include "mapacol.h"

#include <string.h>

/**************************************************************

        Nombre: RellenaMapa
        Tipo: void
        Parametros de entrada: mapa de colisiones, coordenadas de inicio y
                               final del espacio a rellenar del mapa y
                               codigo con el que rellenar ese espacio
        Descripcion: Modifica el mapa de colisiones, rellenando el espacio
                     especificado por las corrdenas con el codigo dado en n.

**************************************************************/

void RellenaMapa (char mapaColisiones[640][380],int x1,int y1,int x2,int y2,
                  int n)
{
 int tx,ty;

 for (tx = x1 ;tx<=x2;tx++)
      for (ty = y1;ty<=y2;ty++)
          mapaColisiones[tx][ty]=n; //Asignamos el codigo a la posicion

 return;
}

/**************************************************************

        Nombre: RellenaPuertas
        Tipo: void
        Parametros de entrada: array con las puertas de la sala. Mapa de
                               colisiones.
        Descripcion: actualiza el mapa de colisiones con los codigos respectivos
                     a las puertas que aparecen en la sala.

                     Codigos: 101, 102, 103, 104

**************************************************************/

void  RellenaPuertas(int *enlaces, char mapaColisiones[640][380])
{
 if (enlaces[0]) RellenaMapa (mapaColisiones,250,0,389,9,101);     // N
 if (enlaces[1]) RellenaMapa (mapaColisiones,629,150,639,229,102); // E
 if (enlaces[2]) RellenaMapa (mapaColisiones,250,369,389,379,103); // S
 if (enlaces[3]) RellenaMapa (mapaColisiones,0,150,9,229,104);     // O

 return;
}


/**************************************************************

        Nombre: RellenaParedes
        Tipo: void
        Parametros de entrada: array con las paredes de la sala. Mapa de
                               colisiones
        Descripcion: actualiza el mapa de colisiones con los codigos de las
                     paredes de la sala.

                     Codigo: 100

**************************************************************/

void  RellenaParedes(int *pared, char mapaColisiones[640][380])
{
 if (pared[0]) RellenaMapa (mapaColisiones,250,0,389,9,100);
 if (pared[1]) RellenaMapa (mapaColisiones,390,0,639,9,100);
 if (pared[2]) RellenaMapa (mapaColisiones,629,0,639,149,100);
 if (pared[3]) RellenaMapa (mapaColisiones,629,150,639,229,100);
 if (pared[4]) RellenaMapa (mapaColisiones,629,230,639,379,100);
 if (pared[5]) RellenaMapa (mapaColisiones,390,369,639,379,100);
 if (pared[6]) RellenaMapa (mapaColisiones,250,369,389,379,100);
 if (pared[7]) RellenaMapa (mapaColisiones,0,369,249,379,100);
 if (pared[8]) RellenaMapa (mapaColisiones,0,230,9,379,100);
 if (pared[9]) RellenaMapa (mapaColisiones,0,150,9,229,100);
 if (pared[10]) RellenaMapa (mapaColisiones,0,0,9,149,100);
 if (pared[11]) RellenaMapa (mapaColisiones,0,0,249,9,100);

 return;
}


/**************************************************************

        Nombre: RellenaObjetos
        Tipo: void
        Parametros de entrada: codigos de los objetos. Coordenadas de los
                               objetos, mapa de colisiones, lista de objetos
        Descripcion: actualiza el mapa de colisiones con los codigos de los
                     objetos de la sala.

                     Codigo: X

**************************************************************/

void RellenaObjetos (TCODIGO *codigo,int coordenada[2][5],
                     char mapaColisiones[640][380], List objetos)
{
 char i = 0;    // Variable contador
 BITMAP *temp;  // Apuntador a imagen

 while (i<5)
 { // Mientras haya objetos, y no hallamos pasado del ultimo...
  if (codigo[i])
  {
   temp = RetrieveI (Find (codigo[i],objetos)); //...recuperamos la imagen...
        // Rellenamos el mapa segun las coordenadas del objeto y las dimen-
        // siones de su imagen, con su codigo...
   RellenaMapa (mapaColisiones,coordenada[0][i],coordenada[1][i],
               coordenada[0][i] + temp->w, coordenada[1][i] + temp->h,
               codigo[i]);
  }
  i++;
 }

 return;
}


/**************************************************************

        Nombre: RellenaPnj
        Tipo: void
        Parametros de entrada: Coordenadas del personaje no jugador, base
                               del nombre de sus fotogramas, mapa de
                               colisiones.
        Descripcion: actualiza el mapa de colisiones en la posicion que
                     ocupa el personaje no jugador de la sala.

                     Codigo: 105

**************************************************************/

void RellenaPnj (int *CoordPnj,char *ImagenPnj,char mapaColisiones[640][380])
{
 BITMAP *temp; // Apundator a BITMAP
 PALETTE pal;  // Paleta de colores
 char temp2[13]; // string temporal

 strcpy (temp2,ImagenPnj);                           // Cargamos uno de los
 temp = load_bitmap (strcat(temp2,"D0000.bmp"),pal); // fotogramas...

        // Rellenamos el mapa dependiendo de las dimensiones del PNJ...
 RellenaMapa (mapaColisiones,CoordPnj[0], CoordPnj[1],
              CoordPnj[0] + temp->w, CoordPnj[1] + temp->h,105);

 destroy_bitmap (temp); // Destruimos la imagen temporal

 return;
}


/**************************************************************

        Nombre: CreaMapaColisiones
        Tipo: void
        Parametros de entrada: sala, mapa de colisiones, lista de objetos
        Descripcion: Crea el mapa de colisiones de la sala especificada
                     para la lista de objetos que le pasamos.

**************************************************************/

void CreaMapaColisiones (TSALA sala,char mapaColisiones[640][380],List objetos)
{
 int x,y; //contadores

 for (x=0;x<=639;x++)            //  Inicializamos el mapa vacio
     for (y=0;y<=379;y++)
         mapaColisiones[x][y]=0;
                                // Rellenamos las diferentes partes.
 RellenaPuertas(sala.enlaces[0],mapaColisiones);
 RellenaParedes(sala.pared, mapaColisiones);
 RellenaObjetos(sala.codObjetosSala,sala.coordObjetos,mapaColisiones,objetos);
 if (strcmp (sala.pnj,"NO"))    // Si hay personaje no jugador, lo rellenamos.
    RellenaPnj (sala.coordenadasPnj,sala.imagenPnj,mapaColisiones);

 return;
}


/**************************************************************

        Nombre: Colision
        Tipo: char
        Parametros de entrada: mapa de colisiones, coordenadas iniciales y
                               finales.
        Descripcion: Devuelve el primer codigo distinto de cero presente en
                     el recinto especificado del mapa de colisiones, o cero
                     si no lo hay.

**************************************************************/

char Colision(char mapaColisiones[640][380], int x1, int y1,int x2, int y2)
{
 int i,j,cod;

 for (i=x1;i<=x2;i++)
     for (j=y1;j<=y2;j++)                // Recorremos el mapa
         if (cod = mapaColisiones[i][j]) return cod;

 return 0;  // Si no habia nada, devolvemos cero.
}

