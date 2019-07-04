#pragma once


#include <stdlib.h>
#include <time.h>

using namespace System::Drawing;
using namespace System;

class CBeacon {

public:
	CBeacon(int **matriz){
		this->wB = 50;
		this->hB = 50;
		setCoordenadas(matriz);
		srand(time(NULL));
		this->numEnemigos = 0 + rand() % (7 + 1 - 0);
		//this->numObjetos = numObjetos;	 

		this->ixMIN = 0;
		this->ixMAX = 3;
		this->ix = ixMIN;
	}
	~CBeacon(){}

	bool verificar_posicion(int **matriz) {

		int UIC = x / 50, UIF = y / 50; // UpIzq
		int UDC = (x + wB) / 50, UDF = y / 50; // UpDer
		int DIC = x / 50, DIF = (y + hB) / 50; // DownIzq
		int DDC = (x + wB) / 50, DDF = (y + hB) / 50; // DownDer

		if (matriz[UIF][UIC] == 2 &&
			matriz[UDF][UDC] == 2 &&
			matriz[DIF][DIC] == 2 &&
			matriz[DDF][DDC] == 2)
			return true;
		else
			return false;

	}

	void setCoordenadas(int **matriz) {

		x = 50;
		y = 650;

	} 

	void dibujar(BufferedGraphics^buffer, Bitmap^img) {

		this->wI = img->Width / 4;
		this->hI = img->Height;

		Rectangle dibujaresto = Rectangle(ix*wI, 0, wI, hI);
		Rectangle aqui = Rectangle(x, y, wB, hB);
		buffer->Graphics->DrawImage(img, aqui, dibujaresto, GraphicsUnit::Pixel);
		if (ix < ixMAX)
			ix++;
		else
			ix = ixMIN;

	}

	bool interseccion_con_personaje(CPersonaje* bueno) {
		
		Rectangle areaBeacon = Rectangle(x, y, wB, hB);
		if (bueno->getCAA().IntersectsWith(areaBeacon) || bueno->getCDI().IntersectsWith(areaBeacon))
			return true;
		else
			return false;
	}

	int getEnemigo() { return this->numEnemigos; }
	void setEnemigo(int n) { this->numEnemigos = n; }

	void transportar(){}

private:

	int x;
	int y;
	int wB;
	int hB;
	int numEnemigos;
	//int numObjetos; 

	int wI;
	int hI;
	int ixMIN;
	int ix;
	int ixMAX;

};