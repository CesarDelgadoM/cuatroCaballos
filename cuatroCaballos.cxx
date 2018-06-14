#include "Tablero.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
  int x;
  int y;
  int pieza = 0;

  //instanciacion de clases
  Pantalla pantalla;
  Tablero tablero;

  //incializamos el tablero con sus posiciones
  tablero.inicializarTablero();

  tablero.seeMove();

  cout<<"(Tablero de 0 a 2 filas y 0 a 2 columnas)\n\nEste juego consiste en rotar "<<
        " los numeros 1 a las posiciones donde " <<
        "se encuentran los numeros 2.\n\nrealizando el movimento de un caballo de ajedrez "<<
        "(Respetando los turnos)\n\n(Presione enter para jugar)";


  cin.get();
  system("clear");

  //bucle del juego
  do
  {
    system("clear");
    tablero.seeMove();
    //valida el turno de la pieza introducida
    do
    {
      pantalla.gotoxy(1, 7);cout<<"digite el numero de la pieza: ";
      pantalla.gotoxy(31, 7);cin>>pieza;
    }while(tablero.turno(pieza) == true);

    pantalla.limpiarLinea1();

    //valida si la pieza esta bloqueada segun su posicion inicial
    do
    {
      pantalla.gotoxy(1, 8);cout<<"digite fila y columna, en donde se encuentre la pieza: ";
      pantalla.gotoxy(59, 8);cout<<"fila = ";cin>>x;
      pantalla.gotoxy(68, 8);cout<<"columna = ";cin>>y;
    }while(tablero.piezaBloqueada(x, y, pieza) != false);

    pantalla.limpiarLinea2();
    tablero.moveNumbers(pieza, x, y);

  }while(tablero.gameOver() != true);

  system("clear");
  tablero.seeMove();
  pantalla.gotoxy(1, 7);cout<<"Felicidades ha terminado el juego!!!\n";
}
