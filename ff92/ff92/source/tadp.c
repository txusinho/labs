/************************************************************************

 personajes

*************************************************************************/


#include "tadp.h"


/**************************************************
  CargaPlayer

  TIPO: TPERSONAJE
  PARµMETROS DE ENTRADA:un puntero al nombre del fichero fuente.
  êsta funci¢n carga temp con el contenido del fichero especificado.
***************************************************/

TPERSONAJE CargaPlayer (char *nombreFich)
{
 TPERSONAJE temp; //vble temporal para recoger los datos.
 FILE *fich;      //vble de tipo fichero.

 fich = fopen (nombreFich,"rb"); //Abrimos el fichero, que es de tipo binario.
 fread (&temp,sizeof(TPERSONAJE),1,fich);//recogemos en temp el valor le°do.
 fclose (fich);

 return temp;
}



/******************************************************************
  GrabaPlayer

  TIPO: void
  PARµMETROS DE ENTRADA: nombre del personaje que se va a grabar (aGrabar),
             nombre del fichero en el que se va a grabar (nombreFich).
  Esta funci¢n graba en el fichero que corresponda (nombreFich) el personaje
  a grabar
*******************************************************************/

void GrabaPlayer (TPERSONAJE aGrabar, char *nombreFich)
{
 FILE *fich; //vble tipo fichero en la que abrimos el archivo de dicho nombre

 fich = fopen (nombreFich,"wb"); //el fichero es de tipo binario
 fwrite (&aGrabar,sizeof(TPERSONAJE),1,fich);
 fclose (fich);

 return;
}
