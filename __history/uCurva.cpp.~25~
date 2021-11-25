// ---------------------------------------------------------------------------

#pragma hdrstop

#include "uCurva.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

Curva::Curva() {
		mundo = Janela();
		vp = Janela();
	}

Curva::Curva(Janela mundo, Janela vp) {
		this->mundo = mundo;
		this->vp = vp;
	}

// ---------------------------------------------------------------------------
// CURVA CASTEJAU
// ---------------------------------------------------------------------------

Poligono Curva::casteljau(Poligono pol) {
		vector<Ponto>p;
		Poligono curva;
		Poligono aux;
		aux.pontos.push_back(pol.pontos[0]);
		aux.pontos.push_back(pol.pontos[1]);
		aux.pontos.push_back(pol.pontos[2]);
		curva.pontos.push_back(pol.pontos[0]);
		desenhaCasteljauRec(&curva, aux);
		return curva;
	}

void Curva::desenhaCasteljauRec(Poligono*curva, Poligono aux) {
		Poligono curvaEsquerda;
		Poligono curvaDireita;

		if (distanciaPontos(aux.pontos[0], aux.pontos[2]) < 1) {
				curva->pontos.push_back(aux.pontos[0]);
			}
		else {
				subdividirCurva(aux, &curvaEsquerda, &curvaDireita);
				desenhaCasteljauRec(curva, curvaEsquerda);
				desenhaCasteljauRec(curva, curvaDireita);
			}
	}

double Curva::distanciaPontos(Ponto p1, Ponto p2) {
		return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
	}

void Curva::subdividirCurva(Poligono aux, Poligono*curvaEsquerda,
	Poligono*curvaDireita) {
		Ponto pontoMedio1 = pontoMedio(aux.pontos[0],
			aux.pontos[1]);
		Ponto pontoMedio2 = pontoMedio(aux.pontos[1],
			aux.pontos[2]);
		Ponto pontoMedio3 = pontoMedio(pontoMedio1, pontoMedio2);

		curvaEsquerda->pontos.push_back(aux.pontos[0]);
		curvaEsquerda->pontos.push_back(pontoMedio1);
		curvaEsquerda->pontos.push_back(pontoMedio3);

		curvaDireita->pontos.push_back(pontoMedio3);
		curvaDireita->pontos.push_back(pontoMedio2);
		curvaDireita->pontos.push_back(aux.pontos[2]);
	}

Ponto Curva::pontoMedio(Ponto p1, Ponto p2) {
		Ponto medio;
		medio.x = (p1.x + p2.x) / 2;
		medio.y = (p1.y + p2.y) / 2;
		return medio;
	}

// ---------------------------------------------------------------------------
// CURVA HERMITE
// ---------------------------------------------------------------------------
Poligono Curva::hermite(Poligono pol) {
		Ponto R1, R4;
		Poligono curva;
		Ponto pontoCurva;
		double matrizAuxiliar[1][1];
		double Cx[4][1], Cy[4][1];
		double T[1][4];

		R1.x = pol.pontos[1].x - pol.pontos[0].x;
		R1.y = pol.pontos[1].y - pol.pontos[0].y;
		R4.x = pol.pontos[3].x - pol.pontos[2].x;
		R4.y = pol.pontos[3].y - pol.pontos[2].y;

		double matrizHermite[4][4] =
			{
					{2, -2, 1, 1},
					{-3, 3, -2, -1},
					{0, 0, 1, 0},
					{1, 0, 0, 0}
			};

		double matrizX[4][1] =
			{
					{pol.pontos[0].x},
					{pol.pontos[3].x},
					{R1.x},
					{R4.x}
			};

		double matrizY[4][1] =
			{
					{pol.pontos[0].y},
					{pol.pontos[3].y},
					{R1.y},
					{R4.y}
			};

		multiplicacaoMatrizCurvas(matrizHermite, matrizX, Cx, 4);
		multiplicacaoMatrizCurvas(matrizHermite, matrizY, Cy, 4);

		for (double t = 0; t <= 1; t += 0.01) {
				T[0][0] = {t*t*t};
				T[0][1] = {t*t};
				T[0][2] = {t};
				T[0][3] = 1;

				multiplicacaoMatrizCurvas(T, Cx, matrizAuxiliar, 1);
				pontoCurva.x = matrizAuxiliar[0][0];
				multiplicacaoMatrizCurvas(T, Cy, matrizAuxiliar, 1);
				pontoCurva.y = matrizAuxiliar[0][0];

				curva.pontos.push_back(pontoCurva);
			}
		return curva;
	}

// ---------------------------------------------------------------------------
// MULTIPLICADOR DE MATRIZ
// ---------------------------------------------------------------------------
void Curva::multiplicacaoMatrizCurvas(double matrizUm[][4],
	double matrizDois[4][1], double matrizAuxiliar[][1], int matrizUmLinha) {
		int i, k;
		int j = 0;

		for (i = 0; i < matrizUmLinha; ++i) {
				matrizAuxiliar[i][j] = 0;

				for (k = 0; k < 4; ++k) {
						matrizAuxiliar[i][j] +=
							matrizUm[i][k] * matrizDois[k][j];
					}
			}
	}

// ---------------------------------------------------------------------------
// CURVA BEZIER
// ---------------------------------------------------------------------------
Poligono Curva::bezier(Poligono pol) {
		double xu = 0.0, yu = 0.0, u = 0.0;
		Poligono pAux;
		vector<Ponto>p;
		p.push_back(pol.pontos[0]);
		p.push_back(pol.pontos[1]);
		p.push_back(pol.pontos[2]);
		p.push_back(pol.pontos[3]);
		for (u = 0.0; u <= 1.0; u += 0.01)
			{
				xu = pow(1 - u, 3) * p[0].x + 3 * u * pow(1 - u, 2) * p[1].x +
					3 * pow(u, 2) * (1 - u) * p[2].x + pow(u, 3) * p[3].x;
				yu = pow(1 - u, 3) * p[0].y + 3 * u * pow(1 - u, 2) * p[1].y +
					3 * pow(u, 2) * (1 - u) * p[2].y + pow(u, 3) * p[3].y;
				pAux.pontos.push_back(Ponto(xu, yu));
			}
		return pAux;
	}

// ---------------------------------------------------------------------------
// CURVA B-SPLINE
// ---------------------------------------------------------------------------
Poligono Curva::bspline(Poligono pol) {
		Poligono curva;
		Ponto pontoCurva;
		double aux[1][1];
		double Cx[4][1], Cy[4][1];
		double T[1][4];
		double matrizBSpline[4][4] =
			{
					{-1.0 / 6.0, 3.0 / 6.0, -3.0 / 6.0, 1.0 / 6.0},
					{3.0 / 6.0, -6.0 / 6.0, 3.0 / 6.0, 0},
					{-3.0 / 6.0, 0, 3.0 / 6.0, 0},
					{1.0 / 6.0, 4.0 / 6.0, 1.0 / 6.0, 0}
			};
		for (int i = 3; i < pol.pontos.size(); i++) {
				double matrizX[4][1] =
					{
							{pol.pontos[i - 3].x},
							{pol.pontos[i - 2].x},
							{pol.pontos[i - 1].x},
							{pol.pontos[i].x}
					};
				double matrizY[4][1] =
					{
							{pol.pontos[i - 3].y},
							{pol.pontos[i - 2].y},
							{pol.pontos[i - 1].y},
							{pol.pontos[i].y}
					};
				multiplicacaoMatrizCurvas(matrizBSpline, matrizX, Cx, 4);
				multiplicacaoMatrizCurvas(matrizBSpline, matrizY, Cy, 4);
				for (double t = 0; t <= 1; t += 0.01) {
						T[0][0] = {t*t*t};
						T[0][1] = {t*t};
						T[0][2] = {t};
						T[0][3] = 1;
						multiplicacaoMatrizCurvas(T, Cx, aux, 1);
						pontoCurva.x = aux[0][0];
						multiplicacaoMatrizCurvas(T, Cy, aux, 1);
						pontoCurva.y = aux[0][0];
						curva.pontos.push_back(pontoCurva);
					}
			}
		return curva;
	}

// ---------------------------------------------------------------------------
// CURVA B-SPLINE FORWARD
// ---------------------------------------------------------------------------
Poligono Curva::forward(Poligono pol) {
		double j;
		int linha, coluna, n, i;
		Poligono aux;
		Ponto auxP(0, 0);
		double bsx[4][1] = {
					{pol.pontos[0].x},
					{pol.pontos[1].x},
					{pol.pontos[2].x},
					{pol.pontos[3].x}};
		double bsy[4][1] = {
					{pol.pontos[0].y},
					{pol.pontos[1].y},
					{pol.pontos[2].y},
					{pol.pontos[3].y}};
		double mbs[4][4] = {
					{-1, 3, -3, 1},
					{3, -6, 3, 0},
					{-3, 0, 3, 0},
					{1, 4, 1, 0}};

		for (linha = 0; linha < 4; linha++) {
				for (coluna = 0; coluna < 4; coluna++) {
						mbs[linha][coluna] = (mbs[linha][coluna]) / 6;
					}
			}
		for (i = 0; i < pol.pontos.size() - 3; i++) {
				double cx[4][1] = { {0}, {0}, {0}, {0}};
				double cy[4][1] = { {0}, {0}, {0}, {0}};
				double bsx[4][1] = {
							{pol.pontos[i].x},
							{pol.pontos[i + 1].x},
							{pol.pontos[i + 2].x},
							{pol.pontos[i + 3].x}};
				double bsy[4][1] = {
							{pol.pontos[i].y},
							{pol.pontos[i + 1].y},
							{pol.pontos[i + 2].y},
							{pol.pontos[i + 3].y}};
				for (linha = 0; linha < 4; linha++) {
						for (coluna = 0; coluna < 1; coluna++) {
								for (n = 0; n < 4; n++) {
										cx[linha][coluna] +=
										mbs[linha][n] * bsx[n][coluna];
										cy[linha][coluna] +=
										mbs[linha][n] * bsy[n][coluna];
									}
							}
					}

				double j = 0.1;
				double tx[4][1] = { {0}, {0}, {0}, {0}};
				double ty[4][1] = { {0}, {0}, {0}, {0}};
				double t[4][4] =
					{
							{0, 0, 0, 1},
							{j*j*j, j * j, j, 0},
							{6 * j * j * j, 2 * j * j, 0, 0},
							{6 * j * j * j, 0, 0, 0}
					};
				for (linha = 0; linha < 4; linha++) {
						for (coluna = 0; coluna < 1; coluna++) {
								for (n = 0; n < 4; n++) {
										tx[linha][coluna] +=
										t[linha][n] * cx[n][coluna];
										ty[linha][coluna] +=
										t[linha][n] * cy[n][coluna];
									}
							}
					}
				int a;
				aux.pontos.push_back(Ponto(tx[0][0], ty[0][0]));
				for (a = 0; a < 10; a++) {
						tx[0][0] += tx[1][0];
						tx[1][0] += tx[2][0];
						tx[2][0] += tx[3][0];
						ty[0][0] += ty[1][0];
						ty[1][0] += ty[2][0];
						ty[2][0] += ty[3][0];
						aux.pontos.push_back(Ponto(tx[0][0], ty[0][0]));
					}

			}
		return aux;
	}
