#pragma once

using namespace System::Drawing;

class CBala
{

private:
	int X;
	int Y;
	int DirX;
	int DirY;
public:
	CBala(int X, int Y, int DireccionX, int DireccionY) {
		this->X = X;
		this->Y = Y;
		this->DirX = DireccionX;
		this->DirY = DireccionY;
	}
	~CBala() {


	}
	void DibujarBala(BufferedGraphics^ buffer, Bitmap^ img)
	{
		buffer->Graphics->DrawImage(img, Rectangle(X, Y, 50, 50));
	}
	void MoverBala() {
		this->X = X + DirX;
		this->Y = Y + DirY;
	}
	void AnimarBala(BufferedGraphics^ buffer, Bitmap^ img) {
		DibujarBala(buffer, img);
		MoverBala();
	}
	Rectangle getArea() {
		Rectangle Area = Rectangle(X, Y, 50, 50);
		return Area;
	}
};
