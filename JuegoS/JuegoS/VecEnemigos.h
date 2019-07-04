#pragma once

#include "Enemigo.h"


class CVecEnemigos {
public:
	CVecEnemigos(int **matriz, CPersonaje* bueno){
		crear_enemigosR(matriz, bueno);
	}

	CVecEnemigos(int **matriz, CPersonaje* bueno, int NEnemigos) {
		crear_enemigosS(matriz, bueno, NEnemigos);
	}

	~CVecEnemigos(){
		bla.clear();
	}

	int getCant() { return bla.size(); } //

	void crear_enemigosR(int **matriz, CPersonaje*bueno) {

		int numE;

		srand(time(NULL));
		numE = rand() % 6 + 1;

		int esp = 750 / (numE+1);

		for (int i = 0; i < numE; i++) 
			bla.push_back(new CEnemigo((i+1)*esp, matriz, bla, i, bueno));

	}

	void crear_enemigosS(int **matriz, CPersonaje*bueno, int NEnemigos) {

		int numE;

		numE = NEnemigos;

		int esp = 750 / (numE + 1);

		for (int i = 0; i < numE; i++)
			bla.push_back(new CEnemigo((i + 1)*esp, matriz, bla, i, bueno));

	}

	void perseguir(BufferedGraphics ^buffer, int **matriz, Bitmap^imgMalo,
		CPersonaje *bueno) {
		for (int i = 0; i < bla.size(); i++)
			bla[i]->perseguir(buffer, matriz, imgMalo, bla, i, bueno);
	}

	bool VerificarColision(Rectangle AreaPersonaje) {
		for (int i = 0; i < bla.size(); i++)
		{
			if (bla.at(i)->ExisteColisionEnemigoWithPersonaje(AreaPersonaje) && bla.at(i) != NULL)
			{
				delete bla.at(i);
				bla.erase(bla.begin() + i);
				return true;
			}
		}
		return false;
	}
	void VerificarColisionEnemigosBalas(CPersonaje *Personaje) {
		for (int i = 0; i < bla.size(); i++)
		{
			if (bla.at(i) != NULL) {
				for (int j = 0; j < Personaje->getBalas().size(); j++)
				{
					if (bla.at(i)->ExisteColisionEnemigoWithPersonaje(Personaje->getBalas().at(j)->getArea()) && Personaje->getBalas().at(j) != NULL)
					{
						EliminarEnemigo(i);
						break;
					}
				}
			}
		}
	}
	void EliminarEnemigo(int i)
	{
		delete bla.at(i);
		bla.erase(bla.begin() + i);
	}
	vector <CEnemigo*> Enemigos() { return this->bla; }

private:
	 vector <CEnemigo*> bla;
};