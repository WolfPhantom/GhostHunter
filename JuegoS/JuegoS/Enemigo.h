#pragma once

#include "Personaje.h"

#include <stdlib.h>
#include <time.h>

#include <vector>
using namespace std;

using namespace System::Drawing;

class CEnemigo{

public:

	CEnemigo(int x0, int **matriz, vector<CEnemigo*> bla, int pos, CPersonaje*bueno) {
		this->vivo = true;
		setTipo(); //color de fantasmita  1-12
		this->wE = 50;
		this->hE = 50;
		setCoordenadas(x0, matriz, bla);
		setVez(bueno);
		this->dx = 20;	 
		this->dy = 20;	 
		setDir();
		ix_limites();
		this->ix = ixMIN;
		this->iy = tipo - 1;
	}
	~CEnemigo() {}

	//Para que solo reste una vez durante pasada
	void setVez(CPersonaje*bueno) {
		if (interseccion_con_personaje(bueno) == true)
			vez = 1;
		else
			vez = 0;
	}

	bool getVivo() { return this->vivo; }
	void setVivo(bool vivo) { this->vivo = vivo; } 

	int getx0() { return this->x0; }
	int gety0() { return this->y0; }
	int getwE() { return this->wE; }
	int gethE() { return this->hE; }


	//Tipo FANTASMITA al azar 
	void setTipo() {

		srand(time(NULL));
		tipo = rand() % 12 + 1;

	}

	//Direccion al azar
	void setDir() {

		srand(time(NULL));
		dir = rand() % 4 + 1;

	}

	void ix_limites() {

		switch (dir) {
		case 1: //derecha
			ixMIN = 0;
			break;
		case 2: //izquierda
			ixMIN = 2;
			break;
		case 3: //arriba
			ixMIN = 4;
			break;
		case 4: //abajo
			ixMIN = 6;
			break;
		}

		ixMAX = ixMIN + 1;

	}

	bool verificar_posicion(int **matriz) {

		int UIC = x / 50, UIF = y / 50; // UpIzq
		int UDC = (x + wE) / 50, UDF = y / 50; // UpDer
		int DIC = x / 50, DIF = (y + hE) / 50; // DownIzq
		int DDC = (x + wE) / 50, DDF = (y + hE) / 50; // DownDer

		if (matriz[UIF][UIC] == 2 &&
			matriz[UDF][UDC] == 2 &&
			matriz[DIF][DIC] == 2 &&
			matriz[DDF][DDC] == 2)
			return true;
		else
			return false;

	}
	bool invade_a_fantasmitas(int xAUX, int yAUX, vector<CEnemigo*> bla, int pos) {

		Rectangle ComparaEste = Rectangle(xAUX, yAUX, wE, hE);

		for (int i = 0; i < bla.size(); i++) {
			Rectangle ConEste = Rectangle(bla[i]->getx0(), bla[i]->gety0(),
				bla[i]->getwE(), bla[i]->gethE());
			if (pos != i) {
				if (ComparaEste.IntersectsWith(ConEste) == true)
					return true;
			}
		}

		return false;

	}

	void setCoordenadas(int x0, int **matriz, vector<CEnemigo*> bla) {

		this->x0 = x0;
		this->y0 = 50;
		
		x = this->x0;
		y = y0;
	}

	void dibujar(BufferedGraphics^buffer, Bitmap^img) {

		ix_limites();

		this->wI = img->Width / 12;
		this->hI = img->Height / 12;

		Rectangle dibujaresto = Rectangle(ix*wI, iy*hI, wI, hI);
		Rectangle aqui = Rectangle(x0, y0, wE, hE);
		buffer->Graphics->DrawImage(img, aqui, dibujaresto, GraphicsUnit::Pixel);
		if (ix < ixMAX)
			ix++;
		else
			ix = ixMIN;
	}

	void perseguir(BufferedGraphics^buffer, int **matriz, Bitmap^img, 
		vector<CEnemigo*>bla, int pos, CPersonaje*bueno) {

		estado_de_colision(bueno);

		x = x0;
		y = y0;

		switch (dir) {
		case 1: //Derecha
			x = x0 + dx;
			break;
		case 2: //Izquierda
			x = x0 - dx;
			break;
		case 3: //Arriba
			y = y0 - dy;
			break;
		case 4: //Abajo
			y = y0 + dy;
			break;
		}

		if (verificar_posicion(matriz) == true &&
			invade_a_fantasmitas(x, y, bla, pos) == false) {
			x0 = x;
			y0 = y;
		}
		else
			setDir();

		dibujar(buffer, img);

	}	   

	bool interseccion_con_personaje(CPersonaje* bueno) {
		Rectangle areaBueno = Rectangle(bueno->getX(), bueno->getY(),
			bueno->getAncho(), bueno->getAlto());
		Rectangle areaMalo = Rectangle(x0, y0, wE, hE);
		if (areaBueno.IntersectsWith(areaMalo))
			return true;
		else
			return false;
	}

	void estado_de_colision(CPersonaje* bueno) {
	
		if (vez == 0 && interseccion_con_personaje(bueno) == true) {
			vez = 1;
			if (bueno->getNumEscu() > 0) {
				bueno->setNumEscu(bueno->getNumEscu() - 1);
			} else
				bueno->SetVida(-20);
		
		} 
		else if (vez == 1 && interseccion_con_personaje(bueno) == false)
			vez = 0;

	}

	// Colision de Enemigos con Personaje
	bool ExisteColisionEnemigoWithPersonaje(Rectangle Area) {
		Rectangle AreaPersonaje = Rectangle(Area);
		if (AreaPersonaje.IntersectsWith(Rectangle(x, y, wI, hI)))
			return true;
		return false;
	}
	//// Colision de Enemigos con Balas del personaje
	bool ExisteColisionEnemigoWithBala(Rectangle Area) {
		Rectangle Area_Bala = Rectangle(Area);
		if (Rectangle(x, y, wI, hI).IntersectsWith(Area_Bala))
			return true;
		return false;
	}

private:

	int tipo; //12 tipos de fantasmitas
	bool vivo;
	int dir; // 1 der 2 izq 3 ar 4 ab
	int x0;	
	int y0;	
	int dx;
	int dy;
	int x;	//luego del desplazamiento
	int y;  //luego del desplazamiento
	int wE;
	int hE;
	bool vez;

	int wI; //ANCHO C/FANTASMITA
	int hI; //ALTO C/FANTASMITA
	int ixMIN;
	int ix;
	int ixMAX;
	int iy;

};
