// ---------------------------------------------------------------------------

#ifndef uDisplayH
#define uDisplayH
#include "uPoligono.h"
#include "uJanela.h"
#include <Vcl.ExtCtrls.hpp>
#include <vector>

using namespace std;
// ---------------------------------------------------------------------------

class DisplayFile {
	public:
		vector<Poligono>poligonos;

		void desenha(TCanvas*canvas, Janela mundo, Janela vp, int tipoReta);

		void mostrar(TListBox*lbPoligonos);
	};

#endif
