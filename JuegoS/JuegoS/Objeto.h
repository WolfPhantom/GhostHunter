#pragma once

#include "Personaje.h"
#include <vector> //Gadd
using namespace std;

public class Objeto
{

private:
	short Tipo;
	bool Existe;
	Rectangle Area;

public:
	Objeto(void) {}
	Objeto(System::Drawing::Rectangle area, int Tipo) {
		this->Tipo = Tipo;
		this->Area = area;
	}
	~Objeto() {}

	bool ExisteColision(CPersonaje*objPersonaje) {
		Rectangle AreaPersonaje = Rectangle(objPersonaje->getX(),
			objPersonaje->getY(), objPersonaje->getAncho(), objPersonaje->getAlto());
		if (AreaPersonaje.IntersectsWith(this->Area)) {
			// Tipo 1 : Sandwich - Vida
			if (Tipo == 1) {
				//objPersonaje->SetVida(20);//Gadd
				if(objPersonaje->getNumSand() < 9)
					objPersonaje->setNumSad(objPersonaje->getNumSand() + 1);
				return true;
			}
			// Tipo 2 : Escudo - Proteccion - Defenza
			if (Tipo == 2) {
				//objPersonaje->SetDefenza(3);
				if (objPersonaje->getNumEscu() < 9)
					objPersonaje->setNumEscu(objPersonaje->getNumEscu() + 1);
				return true;
			}
			// Tipo 3 : Cruces - Municion
			if (Tipo == 3) {
				//objPersonaje->setMunicion(1);
				if (objPersonaje->getNumCru() < 9)
					objPersonaje->setNumCru(objPersonaje->getNumCru() + 1);
				return true;
			}
		}
		return false;
	}

	int getTipo() { return this->Tipo; }

	void Dibujar(BufferedGraphics^ buffer, Bitmap^ img) {
		img->MakeTransparent(img->GetPixel(0, 0));
		buffer->Graphics->DrawImage(img, this->Area);
		buffer->Graphics->DrawRectangle(Pens::Yellow, Area);

	}

	int getX() { return Area.X; }
	int getY() { return Area.Y; }

	bool ValidarPosicion(int **matriz, int X, int Y, vector<Objeto*> &Objetos) {
		int i = Y / 50;
		int j = X / 50;
		if (matriz[i][j] == 2) {
			if (Objetos.size() > 0) {
				for (int i = 0; i < Objetos.size(); i++)
				{
					if (Objetos.at(i)->getX() == X && Objetos.at(i)->getY() == Y) {
						return false;
					}
				}
				return true;
			}
			else
				return true;
		}
		else
			return false;
	}

};
