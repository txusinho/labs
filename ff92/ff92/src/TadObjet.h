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
  PARAMETROS DE ENTRADA:el codigo del objeto a leer (cod)
  �sta funcion abre y procesa el fichero de objetos hasta que encuentra
  el objeto pedido, y lo devuelve.

*********************************************/

TOBJETO CargaObjeto (TCODIGO cod);

