//---------------------------------------------------------------------------

#ifndef charpriznaklibH
#define charpriznaklibH

#include <charprocesslib.h>

//---------------------------------------------------------------------------
//Getters\Setters
std::vector<TPoint> & GetInnerArea();

//Erase variables
void PriznakiClear();

void FindAllInnerAreas(SymbolAttributes* InSymbol);
 void FindAllInnerAreas_debug(SymbolAttributes* testedSymbol);

//---------------------------------------------------------------------------
#endif
