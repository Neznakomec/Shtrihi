//---------------------------------------------------------------------------


#pragma hdrstop

#include "deskew.h"
#define min(a, b) (((a) < (b)) ? (a) : (b)) 
#define max(a, b) (((a) > (b)) ? (a) : (b))

//---------------------------------------------------------------------------

#pragma package(smart_init)

void vRotate(double viAngle, Graphics::TBitmap* pFromBitmap, Graphics::TBitmap* pToBitmap)
{
 float vfRradians=(2*3.1416*viAngle)/360;
 float vfCosinus=(float)cos(vfRradians);
 float vfSinus=(float)sin(vfRradians);
 float vfPoint1x=(-pFromBitmap->Height*vfSinus);
 float vfPoint1y=(pFromBitmap->Height*vfCosinus);
 float vfPoint2x=(pFromBitmap->Width*vfCosinus-pFromBitmap->Height*vfSinus);
 float vfPoint2y=(pFromBitmap->Height*vfCosinus+pFromBitmap->Width*vfSinus);
 float vfPoint3x=(pFromBitmap->Width*vfCosinus);
 float vfPoint3y=(pFromBitmap->Width*vfSinus);
 float vfMinx=min(0,min(vfPoint1x,min(vfPoint2x,vfPoint3x)));
 float vfMiny=min(0,min(vfPoint1y,min(vfPoint2y,vfPoint3y)));
 float vfMaxX=max(vfPoint1x,max(vfPoint2x,vfPoint3x));
 float vfMaxY=max(vfPoint1y,max(vfPoint2y,vfPoint3y));
 int pToBitmapWidth=(int)ceil(vfMaxX-vfMinx);
 int pToBitmapHeight=(int)ceil(vfMaxY-vfMiny);
 pToBitmap->Height=pToBitmapHeight;
 pToBitmap->Width=pToBitmapWidth;
 for(int y = 0;y < pToBitmapHeight; y++)
 {
  for(int x=0;x<pToBitmapWidth;x++)
  {
   int pFromBitmapx=(int)((x+vfMinx)*vfCosinus+(y+vfMiny)*vfSinus);
   int pFromBitmapy=(int)((y+vfMiny)*vfCosinus-(x+vfMinx)*vfSinus);
   if(pFromBitmapx>=0&&pFromBitmapx<pFromBitmap->Width&&pFromBitmapy>=0&&
      pFromBitmapy<pFromBitmap->Height)
   {
    pToBitmap->Canvas->Pixels[x][y]=
    pFromBitmap->Canvas->Pixels[pFromBitmapx][pFromBitmapy];
   }
  }
 }

};
//---------------------------------------------------------------------------
int orient(TImage* Image1)
{
//0 ничего менять не надо
//1 повернуть
//2 может быть повернуть
int* HorizontalHistogram = new int[Image1->Width];
int* VerticalHistogram = new int[Image1->Height];

for (int i=0; i<Image1->Width; i++)
 HorizontalHistogram[i] = 0;
for (int i=0; i<Image1->Height; i++)
 VerticalHistogram[i] = 0;

/*for (int i=0; i<Image1->Width; i++)

 for (int j=0; j<Image1->Height; j++)
 if (Image1->Canvas->Pixels[i][j] == clBlack)
  {
   HorizontalHistogram[i]++;
   VerticalHistogram[j]++;
  }
*/
Graphics::TBitmap* bmp = Image1->Picture->Bitmap;
bmp->PixelFormat = pf8bit;

for (int j=0; j<Image1->Height; j++)
 {
   unsigned char* ptr = (unsigned char*)bmp->ScanLine[j];
   for (int i=0; i<Image1->Width; i++)
   if (!ptr[i])
    {
      HorizontalHistogram[i]++;
      VerticalHistogram[j]++;
    }
 }

int horMean = 0, verMean = 0;
int horDisp = 0, verDisp = 0;

for (int i=0; i<Image1->Width; i++)
 {
 horMean += HorizontalHistogram[i];
 horDisp += HorizontalHistogram[i]*HorizontalHistogram[i];
 }
horMean = horMean / Image1->Width;
horDisp = horDisp / Image1->Width;
horDisp = horDisp - horMean*horMean;
//
for (int i=0; i<Image1->Height; i++)
 {
 verMean += VerticalHistogram[i];
 verDisp += VerticalHistogram[i]*VerticalHistogram[i];
 }
verMean = verMean / Image1->Height;
verDisp = verDisp / Image1->Height;
verDisp = verDisp - verMean*verMean;
/*
ShowMessage("Va="+IntToStr(verMean)+" Vsigma="+IntToStr(verDisp)
                +" Ha="+IntToStr(horMean)+ "Hsigma="+IntToStr(horDisp));  */

float horParam = sqrt((float)horDisp) / (float) horMean;
float verParam = sqrt((float)verDisp) / (float) verMean;

/*ShowMessage("VertContrast="+FloatToStr(verParam)+"\nHoriContrast="+FloatToStr(horParam));*/
if (horParam >= 1.5 * verParam)
 return 1;
if (horParam > verParam)
 return 2;
if (horParam <= verParam)
 return 0;

}
