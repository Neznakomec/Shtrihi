//---------------------------------------------------------------------------


#pragma hdrstop

#include "charprocesslib.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

std::vector<int> redrawLines;

vector<int> & GetRedrawLines()
{
return redrawLines;
}

void Transform1(SymbolAttributes* InSymbol)
{
SymbolAttributes& symbol = *InSymbol;
//пороговые значения длины и ширины объекта
int x_por;

for (int i=0; i < symbol.proNumber; i++)
 {
   // входящий отросток (от штриха начала до штриха слияния)
   if (symbol.pros[i]->startWith == 1 && symbol.pros[i]->endWith == 3)
     symbol.pros[i]->ToDelete = true;
   //исходящий отросток (от штриха расщепления до штриха конца)
   if (symbol.pros[i]->startWith == 2 && symbol.pros[i]->endWith == 1)
     symbol.pros[i]->ToDelete = true;

   //убираем объект из удаления, если его размеры значимы
   x_por = max(symbol.symbolWidth, symbol.pros[i]->DelimiterLength) / 5;
   
   if (symbol.pros[i]->ToDelete)
     if (symbol.pros[i]->width >= x_por)
       symbol.pros[i]->ToDelete = false;
 }

}

//---------------------------------------------------------------------------
void Transform2(SymbolAttributes* InSymbol)
{
SymbolAttributes& symbol = *InSymbol;

redrawLines.clear();

for (int i=0; i < symbol.rowNumber; i++)
 for (int j=0; j < symbol.shtrihNumbers[i]; j++)
  {
    if (symbol.shtrih_attrs[i][j].isR)
     {
       int k0 = symbol.shtrih_attrs[i][j].N_s;
       int k1 = k0 + symbol.shtrih_attrs[i][j].Ksw_s;
       for (int k=k0; k < k1; k++)
        if (symbol.shtrih_attrs[i+1][k].isR)
         redrawLines.push_back(i+1);
     } //1st if
    if (symbol.shtrih_attrs[i][j].isS)
     {
       int k0 = symbol.shtrih_attrs[i][j].N_p;
       int k1 = k0 + symbol.shtrih_attrs[i][j].Ksw_p;
       for (int k=k0; k < k1; k++)
        if (symbol.shtrih_attrs[i-1][k].isS)
         redrawLines.push_back(i-1);
     } //2nd if
  }

Transform2_change_redraw_Lines(InSymbol, false);
}

//---------------------------------------------------------------------------

//изменяет линию, которую надо перерисовать
//ЧИСТИТ ВСЮ ОСТАЛЬНУЮ ИНФОРМАЦИЮ
//но надо будет пересчитать коэфф-ты связи
//особые штрихи
void Transform2_change_redraw_Lines(SymbolAttributes* InSymbol, bool erase)
{
SymbolAttributes& symbol = *InSymbol;
for (int change=0; change < redrawLines.size(); change++)
{
  int i = redrawLines[change];
  ShtrihAttributes* row = new ShtrihAttributes[1];
  int yn = symbol.shtrih_attrs[i][0].yn;
  int yk = symbol.shtrih_attrs[i][symbol.shtrihNumbers[i] - 1].yk;
  row->yn = yn;
  row->yk = yk;
  symbol.shtrihNumbers[i] = 1;
  delete symbol.shtrih_attrs[i];
  symbol.shtrih_attrs[i] = row;
}

//тотальная зачистка (кроме координат yn, yk)
symbol.isNumber = 0;
symbol.nsNumber = 0;
symbol.ksNumber = 0;
symbol.rsNumber = 0;
symbol.ssNumber = 0;

for (int i=0; i < symbol.rowNumber; i++)
 for (int j=0; j < symbol.shtrihNumbers[i]; j++)
  {
    symbol.shtrih_attrs[i][j].N_p = -1;
    symbol.shtrih_attrs[i][j].Ksw_p = 0;
    symbol.shtrih_attrs[i][j].N_s = -1;
    symbol.shtrih_attrs[i][j].Ksw_s = 0;
    symbol.shtrih_attrs[i][j].isBegin = false;
    symbol.shtrih_attrs[i][j].isEnd = false;
    symbol.shtrih_attrs[i][j].isR = false;
    symbol.shtrih_attrs[i][j].isS = false;
    symbol.shtrih_attrs[i][j].isRS = false;
    symbol.shtrih_attrs[i][j].isSeparate = false;
    //инициализация параметров от кластера - РПО (ПРО)
    symbol.shtrih_attrs[i][j].isClustered = false;
    symbol.shtrih_attrs[i][j].M = 0;
  }

if (erase)
 redrawLines.clear();
}
//---------------------------------------------------------------------------

void Transform1_debug(SymbolAttributes* testedSymbol)
{
SymbolAttributes* symbol = testedSymbol;
String message = "";
for (int i=0; i<symbol->proNumber; i++)
 if (symbol->pros[i]->ToDelete)
  {
    message += "нужно удалить объект ПРО №"+IntToStr(i+1)+"\n";
    message += "Рамки объекта: ["+IntToStr(symbol->pros[i]->XMin)
                +","+IntToStr(symbol->pros[i]->XMax)
                +"]x["+IntToStr(symbol->pros[i]->YMin)
                +","+IntToStr(symbol->pros[i]->YMax) + "]\n";
  }

ShowMessage(message);
}
