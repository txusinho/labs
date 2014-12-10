/************************************************************************

 listas, fichero de cabecera

*************************************************************************/


/* TAD SACADO DE INTERNET, hemos hecho algunas modificaciones,
   ya que algunas funciones estaban mal implementadas, y hemos
   configurado el tipo de datos ElementType como TOBJETO.
   As� mismo, en cada nodo, aparte del objeto, tenemos la
   imagen de este. Debido a esto, nosotros hemos implementado
   la funci�n RetrieveI, que no presenta complicaci�n alguna.*/


#include "tadObjet.h"
#include "allegro.h"

/* START: fig3_6.txt */
   #ifndef _List_H
	   #ifndef _List

	   typedef TOBJETO ElementType;   // Elemento de la lista

	   typedef struct Node
	   {                              // Nodo de la lista:
		  ElementType Element;    // Objeto
                  BITMAP *imagen;         // Im�gen
		  struct Node *Next;      // Puntero al siguiente
	   }Node;

	   typedef Node *PtrToNode;

	   typedef PtrToNode List;        // Tipo Lista

	   typedef PtrToNode Position;



/*******************************************************************

                FUNCIONES YA IMPLEMENTADAS

********************************************************************/


	   List MakeEmpty( List L );
	   int IsEmpty( List L );
	   int IsLast( Position P, List L );
	   Position Find( TCODIGO X, List L );
	   void Delete( TCODIGO X, List L );
	   Position FindPrevious( TCODIGO X, List L );
	   void Insert( ElementType X,BITMAP *image, List L, Position P );
	   void DeleteList( List *L );
	   Position Header( List L );
	   Position First( List L );
	   Position Advance( Position P );
	   ElementType RetrieveE( Position P );


/*****************************************************************

                FUNCIONES IMPLEMENTADAS POR NOSOTROS

******************************************************************/



/*****************************************************************

        Nombre: RetrieveI
        Tipo: Puntero a imagen
        Par�metros de entrada: puntero a nodo
        Descripci�n: Devuelve la direcci�n de la imagen contenida en
                     el nodo cuya direcci�n es P.
        Restricciones: P debe de apuntar a un nodo que contenga un
                       apuntador a una imagen creada de tipo BITMAP.

******************************************************************/

	   BITMAP *RetrieveI (Position P);


/*****************************************************************

        Nombre: CargaFicheroObjetos
        Tipo: Lista
        Par�metros de entrada: nada
        Descripci�n: carga el contenido del fichero objetos.ots en
                     una lista en memoria, junto con sus respectivas
                     im�genes.
        Restricciones: el fichero objetos.ots ha de existir y ser
                       correcto.

******************************************************************/

	   List CargaFicheroObjetos();


           #define _List
	   #endif
   #endif    /* _List_H */
/* END */
