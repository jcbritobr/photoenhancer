#pragma once
#include "stdafx.h"

class CImgMelhoramento
{
private:
	RGBTRIPLE* Buffer;
	BYTE* Buffer2;
public:

	CImgMelhoramento(void);
	~CImgMelhoramento(void);
	void Limiarizar(CxImage *tmp, int nivel);
	void Clarear(CxImage* tmp, int Quantidade);
	void Escurecer(CxImage* tmp, int Quantidade);
	void MaisContraste(CxImage* tmp, int Quantidade);
	void Convolui(CxImage* tmp, int nBias, float Mascara[9]);
	void Negativo(CxImage* tmp);
	void MenosContraste(CxImage*  tmp, int  Quantidade);
	void AdicionaRuidoCor(CxImage* tmp, unsigned int Quantidade);
	void GammaCorrecao(CxImage* tmp, float Gamma);
	void EHoritontal(CxImage* tmp);
	// Faz o espelhamento vertical
	void EVertical(CxImage * tmp);
	// D� nova dimens�o � imagem digital
	void Reamostrar(CxImage* tmp, int Largura, int Altura);
	// faz a equaliza��o autom�tica da imagem baseada nos valores m�nimis e m�ximos dos pixels
	void HEqualizar(CxImage* tmp);
	// Produz esticamento de histograma(histogram streching)
	void HEsticamento(CxImage* tmp, float valor);
	// aplica soma de imagens com a finalidade de reduzir ru�dos aleat�rios
};
