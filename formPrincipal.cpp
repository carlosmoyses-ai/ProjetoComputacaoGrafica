// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "formPrincipal.h"
#include "uJanela.h"
#include "uPonto.h"
#include "uDisplay.h"
#include "uPoligono.h"
#include "uClipping.h"
#include "uCurva.h"
#include <vector>

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmPrincipal*frmPrincipal;

Poligono pol;
DisplayFile display;

int contaId = 0;
bool insere = false;
bool CriarCirc = false;
Circunferencia*circBresenham;
double wx, wy;

Janela mundo(-250, -250, 250, 250);
Janela vp(0, 0, 500, 500);
Janela clipping(-100, -100, 100, 100);

Poligono paux1, paux2;
Clipping*clip;
Curva*curva;

// ---------------------------------------------------------------------------
// FUNCOES PARA X E Y EM vp
// ---------------------------------------------------------------------------
double xvpToMundo(int x, Janela mundo, Janela vp) {
		return ((x - vp.Xmin) / (vp.Xmax - vp.Xmin)) *
			(mundo.Xmax - mundo.Xmin) + mundo.Xmin;
	}

double yvpToMundo(int y, Janela mundo, Janela vp) {
		return (1 - ((y - vp.Ymin) / (vp.Ymax - vp.Ymin))) *
			(mundo.Ymax - mundo.Ymin) + mundo.Ymin;
	}

// ---------------------------------------------------------------------------
// FORM PRINCIPAL
// ---------------------------------------------------------------------------
__fastcall TfrmPrincipal::TfrmPrincipal(TComponent*Owner) :TForm(Owner) {

		// eixo horizontal (250,0)(250, 500)
		pol.pontos.push_back(Ponto(mundo.Xmin, 0));
		pol.pontos.push_back(Ponto(mundo.Xmax, 0));
		pol.id = contaId++;
		pol.tipo = 'E';
		display.poligonos.push_back(pol);
		pol.pontos.clear();

		// eixo vertical (0,250)(500, 250)
		pol.pontos.push_back(Ponto(0, mundo.Ymin));
		pol.pontos.push_back(Ponto(0, mundo.Ymax));
		pol.id = contaId++;
		pol.tipo = 'E';
		display.poligonos.push_back(pol);
		pol.pontos.clear();

		display.mostrar(lbPoligonos);

		// area de clipping
		pol.pontos.push_back(Ponto(clipping.Xmin, clipping.Ymin));
		pol.pontos.push_back(Ponto(clipping.Xmin, clipping.Ymax));
		pol.pontos.push_back(Ponto(clipping.Xmax, clipping.Ymax));
		pol.pontos.push_back(Ponto(clipping.Xmax, clipping.Ymin));
		pol.pontos.push_back(Ponto(clipping.Xmin, clipping.Ymin));
		pol.id = contaId++;
		pol.tipo = 'A';
		display.poligonos.push_back(pol);
		pol.pontos.clear();
		display.mostrar(lbPoligonos);
		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}

// ---------------------------------------------------------------------------
// AREA DE DESENHO MOSTRAR POSICOES
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::ImagemMouseMove(TObject*Sender,
	TShiftState Shift, int X, int Y) {
		int ax, ay;

		ax = (int)xvpToMundo(X, mundo, vp);
		ay = (int)yvpToMundo(Y, mundo, vp);

		lblCoordenadaXY->Caption = "(" + IntToStr(X) + "," + IntToStr(Y) + ")";
		lblCoordenadaVP->Caption = "(" + IntToStr(ax) + "," +
			IntToStr(ay) + ")";
	}

// ---------------------------------------------------------------------------
// AREA DE DESENHO PRESSIONADA
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::ImageMouseDown(TObject*Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y) {
		wx = xvpToMundo(X, mundo, vp);
		wy = yvpToMundo(Y, mundo, vp);

		if (insere) {
				if (Button == mbLeft) {
						pol.tipo = 'N';
						pol.pontos.push_back(Ponto(wx, wy));
						pol.desenha(Imagem->Canvas, mundo, vp,
							rgTipoReta->ItemIndex);
					}
				if (Button == mbRight) {
						pol.id = contaId++;
						display.poligonos.push_back(pol);
						display.mostrar(lbPoligonos);
						pol.pontos.clear();
						display.desenha(Imagem->Canvas, mundo, vp,
							rgTipoReta->ItemIndex);
						pol.mostrar(lbPontos);
						insere = false;
					}
			}

		if (CriarCirc) {
				int r = StrToInt(edtAngulo->Text);
				circBresenham =
					new Circunferencia();
				circBresenham->desenha(wx, wy, r, &pol);
				pol.desenha(Imagem->Canvas, mundo, vp,
					rgTipoReta->ItemIndex);
				pol.id = contaId++;
				pol.tipo = 'B';
				display.poligonos.push_back(pol);
				display.mostrar(lbPoligonos);
				pol.pontos.clear();
				display.desenha(Imagem->Canvas, mundo, vp,
					rgTipoReta->ItemIndex);
				pol.mostrar(lbPontos);

				circBresenham->~Circunferencia();
				CriarCirc = false;
			}

	}

// ---------------------------------------------------------------------------
// SELECAO POLIGONOS
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::lbPoligonosClick(TObject*Sender) {
		if (lbPoligonos->ItemIndex > -1)
			display.poligonos[lbPoligonos->ItemIndex].mostrar(lbPontos);
	}

// ---------------------------------------------------------------------------
// BOTAO CRIAR POLIGONO
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCriarPoligonoClick(TObject*Sender) {
		insere = true;
	}

// ---------------------------------------------------------------------------
// BOTAO ZOOM MAIS
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnZoomMaisClick(TObject*Sender) {
		if (cbSelecaoMov->ItemIndex == 0) {
				mundo.Ymax /= 2;
				mundo.Ymin /= 2;
				mundo.Xmax /= 2;
				mundo.Xmin /= 2;
				atualizaMundo();
			}
		if (cbSelecaoMov->ItemIndex == 1 && lbPoligonos->ItemIndex != -1) {
				display.poligonos[lbPoligonos->ItemIndex].escalonamento
					(2.0, 2.0);
			}

		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);

	}

// ---------------------------------------------------------------------------
// BOTAO ZOOM MENOS
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnZoomMenosClick(TObject*Sender) {
		if (cbSelecaoMov->ItemIndex == 0) {
				mundo.Ymax /= 0.5;
				mundo.Ymin /= 0.5;
				mundo.Xmax /= 0.5;
				mundo.Xmin /= 0.5;
				atualizaMundo();
			}
		if (cbSelecaoMov->ItemIndex == 1 && lbPoligonos->ItemIndex != -1) {
				display.poligonos[lbPoligonos->ItemIndex].escalonamento
					(0.5, 0.5);
			}

		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}

// ---------------------------------------------------------------------------
// BOTAO MOVIMENTAR PARA CIMA
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMoveUpClick(TObject*Sender) {
		if (cbSelecaoMov->ItemIndex == 0) {
				mundo.Ymax -= 10;
				mundo.Ymin -= 10;
				atualizaMundo();
			}
		if (cbSelecaoMov->ItemIndex == 1 && lbPoligonos->ItemIndex != -1) {
				display.poligonos[lbPoligonos->ItemIndex].translada(0, 10);
			}

		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}

// ---------------------------------------------------------------------------
// BOTAO MOVIMENTAR PARA BAIXO
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMoveDownClick(TObject*Sender) {
		if (cbSelecaoMov->ItemIndex == 0) {
				mundo.Ymax += 10;
				mundo.Ymin += 10;
				atualizaMundo();
			}
		if (cbSelecaoMov->ItemIndex == 1 && lbPoligonos->ItemIndex != -1) {
				display.poligonos[lbPoligonos->ItemIndex].translada(0, -10);
			}
		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}

// ---------------------------------------------------------------------------
// BOTAO MOVIMENTAR PARA ESQUERDA
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnMoveLeftClick(TObject*Sender) {
		if (cbSelecaoMov->ItemIndex == 0) {
				mundo.Xmax -= 10;
				mundo.Xmin -= 10;
				atualizaMundo();
			}
		if (cbSelecaoMov->ItemIndex == 1 && lbPoligonos->ItemIndex != -1) {
				display.poligonos[lbPoligonos->ItemIndex].translada(-10, 0);
			}
		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}

// ---------------------------------------------------------------------------
// BOTAO MOVIMENTAR PARA DIREITA
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRightClick(TObject*Sender) {
		if (cbSelecaoMov->ItemIndex == 0) {
				mundo.Xmax += 10;
				mundo.Xmin += 10;
				atualizaMundo();
			}
		if (cbSelecaoMov->ItemIndex == 1 && lbPoligonos->ItemIndex != -1) {
				display.poligonos[lbPoligonos->ItemIndex].translada(10, 0);
			}
		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}

// ---------------------------------------------------------------------------
// BOTAO ROTACIONAR
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRotacao2DClick(TObject*Sender) {
		display.poligonos[lbPoligonos->ItemIndex].rotacao2D
			((double)(StrToFloat(txtAngulo->Text)));
		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}

// ---------------------------------------------------------------------------
// BOTAO ESPELHAR VERTICAL
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnVeticalClick(TObject*Sender) {
		display.poligonos[lbPoligonos->ItemIndex].escalonamento(1, -1);
		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}

// ---------------------------------------------------------------------------
// BOTAO ESPELHAR HORIZONTAL
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnHorizontalClick(TObject*Sender) {
		display.poligonos[lbPoligonos->ItemIndex].escalonamento(-1, 1);
		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}

// ---------------------------------------------------------------------------
// BOTAO ESTICAR VERTICAL
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnEsticarVClick(TObject*Sender) {
		display.poligonos[lbPoligonos->ItemIndex].escalonamento(1, 1.5);
		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}

// ---------------------------------------------------------------------------
// BOTAO COMPRIMIR VERTICAL
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnComprVClick(TObject*Sender) {
		display.poligonos[lbPoligonos->ItemIndex].escalonamento(1, 0.5);
		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}

// ---------------------------------------------------------------------------
// BOTAO ESTICAR HORIZONTAL
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnEsticarHClick(TObject*Sender) {
		display.poligonos[lbPoligonos->ItemIndex].escalonamento(1.5, 1);
		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}

// ---------------------------------------------------------------------------
// BOTAO COMPRIMIR HORIZONTAL
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnComprHClick(TObject*Sender) {
		display.poligonos[lbPoligonos->ItemIndex].escalonamento(0.5, 1);
		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}

// ---------------------------------------------------------------------------
// SELECAO TIPO DE RETA
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::rgTipoRetaClick(TObject*Sender)
	{
		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}

// ---------------------------------------------------------------------------
// SELECAO CIRCUNFERENCIA DE BRESENHAN
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCircBresenhamClick(TObject*Sender) {
		if (edtAngulo->Text == "")
			{
				edtAngulo->Text = "50";
			}
		CriarCirc = true;
	}

// ---------------------------------------------------------------------------
// BOTAO DE CLIPPING
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnClippingClick(TObject*Sender)
	{
		clip = new Clipping();
		if (lbPoligonos->ItemIndex > -1) {
				paux1 = display.poligonos[lbPoligonos->ItemIndex];
				paux2 = clip->cohenSutherlandClip(clipping, paux1);
				if (paux2.pontos.size() > 0) {
						paux2.id = contaId++;
						paux2.tipo = 'R';
						display.poligonos.push_back(paux2);
						display.mostrar(lbPoligonos);
						paux2.pontos.clear();
						display.desenha(Imagem->Canvas, mundo, vp,
							rgTipoReta->ItemIndex);
						paux2.mostrar(lbPontos);
					}

			}
		clip->~Clipping();
	}

// ---------------------------------------------------------------------------
// ATUALIZA MUNDO
// ---------------------------------------------------------------------------
void TfrmPrincipal::atualizaMundo() {
		edXWMin->Text = FloatToStr(mundo.Xmin);
		edXWMax->Text = FloatToStr(mundo.Xmax);

		edYWMin->Text = FloatToStr(mundo.Ymin);
		edYWMax->Text = FloatToStr(mundo.Ymax);

		display.poligonos[0].pontos[0].x = mundo.Xmin;
		display.poligonos[0].pontos[1].x = mundo.Xmax;

		display.poligonos[1].pontos[0].y = mundo.Ymin;
		display.poligonos[1].pontos[1].y = mundo.Ymax;
	}

// ---------------------------------------------------------------------------
// CRIAR CURVAS
// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnCriarCurvaClick(TObject*Sender)
	{
		Poligono paux1, paux2;
		curva = new Curva();
		if (lbPoligonos->ItemIndex >
			-1 && display.poligonos[lbPoligonos->ItemIndex].pontos.size() >= 2)
			{
				paux1 = display.poligonos[lbPoligonos->ItemIndex];
				if (rgCurvas->ItemIndex > -1) {
						switch (rgCurvas->ItemIndex) {
							case 0:
								paux2 = curva->casteljau(paux1);
								break;
							case 1:
								paux2 = curva->bezier(paux1);
								break;
							case 2:
								paux2 = curva->hermite(paux1);
								break;
							case 3:
								paux2 = curva->bspline(paux1);
								break;
							case 4:
								paux2 = curva->forward(paux1);
								break;
							}
						paux2.id = contaId++;
						paux2.tipo = 'C';
						display.poligonos.push_back(paux2);
						display.mostrar(lbPoligonos);
						paux2.pontos.clear();
						display.desenha(Imagem->Canvas, mundo, vp,
							rgTipoReta->ItemIndex);
						paux2.mostrar(lbPontos);
					}
			}
	}

// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnAtualizaMundoClick(TObject*Sender)
	{
		mundo.Xmin = StrToFloat(edXWMin->Text);
		mundo.Ymin = StrToFloat(edYWMin->Text);
		mundo.Xmax = StrToFloat(edXWMax->Text);
		mundo.Ymax = StrToFloat(edYWMax->Text);
		atualizaMundo();
		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}

// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnRotacaoHomogeneaClick(TObject*Sender)
	{
		if (lbPoligonos->ItemIndex > -1) {
				display.poligonos[lbPoligonos->ItemIndex]
					.rotacaoHomogenea(StrToFloat(edtHomogenea->Text));
				display.desenha(Imagem->Canvas, mundo, vp,
					rgTipoReta->ItemIndex);
			}
	}
// ---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnEscalonarClick(TObject*Sender)
	{
		double x, y;
		x = StrToFloat(edtXtransformada->Text);
		y = StrToFloat(edtYtransformada->Text);
		display.poligonos[lbPoligonos->ItemIndex].escalonamento(x, y);
		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}

// ---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btnTransladarClick(TObject*Sender)
	{
		double x, y;
		x = StrToFloat(edtXtransformada->Text);
		y = StrToFloat(edtYtransformada->Text);
		display.poligonos[lbPoligonos->ItemIndex].translada(x, y);
		display.desenha(Imagem->Canvas, mundo, vp, rgTipoReta->ItemIndex);
	}
// ---------------------------------------------------------------------------
