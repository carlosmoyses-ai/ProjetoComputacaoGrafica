// ---------------------------------------------------------------------------

#pragma hdrstop

#include "uJanela.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

Janela::Janela() {
	}

Janela::Janela(double winXmin, double winYmin, double winXmax, double winYmax)
	{
		Xmin = winXmin;
		Ymin = winYmin;
		Xmax = winXmax;
		Ymax = winYmax;
	}
