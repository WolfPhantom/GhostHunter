#pragma once

namespace AEDTbFinal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Busqueda
	/// </summary>
	public ref class Busqueda : public System::Windows::Forms::Form
	{
		int n;
	public:
		Busqueda(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Busqueda()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  lblEnemigos;
	private: System::Windows::Forms::TextBox^  txtEnemigos;
	private: System::Windows::Forms::Button^  bntBuscar;
	protected:

	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->lblEnemigos = (gcnew System::Windows::Forms::Label());
			this->txtEnemigos = (gcnew System::Windows::Forms::TextBox());
			this->bntBuscar = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// lblEnemigos
			// 
			this->lblEnemigos->AutoSize = true;
			this->lblEnemigos->Location = System::Drawing::Point(12, 68);
			this->lblEnemigos->Name = L"lblEnemigos";
			this->lblEnemigos->Size = System::Drawing::Size(144, 17);
			this->lblEnemigos->TabIndex = 0;
			this->lblEnemigos->Text = L"Numero de Enemigos";
			this->lblEnemigos->Click += gcnew System::EventHandler(this, &Busqueda::label1_Click);
			// 
			// txtEnemigos
			// 
			this->txtEnemigos->Location = System::Drawing::Point(208, 68);
			this->txtEnemigos->Name = L"txtEnemigos";
			this->txtEnemigos->Size = System::Drawing::Size(100, 22);
			this->txtEnemigos->TabIndex = 1;
			// 
			// bntBuscar
			// 
			this->bntBuscar->Location = System::Drawing::Point(142, 141);
			this->bntBuscar->Name = L"bntBuscar";
			this->bntBuscar->Size = System::Drawing::Size(75, 23);
			this->bntBuscar->TabIndex = 2;
			this->bntBuscar->Text = L"Buscar";
			this->bntBuscar->UseVisualStyleBackColor = true;
			this->bntBuscar->Click += gcnew System::EventHandler(this, &Busqueda::Buscar);
			// 
			// Busqueda
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(420, 327);
			this->Controls->Add(this->bntBuscar);
			this->Controls->Add(this->txtEnemigos);
			this->Controls->Add(this->lblEnemigos);
			this->Name = L"Busqueda";
			this->Text = L"Busqueda";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void Buscar(System::Object^  sender, System::EventArgs^  e) {
		n = Convert::ToInt32(txtEnemigos->Text);
		this->Close();

	}

	public:int getNEnemigos() { return this->n; }
	};
}
