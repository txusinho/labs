/************************************************************************

 listas

*************************************************************************/


        #include "list.h"
        #include <stdlib.h>
        #include "fatal.h"
        #include "TadObjet.h"
        #include "allegro.h"


/*******************************************************************

                FUNCIONES YA IMPLEMENTADAS

********************************************************************/



           List MakeEmpty( List L )
	   {
		  if( L != NULL )
			 DeleteList( &L );
		  L = malloc( sizeof( struct Node ) );
		  if( L == NULL )
			 FatalError( "Out of memory!" );
		  L->Next = NULL;
		  return L;
	   }

/* START: fig3_8.txt */
	   /* Return true if L is empty */

	   int IsEmpty( List L )
	   {
		  return L->Next == NULL;
	   }
/* END */

/* START: fig3_9.txt */
	   /* Return true if P is the last position in list L */
	   /* Parameter L is unused in this implementation */

	   int IsLast( Position P, List L )
	   {
		  return P->Next == NULL;
	   }
/* END */

/* START: fig3_10.txt */
        /* Return Position of X in L; NULL if not found */

        Position Find( TCODIGO X, List L )
        {
            List P;

            P = L;

/* 1*/      while( P != NULL && P->Element.codigo != X )
/* 3*/          P = P->Next;

/* 4*/      return P;
        }
/* END */

/* START: fig3_11.txt */
        /* Delete from a list */
        /* Cell pointed to by P->Next is wiped out */
        /* Assume that the position is legal */
        /* Assume use of a header node */

        void Delete( TCODIGO X, List L )
        {
            Position P, TmpCell;

            P = FindPrevious( X, L );

            if( !IsLast( P, L ) )  /* Assumption of header use */
            {                      /* X is found; delete it */
                TmpCell = P->Next;
                P->Next = TmpCell->Next;  /* Bypass deleted cell */
                destroy_bitmap (TmpCell->imagen); // destruimos el BITMAP
                free( TmpCell );
            }
        }
/* END */

/* START: fig3_12.txt */
        /* If X is not found, then Next field of returned value is NULL */
        /* Assumes a header */

        Position FindPrevious( TCODIGO X, List L )
        {
            Position P;

/* 1*/      P = L;
/* 2*/      while( P->Next != NULL && P->Next->Element.codigo != X )
/* 3*/          P = P->Next;

/* 4*/      return P;
        }
/* END */

/* START: fig3_13.txt */
        /* Insert (after legal position P) */
        /* Header implementation assumed */
        /* Parameter L is unused in this implementation */

        void Insert( ElementType X,BITMAP *image, List L, Position P )
        {
            Position TmpCell;

/* 1*/      TmpCell = malloc( sizeof( struct Node ) );
/* 2*/      if( TmpCell == NULL )
/* 3*/          FatalError( "Out of space!!!" );

/* 4*/      TmpCell->Element = X;
            TmpCell->imagen = image;
/* 5*/      TmpCell->Next = P->Next;
/* 6*/      P->Next = TmpCell;
        }
/* END */

#if 0
/* START: fig3_14.txt */
        /* Incorrect DeleteList algorithm */

        void
        DeleteList( List L )
        {
            Position P;

/* 1*/      P = L->Next;  /* Header assumed */
/* 2*/      L->Next = NULL;
/* 3*/      while( P != NULL )
            {
/* 4*/          free( P );
/* 5*/          P = P->Next;
            }
        }
/* END */
#endif

/* START: fig3_15.txt */
        /* Correct DeleteList algorithm */

        void
        DeleteList( List *L )
        {
         if (*L != NULL)
         {
          DeleteList (&((*L)->Next));
          destroy_bitmap ((*L)->imagen);   // Destruimos la imagen en el nodo
          free (*L);
          *L=NULL;
         }
        }
/*            Position P, Tmp;

/* 1*//*      P = L->Next;  /* Header assumed */
/* 2*//*      L->Next = NULL;
/* 3*//*      while( P != NULL )
            {
/* 4*//*          Tmp = P->Next;
                destroy_bitmap (P->imagen);
/* 5*//*          free( P );
/* 6*//*          P = Tmp;
            }
        }
/* END */

        Position
        Header( List L )
        {
            return L;
        }

        Position
        First( List L )
        {
            return L->Next;
        }

        Position
        Advance( Position P )
        {
            return P->Next;
        }

        ElementType
        RetrieveE( Position P )
        {
            return P->Element;
        }



/*****************************************************************

                FUNCIONES IMPLEMENTADAS POR NOSOTROS

******************************************************************/



/*****************************************************************

        Nombre: RetrieveI
        Tipo: Puntero a imagen
        Par metros de entrada: puntero a nodo
        Descripci¢n: Devuelve la direcci¢n de la imagen contenida en
                     el nodo cuya direcci¢n es P.
        Restricciones: P debe de apuntar a un nodo que contenga un
                       apuntador a una imagen creada de tipo BITMAP.

******************************************************************/


        BITMAP *RetrieveI (Position P)
        {
            return P->imagen;           // Devolvemos la im gen en el nodo
        }

/*****************************************************************

        Nombre: InsertPrimero
        Tipo: void
        Par metros de entrada: puntero a Lista, Elemento de la lista y
                               puntero a im gen.
        Descripci¢n: Inserta el elemento como el primero de la lista.
        Restricciones: La lista debe de estar inicializada.

******************************************************************/

        void InsertPrimero(List *lista ,ElementType Elemento, BITMAP *imagen)
        {
         List listAux=NULL; // Puntero auxiliar

         listAux=calloc(1,sizeof(struct Node)); // Creamos el nuevo nodo
         listAux->Next=*lista;
         listAux->Element=Elemento;   // Asignamos los campos
         listAux->imagen=imagen;
         *lista = listAux;            // El nuevo elemento es el primero

         return;
        }

/*****************************************************************

        Nombre: CargaFicheroObjetos
        Tipo: Lista
        Par metros de entrada: nada
        Descripci¢n: carga el contenido del fichero objetos.ots en
                     una lista en memoria, junto con sus respectivas
                     im genes.
        Restricciones: el fichero objetos.ots ha de existir y ser
                       correcto.

******************************************************************/

        List CargaFicheroObjetos ()
        {
         List listaObjetos;   // Lista
         FILE *fichObjetos;   // Fichero de objetos
         int i=1;             // Variable contador
         TOBJETO objeto;      // variable objeto
         PALETTE pal;         // paleta gr fica (necesario)
         BITMAP *bmp;         // Apuntador a BITMAP

         listaObjetos = NULL; // Inicializamos la lista como vac¡a

         while ((objeto = CargaObjeto (i)).codigo != 0)
         { // Mientras el objeto que pedimos exista...
          bmp = load_bitmap (objeto.imagen,pal);    //... cargamos su imagen
          InsertPrimero (&listaObjetos,objeto,bmp); // insertamos
          i++;
         }

         return listaObjetos;    // Devolvemos la lista
        }
