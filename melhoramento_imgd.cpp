#include "melhoramento_imgd.h"
void CMelhoramento::Linearizar(CxImage* tmp, int Quantidade)
{
            CxImage* tmp = new CxImage(*Imagem);
			tmp->GrayScale();
			
			if(tmp->GetBpp()>8) tmp->DecreaseBpp(8,1,0,0);

			for(int j=0; j<tmp->GetHeight();j++)
			{
				Buffer = tmp->GetBits(j);
		 
				for(int i=0; i<tmp->GetWidth();i++)
				{
				if(Buffer[i]<nivel) Buffer[i] = 0;
				if(Buffer[i]>nivel) Buffer[i] = 255;
				}

			}
}