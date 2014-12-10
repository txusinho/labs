/************************************************************************

 videos

*************************************************************************/

#include "videos.h"



/************************************************************************

                FUNCIONES DE SINCRONIZACION DE EVENTOS
                              CON VIDEOS

                Las funciones que se encuentran a continuacion
                se utilizan para producir retardos en las animaciones,
                y para sincronizar la salida de texto por pantalla
                en determinados momentos.
                Todas ellas tienen la misma estructura:

                      - Busqueda del evento a sicronizar mediante la
                        variable global de Allegro fli_frame
                      - Retardo

*************************************************************************/


/*********
*********/

int StopILucha()
{
 extern int fli_frame;

 if (fli_frame>121 && fli_frame<136 )
 {
  text_mode (-1);
  textprintf (screen,font,20,180,36,"Ahi va!, se me ha caido el arma!");
 }
 rest (166);
 if (keypressed()) return 1;
 else return 0;
}


/*********
*********/

int StopChocobo()
{
 extern int fli_frame;

 text_mode (-1);
 textprintf (screen,font,20,180,36,"EN TODO FF HA DE HABER UN CHOCOBO...");
 if (keypressed()) return 1;
 else return 0;
}


/*********
*********/

int StopEnd()
{
 if (fli_frame>=1 && fli_frame<=12 )
  {
   text_mode (-1);
   textprintf (screen,font,20,180,0,"Bueno, no ha sido tan dificil...");
  } else
 if (fli_frame>=13 && fli_frame<=22 )
  {
   text_mode (-1);
   textprintf (screen,font,20,180,0,"Y tu, Mariluz, estas bien?");
  } else
 if (fli_frame>=23 && fli_frame<=35 )
  {
   text_mode (-1);
   textprintf (screen,font,20,180,0,"Si, si, estoy perfectamente...");
  } else
 if (fli_frame>=36 && fli_frame<=42 )
  {
   text_mode (-1);
   textprintf (screen,font,5,180,0,"Ahora podras volver a la venta de sal...");
  } else
 if (fli_frame>=43 && fli_frame<=58 )
  {
   text_mode (-1);
   textprintf (screen,font,5,180,0,"No, no, he estado reflexionando y...");
  } else
 if (fli_frame>=59 && fli_frame<=68 )
  {
   text_mode (-1);
   textprintf (screen,font,20,180,0,"...voy a ser profesora en Deusto...");
  } else
 if (fli_frame>=69 && fli_frame<=74 )
  {
   text_mode (-1);
   textprintf (screen,font,20,180,0,"QUE!!!!!, Pues oye Bardok, y...");
  } else
 if (fli_frame>=75 && fli_frame<=91 )
  {
   text_mode (-1);
   textprintf (screen,font,5,180,0,"si vendiesemos esto como una historia?");
  }
  else
  {
   text_mode (-1);
   textprintf (screen,font,20,180,0,"Para un videojuego? Bueno, vale.");
  }
 rest (166);
 if (keypressed()) return 1;
 else return 0;
}


/*********
*********/

int StopYoda()
{
 extern int fli_frame;

 if (fli_frame>=1 && fli_frame<=7 )
  {
   text_mode (-1);
   textprintf (screen,font,20,180,20,"Bueno, vamos alla...");
  } else
 if (fli_frame>=8 && fli_frame<=16 )
  {
   text_mode (-1);
   textprintf (screen,font,20,180,15,"Klshlshhhlssh, oye chaval...");
  } else
 if (fli_frame>=17 && fli_frame<=25 )
  {
   text_mode (-1);
   textprintf (screen,font,20,180,20,"Pero que...?");
  } else
 if (fli_frame>=26 && fli_frame<=30 )
  {
   text_mode (-1);
   textprintf (screen,font,20,180,15,"Habia pensado quehhh...");
  } else
 if (fli_frame>=31 && fli_frame<=40 )
  {
   text_mode (-1);
   textprintf (screen,font,20,180,15,"Podrias haa...cerme un favor...");
  } else
 if (fli_frame>=41 && fli_frame<=46 )
  {
   text_mode (-1);
   textprintf (screen,font,20,180,15,"Cun la campanie electoral...");
  } else
 if (fli_frame>=47 && fli_frame<=65 )
  {
   text_mode (-1);
   textprintf (screen,font,20,180,20,"Ni hablar, dejame en paz");
  } else
 if (fli_frame>=66 && fli_frame<=75 )
  {
   text_mode (-1);
   textprintf (screen,font,20,180,15,"Pero oye...!");
  } else
 if (fli_frame>=76 && fli_frame<=95 )
  {
   text_mode (-1);
   textprintf (screen,font,20,180,20,"Hala, p'adentro...");
  }
 rest (166);
 if (keypressed()) return 1;
 else return 0;
}


/*********
*********/

int StopDanste()
{
 extern int fli_frame;

 textprintf (screen,font,20,180,62,"ESTO ES FICCION!!!! (que quede claro)");
 rest (50);
 if (keypressed()) return 1;
 else return 0;
}


/*********
*********/

int StopSephkit()
{
 extern int fli_frame;

 if (fli_frame>=22 && fli_frame<=32 )
 {
  text_mode (-1);
  textprintf (screen,font,20,180,89,"Jefe, aqui! Malas noticias!");
 } else
 if (fli_frame>=41 && fli_frame<=51 )
 {
  text_mode (-1);
  textprintf (screen,font,20,180,89,"Darth Maul ha sido vencido!");
 } else
 if (fli_frame>=61 && fli_frame<=71 )
 {
  text_mode (-1);
  textprintf (screen,font,20,180,89,"Ese inutil...");
 } else
 if (fli_frame>=77 && fli_frame<=90 )
 {
  text_mode (-1);
  textprintf (screen,font,20,180,89,"Y ENCIMA LA SOPA ESTA SOSA!");
 } else
 if (fli_frame>=103 && fli_frame<=113 )
 {
  text_mode (-1);
  textprintf (screen,font,20,180,89,"ESTOY FURIOSO!");
 } else
 if (fli_frame>=123 && fli_frame<=140 )
 {
  text_mode (-1);
  textprintf (screen,font,20,180,89,"...juro que me vengare de esto!");
 }
 rest (166);
 if (keypressed()) return 1;
 else return 0;
}



/*********
*********/

int StopStandard()
{
 rest (166);
 if (keypressed()) return 1;
 else return 0;
}


/*********
*********/

int StopStd ()
{
 rest (66);
 if (keypressed()) return 1;
 else return 0;
}


/**********************************************************************

                FUNCIONES DE REPRODUCCION DE
                          VIDEOS

          Tan solo cargan las musicas, escogen las funciones
          de sincronizacion y reproducen las animaciones
          indicadas.

**********************************************************************/



// Muestra en pantalla los dos logotipos iniciales, con sus musicas

void Logos()
{
 int (*callBack)();
 MIDI *music;
 int cont;

 callBack = StopStandard;
 music = load_midi ("logo1.mid");
 play_midi (music,FALSE);
 set_gfx_mode (GFX_AUTODETECT,320,200,0,0);
 cont = play_fli ("trsoft.fli",screen,FALSE,callBack);
 if (!cont)
 {
  rest (1000);
  destroy_midi (music);
  music = load_midi ("logo2.mid");
  play_midi (music,FALSE);
  rest (3000);
  cont = play_fli ("bdksoft.fli",screen,FALSE,callBack);
  if (!cont) rest (3000);
 }
 destroy_midi (music);
 set_gfx_mode (GFX_AUTODETECT,640,480,0,0);

 return;
}


// Muestra la secuencia de videos de introduccion

void Intro()
{
 MIDI *music;
 int (*CallBack)();

 set_gfx_mode (GFX_AUTODETECT,320,200,0,0); //inicializamos el modo grafico
 music = load_midi ("ilucha.mid");
 play_midi (music,TRUE);
 rest (1000);
 CallBack = StopILucha;
 play_fli ("ilucha.fli",screen,FALSE,CallBack);
 destroy_midi (music);
 music = load_midi ("batwin.mid");
 play_midi (music,TRUE);
 CallBack = StopStandard;
 play_fli ("ivict.fli",screen,FALSE,CallBack);
 destroy_midi (music);
 music = load_midi ("bgtheme.mid");
 play_midi (music,TRUE);
 clear (screen);
 textprintf (screen,font,20,80,16,"De mientras,");
 textprintf (screen,font,20,100,16,"en el castillo del malo...");
 rest (5000);
 CallBack = StopSephkit;
 play_fli ("sephkit.fli",screen,FALSE,CallBack);
 rest (4000);
 destroy_midi (music);
 set_gfx_mode (GFX_AUTODETECT,640,480,0,0); //inicializamos el modo grafico
}


// Muestra el video que aparece cuando muere el personaje

void Mueto ()
{
 int (*callBack)();

 clear_keybuf();
 set_gfx_mode (GFX_AUTODETECT,320,200,0,0); //inicializamos el modo grafico
 callBack = StopStandard;
 play_fli ("mueto.fli",screen,FALSE,callBack);
 set_gfx_mode (GFX_AUTODETECT,640,480,0,0);
 return;
}


// Muestra el video final

void Final ()
{
 MIDI *music;
 int (*callBack)();

 clear_keybuf();
 music = load_midi ("mfin.mid");
 play_midi (music,TRUE);
 set_gfx_mode (GFX_AUTODETECT,320,200,0,0); //inicializamos el modo grafico
 callBack = StopEnd;
 play_fli ("final.fli",screen,FALSE,callBack);
 set_gfx_mode (GFX_AUTODETECT,640,480,0,0);
 destroy_midi (music);

 return;
}

// Muestra la animacion que aparece al ganar un combate.
// Dicha animacion depende de que el personaje sea uno u otro.

void BattleWin (TPERSONAJE player)
{
 MIDI *music;
 int (*callBack)();

 set_gfx_mode (GFX_AUTODETECT,320,200,0,0); //inicializamos el modo grafico
 music = load_midi ("batwin.mid");
 play_midi (music,TRUE);
 callBack = StopStd;
 if (strcmp (player.nombre,"Bardok") == 0)         // Si el nombre es Bardok
    play_fli ("bdkwin.fli",screen,TRUE,callBack);  // mostramos bdkwin.fli
 else play_fli ("txswin.fli",screen,TRUE,callBack);// si no, Txswin.fli
 destroy_midi (music);
 set_gfx_mode (GFX_AUTODETECT,640,480,0,0); //inicializamos el modo grafico

 return;
}

