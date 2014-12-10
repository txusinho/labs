/************************************************************************

 salas, fichero de cabecera

*************************************************************************/


#include <stdio.h>
#include "TadObjet.h"

#ifndef _TSALA

typedef struct TSALA                // tipo de datos SALA
	   {
	    TCODIGO codigo;
	    char nombre[21];
	    char imagen[13];
	    int pared[12];
	    int enlaces[3][4];
	    char pnj[21];
	    int coordenadasPnj[2];
	    char imagenPnj[13];
	    char dialogo[2][13];    // ficheros de conversaci¢n
	    int hablado;
	    TCODIGO objetoSiHablamos;
	    TCODIGO codObjetosSala[5];
	    int coordObjetos[2][5];
            char fondoCombate[13];
            int codMalos[5];
	   } TSALA;
#endif
#define _TSALA



/***************************************************
  CargaSiguiente

  Funci¢n de tipo Tsala
  Par metros de entrada: el puntero al fichero de salas
  funci¢n:
  el siguiente registro del fichero de salas

***************************************************/

TSALA CargaSiguiente (FILE *fichSala);



/***************************************************
  GrabaSiguiente

  La funci¢n es de TIPO entero.
  PARµMETROS: el fichero de salida (*.zkt) y la sala que se va a grabar.
  Descripci¢n:
  Graba la sala siguiente en el archivo de salida, teniendo en cuenta las
  consideraciones anteriores, tales como el NO para pnjïs como para combates.
  Devuelve 0 en caso de que la operaci¢n se realice con ‚xito

***************************************************/

int GrabaSiguiente (FILE *fichSala, TSALA sala);

