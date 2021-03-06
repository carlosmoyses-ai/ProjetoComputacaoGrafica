// ---------------------------------------------------------------------------

#pragma hdrstop
#include "uPoligono.h"
#include "uReta.h"
#include <math.h>
#include "uCircBresenham.h"

#define ABS(x) ((x < 0) ? -x : x)
#define _SIGN_(x) ((x < 0) ? (-1) :(1))
// ---------------------------------------------------------------------------
#pragma package(smart_init)

double xViewPortToMundo(int x, Janela mundo, Janela viewPort) {
		return ((x - viewPort.Xmin) / (viewPort.Xmax - viewPort.Xmin)) *
			(mundo.Xmax - mundo.Xmin) + mundo.Xmin;
	}

double yViewPortToMundo(int y, Janela mundo, Janela viewPort) {
		return (1 - ((y - viewPort.Ymin) / (viewPort.Ymax - viewPort.Ymin))) *
			(mundo.Ymax - mundo.Ymin) + mundo.Ymin;
	}

// -----------------------------------------------------------------------------
// VARIAVEIS GLOBAIS
// -----------------------------------------------------------------------------
int px0 = 0, py0 = 0, px1 = 0, py1 = 0;
Circunferencia*circBresenham;
Reta*reta;

void Poligono::desenha(TCanvas*canvas, Janela mundo, Janela vp, int tipoReta) {
		reta = new Reta(mundo, vp);

		TColor cor = (tipo == 'E') ? clBlack :
			(tipo == 'N') ? clRed :
			(tipo == 'C') ? clGreen :
			(tipo == 'B') ? clPurple :
			(tipo == 'A') ? clBlue : clYellow;

		switch (tipoReta) {
			case 0:
				reta->lineTo(canvas, pontos, cor);
				break;
			case 1:
				reta->DDA(canvas, pontos, cor);
				break;
			case 2:
				reta->bresenham(canvas, pontos, cor);
				break;
			}
	}

// ---------------------------------------------------------------------------
// MOSTRA OS PONTOS DO POLIGONO
// ---------------------------------------------------------------------------
void Poligono::mostrar(TListBox*lbPontos) {
		lbPontos->Clear();
		for (int x = 0; x < pontos.size(); x++) {
				lbPontos->Items->Add(pontos[x].toString());
			}
	}

// ---------------------------------------------------------------------------
// TR5ANSLA??O
// ---------------------------------------------------------------------------
void Poligono::translada(double dx, double dy) {
		for (int x = 0; x < pontos.size(); x++) {
				pontos[x].translada(dx, dy);
			}

	}

// ---------------------------------------------------------------------------
// ESCALONAMENTO
// ---------------------------------------------------------------------------
void Poligono::escalonamento(double dx, double dy) {
		for (int x = 0; x < pontos.size(); x++) {
				pontos[x].escalonamento(dx, dy);
			}
	}

// ---------------------------------------------------------------------------
// REFLEX?O
// ---------------------------------------------------------------------------
void Poligono::reflexao(double dx, double dy) {
		for (int x = 0; x < pontos.size(); x++) {
				pontos[x].translada(dx, dy);
			}
	}

// ---------------------------------------------------------------------------
// ROTA??O
// ---------------------------------------------------------------------------
void Poligono::rotacao2D(double angulo) {
		for (int x = 0; x < pontos.size(); x++) {
				pontos[x].rotacao2D(angulo);
			}
	}

void Poligono::rotacaoHomogenea(double angulo) {
		double radiano = angulo * M_PI / 180;
		double deslocamentoX, deslocamentoY;
		double xAnterior;
		double matrizRotacao[3][3] =
			{
					{cos(radiano), sin(radiano), 0},
					{-sin(radiano), cos(radiano), 0},
					{0, 0, 1}
			};

		Ponto centroPoligono = centro();
		deslocamentoX = centroPoligono.x;
		deslocamentoY = centroPoligono.y;

		double matrizTranslacao[3][3] =
			{
					{1, 0, 0},
					{0, 1, 0},
					{deslocamentoX, deslocamentoY, 1}
			};

		double matrizTranslacaoNegativa[3][3] =
			{
					{1, 0, 0},
					{0, 1, 0},
					{-deslocamentoX, -deslocamentoY, 1}
			};

		double matrizXY[1][3] = {0, 0, 1};
		double matrizAuxiliar[1][3] = {0, 0, 1};

		multiplicacaoMatriz(matrizAuxiliar, matrizXY, matrizTranslacaoNegativa);
		multiplicacaoMatriz(matrizAuxiliar, matrizXY, matrizRotacao);
		multiplicacaoMatriz(matrizAuxiliar, matrizXY, matrizTranslacao);
	}

void Poligono::multiplicacaoMatriz(double matrizAuxiliar[1][3],
	double matrizUm[1][3], double matrizDois[3][3]) {

		for (int i = 0; i < pontos.size(); i++) {
				matrizUm[0][0] = pontos[i].x;
				matrizUm[0][1] = pontos[i].y;

				for (int l = 0; l < 1; l++) {
						for (int c = 0; c < 3; c++) {
								matrizAuxiliar[l][c] = 0;
								for (int w = 0; w < 3; w++) {
										matrizAuxiliar[l][c] =
										matrizAuxiliar[l][c] + matrizUm[l][w]
										* matrizDois[w][c];
									}
							}
					}
				pontos[i].x = matrizAuxiliar[0][0];
				pontos[i].y = matrizAuxiliar[0][1];
			}
	}

Ponto Poligono::centro() {
		double somaX = 0;
		double somaY = 0;

		for (int i = 0; i < pontos.size(); i++) {
				somaX += pontos[i].x;
				somaY += pontos[i].y;
			}

		somaX = somaX / pontos.size();
		somaY = somaY / pontos.size();

		return Ponto(somaX, somaY);
	}

UnicodeString Poligono::toString() {
		return IntToStr(id) + "- tipo" + tipo + "-" +
			IntToStr((int)pontos.size()) + " pontos";
	}
