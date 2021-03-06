// ---------------------------------------------------------------------------

#ifndef uPoligonoH
#define uPoligonoH
#include "uPonto.h"
#include "uJanela.h"
#include <vector>
#include <Vcl.ExtCtrls.hpp>

using namespace std;

// ---------------------------------------------------------------------------
class Poligono {
	public:
		int id;
		char tipo;

		vector<Ponto>pontos;

		UnicodeString toString();
		void desenha(TCanvas*canvas, Janela mundo, Janela vp, int tipoReta);
		void mostrar(TListBox*lbPontos);

		void translada(double dx, double dy);
		void reflexao(double dx, double dy);
		void escalonamento(double dx, double dy);
		void rotacao2D(double angulo);
		void rotacaoHomogenea(double angulo);
		void multiplicacaoMatriz(double matrizAuxiliar[1][3],
			double matrizUm[1][3], double matrizDois[3][3]);
		Ponto centro();
	};

#endif
