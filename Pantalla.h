#include <iostream>
#include <stdio.h>

using namespace std;

class Pantalla
{
	public:
		void gotoxy(int x, int y);
		void limpiarLinea1();
		void limpiarLinea2();
		void limpiarLinea3();
};

void Pantalla::gotoxy(int x, int y)
{
  //invertimos las variables x, y
	printf("%c[%d;%df", 0x1B, y, x);
	fflush(stdout);
}

void Pantalla::limpiarLinea1()
{
  gotoxy(33, 7);cout<<"                                             ";
}

void Pantalla::limpiarLinea2()
{
	gotoxy(80, 8);cout<<"                                             ";
}

void Pantalla::limpiarLinea3()
{
	gotoxy(80, 9);cout<<"                                            ";
}
