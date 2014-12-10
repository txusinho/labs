#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <process.h>
#include <errno.h>
#include <dir.H>

#define  TRUE 	1
#define  FALSE 	0


void make_window (int bkcolor,int txtcolor,int sombra,int border,
		  int x1,int y1,int x2,int y2)
{
 int i,j;
 char c;

 if (sombra)
 {
  window (x1+1,y1+1,x2+1,y2+1);
  textbackground (BLACK);
  clrscr();
 }
 window (x1,y1,x2,y2);
 textbackground (bkcolor);
 textcolor (txtcolor);
 clrscr();
 if (border)
 {
  for (i=y2-1 ; i>=y1-1; i--)
      for (j=x2-1 ; j>=x1-1; j--)
      {
	  ScreenSetCursor (i,j);
	  if (i==y1-1 && j == x1-1)
	     c = 'É';
	  else if (i==y2-1 && j==x1-1)
	       c = 'È';
	  else if (i==y2-1 && j==x2-1)
	       c = '¼';
	  else if (i==y1-1 && j==x2-1)
	       c = '»';
	  else if (i==y1-1 || i==y2-1)
	       c = 'Í';
	  else if (j==x1-1 || j==x2-1)
	       c = 'º';
	  else c = ' ';
	  putc (c,stdout);
	  fflush (stdout);
      }
  window (x1+1,y1+1,x2-1,y1-1);
  clrscr();
 }
}



char Menu (char *path)
{
 char c;

 _setcursortype (_NOCURSOR);

 make_window (LIGHTGRAY,WHITE,TRUE,TRUE,15,2,65,5);
 printf ("  Utilidad de instalaci¢n de Final Fantas¡ 92");
 gotoxy(1,2);
 printf ("    BdkSoftware - TriangleSoft ¸ 1999-2000");

 make_window (LIGHTGRAY,BLACK,TRUE,TRUE,5,20,55,22);
 printf ("Directorio actual: %s", path);

 make_window (LIGHTGRAY,BLACK,TRUE,TRUE,25,9,55,17);
 gotoxy (4,2);
 printf ("1.- Nuevo directorio");
 gotoxy (4,4);
 printf ("2.- Instalar");
 gotoxy (4,6);
 printf ("3.- Salir");
 do
   c = getch();
 while (c<'1' || c>'3');


 return c;
}

int main ()
{
 char path[40];
 char i;

 strcpy (path,"C:\\FF92");

 make_window (BLUE,WHITE,FALSE,TRUE,1,1,80,25);
 while (i != '2' && i != '3')
 {
  i = Menu (path);
  if (i == '1')
  {
   _setcursortype (_SOLIDCURSOR);
   make_window (LIGHTGRAY,BLACK,TRUE,TRUE,5,20,55,22);
   printf ("Introduzca directorio: ");
   scanf ("%s",path);
  }
 }

 make_window (BLACK,LIGHTGRAY,FALSE,FALSE,1,1,80,25);
 _setcursortype (_NORMALCURSOR);

 if (i == '2')
 {
  mkdir (path);
  execlp ("arj.exe","arj.exe","x","-va","-hf2","data.arj",path,0);
 }

 return 0;
}
