/************************************************************************

 salas

*************************************************************************/


#include <stdio.h>
#include "TadSala.h"




/***************************************************
  CargaSiguiente

  Funci¢n de tipo Tsala
  Par metros de entrada: el puntero al fichero de salas
  Descripci¢n
  Carga el siguiente registro del fichero de salas

***************************************************/


TSALA CargaSiguiente (FILE *fichSala)
{
 TSALA temp;
 int i,j; // vbles contadores
 char c;  //se utiliza para saber cuando ha llegado fin de lectura

 fscanf (fichSala,"%d",&(temp.codigo));
 fscanf (fichSala,"%s",temp.nombre);        //s¡mplemente vamos recogiendo
 fscanf (fichSala,"%s",temp.imagen);        //cada uno de los valores y meti‚n-
 for (i=0;i<=11;i++)                        //dolos en su tipo, en la vble temp
     fscanf (fichSala,"%d",&(temp.pared[i]));
 for (i=0;i<=2;i++)
     for (j=0;j<=3;j++)
         fscanf (fichSala,"%d",&(temp.enlaces[i][j]));
 fscanf (fichSala,"%s",temp.pnj);
 if (strcmp (temp.pnj,"NO")) //dado que la marca de que no haya Personajes no
 {                           //jugadores (pnj) es NO, miramos para dar m s
    fscanf (fichSala,"%d",&(temp.coordenadasPnj[0])); //caracter¡sticas suyas
    fscanf (fichSala,"%d",&(temp.coordenadasPnj[1]));
    fscanf (fichSala,"%s",temp.imagenPnj);
    fscanf (fichSala,"%s",temp.dialogo[0]);
    fscanf (fichSala,"%s",temp.dialogo[1]);
    fscanf (fichSala,"%d",&(temp.objetoSiHablamos));
    fscanf (fichSala,"%d",&(temp.hablado));
 }
 for (i=0;i<=4;i++)
     fscanf (fichSala,"%d",&(temp.codObjetosSala[i]));
 for (i=0;i<=4;i++)
     for (j=0;j<=1;j++)
         fscanf(fichSala,"%d",&(temp.coordObjetos[j][i]));
 fscanf (fichSala,"%s",temp.fondoCombate);
 if (strcmp (temp.fondoCombate,"NO")) //en cambio este otro sirve para ver
    for (i=0;i<=4;i++)                //si hay combates en la sala
        fscanf (fichSala,"%d",&(temp.codMalos[i]));
 do
  c = fgetc (fichSala);
 while (!feof (fichSala) && c == '\n'); //seguimos leyendo hasta encontrar
 return temp;                           //un caracter que no sea un cambio de
                                        //linea, para situarnos al comienzo
                                        //de la siguiente sala (razon por la
                                        //que los codigos de sala han de
                                        //empezar por cero en el fichero, para
                                        //no leer un dato incorrecto), o hasta
                                        //que lleguemos al final del fichero.
}



/***************************************************
  GrabaSiguiente

  La funci¢n es de TIPO entero.
  PARµMETROS: el fichero de salida (*.zkt) y la sala que se va a grabar.
  Descripci¢n:
  Graba la sala siguiente en el archivo de salida, teniendo en cuenta las
  consideraciones anteriores, tales como el NO para pnjïs como para combates.
  Devuelve 0 en caso de que la operaci¢n se realice con ‚xito

***************************************************/

int GrabaSiguiente (FILE *fichSala, TSALA sala)
{
 int i,j;  //vbles contadores

 fprintf (fichSala,"0%d\n",sala.codigo); //le concatenamos el 0 porque todas empiezan
 fprintf (fichSala,"%s\n",sala.nombre);  // con el 0.
 fprintf (fichSala,"%s\n",sala.imagen);
 for (i=0;i<=11;i++)
 {
     fprintf (fichSala,"%d",sala.pared[i]); // Grabamos las paredes
     if ( i != 11 ) fprintf (fichSala," ");
     else fprintf (fichSala,"\n");
 }
 for (i=0;i<=2;i++)
     for (j=0;j<=3;j++)
     {
         fprintf (fichSala,"%d",sala.enlaces[i][j]);
         if ( j != 3 ) fprintf (fichSala," "); // Grabamos las salas.
         else fprintf (fichSala,"\n");
     }
 fprintf (fichSala,"%s\n",sala.pnj);
 if (strcmp(sala.pnj,"NO"))  //strcmp devuelve 1 si son diferentes
 {
    fprintf (fichSala,"%d ",sala.coordenadasPnj[0]);
    fprintf (fichSala,"%d\n",sala.coordenadasPnj[1]);
    fprintf (fichSala,"%s\n",sala.imagenPnj);
    fprintf (fichSala,"%s\n",sala.dialogo[0]);
    fprintf (fichSala,"%s\n",sala.dialogo[1]);
    fprintf (fichSala,"%d\n",sala.objetoSiHablamos);
    fprintf (fichSala,"%d\n",sala.hablado);
 }
 for (i=0;i<=4;i++)
 {
     fprintf (fichSala,"%d",sala.codObjetosSala[i]);
     if ( i != 4 ) fprintf (fichSala," ");
     else fprintf (fichSala,"\n");
 }
 for (i=0;i<=4;i++)
     for (j=0;j<=1;j++)
     {
         fprintf(fichSala,"%d",sala.coordObjetos[j][i]);
         if (i == 4 && j == 1 ) fprintf (fichSala,"\n");
         else fprintf (fichSala," ");
     }
 fprintf (fichSala,"%s\n",sala.fondoCombate);
 if (strcmp (sala.fondoCombate,"NO"))
    for (i=0;i<=4;i++)
    {
        fprintf (fichSala,"%d",sala.codMalos[i]);
        if (i != 4) fprintf (fichSala," ");
        else fprintf (fichSala,"\n");
    }
 fprintf (fichSala,"\n"); //introducimos al final de la sala un INTRO, para
 return 0;                //hacer el fichero mas legible
}
