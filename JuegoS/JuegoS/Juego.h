#pragma once

#include "Lista.h"
#include "Arbol.h"
#include <functional>

auto compareEnemigos = [](CBeacon* a, CBeacon* b) {
	if (a->getEnemigo() < b->getEnemigo()) {
		return -1;
	}
	else if (a->getEnemigo() > b->getEnemigo()) {
		return 1;
	}
	else {
		return 0;
	}
};

class CJuego
{
	CMapa *mapa;
	CPersonaje *protagonista;
	DLList *lista_mapas;
	int nivel_Actual = 0;
	AVLTree<CBeacon*>* tEnemigos = new AVLTree<CBeacon*>(compareEnemigos);

	int n = 1000000;
	int step = n / 100;

	CBeacon* piggy;
	int NE;

public:
	CJuego() {
		lista_mapas = new DLList();
		protagonista = new CPersonaje();

		GenerarNuevoMapA();
		for (int i = 0; i < n; i++) {

			NE = 1 + rand() % ((10 + 1) - 1);

			piggy = new CBeacon(mapa->getMatriz());
			piggy->setEnemigo(NE);

			tEnemigos->add(piggy);


		}
	}
	~CJuego() {}

	void GenerarNuevoMapA() {
		mapa = new CMapa(protagonista); //Aqui está generar matriz
		lista_mapas->push_back(mapa);
	}

	void GenerarNuevoMapS(int NEnemigos) //generar mapa con la cantidad de enemigos del beacon
	{
		mapa = new CMapa(protagonista, NEnemigos); //Aqui está generar matriz
		lista_mapas->push_back(mapa);
	}

	void CambiarMapaSup() { nivel_Actual++; }
	void CambiarMapaInf() { nivel_Actual--; }

	void Dibujar(BufferedGraphics ^buffer, Bitmap ^bmpBorde,
		Bitmap ^bmpSuelo, Bitmap ^bmpMuro, Bitmap ^bmpArriba,
		Bitmap ^bmpAbajo, Bitmap^imgMalo,
		Bitmap^ bmpSandwich, Bitmap^ bmpEscudo,
		Bitmap^  bmpCruz, Bitmap^bmpBeacon) { //

		lista_mapas->Elemento(nivel_Actual)->DibujarMapa(buffer, bmpBorde,
			bmpSuelo, bmpMuro, bmpArriba, bmpAbajo, imgMalo,
			bmpSandwich, bmpEscudo, bmpCruz, protagonista, bmpBeacon);
		for (int i = 0; i < protagonista->getBalas().size(); i++)
		{
			protagonista->getBalas().at(i)->AnimarBala(buffer, bmpCruz);
		}
	}

	void mover(BufferedGraphics ^buffer, Bitmap ^bmppersonaje) {
		this->protagonista->mover(buffer,
			lista_mapas->Elemento(nivel_Actual)->getMatriz(), bmppersonaje);
	}

	CPersonaje *getPersonaje() { return this->protagonista; }

	Node *getNodo_actual()
	{
		return lista_mapas->nodo_actual(nivel_Actual);
	}

	void graficar_vidas(BufferedGraphics ^buffer, Bitmap ^bmppersonaje){

		Rectangle graficaEsto = Rectangle(4 * protagonista->getAncho(),
			2 * protagonista->getAlto(), protagonista->getAncho(),
			protagonista->getAlto());
		for (int i = 0; i < protagonista->getNumVidas(); i++) {
			Rectangle aqui = Rectangle(((2*(i+1)+1)*10), 10, 30, 30);
			buffer->Graphics->DrawImage(bmppersonaje, aqui, graficaEsto, GraphicsUnit::Pixel);
		}

	}

	void graficar_objetos(BufferedGraphics ^buffer, Bitmap ^bmpCruz, 
		Bitmap^ bmpEscudo, Bitmap^ bmpSandwich, Bitmap^ imgNumeros) {

		int iX = 0;
		int iY = 0;
		int w = imgNumeros->Width / 5;
		int h = imgNumeros->Height / 3;
		Rectangle graficaEsto;
		Rectangle aqui;

		bmpCruz->MakeTransparent(bmpCruz->GetPixel(0, 0));
		bmpEscudo->MakeTransparent(bmpEscudo->GetPixel(0, 0));
		bmpSandwich->MakeTransparent(bmpSandwich->GetPixel(0, 0));

		//CRUZ
		buffer->Graphics->DrawImage(bmpCruz, 650, 10, 30, 30);

		iX = protagonista->getNumCru();

		if (iX > 4) {
			iX -= 5;
			iY = 1;
		}
		else
			iY = 0;

		graficaEsto = Rectangle(iX*w, iY*h, w, h); 
		aqui = Rectangle(680, 25, 15, 15);
		buffer->Graphics->DrawImage(imgNumeros, aqui, graficaEsto, GraphicsUnit::Pixel);
	
		//ESCUDO
		buffer->Graphics->DrawImage(bmpEscudo, 720, 10, 30, 30);

		iX = protagonista->getNumEscu();

		if (iX > 4) {
			iX -= 5;
			iY = 1;
		}
		else
			iY = 0;

		graficaEsto = Rectangle(iX*w, iY*h, w, h);
		aqui = Rectangle(750, 25, 15, 15);
		buffer->Graphics->DrawImage(imgNumeros, aqui, graficaEsto, GraphicsUnit::Pixel);

		//SANDWICH
		buffer->Graphics->DrawImage(bmpSandwich, 790, 10, 30, 30);
		
		iX = protagonista->getNumSand();

		if (iX > 4) {
			iX -= 5;
			iY = 1;
		}
		else
			iY = 0;

		graficaEsto = Rectangle(iX*w, iY*h, w, h);
		aqui = Rectangle(820, 25, 15, 15);
		buffer->Graphics->DrawImage(imgNumeros, aqui, graficaEsto, GraphicsUnit::Pixel);

	}

	bool beacon() { return this->mapa->getColision(); }
	void setBeacon() { this->mapa->setColisionB(); }

};