#pragma once

#include "Objeto.h"
#include <ctime>

class VObjetos{

public:
	void CrearObjetos(int **Mapa);
	void DibujarObjetos(BufferedGraphics^ buffer, Bitmap ^ imgSandwich, Bitmap^ imgEscudo, Bitmap^ imgCruz);
	void EliminarObjetos(CPersonaje* personaje);
	void VerificarEstadosdeColision(CPersonaje* personaje);
	VObjetos();
	~VObjetos();

private:
	vector<Objeto*> Objetos;

};

void VObjetos::CrearObjetos(int ** Mapa) {
	srand(time(NULL));
	Objetos.clear();
	int Fila = 15;
	int Columna = 18;
	int Cantidad = 0 + rand() % (7 + 1 - 0);

	int ContSand=0;
	int ContEscu=0;
	int ContCru=0;

	for (int i = 0; i < Cantidad; i++)
	{
		// variable = limite_inferior + rand() % (limite_superior +1 - limite_inferior) ;
		int X = 50 + rand() % ((50 * Columna - 100) + 1 - 50);
		int Y = 50 + rand() % ((50 * Fila - 100) + 1 - 50);
		int Tipo = 1 + rand() % (3 + 1 - 1);
		if (X % 50 == 0 && Y % 50 == 0)
		{
			if (Tipo == 1) ContSand++;
			else if (Tipo == 2) ContEscu++;
			else if (Tipo == 3) ContCru++;
			if (ContCru > 4) {
				i--;
				break;
			}
			if (ContSand > 2) {
				i--;
				break;
			}
			if (ContEscu > 1) {
				i--;
				break;
			}
			Objeto*nuevo = new Objeto(Rectangle(X, Y, 50, 50), Tipo);
			if (nuevo->ValidarPosicion(Mapa, X, Y, Objetos) != false) {
				Objetos.push_back(nuevo);
			}
			else
				i--;
		}
		else {
			i--;
		}
	}
}

void VObjetos::DibujarObjetos(BufferedGraphics^ buffer, Bitmap ^ imgSandwich, Bitmap^ imgEscudo, Bitmap^ imgCruz) {
	for (int i = 0; i < Objetos.size(); i++)
	{
		if (Objetos.at(i) != NULL) {
			if (Objetos.at(i)->getTipo() == 1)
				Objetos.at(i)->Dibujar(buffer, imgSandwich);
			else  if (Objetos.at(i)->getTipo() == 2)
				Objetos.at(i)->Dibujar(buffer, imgEscudo);
			else  if (Objetos.at(i)->getTipo() == 3)
				Objetos.at(i)->Dibujar(buffer, imgCruz);
		}
	}
}

void VObjetos::EliminarObjetos(CPersonaje* personaje) {
	for (short i = 0; i < Objetos.size(); i++)
	{
		if (Objetos.at(i)->ExisteColision(personaje) && Objetos.at(i) != NULL) {
			delete Objetos.at(i);
			Objetos.erase(Objetos.begin() + i);
		}
	}
}

void  VObjetos::VerificarEstadosdeColision(CPersonaje* personaje) {
	EliminarObjetos(personaje);
}

VObjetos::VObjetos(){}
VObjetos::~VObjetos(){
	for (short i = 0; i < Objetos.size(); i++)
	{
		delete this->Objetos.at(i);
	}
}

