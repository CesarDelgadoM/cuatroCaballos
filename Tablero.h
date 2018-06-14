#include <iostream>
#include "Pantalla.h"

using namespace std;

class Tablero
{
  private:
    static const int rows = 3;
    static const int cols = 3;
    int **matrix;
    bool turnoN;
    bool turnoB;

  public:
    Tablero();

  public:
    void inicializarTablero();
    void moveNumbers(int pieza, int x, int y);
    bool turno(int pieza);
    void seeMove();
    bool validarMovimiento(int x, int y, int posX, int posY);
    bool piezaBloqueada(int x, int y, int pieza);
    bool gameOver();

    Pantalla pantalla;
};

Tablero::Tablero()
{
  turnoN = true;
  turnoB = true;
}

void Tablero::inicializarTablero()
{
  //creamos una matriz dinamica
  matrix = new int *[rows];

  for(int i=0; i<rows; i++)
  {
    matrix[i] = new int [cols];
  }

  //incializamos las posiciones
  *(*(matrix + 0) + 0) = 1;
  *(*(matrix + 0) + 1) = 0;
  *(*(matrix + 0) + 2) = 1;

  *(*(matrix + 1) + 0) = 0;
  *(*(matrix + 1) + 1) = 0;
  *(*(matrix + 1) + 2) = 0;

  *(*(matrix + 2) + 0) = 2;
  *(*(matrix + 2) + 1) = 0;
  *(*(matrix + 2) + 2) = 2;
}

void Tablero::moveNumbers(int pieza, int x, int y)
{
  int posX;
  int posY;

  //codigo de movimiento
  do
  {
    pantalla.gotoxy(1, 9);cout<<"digite fila y columna, en donde desee mover la pieza: ";
    pantalla.gotoxy(59, 9);cout<<"fila = ";cin>>posX;
    pantalla.gotoxy(68, 9);cout<<"columna = ";cin>>posY;

    pantalla.limpiarLinea3();

  }while(validarMovimiento(x, y, posX, posY) == false);

  //se cambia la pieza a la posicion dejando un 0
  *(*(matrix + x) + y) = 0;
  *(*(matrix + posX) + posY) = pieza;

  seeMove();
}

//metodo encargado de verificar que la pieza se pueda mover
bool Tablero::piezaBloqueada(int x, int y, int pieza)
{
  if(x >= 0 && x <= 2 && y >= 0 && y <= 2)
  {
    if(matrix[x][y] == pieza)
    {
      if(x == 0 && y == 0 && (matrix[1][2] == 0 || matrix[2][1] == 0)) return false;
      if(x == 0 && y == 1 && (matrix[2][0] == 0 || matrix[2][2] == 0)) return false;
      if(x == 0 && y == 2 && (matrix[1][0] == 0 || matrix[2][1] == 0)) return false;
      if(x == 1 && y == 0 && (matrix[0][2] == 0 || matrix[2][2] == 0)) return false;
      if(x == 1 && y == 2 && (matrix[0][0] == 0 || matrix[2][0] == 0)) return false;
      if(x == 2 && y == 0 && (matrix[1][2] == 0 || matrix[0][1] == 0)) return false;
      if(x == 2 && y == 1 && (matrix[0][0] == 0 || matrix[0][2] == 0)) return false;
      if(x == 2 && y == 2 && (matrix[1][0] == 0 || matrix[0][1] == 0)) return false;

      else pantalla.gotoxy(80, 8);cout<<"pieza bloqueada!"; return true;
    }
    else
    {
      pantalla.gotoxy(80, 8);cout<<"posicion de la pieza errada!"; return true;
    }
  }
  else
  {
    pantalla.gotoxy(80, 8);cout<<"fuera de rango en el tablero"<<endl; return true;
  }
}

bool Tablero::validarMovimiento(int x, int y, int posX, int posY)
{
  if(posX >= 0 && posX <= 2 && posY <= 2 && posY >= 0)
  {
    if(matrix[posX][posY] == 0)
    {
      if((x + 2 == posX && y + 1 == posY) || (x + 1 == posX && y + 2 == posY)) return true;
      if((x - 2 == posX && y - 1 == posY) || (x - 1 == posX && y - 2 == posY)) return true;
      if((x + 2 == posX && y - 1 == posY) || (x + 1 == posX && y - 2 == posY)) return true;
      if((x - 2 == posX && y + 1 == posY) || (x - 1 == posX && y + 2 == posY)) return true;

      else pantalla.gotoxy(80, 9);cout<<"movimiento errado!"; return false;
    }
    else
    {
      pantalla.gotoxy(80, 9);cout<<"ya existe una pieza en esa posicion"; return false;
    }
  }
  else
  {
    pantalla.gotoxy(80, 9);cout<<"fuera de rango en el tablero"<<endl; return false;
  }
}

//control de turnos por pieza
bool Tablero::turno(int pieza)
{
  if(pieza == 1 && turnoN == true)
  {
    turnoN = false;
    turnoB = true;
    return turnoN;
  }
  else if(pieza == 2 && turnoB == true)
  {
    turnoB = false;
    turnoN = true;
    return turnoB;
  }
  else if(turnoN == false && pieza == 1)
  {
    pantalla.gotoxy(33, 7);cout<<"ya jugaron los 1, juegan los 2";
  }
  else if(turnoB == false && pieza == 2)
  {
    pantalla.gotoxy(33, 7);cout<<"ya jugaron los 2, juegan los 1";
  }
  else
  {
    pantalla.limpiarLinea1();
    pantalla.gotoxy(33, 7);cout<<"pieza mal elegida! ";
  }
  return true;
}

//metodo encargado de imprimir la matrix o el tablero
void Tablero::seeMove()
{
  for(int i=0; i<rows; i++)
  {
    for(int j=0; j<cols; j++)
    {
      cout<<*(*(matrix + i) + j)<<" | ";
    }
    cout<<"\n\n";
  }
}

//metodo encargado de verificar que las piezas hallan sido rotadas
bool Tablero::gameOver()
{
  if(*(*(matrix + 0) + 0) == 2 && *(*(matrix + 0) + 2) == 2 &&
      *(*(matrix + 2) + 0) == 1 && *(*(matrix + 2) + 2) == 1)
  {
    return true;
  }
  else
  {
    return false;
  }
}
