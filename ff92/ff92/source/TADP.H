/************************************************************************

 personajes, fichero de cabecera

*************************************************************************/


#include <stdio.h>

#ifndef _TPER
        typedef struct TPERSONAJE   // Tipo de datos personaje
                {
                 char nombre[21];
                 char fot[13];
                 int objetos[20];
                 int carac[5];// 1 = fuerza  || 2 = resistencia 3= velocidad
                             // 4 = hp      || 5 = MaxHp
                 int nivel,exp;
                } TPERSONAJE;

        #define _TPER
#endif


/**************************************************
  CargaPlayer

  TIPO: TPERSONAJE
  PARµMETROS DE ENTRADA:un puntero al nombre del fichero fuente.
  êsta funci¢n carga temp con el contenido del fichero especificado.
***************************************************/

TPERSONAJE CargaPlayer (char *nombreFichero);



/******************************************************************
  GrabaPlayer

  TIPO: void
  PARµMETROS DE ENTRADA: nombre del personaje que se va a grabar (aGrabar),
             nombre del fichero en el que se va a grabar (nombreFich).
  Esta funci¢n graba en el fichero que corresponda (nombreFich) el personaje
  a grabar
*******************************************************************/

void GrabaPlayer (TPERSONAJE aGrabar, char *nombreFichero);
