/************************************************************************

M¢dulo principal

*************************************************************************/


#include "allegro.h"           // M¢dulos y librer¡as
#include "List.h"
#include "TadSala.h"
#include "TadObjet.h"
#include "TadLCuad.h"
#include "TadP.h"
#include "files.h"
#include "tadmalo.h"
#include "combate.h"
#include "recuadro.h"
#include "mapacol.h"
#include "videos.h"

#include <string.h>
#include <stdio.h>

#define alleg_mouse_unused     // Esto s¢lo acelera el tiempo de
#define alleg_joystick_unused  // compilaci¢n.
#define alleg_file_unused      //
#define alleg_datafile_unused  //
#define alleg_math_unused      //
#define alleg_gui_unused       //

#define NUMPANTALLAS 4    // constante del n£mero de pantallas



/***********************************************************

        Nombre: InicializaTodo
        Tipo: void
        Par metros de entrada: ninguno
        Descripci¢n: Inicializa Allegro, y las rutinas necesarias
                     para procesar ciertos archivos.
************************************************************/

void InicializaTodo()
{
 allegro_init(); //rutina de inicializaci¢n de alegro
 install_timer(); //necesario para archivos midi y fli/flc
 install_keyboard(); //para utilizar el teclado
 fade_out (1);
 install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL); // controlador de sonido
 srand(time(0)); // Generador de n£meros aleatorios
 return;
}



/***********************************************************

        Nombre: SeleccionPers
        Tipo: TPERSONAJE. Devuelve el personaje elegido.
        Par metros de entrada: ninguno
        Descripci¢n: muestra dos im genes de los personajes en pantalla
                     y permite escoger uno con las teclas de direcci¢n.
************************************************************/

TPERSONAJE SeleccionPers ()
{
 TPERSONAJE temp; // Para guardar el personaje temporalmente

 char i,j,*string;
 BITMAP *bardok,*txus;
 PALETTE pal;

 text_mode (0);
 clear_keybuf();
 bardok = load_bitmap ("bdks0000.bmp",pal); //
 txus = load_bitmap ("txss0000.bmp",pal);   // Cargamos las im genes
 set_palette (pal);                         //
 j = 1;
 clear (screen);
 textprintf (screen,font,200,50,10,"Selecciona tu personaje.");
 draw_sprite (screen,bardok,400,100); //
 draw_sprite (screen,txus,60,100);    // Sacamos las im genes por pantalla
 while (!key[KEY_ENTER])
 { // mientras no pulsemos ENTER...
  string = (j==1)?"Bardok":"Txus  "; // el nombre depende de la posici¢n
  textprintf (screen,font,(j==1)?400:60,110+bardok->h,215,"%s",string);
  textprintf (screen,font,(j==1)?60:400,110+bardok->h,215,"      ");
             // Escribimos el nombre bajo el que est  seleccionado,
             // y espacios bajo el otro
  if (key[KEY_RIGHT])
  { // Derecha selecciona el de la derecha
   j = 1;
   clear_keybuf();
  }
  else if (key[KEY_LEFT])
  { // Izquierda selecciona el de la izquierda
   j = 0;
   clear_keybuf();
  }
 }
 strcpy (temp.nombre,string);         //
 if (j == 1) strcpy (temp.fot,"bdk"); // Configuramos el personaje
 else strcpy (temp.fot,"txs");        //
 for (i=0;i<20;i++)           //colocamos los c¢digos de objetos a 0
     temp.objetos[i] = 0;     //para que no lleve ninguno
 for (i=0;i<5;i++)
     temp.carac[i] = 10;       //definimos las caracter¡sticas de complexi¢n del
 temp.exp = 2000;                //personaje
 temp.nivel = 3;

 destroy_bitmap (bardok); //
 destroy_bitmap (txus);   // Liberamos la memoria din mica
 text_mode (-1);

 return temp; // Devolvemos el personaje
}



/***********************************************************

        Nombre: SeleccionaMusicas
        Tipo: void
        Par metros de entrada: i, entero que representa el n£mero de la
                   pantalla. MusicG y MusicC, strings para guardar el
                   nombre de los ficheros de m£sica.
        Descripci¢n: Devuelve los nombres de los ficheros de m£sica seg£n
                     cu l sea el n£mero de pantalla.
************************************************************/

void SeleccionaMusicas (int i,char musicG[13], char musicC[13])
{
 switch (i) // Elegimos seg£n la pantalla
 {
  case (1): strcpy (musicG,"scr001.mid");
            strcpy (musicC,"scrc001.mid");
            break;
  case (2): strcpy (musicG,"scr002.mid");
            strcpy (musicC,"scrc002.mid");
            break;
  case (3): strcpy (musicG,"scr003.mid");
            strcpy (musicC,"scrc003.mid");
            break;
  case (4): strcpy (musicG,"scr004.mid");
            strcpy (musicC,"scrc004.mid");
            break;
 }
 return;
}



/***********************************************************

        Nombre: SeleccionPantallaInic
        Tipo: TLISTACUAD, devuelve una pantalla
        Par metros de entrada: musicGame, musicCombat, strings para
                   guardar los nombres de los ficheros de m£sica.
                   x, y, apuntadores a entero. En ellos se devolver n las
                   coordenadas iniciales.
        Descripci¢n: Configura los par metros de la primera pantalla, y
                     la devuelve.
************************************************************/

TLISTACUAD SeleccionPantallaInic (char musicGame[13], char musicCombat[13],
                                  int *x, int *y)
{
 strcpy (musicGame,"scr001.mid");
 strcpy (musicCombat,"scrc001.mid");
 *x = 305;
 *y = 290;

 return CargaPantalla ("pant001.zkt"); //selecciona la pantalla escogida
}



/***********************************************************

        Nombre: SeleccionACargar
        Tipo: TLISTACUAD, devuelve la pantalla cargada.
        Par metros de entrada: player, apuntador a personaje. musicG y
                   musicC, strigns. i, x, y, apuntadores a entero.
        Descripci¢n: Devuelve en player musicG, musicC, x e y los par metros
                     necesarios para jugar en una partida guardada.
                     El valor de vuelta es la entrada a la pantalla grabada.
************************************************************/

TLISTACUAD SeleccionACargar (TPERSONAJE *player,int *i,char musicG[13],
                             char musicC[13],int *x, int *y)
{
 BITMAP *doublebuffer;
 int k,j=0; // k: contador de bucle. j: selecci¢n actual
 INFO temp[15];

 text_mode (-1);
 doublebuffer = create_bitmap (640,480); // Creamos el doble buffer
 clear_keybuf();
 clear(doublebuffer);
 textprintf (doublebuffer,font,100,10,215,"Selecciona la partida a cargar");
 CargaSaved (temp);                      // Cargamos las partidas grabadas
 while (!key[KEY_ENTER] && !key[KEY_ESC])
 { // Mientras no se pulse Enter ni Esc...
  for (k=0;k<=14;k++)
      DibujaSlots (doublebuffer,k,j,temp); //...dibujamos la casillas
  blit (doublebuffer,screen,0,0,0,0,640,480); // volcamos a pantalla
  if (key[KEY_UP])
  { // Si se pulsa arriba
   j--;                // movemos
   clear_keybuf();
   j = (j==-1)?0:j;    // vigilamos el l¡mite superior
  }
  else if (key[KEY_DOWN])
  { // Si se pulsa abajo
   j++;               // movemos
   clear_keybuf();
   j = (j==15)?14:j;  // vigilamos el l¡mite inferior
  }
 } // FIN while
 if (key[KEY_ENTER])
 { // Si pulsamos Enter
  clear_keybuf();
  *i = temp[j].codActual;
  if (*i) // si el slot est  ocupado
  {
   SeleccionaMusicas (temp[j].codActual,musicG,musicC);
   *player = CargaPlayer (temp[j].fPlayer);   //
   *x = temp[j].x;                            // Cargamos y devolvemos la
   *y = temp[j].y;                            // pantalla
   return CargaPantalla (temp[j].fPantalla);  //
  } else return NULL;   // si no est  grabada, no retornamos pantalla
 }
 else
 { //Si pulsamos Esc
  clear_keybuf();
  *i = 0;
  return NULL; // no retornamos pantalla
 }
}



/***********************************************************

        Nombre: GuardaPartida
        Tipo: void
        Par metros de entrada: player, el personaje. pantalla, la pantalla
                   actual. i, n£mero de pantalla. x e y, coordenadas del
                   jugador.
        Descripci¢n: Seleccionamos el slot en que guardar, y grabamos en ‚l
                     la partida.
************************************************************/

void GuardaPartida (TPERSONAJE player, TLISTACUAD pantalla,int i,int x,int y)
{
 BITMAP *doublebuffer;
 int k,j=0; // k: contador de bucle. j: selecci¢n actual
 INFO temp[15];

 text_mode (-1);
 doublebuffer = create_bitmap (640,480);  // Creamos el doble buffer
 clear_keybuf();
 clear(doublebuffer);
 textprintf (doublebuffer,font,100,10,215,"Selecciona la partida a grabar");
 CargaSaved (temp);                       // Cargamos las partidas grabadas
 while (!key[KEY_ENTER] && !key[KEY_ESC])
 { // Mientras no pulsemos enter o escape
  for (k=0;k<=14;k++)
      DibujaSlots (doublebuffer,k,j,temp); // Mostramos los slots de grabaci¢n
  blit (doublebuffer,screen,0,0,0,0,640,480);
  if (key[KEY_UP])
  { // si pulsamos arriba
   j--;               // seleccinamos la superior
   clear_keybuf();
   j = (j==-1)?0:j;   // y vigilamos los l¡mites
  }
  else if (key[KEY_DOWN])
  { // si pulsamos abajo
   j++;               // seleccionamos la inferior
   clear_keybuf();
   j = (j==15)?14:j;  // y vigilamos los l¡mites
  }
 } // FIN while
 if (key[KEY_ENTER])
 { // si pulsamos enter
  clear_keybuf();
  strcpy (temp[j].nPlayer,player.nombre);        //
  strcpy (temp[j].nSala,(pantalla->sala).nombre);//
  temp[j].codActual = i;                         // Actualizamos el array de
  temp[j].x = x;                                 // partidas grabadas
  temp[j].y = y;                                 //
  ActualizaSaved (temp);                         // lo guardamos
  GuardaPantalla (pantalla, temp[j].fPantalla);  // Guardamos la pantalla
  GrabaPlayer (player,temp[j].fPlayer);          // y el personaje
 }
 return;
}



/***********************************************************

        Nombre: CargaPantallaI
        Tipo: TLISTACUAD
        Par metros de entrada: codigo, el n£mero de pantalla a cargar.
                   musicGame, musicCombat, x, y: par metros para la nueva
                   pantalla. player: aputador al personaje.
        Descripci¢n:
************************************************************/

TLISTACUAD CargaPantallaI (int codigo, char musicGame[13], char musicCombat[13],
                           int *x, int *y,TPERSONAJE *player)
{
 int i;   // contador de bucle
 int (*callBack)();   // apuntador a funci¢n que devuelve entero para play_fli

 set_gfx_mode (GFX_AUTODETECT,320,200,0,0); //inicializamos el modo gr fico
 clear_keybuf();
 player->nivel++;            // Subimos el nivel del personaje
 *x = 305;                   //
 *y = 290;                   //  Coordenadas iniciales
 switch (codigo)
 {
  case (2): for (i = 0; i < 3; i++)
                player->carac[i] += 5;               //
            player->carac[4] += 20;                  // Subimos atributos
            player->carac[3] = player->carac[4];     //
            callBack = StopChocobo;
            play_fli ("chocobo.fli",screen,FALSE,callBack);//video entre fase
            set_gfx_mode (GFX_AUTODETECT,640,480,0,0); //inicializamos el modo gr fico
            strcpy (musicGame, "scr002.mid");      //
            strcpy (musicCombat, "scrc002.mid");   // M£sicas
            return CargaPantalla ("pant002.zkt");  // Devolvemos la pantalla
  case (3): for (i = 0; i < 5; i++)
                player->carac[i] += 10;
            callBack = StopYoda;
            play_fli ("yoda.fli",screen,FALSE,callBack);
            set_gfx_mode (GFX_AUTODETECT,640,480,0,0);
            strcpy (musicGame, "scr003.mid");          // Lo mismo aqu¡
            strcpy (musicCombat, "scrc003.mid");
            return CargaPantalla ("pant003.zkt");
  case (4): for (i = 0; i < 5; i++)
                player->carac[i] += 15;
            callBack = StopDanste;
            play_fli ("danste1.flc",screen,FALSE,callBack);
            set_gfx_mode (GFX_AUTODETECT,640,480,0,0);  // y aqu¡
            strcpy (musicGame, "scr004.mid");
            strcpy (musicCombat, "scrc004.mid");
            return CargaPantalla ("pant004.zkt");
 }
}



/***********************************************************

        Nombre: DibujaParedes
        Tipo: void
        Par metros de entrada: fondo, BITMAP. pared: array con las paredes
        Descripci¢n: dibuja las paredes especificadas en pared sobre el bitmap
************************************************************/

void DibujaParedes(BITMAP *fondo,int *pared)
{
 int i;

 for (i=0;i<=11;i++)                          //dibuja las paredes de la sala
     if (pared[i])                            //colocando sobre la pantalla
        switch (i)                            //los rect ngulos rellenos de
        {                                     //determinado color
         case (0): rectfill (fondo,250,0,389,9,pared[i]); break;
         case (1): rectfill (fondo,390,0,639,9,pared[i]); break;
         case (2): rectfill (fondo,629,0,639,149,pared[i]); break;
         case (3): rectfill (fondo,629,150,639,229,pared[i]); break;
         case (4): rectfill (fondo,629,230,639,379,pared[i]); break;
         case (5): rectfill (fondo,390,369,639,379,pared[i]); break;
         case (6): rectfill (fondo,250,369,389,379,pared[i]); break;
         case (7): rectfill (fondo,0,369,249,379,pared[i]); break;
         case (8): rectfill (fondo,0,230,9,379,pared[i]); break;
         case (9): rectfill (fondo,0,150,9,229,pared[i]); break;
         case (10): rectfill (fondo,0,0,9,149,pared[i]); break;
         case (11): rectfill (fondo,0,0,249,9,pared[i]); break;
        }
  return;
}



/***********************************************************

        Nombre: DibujaPuertas
        Tipo: void
        Par metros de entrada: fondo, BITMAP. puerta: array con las puertas
        Descripci¢n: dibuja las puertas especificadas en puerta sobre el bitmap
************************************************************/

void DibujaPuertas (BITMAP *fondo,int *puerta)
{
 int i;

 for (i=0;i<=3;i++)                     //idem pero para las puertas
     if (puerta[i])                     //que no es m s que los
        switch (i)                      //rect ngulos que no hemos rellenado
        {                               //antes
         case (0): rectfill (fondo,250,5,389,9,puerta[i]); break;
         case (1): rectfill (fondo,629,150,634,229,puerta[i]); break;
         case (2): rectfill (fondo,250,369,389,374,puerta[i]); break;
         case (3): rectfill (fondo,5,150,9,229,puerta[i]); break;
        }
}



/***********************************************************

        Nombre: CargaFotPlayer
        Tipo: void
        Par metros de entrada: base, string con la base de los fotogramas.
                   fot, array de apuntadores a BITMAP
        Descripci¢n: carga en fot las im genes dadas por base.
************************************************************/

void CargaFotPlayer(char *base,BITMAP **fot)
{
 char temp2[13];
 PALETTE pal;

 strcpy (temp2,base);  // copiamos la base
 fot[0] = load_bitmap (strcat (temp2,"U0000.bmp"),pal); // concatenamos y
 strcpy (temp2,base);                                   // cargamos
 fot[1] = load_bitmap (strcat (temp2,"U0001.bmp"),pal);
 strcpy (temp2,base);
 fot[2] = load_bitmap (strcat (temp2,"U0002.bmp"),pal);
 strcpy (temp2,base);                                   // As¡ con todos
 fot[3] = load_bitmap (strcat (temp2,"U0003.bmp"),pal);
 strcpy (temp2,base);
 fot[4] = load_bitmap (strcat (temp2,"U0004.bmp"),pal);
 strcpy (temp2,base);
 fot[5] = load_bitmap (strcat (temp2,"U0005.bmp"),pal);
 strcpy (temp2,base);
 fot[6] = load_bitmap (strcat (temp2,"U0006.bmp"),pal);
 strcpy (temp2,base);
 fot[7] = load_bitmap (strcat (temp2,"D0000.bmp"),pal);
 strcpy (temp2,base);
 fot[8] = load_bitmap (strcat (temp2,"D0001.bmp"),pal);
 strcpy (temp2,base);
 fot[9] = load_bitmap (strcat (temp2,"D0002.bmp"),pal);
 strcpy (temp2,base);
 fot[10] = load_bitmap (strcat (temp2,"D0003.bmp"),pal);
 strcpy (temp2,base);
 fot[11] = load_bitmap (strcat (temp2,"D0004.bmp"),pal);
 strcpy (temp2,base);
 fot[12] = load_bitmap (strcat (temp2,"D0005.bmp"),pal);
 strcpy (temp2,base);
 fot[13] = load_bitmap (strcat (temp2,"D0006.bmp"),pal);
 strcpy (temp2,base);
 fot[14] = load_bitmap (strcat (temp2,"L0000.bmp"),pal);
 strcpy (temp2,base);
 fot[15] = load_bitmap (strcat (temp2,"L0001.bmp"),pal);
 strcpy (temp2,base);
 fot[16] = load_bitmap (strcat (temp2,"L0002.bmp"),pal);
 strcpy (temp2,base);
 fot[17] = load_bitmap (strcat (temp2,"L0003.bmp"),pal);
 strcpy (temp2,base);
 fot[18] = load_bitmap (strcat (temp2,"L0004.bmp"),pal);
 strcpy (temp2,base);
 fot[19] = load_bitmap (strcat (temp2,"L0005.bmp"),pal);
 strcpy (temp2,base);
 fot[20] = load_bitmap (strcat (temp2,"L0006.bmp"),pal);
 strcpy (temp2,base);
 fot[21] = load_bitmap (strcat (temp2,"R0000.bmp"),pal);
 strcpy (temp2,base);
 fot[22] = load_bitmap (strcat (temp2,"R0001.bmp"),pal);
 strcpy (temp2,base);
 fot[23] = load_bitmap (strcat (temp2,"R0002.bmp"),pal);
 strcpy (temp2,base);
 fot[24] = load_bitmap (strcat (temp2,"R0003.bmp"),pal);
 strcpy (temp2,base);
 fot[25] = load_bitmap (strcat (temp2,"R0004.bmp"),pal);
 strcpy (temp2,base);
 fot[26] = load_bitmap (strcat (temp2,"R0005.bmp"),pal);
 strcpy (temp2,base);
 fot[27] = load_bitmap (strcat (temp2,"R0006.bmp"),pal);

 return;
}



/***********************************************************

        Nombre: CargaFotPnj
        Tipo: void
        Par metros de entrada: sala en la que estamos.
                   pnjFot, array de apuntadores a BITMAP
        Descripci¢n: carga en pnjFot las im genes del PNJ de la sala (si lo
                     hubiere).
************************************************************/

void CargaFotPnj (TSALA sala,BITMAP **pnjFot)
{
 char temp2[13];
 PALETTE pal;

 if (strcmp (sala.pnj,"NO"))
 { // si hay PNJ
  strcpy (temp2,sala.imagenPnj);   // Copiar, concatenar y cargar...
  pnjFot[0] = load_bitmap (strcat (temp2,"R0000.bmp"),pal);
  strcpy (temp2,sala.imagenPnj);
  pnjFot[1] = load_bitmap (strcat (temp2,"L0000.bmp"),pal);
  strcpy (temp2,sala.imagenPnj);
  pnjFot[2] = load_bitmap (strcat (temp2,"D0000.bmp"),pal);
  strcpy (temp2,sala.imagenPnj);
  pnjFot[3] = load_bitmap (strcat (temp2,"U0000.bmp"),pal);
 }

 return;
}



/***********************************************************

        Nombre: DibujaObjetos
        Tipo: void
        Par metros de entrada: objetos: lista de objetos
                   sala: sala actual. Doble buffer.
        Descripci¢n: dibuja en el doble buffer los objetos de la sala.
************************************************************/

void DibujaObjetos (List objetos,TSALA sala,BITMAP *doublebuffer)
{
 BITMAP *temp;
 int i = 0;

 while (i<5) //mientras no miremos todos
 {
  if (sala.codObjetosSala[i])
  { // si hay objeto en esa posici¢n
   temp = RetrieveI (Find (sala.codObjetosSala[i],objetos)); // Coge la imagen
   draw_sprite (doublebuffer,temp,sala.coordObjetos[0][i],   // y la dibujas
        sala.coordObjetos[1][i]);                            // en sus
  }                                                          // coordenadas
  i++;
 }
}



/***********************************************************

        Nombre: DibujaPnj
        Tipo: void
        Par metros de entrada: sala, fotogramas del PNJ, doblebuffer,
                   fotograma a dibujar
        Descripci¢n: dibuja el fotograma del PNJ para que si le miramos nos
                     mire.
************************************************************/

void DibujaPnj (TSALA sala,BITMAP **pnjFot, BITMAP *doublebuffer, int i)
{
 if (strcmp (sala.pnj,"NO"))
 { // Si hay PNJ
  switch (i)
  {
   case (0): i = 2; break;  // Fotogramas para que si le miramos nos mire
   case (1): i = 3; break;
   case (2): i = 0; break;
   case (3): i = 1; break;
  }
  draw_sprite (doublebuffer,pnjFot[i],sala.coordenadasPnj[0],
              sala.coordenadasPnj[1]);  // Lo dibujamos
 }

 return;
}



/***********************************************************

        Nombre: DestruyeTodo
        Tipo: void
        Par metros de entrada: fondo, doblebuffer, texto, pnjFot, fot,
                   music, pantalla
        Descripci¢n: Destruye la memoria din mica asociada a todos los
                     par metros de entrada.
************************************************************/

void DestruyeTodo (BITMAP *fondo,BITMAP *doublebuffer,BITMAP *texto,
                   BITMAP *(pnjFot[4]),BITMAP *(fot[28]),
                   List *objetos,MIDI *music, TLISTACUAD *pantalla)
{
 int i;

 destroy_bitmap (fondo);
 destroy_bitmap (doublebuffer);
 destroy_bitmap (texto);
 destroy_midi (music);
 DeleteList (objetos);
 if (strcmp(((*pantalla)->sala).pnj,"NO"))
    for (i=0;i<4;i++) // Si hay PNJ...
        destroy_bitmap (pnjFot[i]);   //...
 for (i=0;i<28;i++)
     destroy_bitmap (fot[i]);
 DestruyePantalla (pantalla);
}



/***********************************************************

        Nombre: Rotar
        Tipo: void
        Par metros de entrada: objetos, array de 20 enteros. i, entero
        Descripci¢n: desplaza hacia arriba el array en una posici¢n desde
                     la siguiente a la indicada. Inserta cero al final.
************************************************************/

void Rotar ( int objetos[20], int i)
{
 for (;i<19;i++)
   objetos[i]=objetos[i+1];
 objetos[19] = 0;
 return;
}



/***********************************************************

        Nombre: AbrePuerta
        Tipo: int. Devuelve 0 si no se ha abierto la puerta, 1 si lo ha hecho
        Par metros de entrada: aAbrir, n£mero de puerta. sala, personaje.
        Descripci¢n: Si se puede, abre una deerminada puerta.
************************************************************/

int AbrePuerta (char aAbrir,TSALA *sala, TPERSONAJE *personaje)
{
 int i=0;

 if (sala->enlaces[1][aAbrir])
 { // si se necesita un objeto
  while (personaje->objetos[i] != sala->enlaces[1][aAbrir] && i <= 19)
   i++;          // lo buscamos en el inventario
  if (i <= 19)
  {
   Rotar (personaje->objetos, i);
   sala->enlaces[0][aAbrir] = 0;  // Si lo tenemos, lo quitamos y abrimos
   sala->enlaces[1][aAbrir] = 0;
  }
  else return 0;                  // Si no, no abrimos
 }
 else sala->enlaces[0][aAbrir] = 0; // Si no hace falta objeto, abrimos

 return 1;
}



/***********************************************************

        Nombre: ActualizaSalaHablar
        Tipo: void
        Par metros de entrada: sala, conversacion, player.
        Descripci¢n: actualiza la sala al intentar hablar con el PNJ,
                     y devuelve el fichero de conversaci¢n abierto.
************************************************************/

void ActualizaSalaHablar (TSALA *sala, FILE **conversacion, TPERSONAJE *player)
{
 int i=0;

 if (sala->hablado)
 { // Si ya hemos hablado
  *conversacion = fopen (sala->dialogo[1],"r"); // abrimos el segundo
  if (sala->objetoSiHablamos)
  { // si hay que dar un objeto
   while (player->objetos[i] && i<=19) // y hay sitio
         i++;
   if (i<20)
   {
    player->objetos[i]=sala->objetoSiHablamos; // lo ponemos en el inventario
    sala->objetoSiHablamos = 0;
   }
  }
 }
 else
 {
  *conversacion = fopen (sala->dialogo[0],"r"); // sino hablamos por primera
  sala->hablado = 1;                            // vez
 }

 return;
}



/***********************************************************

        Nombre: Hablar
        Tipo: void
        Par metros de entrada: sala, player, doblebuffer
        Descripci¢n: se muestra el archivo de conversaci¢n espec¡fico.
                     EL FICHERO HA DE SER CORRECTO.
************************************************************/

void Hablar (TSALA *sala, TPERSONAJE *player, BITMAP *doublebuffer)
{
 FILE *conversacion;
 char palabra[30];
 int x=153,y=53;

 clear_keybuf();
 ActualizaSalaHablar (sala,&conversacion,player); // Actualizamos la sala..
 rect(doublebuffer,150,50,500,250,215);    // ..y abrimos el archivo
 rectfill(doublebuffer,151,51,499,249,10); // dibujamos el rect ngulo
 fscanf (conversacion,"%s",palabra);       // leemos el archivo
 while (strcmp(palabra,"<end>"))           // hasta la etiqueta <end>
 {
  if (strcmp(palabra,"<nombrep>")==0) strcpy (palabra,player->nombre);
  else if (strcmp(palabra,"<nombrepnj>")==0) strcpy (palabra,sala->pnj);
  else if (strcmp(palabra,"<cl>")==0)
  {                                     // Evaluamos las etiquetas dejando
   strcpy(palabra,"");                  // en palabra el string correspondiente
   x=153;
   y+=12;
  }
  else if(strcmp(palabra,"<wait>")==0)
  { // si hay que esperar, se espera
   strcpy(palabra,"");
   blit (doublebuffer,screen,0,0,0,0,640,480);
   readkey();
   x=153;
   y=53;
   rect(doublebuffer,150,50,500,250,215);
   rectfill(doublebuffer,151,51,499,249,10);
  }
  textprintf(doublebuffer,font,x,y,215,"%s",palabra); // mostramos la palabra
  x+=(text_length(font,palabra)+8);    // y actualizamos el cursor
  fscanf (conversacion,"%s",palabra);  // leemos la siguiente palabra
 }
 fclose (conversacion);                // cerramos el fichero
}



/***********************************************************

        Nombre: CogerObjeto
        Tipo: void
        Par metros de entrada: sala, player, mapacolisiones, codigo,
                   lista de objetos.
        Descripci¢n: Cogemos el objeto del c¢digo escogido. Lo quitamos
                     del mapa de colisiones y de la sala.
************************************************************/

void CogerObjeto (TSALA *sala,TPERSONAJE *player,char mapaColisiones[640][380],
                  char codigo,List objetos)
{
 TOBJETO temp;
 BITMAP  *temp2; //para sacar el objeto que cojemos del bitmap de la sala
 int i=0;

 temp=RetrieveE(Find(codigo,objetos));  // Recuperamos el objeto
 temp2=RetrieveI(Find(codigo,objetos)); // y su imagen
 if (temp.tipo)
 { // si se puede coger
  while (player->objetos[i] && i<=19)
        i++;
  if (i<20)
  { // y tenemos sitio
   player->objetos[i]=codigo; // lo cogemos
   i=0;
   while (sala->codObjetosSala[i]!=codigo)
         i++;
   RellenaMapa (mapaColisiones,sala->coordObjetos[0][i], // lo quitamos del
                sala->coordObjetos[1][i],            // mapa de co. teniendo
                sala->coordObjetos[0][i] + temp2->w, // en cuenta sus medidas
                sala->coordObjetos[1][i] + temp2->h, 0);

   sala->codObjetosSala[i]=0;
   sala->coordObjetos[0][i]=0;  // lo quitamos de la sala.
   sala->coordObjetos[1][i]=0;
  }
 }
 return;
}



/***********************************************************

        Nombre: DibujaCarac
        Tipo: void
        Par metros de entrada: player y doublebuffer
        Descripci¢n: escribe las caracter¡sticas de player en doublebuffer
************************************************************/

void DibujaCarac ( TPERSONAJE *player, BITMAP *doublebuffer)
{
 textprintf (doublebuffer,font,225,140,215,"NOMBRE: %s",player->nombre);
 textprintf (doublebuffer,font,225,180,215,"ATRIBUTOS");
 textprintf (doublebuffer,font,225,220,215,"Fuerza:      %d",player->carac[0]);
 textprintf (doublebuffer,font,225,240,215,"Resistencia: %d",player->carac[1]);
 textprintf (doublebuffer,font,225,260,215,"Velocidad:   %d",player->carac[2]);
 textprintf (doublebuffer,font,225,280,215,"HP:          %d",player->carac[3]);
 textprintf (doublebuffer,font,225,300,215,"MaxHp:       %d",player->carac[4]);
 textprintf (doublebuffer,font,225,340,215,"Experiencia: %d",player->exp);
 textprintf (doublebuffer,font,225,360,215,"Nivel:       %d",player->nivel);


 return;
}



/***********************************************************

        Nombre: EscribeObjetos
        Tipo: void
        Par metros de entrada: objetos, inventario, i, doublebuffer
        Descripci¢n: escribe los objetos del personaje en doublebuffer
                     y pone en blanco el seleccionado por i.
************************************************************/

void EscribeObjetos (List objetos,int inventario[20], int i,
                     BITMAP *doublebuffer)
{
 int j=0;
 TOBJETO temp;

 while (j<20 && inventario[j])
 { // mientras haya objetos
  temp = RetrieveE(Find(inventario[j],objetos)); // lo escribimos, uno debajo
  textprintf (doublebuffer,font,430,110+j*12,(i==j)?215:86,"%s", // de otro.
              temp.nombre);
  j++;
 }

 return;
}



/***********************************************************

        Nombre: UsaObjeto
        Tipo: void
        Par metros de entrada: indice (entero), lista de objetos, player
        Descripci¢n: usa uno de los objetos de player.
************************************************************/

void UsaObjeto ( int *indice, List objetos, TPERSONAJE *player)
{
 TOBJETO temp;
 int i;

 temp = RetrieveE (Find (player->objetos[*indice], objetos));
 if (temp.tipo == 1) // si lo podemos usar
 {
  for (i=0;i<5;i++)
      player->carac[i] += temp.modif[i];  // sumamos modificadores
  if (player->carac[3] > player->carac[4])
     player->carac[3] = player->carac[4]; // sin superar el m ximo de vida
  Rotar (player->objetos,*indice);        // rotamos
  if (player->objetos[*indice] == 0 && *indice) (*indice)--; // si indice era
 }                                         // el £ltimo, ahora es el anterior

 return;
}



/***********************************************************

        Nombre: DibujaFondoMenu
        Tipo: void
        Par metros de entrada: fondo, player
        Descripci¢n: dibuja en fondo el dibujo correspondiente a player,
                     y las l¡neas divisorias.
************************************************************/

void DibujaFondoMenu (BITMAP *fondo, TPERSONAJE *player)
{
 BITMAP *foto, *logo;
 PALETTE pal;

 clear_to_color (fondo,10);
 hline (fondo,0,100,639,215);
 hline (fondo,0,440,639,215);
 vline (fondo,213,100,440,215);
 vline (fondo,426,100,440,215);
 textprintf (fondo,font,200,455,215,"PULSA ESC PARA SALIR");
 logo = load_bitmap("ff92logo.bmp",pal);
 if (strcmp (player->nombre,"Txus  ") == 0)
    foto = load_bitmap ("txss0000.bmp",pal);
 else foto = load_bitmap ("bdks0000.bmp",pal);
 draw_sprite (fondo,logo,50,0);
 draw_sprite (fondo,foto,10,101);
 destroy_bitmap (foto);
 destroy_bitmap (logo);

 return;
}



/***********************************************************

        Nombre: Menu
        Tipo: void
        Par metros de entrada: player, doublebuffer, objetos
        Descripci¢n: muestra los atributos y objetos de player. Permite usar
                     objetos.
************************************************************/

void Menu (TPERSONAJE *player, BITMAP *doublebuffer, List objetos)
{
 BITMAP *fondo;
 int i=0;

 fondo = create_bitmap(640,480);
 while (!key[KEY_ESC])
 {                                            //
  DibujaFondoMenu (fondo, player);            // Dibujamos todo
  blit (fondo,doublebuffer,0,0,0,0,640,480);  //
  DibujaCarac (player,doublebuffer);
  EscribeObjetos (objetos, player->objetos,i,doublebuffer);
  blit (doublebuffer,screen,0,0,0,0,640,480);
  if (key [KEY_DOWN])
  {                  // objeto inferior
   if (player->objetos[i+1] && i < 19) // si hay
      i++;
   clear_keybuf();
  }
  else if (key[KEY_UP])
  {                 // objeto superior
   if (i>0 && player->objetos[i-1])
      i--;
   clear_keybuf();
  }
  else if (key [KEY_ENTER])
  {                        // si tenemos objeto, lo usamos
   if (player->objetos[i])
      UsaObjeto (&i,objetos, player);
   clear_keybuf();
  }
 }
 destroy_bitmap (fondo);

 return;
}



/***********************************************************

        Nombre: MueveArriba
        Tipo: void
        Par metros de entrada: mapacolisiones, x , y , i.
        Descripci¢n: si se puede, desplazamos al jugador hacia arriba,
                     y actualizamos su fotograma.
************************************************************/

void MueveArriba (char mapaColisiones[640][380],int *x,int *y, int *i)
{
 if ((*y) >= 4 && !Colision(mapaColisiones,*x,*y-6,*x+40,*y)) // no estamos
 {                                                            // en el borde
  (*y)-=6;                                                    // y no hay
  if ((*i) >= 0 && (*i)<=5)                                   // colisi¢n
     (*i)++;
  else (*i) = 1;
 }
 else (*i) = 0;

 return;
}



/***********************************************************

        Nombre: MueveAbajo
        Tipo: void
        Par metros de entrada: mapacolisiones, x , y , i.
        Descripci¢n: si se puede, desplazamos al jugador hacia abajo,
                     y actualizamos su fotograma.
************************************************************/

void MueveAbajo (char mapaColisiones[640][380],int *x,int *y, int *i)
{
 if ((*y) <= 304 && !Colision(mapaColisiones,*x,*y+70,*x+40,*y+76)) // colisiones
 {
  (*y)+=6;
  if ((*i) >= 7 && (*i)<=12)
     (*i)++;
  else (*i) = 8;
 }
 else (*i) = 7;

 return;
}



/***********************************************************

        Nombre: MueveIzquierda
        Tipo: void
        Par metros de entrada: mapacolisiones, x , y , i.
        Descripci¢n: si se puede, desplazamos al jugador hacia la izquierda
                     y actualizamos su fotograma.
************************************************************/

void MueveIzquierda (char mapaColisiones[640][380],int *x,int *y, int *i)
{
 if ((*x) >= 6 && !Colision(mapaColisiones,*x-6,*y,*x,*y+70)) // colisiones
 {
  (*x)-=6;
  if ((*i) >= 14 && (*i)<=19)
     (*i)++;
  else (*i) = 15;
 }
 else (*i) = 14;

 return;
}



/***********************************************************

        Nombre: MueveDerecha
        Tipo: void
        Par metros de entrada: mapacolisiones, x , y , i.
        Descripci¢n: si se puede, desplazamos al jugador hacia la derecha
                     y actualizamos su fotograma.
************************************************************/

void MueveDerecha (char mapaColisiones[640][380],int *x,int *y, int *i)
{
 if ((*x) <= 594 && !Colision(mapaColisiones,*x+40,*y,*x+46,*y+70)) // colisiones
 {
  (*x)+=6;
  if ((*i) >= 21 && (*i)<=26)
     (*i)++;
  else (*i) = 22;
 }
 else (*i) = 21;

 return;
}



/***********************************************************

        Nombre: AccionSpace
        Tipo: void
        Par metros de entrada: coordenadas, fotograma actual, mapa de colisiones
                   sala, player, objetos, doublebuffer, pantalla
        Descripci¢n: dependiendo del objeto con el que haya colisi¢n se
                     llamar  a la rutina para tratarla.
************************************************************/

void AccionSpace (int *x,int *y,int *i,char mapaColisiones[640][380],
                  TSALA *sala, TPERSONAJE *player, List objetos,
                  BITMAP *doublebuffer, TLISTACUAD pantalla)
{
 int codCol;

 *i = 7*((int) ((*i)/7)); // i es un fotograma base
 switch (*i)
 { // calculamos la colisi¢n seg£n la direcci¢n en que miramos
  case (0):codCol=Colision(mapaColisiones,*x,*y-6,*x+40,*y);break;
  case (7):codCol=Colision(mapaColisiones,*x,*y+70,*x+40,*y+76);break;
  case (14):codCol=Colision(mapaColisiones,*x-6,*y,*x,*y+70);break;
  case (21):codCol=Colision(mapaColisiones,*x+40,*y,*x+46,*y+70);break;
 }
 switch (codCol) // dependiendo de cu l sea, tendr  un tratamiento.
 {
  case (0):   break;
  case (100): break;
  case (101): if (AbrePuerta(0,sala,player))
              RellenaMapa (mapaColisiones,250,0,389,9,0);
              break;
  case (102): if (AbrePuerta(1,sala,player))
              RellenaMapa (mapaColisiones,629,150,639,229,0);
              break;
  case (103): if (AbrePuerta(2,sala,player))
              RellenaMapa (mapaColisiones,250,369,389,379,0);
              break;
  case (104): if (AbrePuerta(3,sala,player))
              RellenaMapa (mapaColisiones,0,150,9,229,0);
              break;
  case (105): Hablar(sala,player,doublebuffer);
              break;
  default: CogerObjeto (sala,player,mapaColisiones,codCol,objetos);
           break;
 }
 ActualizaSala (*sala,pantalla); // y actualizamos la sala en la pantalla

 return;
}



/***********************************************************

        Nombre: MuevePlayer
        Tipo: void
        Par metros de entrada: coordenadas, fotograma, mapa de colisiones,
                   sala, pantalla, personaje, objetos, codigo de la sala
                   actual, doblebuffer.
        Descripci¢n: se ejecutar  una rutina, dependiendo de la tecla
                     pulsada.
************************************************************/

void MuevePlayer (int *x,int *y,int *i,char mapaColisiones[640][380],
                  TSALA *sala,TLISTACUAD pantalla, TPERSONAJE *player,
                  List objetos, int codActual, BITMAP *doublebuffer)
{
  if (keypressed())
  {
   if (key[KEY_UP])
      MueveArriba (mapaColisiones,x,y,i);
   else
   if (key[KEY_DOWN])
      MueveAbajo (mapaColisiones,x,y,i);
   else
   if (key[KEY_LEFT])
      MueveIzquierda (mapaColisiones,x,y,i);
   else
   if (key[KEY_RIGHT])
      MueveDerecha (mapaColisiones,x,y,i);
   else
   if (key[KEY_S])
      GuardaPartida (*player,pantalla,codActual,*x,*y);
   else
   if (key[KEY_SPACE])
      AccionSpace (x,y,i,mapaColisiones,sala,player,objetos,doublebuffer,
                   pantalla);
   else if (key[KEY_M])
        Menu ( player, doublebuffer, objetos);
   clear_keybuf();
  }
  else (*i) = 7*((int) ((*i) / 7)); // si no hay nada pulsado, estamos quietos
  rest (70);

  return;
}



/***********************************************************

        Nombre: CambiaASalaOeste
        Tipo: void
        Par metros de entrada: fondo, fotogramas PNJ, coordenadas,
                   sala, paleta, pantalla, lista de objetos, mapa de
                   colisiones.
        Descripci¢n: Cambiamos, si se puede, a la sala oeste.
************************************************************/

void CambiaASalaOeste (BITMAP **fondo, BITMAP *(pnjFot[4]), int *x, int *y,
                       TSALA *sala, PALETTE *pal, TLISTACUAD *pantalla,
                       List objetos,char mapaColisiones[640][380])
{
 int k;

 if (sala->enlaces[2][3])
 { // si se puede cambiar
  if (strcmp (sala->pnj,"NO"))
  { // si hay PNJ se destruye
   for (k=0 ; k<=3; k++)
       destroy_bitmap (pnjFot[k]);
  }
  destroy_bitmap (*fondo);                    // Destruimos todo,
  *pantalla = MoverASala ( *pantalla, 'o');   // y cargamos la nueva sala
  *sala = DameSalaRef (*pantalla);
  *fondo = load_bitmap (sala->imagen,*pal);   // y sus elementos...
  set_palette (*pal);
  CargaFotPnj (*sala,pnjFot);
  DibujaParedes (*fondo,sala->pared);
  CreaMapaColisiones (*sala,mapaColisiones,objetos); // y el mapa de colisiones
  *x = 590;
 }
}



/***********************************************************

        Nombre: CambiaASalaEste
        Tipo: void
        Par metros de entrada: fondo, fotogramas PNJ, coordenadas,
                   sala, paleta, pantalla, lista de objetos, mapa de
                   colisiones.
        Descripci¢n: Cambiamos, si se puede, a la sala este.
************************************************************/

void CambiaASalaEste (BITMAP **fondo, BITMAP *(pnjFot[4]), int *x, int *y,
                      TSALA *sala, PALETTE *pal, TLISTACUAD *pantalla,
                      List objetos,char mapaColisiones[640][380])
{
 int k;

 if (sala->enlaces[2][1])
 {
  if (strcmp (sala->pnj,"NO"))
  {
   for (k=0 ; k<=3; k++)
       destroy_bitmap (pnjFot[k]);
  }
  destroy_bitmap (*fondo);
  *pantalla = MoverASala ( *pantalla, 'e');
  *sala = DameSalaRef (*pantalla);
  *fondo = load_bitmap (sala->imagen,*pal);    // Igual que con la oeste...
  set_palette (*pal);
  CargaFotPnj (*sala,pnjFot);
  DibujaParedes (*fondo,sala->pared);
  CreaMapaColisiones (*sala,mapaColisiones,objetos);
  *x = 10;
 }
}



/***********************************************************

        Nombre: CambiaASalaNorte
        Tipo: void
        Par metros de entrada: fondo, fotogramas PNJ, coordenadas,
                   sala, paleta, pantalla, lista de objetos, mapa de
                   colisiones.
        Descripci¢n: Cambiamos, si se puede, a la sala norte.
************************************************************/

void CambiaASalaNorte (BITMAP **fondo, BITMAP *(pnjFot[4]), int *x, int *y,
                       TSALA *sala, PALETTE *pal, TLISTACUAD *pantalla,
                       List objetos,char mapaColisiones[640][380])

{
 int k;

 if (sala->enlaces[2][0])
 {
  if (strcmp (sala->pnj,"NO"))
  {
   for (k=0 ; k<=3; k++)
       destroy_bitmap (pnjFot[k]);
  }
  destroy_bitmap (*fondo);
  *pantalla = MoverASala ( *pantalla, 'n');
  *sala = DameSalaRef (*pantalla);
  *fondo = load_bitmap (sala->imagen,*pal);  // Igual que las anteriores...
  set_palette (*pal);
  CargaFotPnj (*sala,pnjFot);
  DibujaParedes (*fondo,sala->pared);
  CreaMapaColisiones (*sala,mapaColisiones,objetos);
  *y = 300;
 }
}



/***********************************************************

        Nombre: CambiaASalaSur
        Tipo: void
        Par metros de entrada: fondo, fotogramas PNJ, coordenadas,
                   sala, paleta, pantalla, lista de objetos, mapa de
                   colisiones.
        Descripci¢n: Cambiamos, si se puede, a la sala sur.
************************************************************/

void CambiaASalaSur (BITMAP **fondo, BITMAP *(pnjFot[4]), int *x, int *y,
                     TSALA *sala, PALETTE *pal, TLISTACUAD *pantalla,
                     List objetos,char mapaColisiones[640][380])

{
 int k;

 if (sala->enlaces[2][2])
 {
  if (strcmp (sala->pnj,"NO"))
  {
   for (k=0 ; k<=3; k++)
       destroy_bitmap (pnjFot[k]);
  }
  destroy_bitmap (*fondo);
  *pantalla = MoverASala ( *pantalla, 's');
  *sala = DameSalaRef (*pantalla);
  *fondo = load_bitmap (sala->imagen,*pal);  // Igual que las anteriores...
  set_palette (*pal);
  CargaFotPnj (*sala,pnjFot);
  DibujaParedes (*fondo,sala->pared);
  CreaMapaColisiones (*sala,mapaColisiones,objetos);
  *y = 10;
 }
}



/***********************************************************

        Nombre: CargaIniciales
        Tipo: void
        Par metros de entrada: musicG, music, doublebuffer, texto, objetos,
                   sala, mapaColisiones, fondo, personaje, fot, pnjFot
                   pantalla, pal.
        Descripci¢n: Carga todo lo necesario para comenzar a jugar la
                     pantalla.
************************************************************/

void CargaIniciales (char musicG[13],MIDI **music,BITMAP **doublebuffer,
                     BITMAP **texto, List *objetos, TSALA *sala,
                     char mapaColisiones[640][380],BITMAP **fondo,
                     TPERSONAJE *personaje, BITMAP *(fot[28]),
                     BITMAP *pnjFot[4],TLISTACUAD pantalla,PALETTE *pal)
{
 *music = load_midi (musicG);               // M£sica
 play_midi (*music,TRUE);
 text_mode (-1);
 *doublebuffer = create_bitmap (640,480);   // Doble buffer
 *texto = create_bitmap (300,30);
 clear_to_color (*texto,9);                 // texto de salida
 textprintf (*texto,font,10,1,254,"¨Seguro que quieres salir? S/N");
 clear (*doublebuffer);
 *objetos = CargaFicheroObjetos();          // lista de objetos
 *sala = DameSalaRef (pantalla);            // sala
 CreaMapaColisiones (*sala,mapaColisiones,*objetos); // colisiones
 *fondo = load_bitmap (sala->imagen,*pal);  // fondo
 set_palette (*pal);
 CargaFotPlayer (personaje->fot,fot);       // jugador
 CargaFotPnj (*sala,pnjFot);                // PNJ

 return;
}



/***********************************************************

        Nombre: Si hay que cambiar
        Tipo: void
        Par metros de entrada: fondo, fotogramas PNJ, coordenadas,
                   sala, paleta, pantalla, lista de objetos, mapa de
                   colisiones.
        Descripci¢n: decide si hay que cambiar a alguna sala.
************************************************************/

void SiHayQueCambiar (BITMAP **fondo, BITMAP *(pnjFot[4]), int *x, int *y,
                     TSALA *sala, PALETTE *pal, TLISTACUAD *pantalla,
                     List objetos,char mapaColisiones[640][380])
{
   if (*x>=0 && *x<=8) // Si estamos en uno de los bordes...
      CambiaASalaOeste (fondo, pnjFot, x, y, sala, pal, pantalla,
                       objetos,mapaColisiones); //... tal vez cambiemos
   if (*x>=592 && *x<=600)
      CambiaASalaEste (fondo, pnjFot, x, y, sala, pal, pantalla,
                      objetos,mapaColisiones);
   if (*y>=0 && *y<=8)
      CambiaASalaNorte (fondo, pnjFot, x, y, sala, pal, pantalla,
                       objetos,mapaColisiones);
   if (*y>=302 && *y<=310)
      CambiaASalaSur (fondo, pnjFot, x, y, sala, pal, pantalla,
                      objetos,mapaColisiones);
}



/***********************************************************

        Nombre: JuegoEnSi
        Tipo: int
        Par metros de entrada: personaje, pantalla, musicG, musicC,
                   codActual (c¢digo de la pantalla actual), x, y.
        Descripci¢n: es el motor del juego. Desarrolla toda la pantalla,
                     hasta que la terminemos, decidamos salir o el personaje
                     muera, y devuelve la raz¢n de la salida.
************************************************************/

int JuegoEnSi (TPERSONAJE *personaje, TLISTACUAD pantalla, char musicG[13],
               char musicC[13], int codActual, int x, int y)
{
 BITMAP *doublebuffer,*fondo,*texto;
 BITMAP *(fot[28]),*(pnjFot[4]);
 List objetos;
 int i=0,m;
 TSALA sala;
 char mapaColisiones[640][380];
 PALETTE pal;
 MIDI *music;


 CargaIniciales (musicG,&music,&doublebuffer,&texto,&objetos,&sala,
                 mapaColisiones,&fondo,personaje,fot,pnjFot,pantalla,&pal);
 DibujaParedes (fondo,sala.pared); // en fondo tenemos ya la parte est tica
 while (!key[KEY_S] && sala.codigo != 999 && personaje->carac[3])
 { // Mientras no se pulse s, o no sea la £ltima sala o estemos vivos
  while (!key[KEY_X] && sala.codigo != 999 && personaje->carac[3])
  { // Mientras no se pulse x, o no sea la £ltima sala o estemos vivos
   blit (fondo,doublebuffer,0,0,0,0,640,380);
   DibujaPuertas (doublebuffer,sala.enlaces[0]);
   DibujaObjetos (objetos,sala,doublebuffer);
   DibujaPnj (sala,pnjFot,doublebuffer,i/7);    // Construimos el buffer
   MuevePlayer (&x,&y,&i,mapaColisiones,&sala,pantalla,personaje,objetos,
                codActual,doublebuffer); // Nos movemos
   draw_sprite (doublebuffer,fot[i],x,y); // dibujamos al personaje
   DibujaRecuadro (*personaje, sala, doublebuffer,fot[i]); // y el cuadro
   blit (doublebuffer,screen,0,0,0,0,640,480); // volcado a pantalla
   if (m = HayCombate (sala))
   { // si hay combate
    Combate (sala,personaje, m, musicC, doublebuffer); // luchamos
    play_midi (music,TRUE); // vuelve la m£sica
    set_palette (pal); // y la paleta
   }
   SiHayQueCambiar (&fondo, pnjFot, &x, &y, &sala, &pal, &pantalla,
                    objetos,mapaColisiones); // ¨cambiamos de sala?
   if (sala.codigo == 999)
      CombateFinal (personaje,doublebuffer,codActual); // ¨malo final?
  }
  if (key[KEY_X]) // si queremos salir, confirmaci¢n
  {
   blit (texto,screen,0,0,170,200,300,30);
   readkey();
  }
 }
 DestruyeTodo (fondo,doublebuffer,texto,pnjFot,fot,&objetos,music,&pantalla);
 if (key[KEY_S]) return 2; // voluntario
 else if (!personaje->carac[3]) return 1; // muerto
 else if (sala.codigo == 999) return 3; // terminado
}



/***********************************************************

        Nombre: Muestra
        Tipo: void
        Par metros de entrada:fich, doublebuffer, xi, yi
        Descripci¢n: muestra el fichero de cr‚ditos, usando buffer, y con
                     coordenadas base xi yi.
************************************************************/

void Muestra (FILE *fich,BITMAP *doublebuffer,int xi, int yi)
{
 char palabra[26];
 int x = xi, y = yi, temp;

 fscanf (fich,"%s",palabra);
 blit (doublebuffer,screen,0,0,0,0,640,480);
 while (strcmp(palabra,"<end>"))
 { // mientras no haya que terminar...
  if (strcmp(palabra,"<cl>")==0)
  {                                   //Cambio de linea
   x=xi;
   y+=12;
  }
  else if(strcmp(palabra,"<wait>"))
  {                                   // Palabra normal
   textprintf(screen,font,x,y,215,"%s",palabra);
   x+=(text_length(font,palabra)+8);
  }
  else
  { // si no, es <wait>
   fscanf (fich,"%d",&temp);          // Esperar
   rest (temp);
   blit (doublebuffer,screen,0,0,0,0,640,480);
   x = xi;
   y = yi;
  }
  fscanf (fich,"%s",palabra); // leemos la palabra siguiente
 }

 return;
}



/***********************************************************

        Nombre: Creditos
        Tipo: void
        Par metros de entrada: ninguno
        Descripci¢n: Muestra los cr‚ditos del juego
************************************************************/

void Creditos ()
{
 BITMAP *doublebuffer;
 BITMAP *aMostrar;
 MIDI *music;
 PALETTE pal;
 FILE *actual;

 music = load_midi ("credits.mid");             // m£sica...
 doublebuffer = create_bitmap (640,480);
 clear (doublebuffer);
 aMostrar = load_bitmap ("FF92LOGO.bmp",pal);
 set_palette (pal);
 draw_sprite (doublebuffer,aMostrar,50,0);      // Creamos los fondos
 destroy_bitmap (aMostrar);
 play_midi (music,TRUE);
 actual = fopen ("creditos.cdt","r");           // y mostramos los archivos
 Muestra (actual,doublebuffer,300,200);         // de cr‚ditos
 fclose (actual);
 actual = fopen ("musics.cdt","r");
 Muestra (actual,doublebuffer,50,200);
 fclose (actual);
 aMostrar = load_bitmap ("BDKS0000.bmp",pal);   // fondo...
 clear (doublebuffer);
 draw_sprite (doublebuffer,aMostrar,490,150);
 destroy_bitmap (aMostrar);
 actual = fopen ("bdkthank.cdt","r");           // cr‚ditos...
 Muestra (actual,doublebuffer,100,150);
 fclose (actual);
 clear (doublebuffer);
 aMostrar = load_bitmap ("TXSS0000.bmp",pal);
 draw_sprite (doublebuffer,aMostrar,50,150);
 destroy_bitmap (aMostrar);
 actual = fopen ("txsthank.cdt","r");
 Muestra (actual,doublebuffer,175,150);
 fclose (actual);
 aMostrar = load_bitmap ("BDKS0000.bmp",pal);
 draw_sprite (doublebuffer,aMostrar,490,150);
 destroy_bitmap (aMostrar);
 actual = fopen ("conthank.cdt","r");
 Muestra (actual,doublebuffer,175,150);
 fclose (actual);                              // terminamos
 textprintf (screen,font,280,200,215,"THE END");
 textprintf (screen,font,0,120,215,"txusin@euskalnet.net");
 textprintf (screen,font,450,120,215,"bardok@euskalnet.net");
 clear_keybuf();
 readkey();                                  // y esperamos
 destroy_midi (music);
 destroy_bitmap (doublebuffer);

 return;
}



/***********************************************************

        Nombre: FinalizaTodo
        Tipo: void
        Par metros de entrada: ninguno
        Descripci¢n: sale se Allegro
************************************************************/

void FinalizaTodo ()
{
 fade_out (1);        // fundido de pantalla
 allegro_exit();
}



/***********************************************************

        Nombre: MenuInicial
        Tipo: int
        Par metros de entrada: ninguno
        Descripci¢n: muestra el men£ inicial y nos hace escoger
                     opci¢n.
************************************************************/

int MenuInicial ()
{
 BITMAP *logo,*doublebuffer;
 PALETTE pal;
 int i=1;
 MIDI *music;

 music = load_midi ("menu.mid");
 play_midi (music,TRUE);
 clear (screen);
 logo = load_bitmap ("FF92logo.bmp",pal);  // Cargamos fondo y m£sica
 doublebuffer = create_bitmap (640,480);   //
 clear (doublebuffer);                     //
 set_palette (pal);
 draw_sprite (doublebuffer,logo,50,50);
 destroy_bitmap (logo);
 while (!key[KEY_ENTER])
 { // mientras no se pulse enter
  textprintf (doublebuffer,font,300,250,(i==1)?215:86,"JUEGO NUEVO");
  textprintf (doublebuffer,font,300,265,(i==2)?215:86,"CARGAR PARTIDA");
  textprintf (doublebuffer,font,300,280,(i==3)?215:86,"SALIR");
  blit (doublebuffer,screen,0,0,0,0,640,480); // Como siempre el color
  if (key[KEY_UP])                            // depende de la selecci¢n.
  {     // selecci¢n anterior
   i--;
   clear_keybuf();
  }
  else if (key[KEY_DOWN])
  {     // selecci¢n siguiente
   i++;
   clear_keybuf();
  }
  i = (i==4)?3:i;     // control de l¡mites
  i = (i==0)?1:i;
 }
 clear_keybuf();
 destroy_bitmap (doublebuffer);
 destroy_midi (music);

 return i;  // devolvemos la selecci¢n
}



/***********************************************************

        Nombre: main
        Tipo: int
        Par metros de entrada: ninguno
        Descripci¢n: funci¢n principal, que controla cuando hay que
                     salir.
************************************************************/

int main (void)
{
 TPERSONAJE personaje;
 TLISTACUAD pantalla;
 int poque, tipo=1,i,x,y;
 char musicGame[13],musicCombat[13];

 InicializaTodo ();        // Inicializaci¢n
 Logos();                  // Logos iniciales
 while (tipo != 3)
 {                         // Mientras no queramos salir
  tipo = MenuInicial();    // Men£
  poque = 0;
  if (tipo == 1)           // Partida nueva
  {
   Intro();
   personaje = SeleccionPers ();
   pantalla = SeleccionPantallaInic (musicGame,musicCombat,&x,&y);
   i=1;
  }
  else if (tipo ==2)       // Cargar Partida
      pantalla = SeleccionACargar (&personaje,&i,musicGame,musicCombat,&x,&y);
  while (i<=NUMPANTALLAS && i && poque != 1 && poque != 2 && tipo != 3)
  { // mientras no acabemos, y la pantalla no sea cero, y no estemos
    // muertos ni queramos salir, jugamos
   poque = JuegoEnSi (&personaje,pantalla,musicGame,musicCombat,i,x,y);
   if (poque==3)
   {    // si hemos pasado de pantalla
    i++;
    if (i<=NUMPANTALLAS) // y no hemos terminado, la siguiente
       pantalla = CargaPantallaI (i,musicGame,musicCombat,&x,&y,&personaje);
   }
  } // END while i<=NUMPANTALLAS...
  if (poque == 1) Mueto(); // Estamos muertos...
  else if (poque == 3)
  {                  // Si hemos terminado
   Final(personaje); // El final y los cr‚ditos
   Creditos();       //
  }
 }
 FinalizaTodo ();    // Terminamos

 return 0;
}
