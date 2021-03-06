// ---------------------------------------------------------------------------

#pragma hdrstop

#include "uReta.h"

#define _ABS_(x) ((x < 0) ? -x : x)
#define _SIGN_(x) ((x < 0) ? -1 : 1)
// ---------------------------------------------------------------------------
#pragma package(smart_init)

Reta::Reta() {
		mundo = Janela();
		vp = Janela();
	}

Reta::Reta(Janela mundo, Janela vp) {
		this->mundo = mundo;
		this->vp = vp;
	}

// ---------------------------------------------------------------------------
// RETA LINE TO
// ---------------------------------------------------------------------------
void Reta::lineTo(TCanvas*canvas, vector<Ponto>pontos, TColor cor) {
		for (int x = 0; x < pontos.size(); x++) {
				canvas->Pen->Color = cor;

				if (x == 0) {
						canvas->MoveTo(
							pontos[x].xViewPortToMundo(mundo, vp),
							pontos[x].yViewPortToMundo(mundo, vp));
					}
				else {
						canvas->LineTo(
							pontos[x].xViewPortToMundo(mundo, vp),
							pontos[x].yViewPortToMundo(mundo, vp));
					}
			}
	}

// ---------------------------------------------------------------------------
// RETA DDA
// ---------------------------------------------------------------------------
void Reta::DDA(TCanvas*canvas, vector<Ponto>pontos, TColor cor) {
		double x, y, xs, ys;
		double dx, dy, steps;
		double px0, py0, px1, py1;

		for (int i = 1; i < pontos.size(); i++) {
				px0 = pontos[i - 1].xViewPortToMundo(mundo, vp);
				py0 = pontos[i - 1].yViewPortToMundo(mundo, vp);

				px1 = pontos[i].xViewPortToMundo(mundo, vp);
				py1 = pontos[i].yViewPortToMundo(mundo, vp);

				xs = abs(px1 - px0);
				ys = abs(py1 - py0);

				steps = (xs >= ys) ? xs : ys;

				dx = (xs > 0) ? (double)(px1 - px0) / steps :
					(double)(px1 - px0);
				dy = (ys > 0) ? (double)(py1 - py0) / steps :
					(double)(py1 - py0);

				x = px0 + 0.5 * _SIGN_(dx);
				y = py0 + 0.5 * _SIGN_(dy);

				int a = 0;
				canvas->Pixels[floor(x)][floor(y)] = cor;
				while (a < steps) {
						canvas->Pixels[floor(x)][floor(y)] = cor;
						x += dx;
						y += dy;
						a++;
					}
			}
	}

// ---------------------------------------------------------------------------
// RETA DE BRESENHAM
// ---------------------------------------------------------------------------
void Reta::bresenham(TCanvas*canvas, vector<Ponto>pontos, TColor cor) {
		double px0, py0, px1, py1;
		float x, y, dx, dy, erro, signalx, signaly, tmp;
		int interchange;
		int i, j, k;
		for (int i = 1; i < pontos.size(); i++) {
				px0 = pontos[i - 1].xViewPortToMundo(mundo, vp);
				py0 = pontos[i - 1].yViewPortToMundo(mundo, vp);

				px1 = pontos[i].xViewPortToMundo(mundo, vp);
				py1 = pontos[i].yViewPortToMundo(mundo, vp);

				x = (int) px0;
				y = (int) py0;

				dx = _ABS_((px1 - px0));
				dy = _ABS_((py1 - py0));
				signalx = _SIGN_((px1 - px0));
				signaly = _SIGN_((py1 - py0));

				if (signalx < 0)
					x -= 1;
				if (signaly < 0)
					y -= 1;

				interchange = FALSE;

				if (dy > dx) {
						tmp = dx;
						dx = dy;
						dy = tmp;
						interchange = TRUE;
					}

				erro = 2 * dy - dx;

				for (int i = 0; i < dx; i++) {
						canvas->Pixels[floor(x)][floor(y)] = cor;
						while (erro >= 0.0) {
								if (interchange)
									x += signalx;
								else
									y += signaly;
								erro = erro - 2 * dx;
							}
						if (interchange)
							y += signaly;
						else
							x += signalx;
						erro = erro + 2 * dy;
					}
			}
	}
