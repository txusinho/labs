/************************************************************************

 combates

*************************************************************************/


#include "combate.h"



/***********************************************************

        Nombre: HayCombate
        Tipo: entero
        Par metros de entrada: sala
        Descripci¢n: determina de manera aleatoria si ha de producirse un
                     combate. Devuelve cero o el c¢digo de un enemigo de la
                     sala.
************************************************************/

int HayCombate (TSALA sala)
{
 if (strcmp (sala.fondoCombate,"NO"))
    if ( (random () % 165)== 50)
       return sala.codMalos[random () % 5];
 return 0;
}



/***********************************************************

        Nombre: CargaFotPlayerC
        Tipo: void
        Par metros de entrada: base, base del nombre de los fotogramas del
                   personaje. fot, array de apuntadores a BITMAP.
        Descripci¢n: carga todos los fotogramas de combate del personaje, y
                     los devuelve en fot.

************************************************************/

void CargaFotPlayerC (char *base,BITMAP *(fot[12]))
{
 char temp2[13];
 PALETTE pal;

 strcpy (temp2,base); // Copiamos en temp2 la base...
 fot[0] = load_bitmap (strcat (temp2,"C0000.bmp"),pal); // y le encadenamos el
 strcpy (temp2,base);                                   // resto del nombre de
 fot[1] = load_bitmap (strcat (temp2,"C0001.bmp"),pal); // la imagen...
 strcpy (temp2,base);
 fot[2] = load_bitmap (strcat (temp2,"C0002.bmp"),pal);
 strcpy (temp2,base);
 fot[3] = load_bitmap (strcat (temp2,"C0003.bmp"),pal);
 strcpy (temp2,base);
 fot[4] = load_bitmap (strcat (temp2,"C0004.bmp"),pal);
 strcpy (temp2,base);
 fot[5] = load_bitmap (strcat (temp2,"C0005.bmp"),pal);
 strcpy (temp2,base);
 fot[6] = load_bitmap (strcat (temp2,"C0006.bmp"),pal);
 strcpy (temp2,base);
 fot[7] = load_bitmap (strcat (temp2,"C0007.bmp"),pal);
 fot[8] = load_bitmap ("rayo.bmp",pal);
 fot[9] = load_bitmap ("fuego.bmp",pal);
 fot[11] = load_bitmap ("Bahamut.bmp",pal);

 return;
}



/***********************************************************

        Nombre: CargaFotPnjC
        Tipo: void
        Par metros de entrada:base del nombre de los fotogramas. fot: array
                   de apuntadores a BITMAP. malo: enemigo.
        Descripci¢n: Carga los fotogramas del enemigo, dependiendo de cu les
                     sean las magias que pueda hacer. Los devuelve en fot.

************************************************************/

void CargaFotPnjC (char *base,BITMAP *(fot[12]),TMALO malo)
{
 char temp2[13];
 PALETTE pal;

 strcpy (temp2,base); //Copiamos en temp2 la base...
 fot[0] = load_bitmap (strcat (temp2,"C0000.bmp"),pal); // y le encadenamos
                                                        // el resto del nombre
 strcpy (temp2,base);                                   // de la imagen.
 fot[1] = load_bitmap (strcat (temp2,"C0001.bmp"),pal);
 strcpy (temp2,base);
 fot[2] = load_bitmap (strcat (temp2,"C0002.bmp"),pal);
 if (malo.magias[0].tiene) // Si puede hacer la magia 0...
 {
  strcpy (temp2,base);
  fot[3] = load_bitmap (strcat (temp2,"C0003.bmp"),pal);
  strcpy (temp2,base);
  fot[4] = load_bitmap (strcat (temp2,"C0004.bmp"),pal);
 }
 if (malo.magias[1].tiene ||malo.magias[3].tiene ||
    malo.magias[4].tiene ||malo.magias[5].tiene)
 { // Si puede hacer las magias 1, 3, 4, 5...
  strcpy (temp2,base);
  fot[5] = load_bitmap (strcat (temp2,"C0005.bmp"),pal);
 }
 if (malo.magias[2].tiene)
 { // Si puede hacer la magia 2...
  strcpy (temp2,base);
  fot[6] = load_bitmap (strcat (temp2,"C0006.bmp"),pal);
  fot[7] = load_bitmap (malo.magias[2].fot,pal); // carga imagen propia...
 }
 if (malo.magias[3].tiene) // la 3...
   fot[8] = load_bitmap (malo.magias[3].fot,pal);// carga imagen propia...
 if (malo.magias[4].tiene)
   fot[9] = load_bitmap (malo.magias[4].fot,pal);// carga imagen propia...
 if(malo.magias[5].tiene)
   fot[11] = load_bitmap (malo.magias[5].fot,pal);// carga imagen propia...


 return;
}



/***********************************************************

        Nombre: Tirada
        Tipo: entero (int)
        Par metros de entrada: aFavor: dados a favor. enContra: dados en contra
        Descripci¢n: realiza una tirada opuesta de dados a dificultad cinco
                     para la tirada a favor, y siete en contra.

************************************************************/

int Tirada (int aFavor,int enContra)
{
 int res = 0,i;

 for (i=1;i<=aFavor;i++)
     if (((random()%10)+1) >= 5) res++; // Sumamos los ‚xitos a favor
 for (i=1;i<=enContra;i++)
     if (((random()%10)+1) >= 7) res--; // Restamos los ‚xitos en contra

 if (res<0) res = 0;


 return res;
}



/***********************************************************

        Nombre: Pifia
        Tipo: void
        Par metros de entrada: resultado, de tipo entero. doublebuffer,
                   BITMAP.
        Descripci¢n: si resultado es cero escribir  un mensaje aleatorio
                     en doblebuffer. Saca el contenido de doublebuffer en
                     pantalla.
                     Los mensajes son para el "bueno".

************************************************************/

void Pifia ( int resultado, BITMAP *doublebuffer )
{
 int temp;

 if (resultado == 0)
 {
  rect (doublebuffer,95,95,495,115,215);   // Rect ngulo que rodear  el texto
  rectfill (doublebuffer,96,96,494,114,10);
  temp = (random()%8);
  switch (temp)
  {
   case (0) :  textprintf (doublebuffer, font, 100, 100, 200,"%s",
               "Hasta mi abuela pega m s fuerte");
               break;
   case (1) :  textprintf (doublebuffer, font, 100, 100, 200,"%s",
               "Jaaaaaaaa, pifia, patan");
               break;
   case (2) :  textprintf (doublebuffer, font, 100, 100, 200,"%s",
               "Vaya heroe de mis narices");
               break;
   case (3) :  textprintf (doublebuffer, font, 100, 100, 200,"%s",
               "Menos mal que de heroes no vive la humanidad...");
               break;
   case (4) :  textprintf (doublebuffer, font, 100, 100, 200,"%s",
               "Uuuuuuui, casi le pegas");
               break;
   case (5) :  textprintf (doublebuffer, font, 100, 100, 200,"%s",
               "Seras...");
               break;
   case (6) :  textprintf (doublebuffer, font, 100, 100, 200,"%s",
               "En fin...PIFIA!");
               break;
   case (7) :  textprintf (doublebuffer, font, 100, 100, 200,"%s",
               "No Comment");
               break;
  }
  blit (doublebuffer,screen,0,0,0,0,640,480); // Sacamos el texto en pantalla
  rest (2000); // Damos tiempo a leerlo (dos segundos)
 }
}



/***********************************************************

        Nombre: PifiaM
        Tipo: void
        Par metros de entrada: resultado, de tipo entero. doublebuffer,
                   BITMAP.
        Descripci¢n: si resultado es cero escribir  un mensaje aleatorio
                     en doblebuffer. Saca el contenido de doublebuffer en
                     pantalla.
                     Esta vez los mensajes son para el "malo".

************************************************************/

void PifiaM ( int resultado, BITMAP *doublebuffer )
{
 int temp;

 if (resultado == 0)
 {
  rect (doublebuffer,95,95,495,115,215);
  rectfill (doublebuffer,96,96,494,114,10); // Rect ngulo...
  temp = (random()%8);
  switch (temp)
  {
   case (0) :  textprintf (doublebuffer, font, 100, 100, 400,"%s",
               "Como se nota que es al malo, eh?");
               break;
   case (1) :  textprintf (doublebuffer, font, 100, 100, 400,"%s",
               "Como te mate unen migo asi...");
               break;
   case (2) :  textprintf (doublebuffer, font, 100, 100, 400,"%s",
               "No me extra¤a que se haya vuelto malo...");
               break;
   case (3) :  textprintf (doublebuffer, font, 100, 100, 400,"%s",
               "Ser ...");
               break;
   case (4) :  textprintf (doublebuffer, font, 100, 100, 400,"%s",
               "Uuuuuuui, casi te pega");
               break;
   case (5) :  textprintf (doublebuffer, font, 100, 100, 400,"%s",
               "Acojonado, eh?");
               break;
   case (6) :  textprintf (doublebuffer, font, 100, 100, 400,"%s",
               "PIFIA!");
               break;
   case (7) :  textprintf (doublebuffer, font, 100, 100, 400,"%s",
               "Ser  pringadillo...");
               break;
  }
  blit (doublebuffer,screen,0,0,0,0,640,480); // Volcamos a pantalla...
  rest (2000); // ... y esperamos
 }
}



/***********************************************************

        Nombre: AtaqueBase
        Tipo: void
        Par metros de entrada: doublebuffer, BITMAP. fondo, BITMAP. personaje,
                   personaje jugador. fot, fotogramas del personaje jugador.
                   malo, PNJ. pnjFot, fotogramas del PNJ.
        Descripci¢n: Realiza el ataque base al "malo".

************************************************************/

void AtaqueBase (BITMAP *doublebuffer,BITMAP *fondo,TPERSONAJE *personaje,
                 BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]))
{
 int resultado;

 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[3],30+pnjFot[0]->w,480-(100+fot[3]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480); // Nos lanzamos...
 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[1],30,480-(100+pnjFot[1]->h));
 draw_sprite (doublebuffer,fot[4],30+pnjFot[0]->w,480-(100+fot[4]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480); // Le pegamos...
 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[3],30+pnjFot[0]->w,480-(100+fot[3]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480); // Volvemos...
 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480); // ya.
 resultado = Tirada (personaje->carac[0],malo->carac[1]); // Calculamos el
                                                          // da¤o...
 textprintf (screen, font, 30+pnjFot[0]->w, 380-pnjFot[0]->h,215,"%d",
             resultado);                                  // ... lo mostramos
 Pifia (resultado,doublebuffer);
 malo->carac[3] -= resultado;           // Modificamos la vida del malo.
 rest(500);

 return;
}



/***********************************************************

        Nombre: AtaqueBaseM
        Tipo: void
        Par metros de entrada: doublebuffer, BITMAP. fondo, BITMAP. personaje,
                   personaje jugador. fot, fotogramas del personaje jugador.
                   malo, PNJ. pnjFot, fotogramas del PNJ.
        Descripci¢n: Realiza el ataque base al "bueno".

************************************************************/

void AtaqueBaseM (BITMAP *doublebuffer,BITMAP *fondo,TPERSONAJE *personaje,
                 BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]))
{
 int resultado;

 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[3],500-pnjFot[3]->w,480-(100+pnjFot[3]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[4],500-pnjFot[4]->w,480-(100+pnjFot[4]->h));
 draw_sprite (doublebuffer,fot[1],500,480-(100+fot[1]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[3],500-pnjFot[3]->w,480-(100+pnjFot[3]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 resultado = Tirada (malo->carac[0],personaje->carac[1]);
 textprintf (screen, font, 500, 380-fot[0]->h,215,"%d",resultado);
 PifiaM (resultado,doublebuffer);
 personaje->carac[3] -= resultado;
 rest(500);

 return;
}



/***********************************************************

        Nombre: Curarse
        Tipo: void
        Par metros de entrada: doublebuffer, BITMAP. fondo, BITMAP. personaje,
                   personaje jugador. fot, fotogramas del personaje jugador.
                   malo, PNJ. pnjFot, fotogramas del PNJ.
        Descripci¢n: En bueno se cura...

************************************************************/

void Curarse (BITMAP *doublebuffer,BITMAP *fondo,TPERSONAJE *personaje,
              BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]))
{
 int resultado;

 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[5],500,480-(100+fot[5]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (400);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 resultado = Tirada (personaje->carac[1],0);
 textprintf (screen, font, 500, 380-fot[0]->h,215,"%d",
             resultado);
 personaje->carac[3] += resultado;
 if (personaje->carac[3] > personaje->carac[4])
    personaje->carac[3] = personaje->carac[4];
 rest(500);

 return;
}



/***********************************************************

        Nombre: CurarseM
        Tipo: void
        Par metros de entrada: doublebuffer, BITMAP. fondo, BITMAP. personaje,
                   personaje jugador. fot, fotogramas del personaje jugador.
                   malo, PNJ. pnjFot, fotogramas del PNJ.
        Descripci¢n: el "malo" se cura

************************************************************/

void CurarseM (BITMAP *doublebuffer,BITMAP *fondo,TPERSONAJE *personaje,
              BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]))
{
 int resultado;

 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[5],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[5]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (400);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 resultado = Tirada (malo->carac[1],0);
 textprintf (screen, font, 30+pnjFot[0]->w, 380-pnjFot[0]->h,215,"%d",
             resultado);
 malo->carac[3] += resultado;
 if (malo->carac[3] > malo->carac[4])
    malo->carac[3] = malo->carac[4];
 rest(500);

 return;
}



/***********************************************************

        Nombre: AtaqueBestia
        Tipo: void
        Par metros de entrada: doublebuffer, BITMAP. fondo, BITMAP. personaje,
                   personaje jugador. fot, fotogramas del personaje jugador.
                   malo, PNJ. pnjFot, fotogramas del PNJ.
        Descripci¢n: Realiza el ataque bestia al "malo".

************************************************************/

void AtaqueBestia (BITMAP *doublebuffer,BITMAP *fondo,TPERSONAJE *personaje,
                   BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]))
{
 int resultado;

 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[6],500,480-(100+fot[6]->h));
 draw_sprite (doublebuffer,fot[7],500-fot[7]->w,480-(125+fot[6]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[1],30,480-(100+pnjFot[1]->h));
 draw_sprite (doublebuffer,fot[6],500,480-(100+fot[6]->h));
 draw_sprite (doublebuffer,fot[7],30+pnjFot[1]->w,480-(125+fot[6]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 resultado = Tirada (personaje->carac[0]+personaje->carac[2],malo->carac[1]);
                    // fuerza + velocidad  ||  resitencia
 textprintf (screen, font, 30+pnjFot[0]->w, 380-pnjFot[0]->h,215,"%d",
             resultado);
 Pifia (resultado,doublebuffer);
 malo->carac[3] -= resultado;
 rest(500);

 return;
}



/***********************************************************

        Nombre: AtaqueBestiaM
        Tipo: void
        Par metros de entrada: doublebuffer, BITMAP. fondo, BITMAP. personaje,
                   personaje jugador. fot, fotogramas del personaje jugador.
                   malo, PNJ. pnjFot, fotogramas del PNJ.
        Descripci¢n: Realiza el ataque bestia al "bueno".

************************************************************/

void AtaqueBestiaM (BITMAP *doublebuffer,BITMAP *fondo,TPERSONAJE *personaje,
                   BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]))
{
 int resultado;

 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[6],30,480-(100+pnjFot[6]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 draw_sprite (doublebuffer,pnjFot[7],30+pnjFot[7]->w,480-(125+pnjFot[6]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[6],30,480-(100+pnjFot[6]->h));
 draw_sprite (doublebuffer,fot[1],500,480-(100+fot[1]->h));
 draw_sprite (doublebuffer,pnjFot[7],500-pnjFot[1]->w,480-(125+pnjFot[6]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 resultado = Tirada (malo->carac[0]+malo->carac[2],personaje->carac[1]);
                    // Fuerza + velocidad || resistencia
 textprintf (screen, font, 500, 380-fot[0]->h,215,"%d",resultado);
 PifiaM (resultado,doublebuffer);
 personaje->carac[3] -= resultado;
 rest(500);

 return;
}



/***********************************************************

        Nombre: Rayo
        Tipo: void
        Par metros de entrada: doublebuffer, BITMAP. fondo, BITMAP. personaje,
                   personaje jugador. fot, fotogramas del personaje jugador.
                   malo, PNJ. pnjFot, fotogramas del PNJ.
        Descripci¢n: Realiza la magia rayo al "malo".

************************************************************/

void Rayo (BITMAP *doublebuffer,BITMAP *fondo,TPERSONAJE *personaje,
           BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]))
{
 int resultado;

 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[5],500,480-(100+fot[5]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[1],30,480-(100+pnjFot[1]->h));
 draw_sprite (doublebuffer,fot[5],500,480-(100+fot[5]->h));
 draw_sprite (doublebuffer,fot[8],70,0);
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (600);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 resultado = Tirada (personaje->carac[0]+((personaje->carac[2]) << 1)
                    ,malo->carac[1]);
                    // fuerza + (velocidad x 2)  || resistencia
 textprintf (screen, font, 30+pnjFot[0]->w, 380-pnjFot[0]->h,215,"%d",
             resultado);
 Pifia (resultado,doublebuffer);
 malo->carac[3] -= resultado;
 rest(500);

 return;
}



/***********************************************************

        Nombre: Magia1M
        Tipo: void
        Par metros de entrada: doublebuffer, BITMAP. fondo, BITMAP. personaje,
                   personaje jugador. fot, fotogramas del personaje jugador.
                   malo, PNJ. pnjFot, fotogramas del PNJ.
        Descripci¢n: Realiza la magia 1 del "malo".

************************************************************/

void Magia1M (BITMAP *doublebuffer,BITMAP *fondo,TPERSONAJE *personaje,
           BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]))
{
 int resultado;

 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[5],30,480-(100+pnjFot[5]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[5],30,480-(100+pnjFot[5]->h));
 draw_sprite (doublebuffer,fot[1],500,480-(100+fot[1]->h));
 draw_sprite (doublebuffer,pnjFot[8],540,0);
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (600);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 resultado = Tirada (malo->carac[0]+((malo->carac[2]) << 1)
                         ,personaje->carac[1]);
                    // fuerza + (velocidad x 2)  || resistencia
 textprintf (screen, font, 500, 380-fot[0]->h,215,"%d",resultado);
 PifiaM (resultado,doublebuffer);
 personaje->carac[3] -= resultado;
 rest(500);

 return;
}



/***********************************************************

        Nombre: Fuego
        Tipo: void
        Par metros de entrada: doublebuffer, BITMAP. fondo, BITMAP. personaje,
                   personaje jugador. fot, fotogramas del personaje jugador.
                   malo, PNJ. pnjFot, fotogramas del PNJ.
        Descripci¢n: Realiza la magia fuego al "malo".

************************************************************/

void Fuego (BITMAP *doublebuffer,BITMAP *fondo,TPERSONAJE *personaje,
            BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]))
{
 int resultado;

 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[5],500,480-(100+fot[5]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[1],30,480-(100+pnjFot[1]->h));
 draw_sprite (doublebuffer,fot[5],500,480-(100+fot[5]->h));
 draw_sprite (doublebuffer,fot[9],70,380-fot[9]->h);
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (600);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 resultado = Tirada (((personaje->carac[0]+personaje->carac[2]) << 1)
                    ,malo->carac[1]);
                    // (fuerza + velocidad) x 2   || resistencia
 textprintf (screen, font, 30+pnjFot[0]->w, 380-pnjFot[0]->h,215,"%d",
             resultado);
 Pifia (resultado,doublebuffer);
 malo->carac[3] -= resultado;
 rest(500);

 return;
}



/***********************************************************

        Nombre: Magia2M
        Tipo: void
        Par metros de entrada: doublebuffer, BITMAP. fondo, BITMAP. personaje,
                   personaje jugador. fot, fotogramas del personaje jugador.
                   malo, PNJ. pnjFot, fotogramas del PNJ.
        Descripci¢n: Realiza la segunda magia del malo al "bueno".

************************************************************/

void Magia2M (BITMAP *doublebuffer,BITMAP *fondo,TPERSONAJE *personaje,
              BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]))
{
 int resultado;

 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[5],30,480-(100+pnjFot[5]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[5],30,480-(100+pnjFot[5]->h));
 draw_sprite (doublebuffer,fot[1],500,480-(100+fot[1]->h));
 draw_sprite (doublebuffer,pnjFot[9],540,380-(pnjFot[9]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (600);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 resultado = Tirada (((malo->carac[0]+malo->carac[2]) << 1)
                        ,personaje->carac[1]);
                    // (fuerza + velocidad) x 2   || resistencia
 textprintf (screen, font, 500, 380-fot[0]->h,215,"%d",resultado);
 PifiaM (resultado,doublebuffer);
 personaje->carac[3] -= resultado;
 rest(500);

 return;
}



/***********************************************************

        Nombre: Bahamut
        Tipo: void
        Par metros de entrada: doublebuffer, BITMAP. fondo, BITMAP. personaje,
                   personaje jugador. fot, fotogramas del personaje jugador.
                   malo, PNJ. pnjFot, fotogramas del PNJ.
        Descripci¢n: Invoca al drag¢n Bahamut por parte del bueno...

************************************************************/

void Bahamut (BITMAP *doublebuffer,BITMAP *fondo,TPERSONAJE *personaje,
              BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]))
{
 int resultado;

 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[5],500,480-(100+fot[5]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (400);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[5],500,480-(100+fot[5]->h));
 draw_sprite (doublebuffer,fot[11],640-fot[11]->w,0);
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (400);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[1],30,480-(100+pnjFot[1]->h));
 draw_sprite (doublebuffer,fot[5],500,480-(100+fot[5]->h));
 draw_sprite (doublebuffer,fot[11],0,380-fot[11]->h);
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (400);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 resultado = Tirada (((personaje->carac[0]+personaje->carac[2])<<1)
                      +(personaje->carac[1]>>1),malo->carac[1]);
             // ((fuerza + velocidad) x 2) + resistencia / 2  || resistencia
 textprintf (screen, font, 30+pnjFot[0]->w, 380-pnjFot[0]->h,215,"%d",
             resultado);
 Pifia (resultado,doublebuffer);
 malo->carac[3] -= resultado;
 rest(500);

 return;
}



/***********************************************************

        Nombre: InvocacionM
        Tipo: void
        Par metros de entrada: doublebuffer, BITMAP. fondo, BITMAP. personaje,
                   personaje jugador. fot, fotogramas del personaje jugador.
                   malo, PNJ. pnjFot, fotogramas del PNJ.
        Descripci¢n: Realiza la invocaci¢n del malo sobre el bueno.

************************************************************/

void InvocacionM (BITMAP *doublebuffer,BITMAP *fondo,TPERSONAJE *personaje,
              BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]))
{
 int resultado;

 rest (200);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[5],30,480-(100+pnjFot[5]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (400);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[5],30,480-(100+pnjFot[5]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 draw_sprite (doublebuffer,pnjFot[11],0,0);
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (400);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[5],30,480-(100+pnjFot[5]->h));
 draw_sprite (doublebuffer,fot[1],500,480-(100+fot[1]->h));
 draw_sprite (doublebuffer,pnjFot[11],640-pnjFot[11]->w,380-pnjFot[11]->h);
 blit (doublebuffer,screen,0,0,0,0,640,480);
 rest (400);
 blit (fondo,doublebuffer,0,0,0,0,640,380);
 draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
 draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
 blit (doublebuffer,screen,0,0,0,0,640,480);
 resultado = Tirada (((malo->carac[0]+malo->carac[2])<<1)
                        +(malo->carac[1]>>1),personaje->carac[1]);
           // ((fuerza + velocidad) x 2) + resistencia / 2  ||  resistencia
 textprintf (screen, font, 500, 380-fot[0]->h,215,"%d",resultado);
 PifiaM (resultado,doublebuffer);
 personaje->carac[3] -= resultado;
 rest(500);

 return;
}



/***********************************************************

        Nombre: EjecutaAccion
        Tipo: void
        Par metros de entrada: i, entero con la selecci¢n. doublebuffer y
                   fondo, BITMAPs. Personaje y malo, con sus fotogramas.
                   Apuntador a entero con el tiempo para combates...
        Descripci¢n: ejecuta una acci¢n dependiendo del valor de i.
                     actualiza el contenido de tiempo.

************************************************************/

void EjecutaAccion (int i,BITMAP *doublebuffer,TPERSONAJE *personaje,
                 BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]),
                 int *tiempo,BITMAP *fondo)
{
 switch (i)
 {
  case (1): AtaqueBase (doublebuffer,fondo,personaje,fot,malo,pnjFot);
            *tiempo = 150;      // El tiempo es fijo para cada ataque.
            break;
  case (2): Curarse (doublebuffer,fondo,personaje,fot,malo,pnjFot);
            *tiempo = 350;
            break;
  case (3): AtaqueBestia (doublebuffer,fondo,personaje,fot,malo,pnjFot);
            *tiempo = 400;
            break;
  case (4): Rayo (doublebuffer,fondo,personaje,fot,malo,pnjFot);
            *tiempo = 450;
            break;
  case (5): Fuego (doublebuffer,fondo,personaje,fot,malo,pnjFot);
            *tiempo = 500;
            break;
  case (6): Bahamut (doublebuffer,fondo,personaje,fot,malo,pnjFot);
            *tiempo = 700;
            break;
 }
}



/***********************************************************

        Nombre: EjecutaAccionMalo
        Tipo: void
        Par metros de entrada: i, entero con la selecci¢n. doublebuffer y
                   fondo, BITMAPs. Personaje y malo, con sus fotogramas.
                   Apuntador a entero con el tiempo para combates...
        Descripci¢n: ejecuta una acci¢n dependiendo del valor de i.
                     actualiza el contenido de tiempo.

************************************************************/

void EjecutaAccionMalo (BITMAP *doublebuffer,TPERSONAJE *personaje,
                 BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]),
                 int *tiempo,BITMAP *fondo,int i)
{
 switch (i)
 {
  case (0): AtaqueBaseM (doublebuffer,fondo,personaje,fot,malo,pnjFot);
            *tiempo = (malo->magias[0]).tiempo;  // El tiempo depender  del
            break;                               // personaje...
  case (1): CurarseM (doublebuffer,fondo,personaje,fot,malo,pnjFot);
            *tiempo = (malo->magias[1]).tiempo;
            break;
  case (2): AtaqueBestiaM (doublebuffer,fondo,personaje,fot,malo,pnjFot);
            *tiempo = (malo->magias[2]).tiempo;
            break;
  case (3): Magia1M (doublebuffer,fondo,personaje,fot,malo,pnjFot);
            *tiempo = (malo->magias[3]).tiempo;
            break;
  case (4): Magia2M (doublebuffer,fondo,personaje,fot,malo,pnjFot);
            *tiempo = (malo->magias[4]).tiempo;
            break;
  case (5): InvocacionM (doublebuffer,fondo,personaje,fot,malo,pnjFot);
            *tiempo = (malo->magias[5]).tiempo;
            break;
 }
}



/***********************************************************

        Nombre: AtacarAMalo
        Tipo: entero (int). Ser  uno si se ha ejecutado alguna opci¢n,
              cero si no se ha ejecutado nada.
        Par metros de entrada: doublebuffer y fondo, BITMAPs. Personaje y
                   malo, con sus fotogramas. Apuntador a entero con el
                   tiempo para combates...
        Descripci¢n: Nos permite seleccionar un ataque de los disponibles, o
                     volver al men£ anterior. El jugador se desplaza por el
                     men£ de izquierda a derecha. El men£ es c¡clico.

************************************************************/

int AtacarAMalo (BITMAP *doublebuffer,TPERSONAJE *personaje,
                 BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]),
                 int *tiempo,BITMAP *fondo)
{
 int i=1; // Selecci¢n actual

 while (!key[KEY_ENTER] && !key[KEY_ESC])
 { // Mientras no pulsemos Enter o Escape...
  DibujaRecuadroAtaque (doublebuffer,i);   // ...dibujamos el recuadro con la
  blit (doublebuffer,screen,0,0,0,0,640,480); // opci¢n seleccionada
  if (key[KEY_LEFT])
  { // si se pulsa la izquierda
   i--;                                 // Selecci¢n anterior
   clear_keybuf();
   i = (i==0)?personaje->nivel:i;       // si se pasa de la primera, mostramos
  }                                     // la £ltima.
  if (key[KEY_RIGHT])
  { // para la derecha se selecciona el siguiente...
   i++;
   clear_keybuf();
   i = (i > personaje->nivel)?1:i;      // o se va al primero
  }
 }
 if (key[KEY_ENTER])
 { // Si se pulsa el enter
  clear_keybuf();
  EjecutaAccion (i,doublebuffer,personaje,fot,malo,pnjFot,tiempo,fondo);
  return 1;  // se ejecuta la acci¢n y devolvemos uno
 }
 if (key[KEY_ESC])
 { // Si se pulsa el Escape
  clear_keybuf();
  return 0;  // se devuelve cero
 }
}



/***********************************************************

        Nombre: MovimientoBueno
        Tipo: void
        Par metros de entrada: doublebuffer y fondo, BITMAPs. Personaje y
                   malo, con sus fotogramas.
                   Apuntador a entero con el tiempo para combates...
        Descripci¢n: seleccionamos el movimiento que realizar el bueno:
                     Atacar, Esperar o Salir.

************************************************************/

void MovimientoBueno (BITMAP *doublebuffer,TPERSONAJE *personaje,
                      BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]),
                      int *tiempo,BITMAP *fondo)
{
 int hecho=0,i=0; // hecho: indica si hemos hecho algo.
                  // i: selecci¢n actual

 while (!hecho)
 { // Mientras no hagamos nada...
  DibujaRecuadroMove (doublebuffer,i); // dibuja las opciones
  blit (doublebuffer,screen,0,0,0,0,640,480);
  if (key[KEY_UP])
  { // Si pulsamos arriba...
   clear_keybuf();
   i--;              // seleccionamos el superior,
   i = (i==-1)?0:i;  // del que no se puede pasar si es el primero (i==0).
  } else
  if (key[KEY_DOWN])
  { // Si pulsamos abajo...
   clear_keybuf();
   i++;              // seleccionamos el inferior,
   i = (i==3)?2:i;   // del que no se puede pasar si es el £ltimo (i==2).
  } else
  if (key[KEY_M])
  { // Si pulsamos la M (truco)...
   clear_keybuf();
   hecho = 1; // hemos hecho algo.
   malo->carac[3] = 0; // matamos al malo
  } else
  if (key[KEY_ENTER])
  { // si pulsamos enter...
   clear_keybuf();
   switch (i)
   {
    case (0): hecho = AtacarAMalo (doublebuffer,personaje,fot,malo,pnjFot,
                                  tiempo,fondo); // Se puede atacar
              break;
    case (1): hecho = 1;  // Hacemos algo...
              *tiempo = 100; // ... esperar
              break;
    case (2): hecho = 1;  // Hacemos algo...
              personaje->carac[3] = 0; // ... suicidarnos
              break;
   }
  }
 }

 return;
}



/***********************************************************

        Nombre: MovimientoMalo
        Tipo: void
        Par metros de entrada: doublebuffer y fondo, BITMAPs. Personaje y
                   malo, con sus fotogramas.
                   Apuntador a entero con el tiempo para combates...
        Descripci¢n: escoge un movimiento para el malo y lo ejecuta...

************************************************************/

void MovimientoMalo(BITMAP *doublebuffer,TPERSONAJE *personaje,
                    BITMAP *(fot[12]),TMALO *malo,BITMAP *(pnjFot[12]),
                    int *tiempo,BITMAP *fondo )

{
 int accion;

 do
   accion = random() % 6;
 while (!malo->magias[accion].tiene); // selecciona una magia que tenga (al
                                      // azar)...
                                      // y ejecutala...
 EjecutaAccionMalo (doublebuffer,personaje,fot,malo,pnjFot,tiempo,fondo,
                    accion);

 return;
}



/***********************************************************

        Nombre: CombateEnSi
        Tipo: void
        Par metros de entrada: doublebuffer y fondo, BITMAPs. Personaje y
                   malo, con sus fotogramas.
                   Apuntador a entero con el tiempo para combates...
        Descripci¢n: Gestiona el tiempo de los combatientes. Sale del
                     combate cuando uno est‚ muerto.

************************************************************/

void CombateEnSi (BITMAP *fondo, TPERSONAJE *personaje, TMALO *malo,
                  BITMAP *(fot[12]),BITMAP *(pnjFot[12]),
                  BITMAP *doublebuffer)
{
 int tiempoBueno, tiempoMalo;

 tiempoBueno = (random() %100); // Bueno y malo comienzan con
 tiempoMalo = (random() % 100); // un tiempo aleatorio...
 while (personaje->carac[3] && malo->carac[3])
 { // Mientras esten los dos vivos...
  blit (fondo, doublebuffer,0,0,0,0,640,380); // Pon el fondo
  DibujaRecuadroC (doublebuffer,*personaje,tiempoBueno);
  draw_sprite (doublebuffer,fot[0],500,480-(100+fot[0]->h));
  draw_sprite (doublebuffer,pnjFot[0],30,480-(100+pnjFot[0]->h));
  blit (doublebuffer,screen,0,0,0,0,640,480);//dibuja y vuelca el doble buffer
  if (tiempoBueno==0) // Si le toca moverse al bueno...
   MovimientoBueno(doublebuffer,personaje,fot,malo,pnjFot,&tiempoBueno,fondo);
  else tiempoBueno--;
  if ( tiempoMalo==0) // Si le toca moverse al malo...
   MovimientoMalo (doublebuffer,personaje,fot,malo,pnjFot,&tiempoMalo,fondo);
  else tiempoMalo--;
  if (personaje->carac[3] < 0) personaje->carac[3] = 0; // La vida no puede
  if (malo->carac[3] < 0) malo->carac[3] = 0;           // ser negativa
 }

 return;
}



/***********************************************************

        Nombre: DestruyeFotPlayer
        Tipo: void
        Par metros de entrada: fot, fotogramas del jugador.
        Descripci¢n: Libera la memoria usada por estos...

************************************************************/

void DestruyeFotPlayer (BITMAP *(fot[12]))
{
 int i;

 for (i=0;i<=11;i++)
  if (i != 10) destroy_bitmap (fot [i]); // Destruimos todos menos el 10
                                         // que no existe...

 return;
}



/***********************************************************

        Nombre: DestruyeFotPnj
        Tipo: void
        Par metros de entrada: fot, fotogramas del PNJ.
                               malo, el PNJ.
        Descripci¢n: Destruye los fotogramas cargados del malo...

************************************************************/

void DestruyeFotPnj (BITMAP *(fot[12]),TMALO malo)
{
 destroy_bitmap (fot[0]);
 destroy_bitmap (fot[1]);
 destroy_bitmap (fot[2]);
 if (malo.magias[0].tiene) // Tan s¢lo destruye los que se cargaron
 {
   destroy_bitmap (fot[3]);
   destroy_bitmap (fot[4]);
 }
 if (malo.magias[1].tiene ||malo.magias[3].tiene ||
     malo.magias[4].tiene ||malo.magias[5].tiene)
      destroy_bitmap (fot[5]);

 if (malo.magias[2].tiene)
 {
   destroy_bitmap (fot[6]);
   destroy_bitmap (fot[7]);
 }
 if (malo.magias[3].tiene)
    destroy_bitmap (fot[8]);
 if (malo.magias[4].tiene)
    destroy_bitmap (fot[9]);
 if(malo.magias[5].tiene)
    destroy_bitmap (fot[11]);
 return;
}



/***********************************************************

        Nombre: Combate
        Tipo: void
        Par metros de entrada: sala en que se desarrolla el combate.
                   personaje. m, c¢digo del malo con el que luchar.
                   musicC, nombre del fichero con la m£sica para el combate.
                   doublebuffer, BITMAP.
        Descripci¢n: carga lo necesario para el combate, y llama a CombateEnSi

************************************************************/

void Combate (TSALA sala, TPERSONAJE *personaje,int m, char musicC[13],
              BITMAP *doublebuffer)
{
 TMALO malo;                      // El enemigo
 BITMAP *fondo;                   // El fondo
 BITMAP *(fot[12]),*(pnjFot[12]); // Los fotogramas
 PALETTE pal;                     // La paleta
 MIDI *musicCombate;              // La m£sica

 clear (doublebuffer);
 malo = CargaMalo (m);            // Cargamos el malo,
 CargaFotPlayerC(personaje->fot,fot);         //
 CargaFotPnjC(malo.fotogramas,pnjFot,malo);   // los fotogramas,
 fondo = load_bitmap(sala.fondoCombate,pal);  // el fondo,
 musicCombate = load_midi (musicC);           // la m£sica
 play_midi (musicCombate,TRUE);               // y que suene...
 CombateEnSi(fondo,personaje, &malo, fot,pnjFot, doublebuffer); // lucha
 if (personaje->carac[3])     // Si hemos ganado muestra la
    BattleWin (*personaje);   // secuncia.
 DestruyeFotPlayer(fot);          //
 DestruyeFotPnj(pnjFot,malo);     // Destruye la memoria din mica
 destroy_bitmap(fondo);           //
 destroy_midi (musicCombate);     //

 return;
}



/***********************************************************

        Nombre: CombateFinal
        Tipo: void
        Par metros de entrada: personaje. m, c¢digo del malo con el que luchar.
                   doublebuffer, BITMAP. C¢digo de la pantalla actual.
        Descripci¢n: carga lo necesario para el combate con el enemigo final
                     de pantalla, y llama a CombateEnSi

************************************************************/

void CombateFinal (TPERSONAJE *personaje,BITMAP *doublebuffer,int codActual)
{
 TMALO malo;
 BITMAP *fondo;
 BITMAP *(fot[12]),*(pnjFot[12]);
 PALETTE pal;
 MIDI *musicCombate;
 int (*callBack)();

 clear (doublebuffer);
 switch (codActual) // Cargamos lo necesario dependiendo de la pantalla
 {
  case (1): malo = CargaMalo (25);
            musicCombate = load_midi ("jefe01.mid");
            fondo = load_bitmap ("unic.bmp",pal);
            break;
  case (2): malo = CargaMalo (50);
            musicCombate = load_midi ("ara¤a.mid");
            fondo = load_bitmap ("fara¤a.bmp",pal);
            break;
  case (3): malo = CargaMalo (123);
            musicCombate = load_midi ("balrog.mid");
            fondo = load_bitmap ("fbalrog.bmp",pal);
            break;
  case (4): clear_keybuf ();
            set_gfx_mode (GFX_AUTODETECT,320,200,0,0); //inicializamos el modo gr fico
            callBack = StopStd;
            play_fli ("sephmask.fli",screen,FALSE,callBack);
            rest (1000);
            set_gfx_mode (GFX_AUTODETECT,640,480,0,0); //inicializamos el modo gr fico
            malo = CargaMalo (999);
            musicCombate = load_midi ("bgtheme.mid");
            fondo = load_bitmap ("fmalofin.bmp",pal);
            set_palette (pal);
            break;
  default: break;
 }
 CargaFotPlayerC(personaje->fot,fot);
 CargaFotPnjC(malo.fotogramas,pnjFot,malo); // Cargamos los fotogramas
 play_midi (musicCombate,TRUE);
 CombateEnSi(fondo,personaje, &malo, fot,pnjFot, doublebuffer); // la lucha
 if (personaje->carac[3])
    BattleWin (*personaje);
 DestruyeFotPlayer(fot);      //
 DestruyeFotPnj(pnjFot,malo); // Liberamos la memoria
 destroy_bitmap(fondo);       // din mica
 destroy_midi (musicCombate); //

 return;
}
