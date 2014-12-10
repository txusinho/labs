/************************************************************************

 objetos

*************************************************************************/


#include <stdio.h>
#include "TadObjet.h"



/*********************************************
  CargaSiguiente

  TIPO: TOBJETO
  PARµMETROS DE ENTRADA: el puntero al fichero de objetos, apuntando
  siguiente registro a leer.
  êsta funci¢n recoge el fichero de Objetos y devuelve
  el objeto siguiente.

*********************************************/
static TOBJETO CargaSiguiente (FILE *fichObjetos)
{
 TOBJETO temp; //vble temporal para recoger datos
 unsigned char i; //vble contador

 fscanf (fichObjetos,"%d",&(temp.codigo));
 fscanf (fichObjetos,"%s",temp.nombre);
 fscanf (fichObjetos,"%d",&(temp.tipo));
 fscanf (fichObjetos,"%s",temp.imagen);
 for (i = 0; i <= 4; i ++)
     fscanf ( fichObjetos, "%d",&(temp.modif[i]));
 return temp;
}



/*********************************************
  CargaObjeto

  TIPO: TOBJETO.
  PARµMETROS DE ENTRADA:el c¢digo del objeto a leer (cod)
  êsta funci¢n abre y procesa el fichero de objetos hasta que encuentra
  el objeto pedido, y lo devuelve.

*********************************************/

TOBJETO CargaObjeto (TCODIGO cod)

{
 FILE *fichObjetos; //vble en la que vamos a abrir el fichero
 TOBJETO temp;      //vble temporal en la que vamos arecoger los datos
                    //le°dos
 fichObjetos = fopen ("objetos.ots","r");
 temp = CargaSiguiente(fichObjetos);

 while (temp.codigo != cod && (!(feof (fichObjetos))))
       temp = CargaSiguiente(fichObjetos);
  //por si se ha salido del bucle por encontrar el elemento buscado, cerramos
  //el fichero, en cambio si se ha hecho por fin de fichero, devolvemos 0
  //en el c¢digo del elemento, para indicar que se ha hecho mal la operaci¢n,
  //o se ha buscado un elemento inexistente.
 if (temp.codigo == cod)
 {
  fclose (fichObjetos);
  return temp;
 }
 else
 {
  fclose (fichObjetos);
  temp.codigo = 0;
  return temp;
 }
}
