/************************************************************************

 listas cu druples - grafos

*************************************************************************/


#include "TadLCuad.h"

typedef struct TNODOAUX        // TIPO AUXILIAR DE DATOS, LISTA DE SALAS
        {
         TAPNODO salaActual;
         struct TNODOAUX *sig;
        } TNODOAUX;

typedef TNODOAUX *TLISTAAUX;


/**************************************************************

        Nombre: BuscaSala
        Tipo: TAPNODO
        Par metros de entrada: cod, lista
        Descripci¢n: busca en la lista el nodo con la sala de c¢digo cod,
                     y devuelve su direcci¢n.

**************************************************************/

TAPNODO BuscaSala (int cod,TLISTAAUX lista)
{
 if (cod) // si el codigo no es cero
  while (lista)
  { // recorremos la lista mientras no sea vacia.
   if (lista->salaActual->sala.codigo == cod) // si lo encontramos
      return lista->salaActual; // devolvemos la direcci¢n
   lista = lista->sig;
  }
 else return NULL; // si no, devolvemos NULL
}


/**************************************************************

        Nombre: DestruyeColumna
        Tipo: void
        Par metros de entrada: listaAux
        Descripci¢n: destruye la lista auxiliar, sin destruir los
                     nodos con las salas que cualgan de ella.

**************************************************************/

void DestruyeColumna (TLISTAAUX listaAux)
{
 if (listaAux) // Caso base: lista vac¡a
 { // Destruimos los siguientes, y luego el actual.
  DestruyeColumna (listaAux->sig);
  free (listaAux);
  return;
 }
}


/**************************************************************

        Nombre: CargaPantalla
        Tipo: TLISTACUAD
        Par metros de entrada: nombreFichero
        Descripci¢n: carga la pantalla contenida en el fichero
                     nombreFichero. Se vale de una lista auxiliar,
                     y devuelve la direcci¢n de la primera sala,
                     que ser  la primera del fichero.

**************************************************************/

TLISTACUAD CargaPantalla (char nombreFichero[13])
{
 FILE *fichPantalla;
 TAPNODO primera;
 TLISTAAUX listaAux, temp;

 listaAux=NULL; // Inicializamos la lista
 fichPantalla=fopen (nombreFichero,"r"); // abrimos el fichero
 listaAux=calloc(1,sizeof(TNODOAUX)); // Creamos la lista
 listaAux->salaActual=calloc(1,sizeof(TNODOCUAD)); // nodo de sala
 listaAux->salaActual->control=0;                  // control a 0
 listaAux->salaActual->sala=CargaSiguiente(fichPantalla); // cargamos sala
                                                          // de entrada
 temp=listaAux;
 listaAux->sig=NULL;
 while (!(feof(fichPantalla)))
 { // Creamos nodos a medida que leemos m s salas
  temp->sig=calloc(1,sizeof(TNODOAUX));
  temp=temp->sig;
  temp->salaActual=calloc(1,sizeof(TNODOCUAD));
  temp->salaActual->control=0;
  temp->salaActual->sala=CargaSiguiente(fichPantalla);
 }
 temp->sig=NULL; // final de lista

 fclose (fichPantalla); // cerramos el fichero

 temp=listaAux;
 primera = listaAux->salaActual; // Entrada a la pantalla -> primera
 while (temp)
 { // Lanzamos los punteros de los enlaces hasta terminar la lista
  temp->salaActual->n=BuscaSala (temp->salaActual->sala.enlaces[2][0],listaAux);
  temp->salaActual->e=BuscaSala (temp->salaActual->sala.enlaces[2][1],listaAux);
  temp->salaActual->s=BuscaSala (temp->salaActual->sala.enlaces[2][2],listaAux);
  temp->salaActual->o=BuscaSala (temp->salaActual->sala.enlaces[2][3],listaAux);
  temp = temp->sig;
 }
 DestruyeColumna (listaAux); // destruimos la lista actual

 return primera; // Devolvemos el punto de entrada
}


/**************************************************************

        Nombre: MoverASala
        Tipo: TAPNODO
        Par metros de entrada: pantalla, direc
        Descripci¢n: devuelve la direcci¢n del nodo seleccionado
                     por el caracter direc. Devuelve la direcci¢n
                     actual si no hay nodo.

**************************************************************/

TAPNODO MoverASala (TLISTACUAD pantalla,char direc)
{
 switch (direc)
 {
  case ('n'): if (pantalla->n)
                 return pantalla->n;   // Devolvemos la solicitada, si existe
              else return pantalla;    // si no la actual
  case ('s'): if (pantalla->s)
                 return pantalla->s;
              else return pantalla;
  case ('e'): if (pantalla->e)
                 return pantalla->e;
              else return pantalla;
  case ('o'): if (pantalla->o)
                 return pantalla->o;
              else return pantalla;
 }
}


/**************************************************************

        Nombre: DestruyePantalla
        Tipo: void
        Par metros de entrada: pantalla
        Descripci¢n: destruye la pantalla apuntada por el par metro
                     de entrada.

**************************************************************/

void DestruyePantalla (TLISTACUAD *pantalla)
{
 if (*pantalla != NULL && !(*pantalla)->control)
    { // Si no est  destruida...
     (*pantalla)->control = 1;
     DestruyePantalla (&((*pantalla)->n));
     DestruyePantalla (&((*pantalla)->s)); // Destruimos el resto
     DestruyePantalla (&((*pantalla)->e));
     DestruyePantalla (&((*pantalla)->o));
     free (*pantalla); // liberamos esta
     *pantalla = NULL;
    }
 return;
}


/**************************************************************

        Nombre: GuardaPantallaRecursivo
        Tipo: void
        Par metros de entrada: pantalla, fichPantalla
        Descripci¢n: guarda la pantalla recibida en el fichero, que
                     se recibe ya abierto.

**************************************************************/

void GuardaPantallaRecursivo (TLISTACUAD pantalla, FILE *fichPantalla)
{
 if (pantalla != NULL && !(pantalla->control))
 { // si no est  guardada (ni es NULL)
  pantalla->control = 1;
  GrabaSiguiente(fichPantalla,DameSalaRef(pantalla)); // Guardamos esta
  GuardaPantallaRecursivo(pantalla->n, fichPantalla);
  GuardaPantallaRecursivo(pantalla->e, fichPantalla); // Guardamos las
  GuardaPantallaRecursivo(pantalla->s, fichPantalla); // dem s
  GuardaPantallaRecursivo(pantalla->o, fichPantalla);
 }
 return;
}


/**************************************************************

        Nombre: GuardaPantalla
        Tipo: void
        Par metros de entrada: pantalla, nombreFichero
        Descripci¢n: abre nombreFichero para as¡ poder llamar
                     a GuardaPantallaRecursivo.

**************************************************************/

void GuardaPantalla (TLISTACUAD pantalla, char *nombreFichero )
{
 FILE *fichPantalla;

 fichPantalla= fopen (nombreFichero, "w"); // Abrimos el fichero
 GuardaPantallaRecursivo( pantalla, fichPantalla); // Guardamos
 fclose( fichPantalla);                    // Cerramos
 PonerControlACero (pantalla);             // Restauramos control
 return;
}


/**************************************************************

        Nombre: PonerControlACero
        Tipo: void
        Par metros de entrada: pantalla
        Descripci¢n: pone a cero los campos de control de la pantalla.

**************************************************************/

void PonerControlACero(TLISTACUAD pantalla)
{
 if (pantalla != NULL && pantalla->control)
 { // Si no ha sido procesada (y no es NULL)
  pantalla->control = 0; // Control a cero
  PonerControlACero(pantalla->n);
  PonerControlACero(pantalla->e); // Procesar el resto
  PonerControlACero(pantalla->s);
  PonerControlACero(pantalla->o);
 }
 return;
}


/**************************************************************

        Nombre: DameSalaRef
        Tipo: TSALA
        Par metros de entrada: pantalla
        Descripci¢n: devuelve la sala referenciada por pantalla

**************************************************************/

TSALA DameSalaRef (TLISTACUAD pantalla)
{
 return pantalla->sala;
}


/**************************************************************

        Nombre: ActualizaSala
        Tipo: void
        Par metros de entrada: sala, pantalla
        Descripci¢n: actualiza la sala del nodo de entrada a la
                     pantalla, con la sala actual.

**************************************************************/

void ActualizaSala (TSALA sala,TLISTACUAD pantalla)
{
 pantalla->sala = sala;

 return;
}
