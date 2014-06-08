//---------------------------------------------------------------------------


#pragma hdrstop

#include "libs/charpriznaklib.h"

std::vector<TPoint> AreaPoints;

//---------------------------------------------------------------------------


std::vector<TPoint> & GetInnerArea()
{
return AreaPoints;
}

//---------------------------------------------------------------------------

void PriznakiClear()
{
AreaPoints.clear();
}

//---------------------------------------------------------------------------

void FindAllInnerAreas(SymbolAttributes* InSymbol)
{
SymbolAttributes& symbol = *InSymbol;
for (int i=0; i < symbol.rowNumber; i++)
 for (int j=0; j < symbol.shtrihNumbers[i]; j++)
  {
    if (symbol.shtrih_attrs[i][j].isR)
      for (int k=symbol.shtrih_attrs[i][j].N_s;
        k < symbol.shtrih_attrs[i][j].N_s+symbol.shtrih_attrs[i][j].Ksw_s; k++)
         {
           ShtrihAttributes& shtrih = symbol.shtrih_attrs[i+1][k];
           //shtrih.M - 1 = Индекс в массиве ПРО
           if (shtrih.M == 0)
            {
              if (shtrih.Ksw_s > 0)  //штрих может быть особым, но должен продолжаться другими
               AreaPoints.push_back(TPoint(i+1,shtrih.yk + 1 - symbol.YMin) );
              continue;
            }
           if (symbol.pros[shtrih.M - 1]->endWith > 1)
            AreaPoints.push_back(TPoint(i+1, shtrih.yk + 1 - symbol.YMin));
         }
  }
}

//---------------------------------------------------------------------------

void FindAllInnerAreas_debug(SymbolAttributes* testedSymbol)
{
TPoint p;
AnsiString message = "";

for (int i = 0; i < AreaPoints.size(); i++)
 {
   p = AreaPoints[i];
   message += "["+IntToStr(p.x)+";"+IntToStr(p.y)+"]\n";
 }

ShowMessage(message);

}
#pragma package(smart_init)

