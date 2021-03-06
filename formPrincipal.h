// ---------------------------------------------------------------------------

#ifndef formPrincipalH
#define formPrincipalH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "uCircBresenham.h"

// ---------------------------------------------------------------------------
class TfrmPrincipal :public TForm {
	__published: // IDE-managed Components
		TPanel*pnlAreaDesenho;
		TImage*Imagem;
		TLabel*lblCoordenadaXY;
		TLabel*lblCoordenadaVP;
		TListBox*lbPoligonos;
		TListBox*lbPontos;
		TButton*btnCriarPoligono;
		TRadioGroup*rgTipoReta;
		TButton*btnZoomMais;
		TButton*btnRotacao2D;
		TEdit*txtAngulo;
		TButton*btnVetical;
		TButton*btnHorizontal;
		TButton*btnZoomMenos;
		TButton*btnEsticarV;
		TButton*btnComprV;
		TButton*btnEsticarH;
		TButton*btnComprH;
		TLabel*lblVertical;
		TLabel*lblHorizontal;
		TButton*btnCircBresenham;
		TEdit*edtAngulo;
		TButton*btnClipping;
		TLabel*lblReflexao;
		TComboBox*cbSelecaoMov;
		TGroupBox*gbMovimentacao;
		TButton*btnMoveUp;
		TButton*btnMoveDown;
		TButton*btnMoveLeft;
		TButton*btnRight;
		TRadioGroup*rgCurvas;
		TButton*btnCriarCurva;
		TEdit*edXWMin;
		TEdit*edYWMin;
		TEdit*edXWMax;
		TEdit*edYWMax;
		TButton*btnAtualizaMundo;
		TButton*btnRotacaoHomogenea;
		TEdit*edtHomogenea;
	TButton *btnTransladar;
	TButton *btnEscalonar;
	TEdit *edtXtransformada;
	TEdit *edtYtransformada;

		void __fastcall ImagemMouseMove(TObject*Sender, TShiftState Shift,
			int X, int Y);
		void __fastcall ImageMouseDown(TObject*Sender, TMouseButton Button,
			TShiftState Shift, int X, int Y);
		void __fastcall btnCriarPoligonoClick(TObject*Sender);
		void __fastcall lbPoligonosClick(TObject*Sender);
		void __fastcall btnZoomMaisClick(TObject*Sender);
		void __fastcall btnMoveUpClick(TObject*Sender);
		void __fastcall btnMoveDownClick(TObject*Sender);
		void __fastcall btnMoveLeftClick(TObject*Sender);
		void __fastcall btnRightClick(TObject*Sender);
		void __fastcall btnRotacao2DClick(TObject*Sender);
		void __fastcall btnVeticalClick(TObject*Sender);
		void __fastcall btnHorizontalClick(TObject*Sender);
		void __fastcall btnZoomMenosClick(TObject*Sender);
		void __fastcall btnEsticarVClick(TObject*Sender);
		void __fastcall btnComprVClick(TObject*Sender);
		void __fastcall btnEsticarHClick(TObject*Sender);
		void __fastcall btnComprHClick(TObject*Sender);
		void __fastcall btnCircBresenhamClick(TObject*Sender);
		void __fastcall rgTipoRetaClick(TObject*Sender);
		void __fastcall btnClippingClick(TObject*Sender);
		void __fastcall btnCriarCurvaClick(TObject*Sender);
		void __fastcall btnAtualizaMundoClick(TObject*Sender);
		void __fastcall btnRotacaoHomogeneaClick(TObject*Sender);
	void __fastcall btnEscalonarClick(TObject *Sender);
	void __fastcall btnTransladarClick(TObject *Sender);

	private: // User declarations
	public: // User declarations
		void atualizaMundo();
		__fastcall TfrmPrincipal(TComponent*Owner);
	};

// ---------------------------------------------------------------------------
extern PACKAGE TfrmPrincipal*frmPrincipal;
// ---------------------------------------------------------------------------
#endif
