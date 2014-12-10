/************************************************************************

 objetos, fichero de cabecera

*************************************************************************/


#ifndef _OBJ
typedef int TCODIGO;

typedef struct TOBJETO       // tipo de datos OBJETO
	   {
	    TCODIGO codigo;
	    char nombre[21];
	    char tipo;       // 0,1,2
	    char imagen[13];
	    int modif[5];     // modificadores de atributos
	   } TOBJETO;
#define _OBJ
#endif



/*********************************************
  CargaObjeto

  TIPO: TOBJETO.
  PARµMETROS DE ENTRADA:el c¢digo del objeto a leer (cod)
  êsta funci¢n abre y procesa el fichero de objetos hasta que encuentra
  el objeto pedido, y lo devuelve.

*********************************************/

TOBJETO CargaObjeto (TCODIGO cod);

