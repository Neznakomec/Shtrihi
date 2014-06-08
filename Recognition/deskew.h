//---------------------------------------------------------------------------

#ifndef deskewH
#define deskewH
#include <vcl.h>
#include <math.h>
//---------------------------------------------------------------------------
void vRotate(double viAngle, Graphics::TBitmap* pFromBitmap, Graphics::TBitmap* pToBitmap);
int orient(TImage* Image1);

class gmseDeskew
{
protected:
Graphics::TBitmap* cBmp;
public:
//
struct HougLine
{
int Count;
int Index;
double Alpha;
double d;

HougLine()
{
Count = 0;
}
};
//
double cAlphaStart;
double cAlphaStep;
int* SumFunc;
int cSteps;

// Precalculation of sin and cos.
    double* cSinA;
    double* cCosA;
// Range of d
    double cDMin;
    double cDStep;
    int cDCount;
// Count of points that fit in a line.
    int* cHMatrix;
    int cHMatrixLength;
    
~gmseDeskew()
{
delete[] cHMatrix; cHMatrix = NULL;
delete[] cSinA; cSinA = NULL;
delete[] cCosA; cCosA = NULL;
};

double GetSkewAngle()
{
gmseDeskew::HougLine* hl = NULL;
int i;
double sum = 0.0;
int count = 0;

Calc();
//Top 20 of the detected lines in the image.
hl = GetTop(20);
//Average angle of the lines
for (int i=0; i<20; i++)
 {
   sum += hl[i].Alpha;
   count += 1;//
 }


for (int alpha = 0; alpha < cSteps; alpha++)
 {
   for (int d=0; d<cDCount; d++)
   {
   int Index = d * cSteps + alpha;

   SumFunc[alpha] += cHMatrix[Index]*cHMatrix[Index];
   }

 }

while (true)
{
if (cAlphaStep < 0.05) break;

int maxAlpha = 0;
for (int alpha = 0; alpha < cSteps; alpha++)
 if (SumFunc[alpha] > SumFunc[maxAlpha])
   maxAlpha = alpha;

float AlphaStart = GetAlpha(maxAlpha-1);
float AlphaEnd = GetAlpha(maxAlpha+1);
cAlphaStep = (AlphaEnd - AlphaStart) / 5;
cAlphaStart = AlphaStart;
delete []cHMatrix;
delete []SumFunc;
cSteps = 6;

Calc();

for (int alpha = 0; alpha < cSteps; alpha++)
 {
   for (int d=0; d<cDCount; d++)
   {
   int dIndex = d;
   int Index = dIndex * cSteps + alpha;
   SumFunc[alpha] += cHMatrix[Index]*cHMatrix[Index];
   }

 }
}

int index=0;
for (int i=0; i<6; i++)
if (SumFunc[i] > SumFunc[index]) index = i;

float returnAlpha = cAlphaStart + index*cAlphaStep;
return returnAlpha;
//return sum / count;
};

gmseDeskew::HougLine* GetTop(int Count)
{
gmseDeskew::HougLine* hl = NULL;
HougLine tmp;
int AlphaIndex;
int dIndex;
delete []hl;
hl = new gmseDeskew::HougLine[Count];

for (int i=0; i<cHMatrixLength; i++)
 {
   if (cHMatrix[i] > hl[Count - 1].Count)
    {
      hl[Count - 1].Count = cHMatrix[i];
      hl[Count - 1].Index = i;
      int j = Count - 1;
      while (j >0 && hl[j].Count > hl[j-1].Count)
       {
         tmp = hl[j];
         hl[j] = hl[j - 1];
         hl[j - 1] = tmp;
         j--;
       }
    }
 }
for (int i=0; i<Count; i++)
 {
   dIndex = hl[i].Index / cSteps;
   AlphaIndex = hl[i].Index - dIndex * cSteps;
   hl[i].Alpha = GetAlpha(AlphaIndex);
   hl[i].d = dIndex + cDMin;
 }

return hl;
}

void Calc()
{
cBmp->PixelFormat = pf8bit;

Init();
for (int y = 0; y<cBmp->Height; y++)
{
unsigned char* ptr = (unsigned char*)cBmp->ScanLine[y];
for (int x=0; x < cBmp->Width; x++)
if (!ptr[x])
 Calc(x, y);
}
}

// Calculate all lines through the point (x,y).
void Calc(int x, int y)
{
int alpha;
double d;
int dIndex;
int Index;

for (alpha = 0; alpha < cSteps; alpha++)
 {
   d = y * cCosA[alpha] - x * cSinA[alpha];
   dIndex = CalcDIndex(d);
   Index = dIndex * cSteps + alpha;
   try
   { cHMatrix[Index] += 1; }
   catch (Exception* e)
   { ShowMessage(e->Message); }
 }
}

double CalcDIndex(double d)
{
 return (int)(d - cDMin);
}

bool IsBlack(int x, int y)
{
TColor c;
double luminance;

c = cBmp->Canvas->Pixels[x][y];
luminance = (GetRValue(c) * 0.299) + (GetGValue(c) * 0.587) + (GetBValue(c) * 0.114);
if (luminance < 140) return true;
return false;
}

void Init()
{
double angle;
// Precalculation of sin and cos.
cSinA = new double[cSteps];
cCosA = new double[cSteps];
for (int i=0; i<cSteps; i++)
 {
   angle = GetAlpha(i) * M_PI / 180.0;
   cSinA[i] = sin(angle);
   cCosA[i] = cos(angle);
 }
// Range of d:
cDMin = - (cBmp->Width);
cDCount = 2 * (cBmp->Width + cBmp->Height) / cDStep;
cHMatrix = new int[cDCount * cSteps];
cHMatrixLength = cDCount * cSteps;
for (int i=0; i<cHMatrixLength; i++)
cHMatrix[i] = 0;
//
SumFunc = new int[cSteps];
for (int alpha = 0; alpha < cSteps; alpha++)
        SumFunc[alpha] = 0;
}

double GetAlpha(int Index)
{
return cAlphaStart + Index * cAlphaStep;
}

gmseDeskew(Graphics::TBitmap* bmp)
 {
   cBmp = bmp;
   cAlphaStart = -45;
   cAlphaStep = 0.2;
   cSteps = 90 * 5;
   cDStep = 1;
 };

};

Graphics::TBitmap* RotateImage(Graphics::TBitmap* bmp, double angle)
{
Graphics::TBitmap* tmp = new Graphics::TBitmap();
vRotate(angle, bmp, tmp);
return tmp;
}

#endif
