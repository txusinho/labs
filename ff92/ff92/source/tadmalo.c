/************************************************************************

 enemigos

*************************************************************************/


#include "tadmalo.h"


/**************************************************************

        Nombre: CargaMaloSiguiente
        Tipo: TMALO
        Parametros de entrada: fichMalos
        Descripcion: lee el siguiente enemigo del fichero.
                     El fichero ha de ser correcto.

**************************************************************/

TMALO CargaMaloSiguiente ( FILE *fichMalos )
{
 TMALO temp;
 int i;

 fscanf (fichMalos, "%d",&temp.codigo);
 fscanf (fichMalos, "%s",temp.nombre);
 fscanf (fichMalos, "%s",temp.fotogramas);       // Leemos los diversos
 for (i=0;i<=4;i++)                              // campos del fichero
     fscanf (fichMalos,"%d", &(temp.carac[i]));  // de texto de la
 for (i=0;i<=5;i++)                              // estructura adecuada
 {
  fscanf (fichMalos,"%d", &(temp.magias[i].tiene));
  if (temp.magias[i].tiene)
  {
   fscanf (fichMalos,"%s", temp.magias[i].fot);
   fscanf (fichMalos,"%d", &(temp.magias[i].tiempo));
  }
 }
 return temp;
}


/**************************************************************

        Nombre: CargaMalo
        Tipo: TMALO
        Parametros de entrada: codigo
        Descripcion: mediante llamadas a CargaMaloSiguiente, devuelve
                     el enemigo del codigo solicitado.

**************************************************************/

TMALO CargaMalo ( int codigo )
{
 FILE *fichMalos;
 TMALO temp;

 fichMalos = fopen("malos.psj","r"); // Abrimos el fichero
 temp = CargaMaloSiguiente (fichMalos); // leemos hasta encontrarlo.
 while (temp.codigo != codigo)
       temp = CargaMaloSiguiente(fichMalos);
 fclose (fichMalos);

 return temp;
}
