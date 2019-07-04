#pragma once

#include "Bala.h"
#include <vector>
using namespace std;

using namespace System::Drawing;

enum Direcciones { Ninguna, Abajo, Arriba, Izquierda, Derecha };


class CPersonaje
{

private:

	int x;
	int y;
	int dy;
	int dx;
	int alto;
	int ancho;
	int indiceX;
	int indiceY;

	int Vida;
	int Defenza;
	int Municion;
	vector<CBala*> Cruces;

	Direcciones ultimaTecla;
	Rectangle CDI;
	Rectangle CAA;
	Rectangle c1;
	int tp;

	int numSand;
	int numEscu;
	int numCru;

public:
	Direcciones direccion;
	CPersonaje()
	{

		tp = -1;
		this->x = 400;
		this->y = 600;
		dx = 0;
		dy = 0;
		ultimaTecla = Direcciones::Abajo;
		direccion = Direcciones::Ninguna;

		this->alto = 64;
		this->ancho = 64;
		indiceX = 0;
		indiceY = 0;
		this->Vida = 120;//lo he dejado en 120
		this->Defenza = 0;

		this->numSand = 0;
		this->numEscu = 0;
		this->numCru = 0;
	}
	~CPersonaje() {
		Cruces.clear();
	}

	int getNumSand() { return this->numSand; }
	int getNumEscu() { return this->numEscu; }
	int getNumCru() { return this->numCru; }
	void setNumSad(int numSand) { this->numSand = numSand; }
	void setNumEscu(int numEscu) { this->numEscu = numEscu; }
	void setNumCru(int numCru) { this->numCru = numCru; }

	int getX() { return this->x; }
	int getY() { return this->y; }

	int getVida() { return this->Vida; }
	int getDefenza() { return this->Defenza; }
	int getMunicion() { return this->Municion; }

	void ValidarMovimiento(int **matriz)
	{
		int a = 0;
		int b = 0;

		for (int i = 0; i < 15; i++)
		{
			a = 0;
			for (int j = 0; j <18; j++)
			{
				c1 = Rectangle(a, b, 50, 50);

				if (matriz[i][j] == 1 || matriz[i][j] == 3)
				{
					if (CDI.IntersectsWith(c1))dx = 0;
					if (CAA.IntersectsWith(c1))dy = 0;
				}
				else if (matriz[i][j] == 4)
				{
					if (CAA.IntersectsWith(c1))tp = 1;
				}
				else if (matriz[i][j] == 5)
				{
					if (CAA.IntersectsWith(c1))tp = 2;
				}

				a += 50;

			}
			b += 50;
		}


	}

	void dibujar(BufferedGraphics ^buffer, int **matriz, Bitmap ^img)
	{
		CDI = Rectangle(x + 8 * 3 + dx, y + 15 * 3, ancho - 30, alto - 20);
		CAA = Rectangle(x + 8 * 3, y + 15 * 3 + dy, (ancho - 30), (alto - 20));
		ValidarMovimiento(matriz);
		buffer->Graphics->DrawRectangle(Pens::Red, CDI);
		buffer->Graphics->DrawRectangle(Pens::Yellow, CAA);
		buffer->Graphics->DrawRectangle(Pens::Blue, c1);
		Rectangle porcionUsar = Rectangle(indiceX*ancho, indiceY*alto, ancho, alto);
		buffer->Graphics->DrawImage(img, x, y, porcionUsar, GraphicsUnit::Pixel);
		x += dx;
		y += dy;
	}

	void mover(BufferedGraphics ^buffer, int **matriz, Bitmap ^img)
	{
		switch (direccion)
		{
		case Direcciones::Arriba:
			indiceY = 0;
			if (indiceX >= 0 && indiceX <= 7)
			{
				indiceX++;
			}
			else
			{
				indiceX = 0;
			}
			dx = 0;
			dy = -15;
			ultimaTecla = Arriba; break;
		case Direcciones::Abajo:
			indiceY = 2;
			if (indiceX >= 0 && indiceX <= 7)
			{
				indiceX++;
			}
			else
			{
				indiceX = 0;
			}
			dx = 0;
			dy = 15;
			ultimaTecla = Abajo; break;
		case Direcciones::Izquierda:
			indiceY = 1;
			if (indiceX >= 0 && indiceX <= 7)
			{
				indiceX++;
			}
			else
			{
				indiceX = 0;
			}
			dx = -15;
			dy = 0;
			ultimaTecla = Izquierda; break;
		case Direcciones::Derecha:
			indiceY = 3;
			if (indiceX >= 0 && indiceX <= 7)
			{
				indiceX++;
			}
			else
			{
				indiceX = 0;
			}
			dx = 15;
			dy = 0;
			ultimaTecla = Derecha; break;
		case Direcciones::Ninguna:
			dx = 0;
			dy = 0;
			switch (ultimaTecla)
			{
			case Direcciones::Abajo:
				indiceX = 0;
				indiceY = 2;
				break;
			case Direcciones::Arriba:
				indiceX = 0;
				indiceY = 0;
				break;
			case Direcciones::Izquierda:
				indiceX = 0;
				indiceY = 1;
				break;
			case Direcciones::Derecha:
				indiceX = 0;
				indiceY = 3;
				break;
			}
			break;
		}
		dibujar(buffer, matriz, img);
	}

	int getTp() { return tp; }
	void setTpArriba() { this->tp = -1; x = 400, y = 40; }
	void setTpAbajo() { this->tp = -1; x = 400, y = 600; }
	
	int getAncho() { return ancho; }
	int getAlto() { return alto; }
	void SetVida(int Vida) {
		int VidaMaxima = 120;
		int VidaMinima = 0;
		if ((this->Vida + Vida <= VidaMaxima) && 
			(this->Vida + Vida >= VidaMinima)) 
			this->Vida = this->Vida + Vida;
	}
	void SetDefenza(int Defenza) {
		this->Defenza = this->Defenza + Defenza;
	}
	void setMunicion(int Municion) {
		this->Municion = this->Municion + Municion;
	}

	void Disparar(int FuerzaX, int FuerzaY) {
		Cruces.push_back(new CBala(this->CAA.X, this->CAA.Y, FuerzaX, FuerzaY));
		numCru--;
	}

	int getNumVidas() {

		int valVida = 20;
		return (this->Vida / valVida);

	}

	Rectangle getCDI() { return CDI; }
	Rectangle getCAA() { return CAA; }

	vector<CBala*> getBalas() { return this->Cruces; }
	Rectangle getArea() { return this->CAA; }
	Direcciones getUltimaTecla() { return this->ultimaTecla; }
};