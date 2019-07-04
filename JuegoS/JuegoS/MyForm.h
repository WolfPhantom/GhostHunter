#pragma once

#include"Juego.h"
#include "Busqueda.h"

namespace AEDTbFinal {


	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		CJuego *juego = new CJuego();

		Bitmap ^bmppersonaje = gcnew Bitmap("Imagenes\\Sprites.png");
		Bitmap ^bmpBorde = gcnew Bitmap("Imagenes\\bmpSolido.png");
		Bitmap ^bmpSuelo = gcnew Bitmap("Imagenes\\bmpSuelo.png");
		Bitmap ^bmpArriba = gcnew Bitmap("Imagenes\\Arriba.png");
		Bitmap ^bmpAbajo = gcnew Bitmap("Imagenes\\Abajo.png");
		Bitmap ^ bmpMuro = gcnew Bitmap("Imagenes\\bmpDestruible.png");

		Bitmap ^ bmpCruz = gcnew Bitmap("Imagenes\\Cruz.png");
		Bitmap ^ bmpEscudo = gcnew Bitmap("Imagenes\\Escudo.png");
		Bitmap ^ bmpSandwich = gcnew Bitmap("Imagenes\\Sandwich.png");

		Bitmap^ imgNumeros = gcnew Bitmap("Imagenes/Numeros.jpg");

		Bitmap^imgMalo = gcnew Bitmap("Imagenes/GhostSprite.png");
	    Bitmap^bmpBeacon = gcnew Bitmap("Imagenes/PortalSprite.png");
				
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			imgNumeros->MakeTransparent(imgNumeros->GetPixel(0, 0));
			bmpBeacon->MakeTransparent(bmpBeacon->GetPixel(0, 0));
			imgMalo->MakeTransparent(imgMalo->GetPixel(0, 0)); 
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Timer^  Cargando;
	private: System::Windows::Forms::Timer^  timer1;
	protected:
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->Cargando = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::Game);
			// 
			// Cargando
			// 
			this->Cargando->Interval = 10;
			this->Cargando->Tick += gcnew System::EventHandler(this, &MyForm::Carga);
			// 
			// MyForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(900, 750);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::PresionarTecla);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::SoltarTecla);
			this->ResumeLayout(false);

		}
#pragma endregion
	
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void Game(System::Object^  sender, System::EventArgs^  e) {

		if (juego->getPersonaje()->getVida() == 0) {
			if(juego->getPersonaje()->getNumSand() == 0)
				Close();
			else {
				juego->getPersonaje()->SetVida(120);
				juego->getPersonaje()->setNumSad(juego->getPersonaje()->getNumSand() - 1);
			}
		}
		else {
			Graphics ^g = this->CreateGraphics();
			BufferedGraphicsContext ^espacio = BufferedGraphicsManager::Current;
			BufferedGraphics ^buffer = espacio->Allocate(g, this->ClientRectangle);

			juego->Dibujar(buffer, bmpBorde, bmpSuelo, bmpMuro, bmpArriba,
				bmpAbajo, imgMalo, bmpSandwich, bmpEscudo, bmpCruz, bmpBeacon);
			juego->graficar_vidas(buffer, bmppersonaje);
			juego->graficar_objetos(buffer, bmpCruz, bmpEscudo, bmpSandwich,
				imgNumeros);

			juego->mover(buffer, bmppersonaje);

			if (juego->getPersonaje()->getTp() == 1)
			{
				if (juego->getNodo_actual()->next == nullptr)
				{
					juego->GenerarNuevoMapA();
				}

				this->juego->getPersonaje()->setTpAbajo();

				timer1->Stop();
				juego->CambiarMapaSup();
				Cargando->Start();
			}

			else if (juego->getPersonaje()->getTp() == 2)
			{
				this->juego->getPersonaje()->setTpArriba();
				juego->CambiarMapaInf();
				timer1->Stop();
				Cargando->Start();
			}
			else if (juego->beacon() == true)
			{
				this->juego->getPersonaje()->setTpAbajo();
				juego->setBeacon();
				timer1->Stop();
				Busqueda ^app = gcnew Busqueda();
				app->ShowDialog();
				int n = app->getNEnemigos();

				juego->GenerarNuevoMapS(n);
				timer1->Stop();
				juego->CambiarMapaSup();
				Cargando->Start();


			}

			buffer->Render(g);
			delete g, espacio, buffer;
		}
	}

	private: System::Void PresionarTecla(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		switch (e->KeyCode)
		{
		case Keys::Up:
			juego->getPersonaje()->direccion = Direcciones::Arriba;
			break;
		case Keys::Down:
			juego->getPersonaje()->direccion = Direcciones::Abajo;
			break;
		case Keys::Left:
			juego->getPersonaje()->direccion = Direcciones::Izquierda;
			break;
		case Keys::Right:
			juego->getPersonaje()->direccion = Direcciones::Derecha;
			break;

		case Keys::A:
			if (juego->getPersonaje()->getUltimaTecla() == Direcciones::Arriba && 
				juego->getPersonaje()->getNumCru() > 0)
				juego->getPersonaje()->Disparar(0, -30);
			if (juego->getPersonaje()->getUltimaTecla() == Direcciones::Abajo &&
				juego->getPersonaje()->getNumCru() > 0)
				juego->getPersonaje()->Disparar(0, 30);
			if (juego->getPersonaje()->getUltimaTecla() == Direcciones::Derecha &&
				juego->getPersonaje()->getNumCru() > 0)
				juego->getPersonaje()->Disparar(30, 0);
			if (juego->getPersonaje()->getUltimaTecla() == Direcciones::Izquierda &&
				juego->getPersonaje()->getNumCru() > 0)
				juego->getPersonaje()->Disparar(-30, 0);
		}

	}

	private: System::Void SoltarTecla(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		
		juego->getPersonaje()->direccion = Direcciones::Ninguna;

	}

	private: System::Void Carga(System::Object^  sender, System::EventArgs^  e) {

		timer1->Start();

		Cargando->Stop();

	}

	};
}