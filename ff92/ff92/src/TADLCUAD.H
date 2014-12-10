/************************************************************************

 listas cu druples - grafos. Fichero de cabecera

*************************************************************************/


#include <malloc.h>
#include <stdio.h>
#include "allegro.h"
#include "list.h"
#include "TadObjet.h"
#include "TadSala.h"

#ifndef _TLISTACUAD

typedef struct TNODOCUAD      // Tipo de datos lista cu druple - grafo
	   {
	    TSALA sala;       // sala
	    char control;     // campo de control
	    struct TNODOCUAD *n,*s,*e,*o; // enlaces
	   } TNODOCUAD;

typedef TNODOCUAD *TLISTACUAD;


typedef TNODOCUAD *TAPNODO;
#endif
#define _TLISTACUAD


/**************************************************************

        Nombre: CargaPantalla
        Tipo: TLISTACUAD
        Parametros de entrada: nombreFichero
        Descripcion: carga la pantalla contenida en el fichero
                     nombreFichero. Se vale de una lista auxiliar,
                     y devuelve la direccion de la primera sala,
                     que ser  la primera del fichero.

**************************************************************/

TLISTACUAD CargaPantalla (char nombreFichero[13]);


/**************************************************************

        Nombre: MoverASala
        Tipo: TAPNODO
        Parametros de entrada: pantalla, direc
        Descripcion: devuelve la direccion del nodo seleccionado
                     por el caracter direc. Devuelve la direccion
                     actual si no hay nodo.

**************************************************************/

TAPNODO MoverASala (TLISTACUAD pantalla,char direc);


/**************************************************************

        Nombre: DestruyePantalla
        Tipo: void
        Parametros de entrada: pantalla
        Descripcion: destruye la pantalla apuntada por el parametro
                     de entrada.

**************************************************************/

void DestruyePantalla (TLISTACUAD *pantalla);


/**************************************************************

        Nombre: GuardaPantalla
        Tipo: void
        Parametros de entrada: pantalla, nombreFichero
        Descripcion: abre nombreFichero para asi poder llamar
                     a GuardaPantallaRecursivo.

**************************************************************/

void GuardaPantalla (TLISTACUAD pantalla,char *fichPantalla);


/**************************************************************

        Nombre: PonerControlACero
        Tipo: void
        Parametros de entrada: pantalla
        Descripcion: pone a cero los campos de control de la pantalla.

**************************************************************/

void PonerControlACero(TLISTACUAD pantalla);


/**************************************************************

        Nombre: DameSalaRef
        Tipo: TSALA
        Parametros de entrada: pantalla
        Descripcion: devuelve la sala referenciada por pantalla

**************************************************************/

TSALA DameSalaRef (TLISTACUAD pantalla);


/**************************************************************

        Nombre: ActualizaSala
        Tipo: void
        Parametros de entrada: sala, pantalla
        Descripcion: actualiza la sala del nodo de entrada a la
                     pantalla, con la sala actual.

**************************************************************/

void ActualizaSala (TSALA sala,TLISTACUAD pantalla);
