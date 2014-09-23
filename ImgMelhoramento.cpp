#include "StdAfx.h"
#include ".\imgmelhoramento.h"

CImgMelhoramento::CImgMelhoramento(void)
{
}

CImgMelhoramento::~CImgMelhoramento(void)
{
}

void CImgMelhoramento::Limiarizar(CxImage *tmp, int nivel)
{
  	tmp->GrayScale();
	for(int j=0; j<tmp->GetHeight();j++)
	{
		Buffer2 = (BYTE*) tmp->GetBits(j);
		 
		for(int i=0; i<tmp->GetWidth();i++)
		{
	      if(Buffer2[i]< nivel) Buffer2[i] = 0;
		  if(Buffer2[i]>= nivel) Buffer2[i] = 255;
		}
	}

}
void CImgMelhoramento::Clarear(CxImage* tmp, int Quantidade)
{
	for(int y=0;y<tmp->GetHeight();y++)
	{
		Buffer = (RGBTRIPLE*)tmp->GetBits(y);
		for(int x=0;x<tmp->GetWidth();x++)
		{
			Buffer[x].rgbtRed = Buffer[x].rgbtRed+((255-Buffer[x].rgbtRed)*Quantidade)/255;
			Buffer[x].rgbtGreen = Buffer[x].rgbtGreen+((255-Buffer[x].rgbtGreen)*Quantidade)/255;
			Buffer[x].rgbtBlue = Buffer[x].rgbtBlue+((255-Buffer[x].rgbtBlue)*Quantidade)/255;
		}
	}
}

void CImgMelhoramento::Escurecer(CxImage* tmp, int Quantidade)
{
	for(int y=0;y<tmp->GetHeight();y++)
	{
		Buffer = (RGBTRIPLE*)tmp->GetBits(y);
		for(int x=0;x<tmp->GetWidth();x++)
		{
			Buffer[x].rgbtRed = Buffer[x].rgbtRed-((Buffer[x].rgbtRed)*Quantidade)/255;
			Buffer[x].rgbtGreen = Buffer[x].rgbtGreen-((Buffer[x].rgbtGreen)*Quantidade)/255;
			Buffer[x].rgbtBlue = Buffer[x].rgbtBlue-((Buffer[x].rgbtBlue)*Quantidade)/255;
		}
	}
}

void CImgMelhoramento::MaisContraste(CxImage* tmp, int Quantidade)
{
		int rg,gg,bg,r,g,b;
		for(int y=0;y<tmp->GetHeight();y++)
		{
			Buffer = (RGBTRIPLE*)tmp->GetBits(y);
			for(int x=0;x<tmp->GetWidth();x++)
			{
				r = Buffer[x].rgbtRed;
				g = Buffer[x].rgbtGreen;
				b = Buffer[x].rgbtBlue;

				rg = abs((127-r)*Quantidade)/255;
				gg = abs((127-g)*Quantidade)/255;
				bg = abs((127-b)*Quantidade)/255;

				if(r>127)r=r+rg; else r = r-rg;

				if(g>127)g=g+gg; else g = g-gg;

				if(b>127)b=b+bg; else b = b-bg;

				if(r>255)r=255; if(r<0)r=0;
				if(g>255)g=255; if(g<0)g=0;
				if(b>255)b=255; if(b<0)b=0;
				
				Buffer[x].rgbtRed =(BYTE) r;
				Buffer[x].rgbtGreen = (BYTE)g;
				Buffer[x].rgbtBlue = (BYTE)b;
			}
		}
}

void CImgMelhoramento::Convolui(CxImage* tmp, int nBias, float Mascara[])
{
	RGBTRIPLE* Linha1; 
	RGBTRIPLE* Linha2; 
	RGBTRIPLE* Linha3; 
	RGBTRIPLE* Resultado; 
	int r,g,b;
	CxImage *imgResult = new CxImage(*tmp);
	
	 if(tmp->GetBpp()<24) tmp->IncreaseBpp(24);
	 
	 for(int j=1; j<=tmp->GetHeight()-2;j++)
	 {
		 Linha1 =(RGBTRIPLE*) tmp->GetBits(j-1);
		 Linha2 =(RGBTRIPLE*) tmp->GetBits(j);
		 Linha3 =(RGBTRIPLE*) tmp->GetBits(j+1);
	  Resultado =(RGBTRIPLE*) imgResult->GetBits(j);
		 
		 
		 
		 for(int i=1; i<=tmp->GetWidth()-2;i++)
		 {
			 b = (Linha1[i-1].rgbtBlue*Mascara[0])+(Linha1[i].rgbtBlue*Mascara[1])+(Linha1[i+1].rgbtBlue*Mascara[2])+
				 (Linha2[i-1].rgbtBlue*Mascara[3])+(Linha2[i].rgbtBlue*Mascara[4])+(Linha2[i+1].rgbtBlue*Mascara[5])+
				 (Linha3[i-1].rgbtBlue*Mascara[6])+(Linha3[i].rgbtBlue*Mascara[7])+(Linha3[i+1].rgbtBlue*Mascara[8]);

			 g = (Linha1[i-1].rgbtGreen*Mascara[0])+(Linha1[i].rgbtGreen*Mascara[1])+(Linha1[i+1].rgbtGreen*Mascara[2])+
				 (Linha2[i].rgbtGreen*Mascara[3])+(Linha2[i].rgbtGreen*Mascara[4])+(Linha2[i+1].rgbtGreen*Mascara[5])+
				 (Linha3[i-1].rgbtGreen*Mascara[6])+(Linha3[i].rgbtGreen*Mascara[7])+(Linha3[i+1].rgbtGreen*Mascara[8]);
		 		 
			 r = (Linha1[i-1].rgbtRed*Mascara[0])+(Linha1[i].rgbtRed*Mascara[1])+(Linha1[i+1].rgbtRed*Mascara[2])+
				 (Linha2[i-1].rgbtRed*Mascara[3])+(Linha2[i].rgbtRed*Mascara[4])+(Linha2[i+1].rgbtRed*Mascara[5])+
				 (Linha3[i-1].rgbtRed*Mascara[6])+(Linha3[i].rgbtRed*Mascara[7])+(Linha3[i+1].rgbtRed*Mascara[8]);
		 
		if(abs(b)>255)b = 255;
		if(abs(g)>255)g = 255;
		if(abs(r)>255)r = 255;
		
		if(abs(b)<0)b = 0;
		if(abs(g)<0)g = 0;
		if(abs(r)<0)r = 0;

			 Resultado[i].rgbtBlue = abs(b)/nBias;
			 Resultado[i].rgbtGreen = abs(g)/nBias;
			 Resultado[i].rgbtRed = abs(r)/nBias;
 		
		 }

	 }
	 tmp->Copy(*imgResult);
	 delete imgResult;
	 imgResult = NULL;
}

void CImgMelhoramento::Negativo(CxImage* tmp)
{
	for(int j=0; j<tmp->GetHeight();j++)
	 {
		 Buffer = (RGBTRIPLE*)tmp->GetBits(j);
		 
		 for(int i=0; i<tmp->GetWidth();i++)
		 {
			 Buffer[i].rgbtRed = 255 - Buffer[i].rgbtRed;
			 Buffer[i].rgbtGreen = 255 - Buffer[i].rgbtGreen;
			 Buffer[i].rgbtBlue = 255 - Buffer[i].rgbtBlue;
		 }

	 }
}

void CImgMelhoramento::MenosContraste(CxImage*  tmp, int  Quantidade)
{
	int rg,gg,bg,r,g,b;

		for(int y=0;y<tmp->GetHeight();y++)
		{
			Buffer = (RGBTRIPLE*)tmp->GetBits(y);
			for(int x=0;x<tmp->GetWidth();x++)
			{
				r = Buffer[x].rgbtRed;
				g = Buffer[x].rgbtGreen;
				b = Buffer[x].rgbtBlue;

				rg = abs((127-r)*Quantidade)/255;
				gg = abs((127-g)*Quantidade)/255;
				bg = abs((127-b)*Quantidade)/255;

				//if(r>127)r=r+rg;// else r = r-rg;
				if(r>127)r=r-rg;

				//if(g>127)g=g+gg; //else g = g-gg;
				if(g>127)g=g-gg;
				
				//if(b>127)b=b+bg;// else b = b-bg;
				if(b>127)b=b-bg;

				if(r>255)r=255; if(r<0)r=0;
				if(g>255)g=255; if(g<0)g=0;
				if(b>255)b=255; if(b<0)b=0;
				
				Buffer[x].rgbtRed =(BYTE) r;
				Buffer[x].rgbtGreen = (BYTE)g;
				Buffer[x].rgbtBlue = (BYTE)b;
			}
		}
}

void CImgMelhoramento::AdicionaRuidoCor(CxImage* tmp, unsigned int Quantidade)
{
	int r,g,b;

	if(tmp->GetBpp()<24) tmp->IncreaseBpp(24);
	if(tmp->GetBpp()>24) tmp->DecreaseBpp(24,0,0,0);
	for(int y=0;y<tmp->GetHeight();y++)
		{
			Buffer = (RGBTRIPLE*)tmp->GetBits(y);
			for(int x=0;x<tmp->GetWidth();x++)
			{
				if(Quantidade <= 0)	break;
				
				r = Buffer[x].rgbtRed + ((rand()%Quantidade)-(Quantidade >> 1));
				g = Buffer[x].rgbtGreen + ((rand()%Quantidade)-(Quantidade >> 1));
				b = Buffer[x].rgbtBlue + ((rand()%Quantidade)-(Quantidade >> 1));
				
				if(r>255)r=255; if(r<0)r=0;
				if(g>255)g=255; if(g<0)g=0;
				if(b>255)b=255; if(b<0)b=0;


				Buffer[x].rgbtRed = r;
				Buffer[x].rgbtGreen = g;
				Buffer[x].rgbtBlue = b;
			}
		}

}

void CImgMelhoramento::GammaCorrecao(CxImage* tmp, float Gamma)
{
	CxImage* GImagem = new CxImage(*tmp);
    double r,g,b;
	const int C = 1;

	if(GImagem)
	{
		for(int j = 0;j<GImagem->GetHeight();j++)
		{
			Buffer = (RGBTRIPLE*)GImagem->GetBits(j);
			for(int i = 0;i<GImagem->GetWidth();i++)
			{
				r =abs( C*( pow((float)Buffer[i].rgbtRed,Gamma)));
				g =abs( C*( pow((float)Buffer[i].rgbtGreen,Gamma)));
				b =abs( C*( pow((float)Buffer[i].rgbtBlue,Gamma)));
				
				if(r>255)r = 255;if(r<0)r = 0;
				if(g>255)g = 255;if(g<0)g = 0;
				if(b>255)b = 255;if(b<0)b = 0;

				Buffer[i].rgbtRed = r;
				Buffer[i].rgbtGreen = g;
				Buffer[i].rgbtBlue = b;
			}
		}
		tmp->Copy(*GImagem);
		delete GImagem;
		GImagem = NULL;
	}
}

//Faz o espelhamento horizontal da imagem
void CImgMelhoramento::EHoritontal(CxImage* tmp)
{
	if(tmp)
	{
		if(tmp->GetBpp()>24) tmp->DecreaseBpp(24,0,0,0);
		if(tmp->GetBpp()<24) tmp->IncreaseBpp(24);		
		int w = tmp->GetWidth();
		RGBTRIPLE* Original = NULL;
		CxImage *Resultado = new CxImage(*tmp); 
		for(int i=0;i<Resultado->GetHeight();i++)
		{
			Original = (RGBTRIPLE*)tmp->GetBits(i);
			Buffer   = (RGBTRIPLE*)Resultado->GetBits(i);
			for(int j=0;j<Resultado->GetWidth();j++)
			{
				Buffer[j].rgbtRed = Original[w-j].rgbtRed;
				Buffer[j].rgbtGreen = Original[w-j].rgbtGreen;
				Buffer[j].rgbtBlue = Original[w-j].rgbtBlue;
			}
		}
		tmp->Copy(*Resultado);
		delete Resultado;
		Resultado = NULL;
	}
}

// Faz o espelhamento vertical
void CImgMelhoramento::EVertical(CxImage * tmp)
{
	if(tmp)
	{
		if(tmp->GetBpp()>24) tmp->DecreaseBpp(24,0,0,0);
		if(tmp->GetBpp()<24) tmp->IncreaseBpp(24);
		int h = tmp->GetHeight();
		RGBTRIPLE* Original = NULL;
		CxImage *Resultado = new CxImage(*tmp); 
		for(int i=0;i<Resultado->GetHeight();i++)
		{
			Original = (RGBTRIPLE*)tmp->GetBits(i);
			Buffer   = (RGBTRIPLE*)Resultado->GetBits(h-1-i);
			for(int j=0;j<Resultado->GetWidth();j++)
			{
				Buffer[j].rgbtRed = Original[j].rgbtRed;
				Buffer[j].rgbtGreen = Original[j].rgbtGreen;
				Buffer[j].rgbtBlue = Original[j].rgbtBlue;
			}
		}
		tmp->Copy(*Resultado);
		delete Resultado;
		Resultado = NULL;
	}
}

// Dá nova dimensão á imagem digital
void CImgMelhoramento::Reamostrar(CxImage* tmp, int Largura, int Altura)
{
   if(tmp)
   {
	   CxImage *Resultado = new CxImage(*tmp);
	   if(Resultado)
	   {
		   Resultado->Resample(Largura, Altura, 1, 0);
		   tmp->Copy(*Resultado);
		   delete Resultado;
		   Resultado = NULL;
	   }
   }
}

// faz a equalização automática da imagem baseada nos valores mínimis e máximos dos pixels
void CImgMelhoramento::HEqualizar(CxImage* tmp)
{
	if(tmp)
	{
		//CxImage *Resultado = new CxImage(*tmp);
		if(tmp->GetBpp()<24) tmp->IncreaseBpp(24);
		else tmp->DecreaseBpp(24,0,0,0);
		int rMax = -32000;
		int rMin =  32000;
		int gMax = -32000;
		int gMin =  32000;
		int bMax = -32000;
		int bMin =  32000;

		for(int y=0;y<tmp->GetHeight();y++)
		{
			Buffer = (RGBTRIPLE*)tmp->GetBits(y);
			for(int x=0;x<tmp->GetWidth();x++)
			{
				if(Buffer[x].rgbtRed > rMax) rMax = Buffer[x].rgbtRed;
				if(Buffer[x].rgbtRed < rMin) rMin = Buffer[x].rgbtRed;

				if(Buffer[x].rgbtGreen > gMax) gMax = Buffer[x].rgbtGreen;
				if(Buffer[x].rgbtGreen < gMin) gMin = Buffer[x].rgbtGreen;

				if(Buffer[x].rgbtBlue > bMax) bMax = Buffer[x].rgbtBlue;
				if(Buffer[x].rgbtBlue < bMin) bMin = Buffer[x].rgbtBlue;

			}
		}		
	
	
		for(int y=0;y<tmp->GetHeight();y++)
		{
			Buffer = (RGBTRIPLE*)tmp->GetBits(y);
			for(int x=0;x<tmp->GetWidth();x++)
			{
				Buffer[x].rgbtRed = (255/(rMax-rMin))*(Buffer[x].rgbtRed-rMin);
				Buffer[x].rgbtGreen = (255/(gMax-gMin))*(Buffer[x].rgbtGreen-gMin);
				Buffer[x].rgbtBlue = (255/(bMax-bMin))*(Buffer[x].rgbtBlue-bMin);	
			}
		}			
	}
}

// Produz esticamento de histograma(histogram streching)
void CImgMelhoramento::HEsticamento(CxImage* tmp, float valor)
{
	int r,g,b;

	if(tmp)
	{
		if(tmp->GetBpp()<24) tmp->IncreaseBpp(24);
		else tmp->DecreaseBpp(24,0,0,0);

			for(int y=0;y<tmp->GetHeight();y++)
			{
				Buffer = (RGBTRIPLE*)tmp->GetBits(y);
				for(int x=0;x<tmp->GetWidth();x++)
				{
					r = Buffer[x].rgbtRed * valor;
					g = Buffer[x].rgbtGreen * valor;
					b = Buffer[x].rgbtBlue * valor;

					if(r>255)r=255;
					if(r<0)r=0;
					if(g>255)g=255;
					if(g<0)g=0;
					if(b>255)b=255;
					if(b<0)b=0;
					
					Buffer[x].rgbtRed = (BYTE)r;
					Buffer[x].rgbtGreen = (BYTE)g;
					Buffer[x].rgbtBlue = (BYTE)b;
				}
			}
	}
}

