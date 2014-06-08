//---------------------------------------------------------------------------

#ifndef convertlibH
#define convertlibH

#include <vcl.h>
#include "libs\shtrihlib.h"

#include <list>

using namespace std;

typedef pair<short, short> str1;
typedef pair<unsigned short, unsigned short> str2;
typedef pair<long, long> str5;

TColor ShtrihColor;

void Convert(Graphics::TBitmap* bmp, AnsiString InPath, char ShtrihFormat);
void Convert1(Graphics::TBitmap* bmp, AnsiString InPath, AnsiString OutPath);
void Convert2(Graphics::TBitmap* bmp, AnsiString InPath, AnsiString OutPath);
void Convert5(Graphics::TBitmap* bmp, AnsiString InPath, AnsiString OutPath);

void FastConvert2(Graphics::TBitmap* bmp, AnsiString InPath, AnsiString OutPath);
//---------------------------------------------------------------------------
#endif


