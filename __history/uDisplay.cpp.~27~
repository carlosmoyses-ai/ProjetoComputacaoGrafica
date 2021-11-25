// ---------------------------------------------------------------------------

#pragma hdrstop

#include "uDisplay.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

void DisplayFile::desenha(TCanvas*canvas, Janela mundo, Janela vp, int tipoReta)
	{
		canvas->Brush->Color = clWhite;
		canvas->FillRect(Rect(0, 0, 500, 500));
		canvas->Pen->Width = 2;
		for (int x = 0; x < poligonos.size(); x++) {
				poligonos[x].desenha(canvas, mundo, vp, tipoReta);
			}
	}

void DisplayFile::mostrar(TListBox*lbPoligonos) {
		lbPoligonos->Clear();
		for (int x = 0; x < poligonos.size(); x++) {
				lbPoligonos->Items->Add(poligonos[x].toString());
			}
	}
