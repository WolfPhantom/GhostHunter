#pragma once

#include "VecEnemigos.h" 
#include "Beacon.h"//
#include "VecObjetos.h"

#include<stdlib.h>
#include<ctime>

#define filas 15
#define columnas 18

using namespace System;

class CMapa
{
	int **matriz;
	int x;
	int y;
	CVecEnemigos *malos; 

	VObjetos *objetos;
	int probabilidad_B;
	bool colision_B;
	
public:
	CBeacon *portal;

	CMapa(CPersonaje*prota)
	{
		matriz = new int*[filas];

		for (int a = 0; a < filas; a++)
		{
			matriz[a] = new int[columnas];

		}

		generarMatriz(); 
		malos = new CVecEnemigos(matriz, prota);
		portal = new CBeacon(matriz);
		objetos = new VObjetos();
		objetos->CrearObjetos(matriz);

	}

	CMapa(CPersonaje*prota, int NEnemigos)
	{
		matriz = new int*[filas];

		for (int a = 0; a < filas; a++)
		{
			matriz[a] = new int[columnas];

		}

		generarMatriz();
		malos = new CVecEnemigos(matriz, prota, NEnemigos); 
		portal = new CBeacon(matriz); //Gadd
		objetos = new VObjetos();
		objetos->CrearObjetos(matriz);

	}

	~CMapa() { }

	void generarMatriz()
	{
		srand(time(NULL));
		probabilidad_B = 0;
		for (int i = 0; i < filas; i++)
		{

			for (int j = 0; j < columnas; j++)
			{
				if (i == 0 || j == 0)
				{
					matriz[i][j] = 1;

				}
				else if (i == filas - 1 || j == columnas - 1)
				{
					matriz[i][j] = 1;
				}


				else
				{
					matriz[i][j] = 2;//suelo
				}



			}


		}

		for (int i = 0; i < 10; i++)
		{
			matriz[3 + rand() % (10 - 2)][1 + rand() % (15)] = 3;
		}
		matriz[0][8] = 4;
		matriz[0][9] = 4;

		matriz[14][8] = 5;
		matriz[14][9] = 5;
	}
	
	void DibujarMapa(BufferedGraphics ^buffer, Bitmap ^bmpBorde, 
		Bitmap ^bmpSuelo, Bitmap ^bmpMuro, Bitmap ^bmpArriba, 
		Bitmap ^bmpAbajo, Bitmap^imgMalo,
		Bitmap^ bmpSandwich, Bitmap^ bmpEscudo, Bitmap^  bmpCruz,
		CPersonaje *prota, Bitmap ^bmpBeacon){
		
		int X, Y = 0;
		for (int i = 0; i < filas; i++)
		{
			X = 0;
			for (int j = 0; j < columnas; j++)
			{
				if (matriz[i][j] == 1)
				{
					buffer->Graphics->DrawImage(bmpBorde, X, Y, 50, 50);
				}
				else if (matriz[i][j] == 2)
				{
					buffer->Graphics->DrawImage(bmpSuelo, X, Y, 50, 50);
				}
				else if (matriz[i][j] == 4)
				{

					buffer->Graphics->DrawImage(bmpArriba, X, Y, 50, 50);

				}
				else if (matriz[i][j] == 5)
				{
					buffer->Graphics->DrawImage(bmpAbajo, X, Y, 50, 50);


				}
				else
				{
					buffer->Graphics->DrawImage(bmpMuro, X, Y, 50, 50);

				}
				X += 50;
			}
			Y += 50;
		}

		malos->perseguir(buffer, matriz, imgMalo, prota);
		objetos->DibujarObjetos(buffer, bmpSandwich, bmpEscudo, bmpCruz);
		objetos->VerificarEstadosdeColision(prota);

		malos->VerificarColisionEnemigosBalas(prota);//

		if (probabilidad_B == 0)
		{
			portal->dibujar(buffer, bmpBeacon);

			colision_B = portal->interseccion_con_personaje(prota);
		}
	}

	int **getMatriz() { return this->matriz; }

	int getFilas() { return filas; }
	int getColumnas() { return columnas; }

	VObjetos *getObjetos() { return objetos; }

	bool getColision() { return this->colision_B; }
	void setColisionB() { colision_B = NULL; }

	CVecEnemigos *getEnemigos() { return this->malos; }
};