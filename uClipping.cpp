// ---------------------------------------------------------------------------

#pragma hdrstop

#include "uClipping.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

const int INSIDE = 0; // 0000
const int LEFT = 1; // 0001
const int RIGHT = 2; // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8; // 1000

Clipping::Clipping() {

	}

int Clipping::cohenCodigo(Janela clipping, double x, double y) {
		int codigo = INSIDE;
		if (x < clipping.Xmin)
			codigo |= LEFT;
		if (x > clipping.Xmax)
			codigo |= RIGHT;
		if (y < clipping.Ymin)
			codigo |= BOTTOM;
		if (y > clipping.Ymax)
			codigo |= TOP;
		return codigo;
	}

Poligono Clipping::cohenSutherlandClip(Janela clipping, Poligono pol)
	{
		Poligono aux;
		Ponto p1, p2, Paux1, Paux2;
		int code1, code2, M, code_out; ;
		for (int i = 1; i < pol.pontos.size(); i++) {
				p1 = pol.pontos[i - 1];
				p2 = pol.pontos[i];
				code1 = cohenCodigo(clipping, p1.x, p1.y);
				code2 = cohenCodigo(clipping, p2.x, p2.y);

				bool accept = false;
				while (true) {
						if ((code1 == 0) && (code2 == 0)) {
								accept = true;
								break;
							}
						else if (code1 & code2) {
								break;
							}
						else {

								int code_out;
								double x, y;

								code_out = (code1 != 0) ? code1 : code2;

								if (code_out & TOP) {

										x = p1.x + (p2.x - p1.x) *
										(clipping.Ymax - p1.y) /
										(p2.y - p1.y);
										y = clipping.Ymax;
									}
								else if (code_out & BOTTOM) {
										x = p1.x + (p2.x - p1.x) *
										(clipping.Ymin - p1.y) /
										(p2.y - p1.y);
										y = clipping.Ymin;
									}
								else if (code_out & RIGHT) {
										y = p1.y + (p2.y - p1.y) *
										(clipping.Xmax - p1.x) /
										(p2.x - p1.x);
										x = clipping.Xmax;
									}
								else if (code_out & LEFT) {
										y = p1.y + (p2.y - p1.y) *
										(clipping.Xmin - p1.x) /
										(p2.x - p1.x);
										x = clipping.Xmin;
									}
								if (code_out == code1) {
										p1.x = x;
										p1.y = y;
										code1 = cohenCodigo(clipping,
										p1.x, p1.y);
									}
								else {
										p2.x = x;
										p2.y = y;
										code2 = cohenCodigo(clipping,
										p2.x, p2.y);
									}
							}
					}
				if (accept) {

						aux.pontos.push_back(p1);
						aux.pontos.push_back(p2);
					}

			}
		return aux;

	}
