// ---------------------------------------------------------------------------

#pragma hdrstop
#include "uPonto.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

Ponto::Ponto() {
		x = 0.0;
		y = 0.0;
	}

Ponto::Ponto(double pontoX, double pontoY) {
		x = pontoX;
		y = pontoY;
	}

// -----------------------------------------------------------------------------
// CALCULO DO PONTO X
// -----------------------------------------------------------------------------
double Ponto::xViewPortToMundo(Janela mundo, Janela viewPort) {
		return ((x - mundo.Xmin) / (mundo.Xmax - mundo.Xmin)) *
			(viewPort.Xmax - viewPort.Xmin);
	}

// -----------------------------------------------------------------------------
// CALCULO DO PONTO Y
// -----------------------------------------------------------------------------
double Ponto::yViewPortToMundo(Janela mundo, Janela viewPort) {
		return (1 - ((y - mundo.Ymin) / (mundo.Ymax - mundo.Ymin))) *
			(viewPort.Ymax - viewPort.Ymin);
	}

// -----------------------------------------------------------------------------
// TRANSLAÇÃO
// -----------------------------------------------------------------------------
void Ponto::translada(double dx, double dy) {
		x = x + dx;
		y = y + dy;
	}

// -----------------------------------------------------------------------------
// REFLEXÃO
// -----------------------------------------------------------------------------
void Ponto::reflexao(double dx, double dy) {
		if (dx < 0)
			x *= dx;
		if (dy < 0)
			y *= dy;
		if (dx < 0 && dy < 0) {
				x *= dx;
				y *= dy;
			}
	}

// -----------------------------------------------------------------------------
// ESCALONAMENTO
// -----------------------------------------------------------------------------
void Ponto::escalonamento(double dx, double dy) {
		x = x * dx;
		y = y * dy;
	}

// -----------------------------------------------------------------------------
// ROTAÇÃO 2D
// -----------------------------------------------------------------------------
void Ponto::rotacao2D(double angulo) {
		double coseno = cos(angulo * 3.141516 / 180);
		double seno = sin(angulo * 3.141516 / 180);
		double nx = x * coseno - y * seno;
		double ny = x * seno + y * coseno;
		x = nx;
		y = ny;
	}

UnicodeString Ponto::toString() {
		return "Ponto(" + FloatToStr(floor(x)) + ";" +
			FloatToStr(floor(y)) + ")";
	}

// ---------------------------------------------------------------------------
// DISTANCI ENTRE DOIS PONTOS
// ---------------------------------------------------------------------------
double Ponto::distanciaPontos(Ponto p1, Ponto p2) {
		return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
	}

// ---------------------------------------------------------------------------
// PONTO MEDIO
// ---------------------------------------------------------------------------
Ponto Ponto::pontoMedio(Ponto p1, Ponto p2) {
		Ponto medio;
		medio.x = (p1.x + p2.x) / 2;
		medio.y = (p1.y + p2.y) / 2;
		return medio;
	}
