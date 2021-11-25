// ---------------------------------------------------------------------------

#ifndef uPontoH
#define uPontoH

#include "uJanela.h"
#include <Vcl.ExtCtrls.hpp>
// ---------------------------------------------------------------------------

class Ponto {
	public:
		double x, y;

		Ponto();

		Ponto(double pontoX, double pontoY);

		UnicodeString toString();

		double xViewPortToMundo(Janela mundo, Janela viewPort);

		double yViewPortToMundo(Janela mundo, Janela viewPort);

		void translada(double dx, double dy);

		void reflexao(double dx, double dy);

		void escalonamento(double dx, double dy);

		void rotacao2D(double angulo);

		double distanciaPontos(Ponto p1, Ponto p2);

		Ponto pontoMedio(Ponto p1, Ponto p2);

	};

#endif
