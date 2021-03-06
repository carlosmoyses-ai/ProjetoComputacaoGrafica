// ---------------------------------------------------------------------------

#ifndef uCurvaH
#define uCurvaH

#include <Vcl.StdCtrls.hpp>
#include "uJanela.h"
#include "uPonto.h"
#include "uPoligono.h"
#include <vector>
// ---------------------------------------------------------------------------

using namespace std;

class Curva {
	private:
		Janela mundo;
		Janela vp;

	public:
		Curva();
		Curva(Janela mundo, Janela vp);
		Poligono casteljau(Poligono pol);
		void desenhaCasteljauRec(Poligono*curva, Poligono aux);
		double distanciaPontos(Ponto p1, Ponto p2);
		void subdividirCurva(Poligono aux, Poligono*curvaEsquerda,
			Poligono*curvaDireita);
		Ponto pontoMedio(Ponto p1, Ponto p2);
		Poligono hermite(Poligono pol);
		Poligono bezier(Poligono pol);
		Poligono bspline(Poligono pol);
		Poligono forward(Poligono pol);
		void multiplicacaoMatrizCurvas(double matrizUm[][4],
			double matrizDois[4][1], double matrizAuxiliar[][1],
			int matrizUmLinha);
	};

#endif
