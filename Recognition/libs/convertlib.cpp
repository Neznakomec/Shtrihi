//---------------------------------------------------------------------------


#pragma hdrstop

#include "convertlib.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
void Convert(Graphics::TBitmap* bmp, AnsiString InPath, char ShtrihFormat)
{
AnsiString OutPath = InPath;
OutPath = ChangeFileExt(OutPath, ".str");

if (ShtrihFormat == SHTRIH_FORMAT_1)
 {
   Convert1(bmp, InPath, OutPath);
 }
if (ShtrihFormat == SHTRIH_FORMAT_2)
 {
   Convert2(bmp, InPath, OutPath);
 }
}
//---------------------------------------------------------------------------
void Convert1(Graphics::TBitmap* bmp, AnsiString InPath, AnsiString OutPath)
{
SHTRIH* ShtrihFile = NULL;
STROKA_2 ShtrihString;
//////////////////////////////////
list<str1> TempList;
TColor TempColor;
int yn, yk;

ShtrihFile = new SHTRIH();
if (ShtrihFile == NULL) return;

ShtrihFile->InitStr(OutPath.c_str(), REGWRITE, SHTRIH_FORMAT_1);
if(ShtrihFile->ErrorCode)
 {
    ShowMessage("Convert1() Error, can't initialize Shtrih Object\nInPath = "+InPath+"\nOutPath = "+OutPath);
    delete ShtrihFile; ShtrihFile = NULL; return;
 }

//начало перевода картинки в штрихи

for (int i=0; i<bmp->Width; i++)
 {
   TempList.clear();
   for (int j=0; j<bmp->Height; j++)
    {
      TempColor = bmp->Canvas->Pixels[i][j];
      if (TempColor == ShtrihColor)
       {
         yn = j;
         while ((TempColor == ShtrihColor) && (j < bmp->Height - 1))
          {
            TempColor = bmp->Canvas->Pixels[i][j+1];
            if (TempColor == ShtrihColor) j++;
          }
         yk = j;
         TempList.push_back(str1(yn, yk));
       }
    }
      ShtrihString.Length = TempList.size();
      ShtrihString.Stroka = NULL;
      if (ShtrihString.Length != 0)
       {
         ShtrihString.Stroka = new SHTRIH_2[ShtrihString.Length];
         if (ShtrihString.Stroka == NULL)
          {
            ShowMessage("Convert1() Error, can't create shtrih string");
            delete ShtrihFile; ShtrihFile = NULL; return;
          }
         list<str1>::iterator it = TempList.begin();
         for (int k = 0;
                it != TempList.end(), k<ShtrihString.Length;
                it++, k++)
          {
            // переводим yk, yn из системы [0..n-1] в систему [1..n]
            ShtrihString.Stroka[k].yn = (*it).first  + 1;
            ShtrihString.Stroka[k].yk = (*it).second + 1;
          }
       }
      ShtrihFile->PutString(ShtrihString);
      delete []ShtrihString.Stroka;
      ShtrihString.Length = 0;
 }
// конец переписывания в штрих файл
// запись информации о размерах
ShtrihFile->PutXmin(1);
ShtrihFile->PutXmax(bmp->Width);
ShtrihFile->PutYmin(1);
ShtrihFile->PutYmax(bmp->Height);
//сохранение
delete ShtrihFile; ShtrihFile = NULL;
}

//---------------------------------------------------------------------------
void Convert2(Graphics::TBitmap* bmp, AnsiString InPath, AnsiString OutPath)
{
SHTRIH* ShtrihFile = NULL;
STROKA_2U ShtrihString;
//////////////////////////////////
list<str2> TempList;
TColor TempColor;
int yn, yk;

ShtrihFile = new SHTRIH();
if (ShtrihFile == NULL) return;

ShtrihFile->InitStr(OutPath.c_str(), REGWRITE, SHTRIH_FORMAT_2);
if(ShtrihFile->ErrorCode)
 {
    ShowMessage("Convert1() Error, can't initialize Shtrih Object\nInPath = "+InPath+"\nOutPath = "+OutPath);
    delete ShtrihFile; ShtrihFile = NULL; return;
 }

//начало перевода картинки в штрихи

for (int i=0; i<bmp->Width; i++)
 {
   TempList.clear();
   for (int j=0; j<bmp->Height; j++)
    {
      TempColor = bmp->Canvas->Pixels[i][j];
      if (TempColor == ShtrihColor)
       {
         yn = j;
         while ((TempColor == ShtrihColor) && (j < bmp->Height - 1))
          {
            TempColor = bmp->Canvas->Pixels[i][j+1];
            if (TempColor == ShtrihColor) j++;
          }
         yk = j;
         TempList.push_back(str2(yn, yk));
       }
    }
      ShtrihString.Length = TempList.size();
      ShtrihString.Stroka = NULL;
      if (ShtrihString.Length != 0)
       {
         ShtrihString.Stroka = new SHTRIH_2U[ShtrihString.Length];
         if (ShtrihString.Stroka == NULL)
          {
            ShowMessage("Convert2() Error, can't create shtrih string");
            delete ShtrihFile; ShtrihFile = NULL; return;
          }
         list<str2>::iterator it = TempList.begin();
         for (int k = 0;
                it != TempList.end(), k<ShtrihString.Length;
                it++, k++)
          {
            // переводим yk, yn из системы [0..n-1] в систему [1..n]    
            ShtrihString.Stroka[k].yn = (*it).first  + 1;
            ShtrihString.Stroka[k].yk = (*it).second + 1;
          }
       }
      ShtrihFile->PutString(ShtrihString);
      delete []ShtrihString.Stroka;
      ShtrihString.Length = 0;
 }
// конец переписывания в штрих файл
// запись информации о размерах
ShtrihFile->PutXmin(1);
ShtrihFile->PutXmax(bmp->Width);
ShtrihFile->PutYmin(1);
ShtrihFile->PutYmax(bmp->Height);
//сохранение
delete ShtrihFile; ShtrihFile = NULL;
}

//---------------------------------------------------------------------------
void Convert5(Graphics::TBitmap* bmp, AnsiString InPath, AnsiString OutPath)
{
SHTRIH* ShtrihFile = NULL;
STROKA_4 ShtrihString;
//////////////////////////////////
list<str5> TempList;
TColor TempColor;
int yn, yk;

ShtrihFile = new SHTRIH();
if (ShtrihFile == NULL) return;

ShtrihFile->InitStr(OutPath.c_str(), REGWRITE, SHTRIH_FORMAT_5);
if(ShtrihFile->ErrorCode)
 {
    ShowMessage("Convert5() Error, can't initialize Shtrih Object\nInPath = "+InPath+"\nOutPath = "+OutPath);
    delete ShtrihFile; ShtrihFile = NULL; return;
 }

//начало перевода картинки в штрихи

for (int i=0; i<bmp->Width; i++)
 {
   TempList.clear();
   for (int j=0; j<bmp->Height; j++)
    {
      TempColor = bmp->Canvas->Pixels[i][j];
      if (TempColor == ShtrihColor)
       {
         yn = j;
         while ((TempColor == ShtrihColor) && (j < bmp->Height - 1))
          {
            TempColor = bmp->Canvas->Pixels[i][j+1];
            if (TempColor == ShtrihColor) j++;
          }
         yk = j;
         TempList.push_back(str5(yn, yk));
       }
    }
      ShtrihString.Length = TempList.size();
      ShtrihString.Stroka = NULL;
      if (ShtrihString.Length != 0)
       {
         ShtrihString.Stroka = new SHTRIH_4[ShtrihString.Length];
         if (ShtrihString.Stroka == NULL)
          {
            ShowMessage("Convert1() Error, can't create shtrih string");
            delete ShtrihFile; ShtrihFile = NULL; return;
          }
         list<str5>::iterator it = TempList.begin();
         for (int k = 0;
                it != TempList.end(), k<ShtrihString.Length;
                it++, k++)
          {
            // переводим yk, yn из системы [0..n-1] в систему [1..n]    
            ShtrihString.Stroka[k].yn = (*it).first  + 1;
            ShtrihString.Stroka[k].yk = (*it).second + 1;
          }
       }
      ShtrihFile->PutString(ShtrihString);
      delete []ShtrihString.Stroka;
      ShtrihString.Length = 0;
 }
// конец переписывания в штрих файл
// запись информации о размерах
ShtrihFile->PutXmin(1);
ShtrihFile->PutXmax(bmp->Width);
ShtrihFile->PutYmin(1);
ShtrihFile->PutYmax(bmp->Height);
//сохранение
delete ShtrihFile; ShtrihFile = NULL;
}
//---------------------------------------------------------------------------
//
//      FAST
//
//---------------------------------------------------------------------------

void FastConvert2(Graphics::TBitmap* bmp, AnsiString InPath, AnsiString OutPath)
{
SHTRIH* ShtrihFile = NULL;
STROKA_2U ShtrihString;
//////////////////////////////////
list<str2> TempList;
TColor TempColor;
int yn, yk;

ShtrihFile = new SHTRIH();
if (ShtrihFile == NULL) return;

ShtrihFile->InitStr(OutPath.c_str(), REGWRITE, SHTRIH_FORMAT_2);
if(ShtrihFile->ErrorCode)
 {
    ShowMessage("Convert2() Error, can't initialize Shtrih Object\nInPath = "+InPath+"\nOutPath = "+OutPath);
    delete ShtrihFile; ShtrihFile = NULL; return;
 }

//начало перевода картинки в штрихи

TPixelFormat TempPixel = bmp->PixelFormat;
bmp->PixelFormat = pf32bit;

if (bmp->Width == 0 || bmp->Height == 0)
 {
   delete ShtrihFile; ShtrihFile = NULL; return;
 }

int** BitImage = new int*[bmp->Height];
for (int y=0; y < bmp->Height; y++)
 BitImage[y] = (int*) bmp->ScanLine[y];

for (int i=0; i<bmp->Width; i++)
 {
   TempList.clear();
   for (int j=0; j<bmp->Height; j++)
    {
      TempColor = BitImage[j][i];
      if (TempColor == ShtrihColor)
       {
         yn = j;
         while ((TempColor == ShtrihColor) && (j < bmp->Height - 1))
          {
            TempColor = BitImage[j+1][i];
            if (TempColor == ShtrihColor) j++;
          }
         yk = j;
         TempList.push_back(str2(yn, yk));
       }
    }
      ShtrihString.Length = TempList.size();
      ShtrihString.Stroka = NULL;
      if (ShtrihString.Length != 0)
       {
         ShtrihString.Stroka = new SHTRIH_2U[ShtrihString.Length];
         if (ShtrihString.Stroka == NULL)
          {
            ShowMessage("Convert1() Error, can't create shtrih string");
            delete ShtrihFile; ShtrihFile = NULL; return;
          }
         list<str2>::iterator it = TempList.begin();
         for (int k = 0;
                it != TempList.end(), k<ShtrihString.Length;
                it++, k++)
          {
            // переводим yk, yn из системы [0..n-1] в систему [1..n]    
            ShtrihString.Stroka[k].yn = (*it).first  + 1;
            ShtrihString.Stroka[k].yk = (*it).second + 1;
          }
       }
      ShtrihFile->PutString(ShtrihString);
      delete []ShtrihString.Stroka;
      ShtrihString.Length = 0;
 }
// конец переписывания в штрих файл
// запись информации о размерах
ShtrihFile->PutXmin(1);
ShtrihFile->PutXmax(bmp->Width);
ShtrihFile->PutYmin(1);
ShtrihFile->PutYmax(bmp->Height);
//сохранение
delete ShtrihFile; ShtrihFile = NULL;
bmp->PixelFormat = TempPixel;
}
