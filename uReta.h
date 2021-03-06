// ---------------------------------------------------------------------------

#ifndef uRetaH
#define uRetaH

#include <Vcl.StdCtrls.hpp>
#include "uJanela.h"
#include "uPonto.h"
#include <vector>
// ---------------------------------------------------------------------------

using namespace std;

class Reta {
	private:
		Janela mundo;
		Janela vp;

	public:
		Reta();
		Reta(Janela mundo, Janela vp);
		void lineTo(TCanvas*canvas, vector<Ponto>pontos, TColor cor);
		void DDA(TCanvas*canvas, vector<Ponto>pontos, TColor cor);
		void bresenham(TCanvas*canvas, vector<Ponto>pontos, TColor cor);
	};
#endif
