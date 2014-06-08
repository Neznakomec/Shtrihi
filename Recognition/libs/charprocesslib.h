//---------------------------------------------------------------------------

#ifndef charprocesslibH
#define charprocesslibH

#include <iostream>
#include <vector>
#include "libs\shtrihlib.h"
//---------------------------------------------------------------------------
//Атрибуты отдельного штриха
struct ShtrihAttributes
{
   long yn;
   long yk;    // координаты штриха
   long N_p;
   long Ksw_p; // номер и кол-во связных штрихов слева
   long N_s;
   long Ksw_s; // номер и кол-во связных штрихов справа
   bool isBegin;        // начало растрового объекта
   bool isEnd;          // конец растрового объекта
   bool isR;            // расщепление растровых объектов
   bool isS;            // слияние растровых объектов
   bool isRS;           // слияние и расщепление
   bool isSeparate;     // изолированный штрих

   bool isAfterRS;      // штрих после слияния/расщепления

   bool isClustered;    // учтен ли штрих в кластере
   int M;               // классификационная метка - номер кластера
};

struct ShtrihCoord
{
   long row;
   long col;
   ShtrihCoord(long _row, long _col)
   {
     row = _row;
     col = _col;
   }
}; 

struct ProAttributes
{
    long shtrihNumbers;    //количество штрихов
    int pixelSquare;       //площадь (число пикселей)

    ProAttributes()
    {
        shtrihNumbers = 0;
        pixelSquare = 0.0;
        XMax = YMax = width = height = 0;
        XMin = YMin = MaxInt;
        startWith = 0;
        endWith = 0;
        DelimiterLength = 0;
        ToDelete = false;
    }

    int XMin;
    int XMax;
    int YMin;
    int YMax;
    int width;
    int height;
    int DelimiterLength;        //длина штриха-разделителя (макс. из 2-х)
    //чем порождается
    //
    //0 - не определено
    //1 - штрихом начала
    //2 - штрихом расщепления
    //3 - штрихом слияния
    // ( для startWith штрих слияния/расщепления
    // интересен как штрих расщепления)
    int startWith;
    //чем прерывается
    //
    //0 - не определено
    //1 - штрихом конца
    //2 - штрихом расщепления
    //3 - штрихом слияния
    // (для endWith штрих слияния/расщепления
    // интересен как штрих слияния)
    int endWith;

    //маркер того, стоит ли удалить этот объект на реальном изображении
    bool ToDelete;
};

//Атрибуты распознаваемого символа
struct SymbolAttributes
{
   int rowNumber;
   int* shtrihNumbers;
   ShtrihAttributes** shtrih_attrs;

   int isNumber; // количество изолированных штрихов
   int nsNumber; //количество штрихов начала
   std::vector<ShtrihCoord> nShtrih;
   int ksNumber; //количество штрихов конца
   std::vector<ShtrihCoord> kShtrih;
   int rsNumber; //количество штрихов расщепления
   std::vector<ShtrihCoord> rShtrih;
   int ssNumber; //количество штрихов слияния
   std::vector<ShtrihCoord> sShtrih;

   int proNumber;
   std::vector<ProAttributes*> pros;
   //штрихи конца (или разделители)
   //и штрихи начала(или разделители) ПРО
   //
   //(индексы в массиве shtrih_attrs)
   std::vector<ShtrihCoord> proStart;
   std::vector<ShtrihCoord> proEnd;
   
   ~SymbolAttributes()
   {
   for (int i=0; i<rowNumber; i++)
   delete[] shtrih_attrs[i];

   delete[]shtrih_attrs;

   for (int i=0; i<proNumber; i++)
    {
      delete pros[i];
      pros[i] = NULL;
    }

   proStart.clear();
   proEnd.clear();
   }

   int XMin;  //характеристики из штрихового файла
   int YMin;  //нужны для отрисовки изображения на Canvas (MoveTo,LineTo)

   int symbolWidth;     //длина/ширина символа
   int symbolHeight;    //берется из Image->Width, Image->Height картинки
};


//---------------------------------------------------------------------------
void closeLibrary();

void SymbolToAttributes(char* fileName, SymbolAttributes* OutAttributes);
 void SymbolToAttributes_debug(SymbolAttributes* testedSymbol);
 void SymbolToAttributes_debug(SymbolAttributes* testedSymbol, int startX);

void AttributesToSwStr(SymbolAttributes* InSymbol);
 void AttributesToSwStr_debug(SymbolAttributes* testedSymbol);
 void AttributesToSwStr_debug(SymbolAttributes* testedSymbol, int startX);

void SwStrToStrTags(SymbolAttributes* InSymbol);
 void SwStrToStrTags_debug(SymbolAttributes* testedSymbol);
 void SwStrToStrTags_debug(SymbolAttributes* testedSymbol, int advanced);

void StrTagsToProObjects(SymbolAttributes* InSymbol);
 void StrTagsToProObjects_debug(SymbolAttributes* testedSymbol);

void ProObjectGetStatistics(SymbolAttributes* InSymbol);
 void ProObjectGetStatistics_debug(SymbolAttributes* testedSymbol);

//Transform Part
void Transform1(SymbolAttributes* InSymbol);
 void Transform1_debug(SymbolAttributes* testedSymbol);

void Transform2(SymbolAttributes* InSymbol);
void Transform2_change_redraw_Lines(SymbolAttributes* InSymbol, bool erase);
vector<int> & GetRedrawLines();

#endif
