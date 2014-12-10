/************************************************************************

 ficheros de partidas grabadas

*************************************************************************/


#include "files.h"


/**************************************************************

        Nombre: ActualizaSaved
        Tipo: void
        Par metros de entrada: array de elementos INFO
        Descripcion: graba el array en el archivo saved.dat

**************************************************************/


void ActualizaSaved (INFO temp[15])
{
 FILE *fich; // fichero a grabar

 fich = fopen ("saved.dat","wb");
 fwrite (temp,sizeof(INFO),15,fich);
 fclose (fich);

 return;
}


/**************************************************************

        Nombre: CargaSaved
        Tipo: void
        Par metros de entrada: array de elementos INFO
        Descripcion: carga en el array el archivo saved.dat

**************************************************************/


void CargaSaved (INFO temp[15])
{
 FILE *fich;

 fich = fopen ("saved.dat","rb");
 fread (temp,sizeof(INFO),15,fich);
 fclose (fich);

 return;
}
