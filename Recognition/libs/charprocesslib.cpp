//---------------------------------------------------------------------------


#pragma hdrstop

#include "charprocesslib.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

SHTRIH* ShtrihFile;
INFO_STR info_STR;

// ������� ������������ ����� ������� ���� ������� �����
void __fastcall SwStr(ShtrihAttributes* S1, long ks1, ShtrihAttributes* S2,long ks2)
{
//��������� :
//  S1- ������ � ���������������� ������� ������ ks1 ������� [0..ks1-1]
//  S2- ������� (����������� ������) � S1 ������ ������ ks2 ������� [0..ks2-1]

long  n_1, n_2; //������ ���������������� ������ � 1 � 2 �������
long yn_1, yk_1;        //������/����� �������� ������ � 1-� ������
long yn_2, yk_2;        //������/����� �������� ������ � 2-� ������

//���� ���� �� ����� ������
if(ks1 == 0 || ks2 == 0)
 return;
//���� ������ �� ���������������
if((S1[ks1-1].yk < S2[0].yn - 1) || (S2[ks2-1].yk < S1[0].yn-1))
 return;

n_1=0;
n_2=0;

while(n_1<ks1 && n_2<ks2)    //���� �� ��������� ��� ������ ����� �����
 {
   if(S1[n_1].yn>S2[ks2-1].yk + 1)
    break;      //���� ��� ������ ������ ������
                //����� ���� ������� ������ ������
   if(S2[n_2].yn>S1[ks1-1].yk + 1)
   break;       //���� ��� ������ ������ ������
                //����� ���� ������� ������ ������

   yn_1=S1[n_1].yn; yk_1=S1[n_1].yk;  //�������� ���������� �������
   yn_2=S2[n_2].yn; yk_2=S2[n_2].yk;  //� ������� ������

   if (yn_1>yk_2 + 1)   //���� ������ �� ������������ -
    {                   //������ ����� ��������� ���� �������
      n_2++; continue;
    }

   if (yk_1<yn_2 - 1)   //���� ������ �� ������������ -
    {                   //������ ����� ��������� ���� �������
      n_1++; continue;
    }

   if(S1[n_1].N_s==-1)                  //���� � ������ � ������ ������ ��� �� ����
    S1[n_1].N_s=n_2;                    //������� �� ������ �������� ������ ������

   if(S2[n_2].N_p==-1)                  //���� � ������ �� ������ ������ ��� �� ����
    S2[n_2].N_p=n_1;                    //������� �� ������ �������� ����� ������

   //��������� ����� ��������� �������
   S1[n_1].Ksw_s++;
   S2[n_2].Ksw_p++;
//-----------------------
   if(yk_1<yk_2)        //���� ��� ����������� ����� ������� ��������� �����
    n_1++;              //� ������ ������ - ������� � ��� � ���������� ������

   if(yk_1>yk_2)        //���� ��� ����������� ����� ������� ��������� �����
    n_2++;              //�� ������ ������ - ������� � ��� � ���������� ������

   if(yk_1==yk_2)       //���� � ����� ������� ������
    {                   //���������� ������������
      n_1++;            //������� � �����������
      n_2++;            //������� � ����� �������
    }
 }//end while

return;
}

void OpenShtrihFile(char* fileName)
{
ShtrihFile = NULL;
//-------------
bool ber;

ShtrihFile = new SHTRIH();
if (ShtrihFile == NULL)
 return;

ShtrihFile->InitStr(fileName, REGREAD);
if(ShtrihFile->ErrorCode)
 {
   delete ShtrihFile;
   ShtrihFile = NULL;
   return;
 }

ber = ShtrihFile->GetInfoStr(info_STR);
if(!ber)
 {
   delete ShtrihFile;
   ShtrihFile = NULL;
   return;
 }
}
//---------------------------------------------------------------------------
//<PRIVATE PROCEDURE> ������ �� ��������� ������
int checkShtrihFile(SHTRIH* sFile)
{
if (sFile == NULL)
 return 1;
if (sFile->ErrorCode)
 return 2;
return 0;
}

//<PUBLIC PROCEDURE> ����� ������ � �����������
void closeLibrary()
{
delete ShtrihFile;
ShtrihFile = NULL;
}

//---------------------------------------------------------------------------

void SymbolToAttributes(char* fileName, SymbolAttributes* OutAttributes)
{

STROKA_2U ShtrihString;
long Ns;                //��� ������� �� �������� ���������� �����

OpenShtrihFile(fileName);
if (checkShtrihFile(ShtrihFile)) return;

ShtrihString.Stroka = NULL;
ShtrihString.Stroka = new SHTRIH_2U[info_STR.CoShtrihStrokaMax];
if (ShtrihString.Stroka == NULL)
 {
   delete ShtrihFile;
   ShtrihFile = NULL;
   return;
 }
//������� ��������� ��� ������ ��������� � �������
SymbolAttributes& symbol = *OutAttributes;
symbol.isNumber = 0;
symbol.nsNumber = 0;
symbol.ksNumber = 0;
symbol.rsNumber = 0;
symbol.ssNumber = 0;
symbol.rowNumber = info_STR.XmaxRastr - info_STR.XminRastr + 1;
//����������� ���������� �� ���������� �����
symbol.XMin = info_STR.XminRastr;
symbol.YMin = info_STR.YminRastr;

symbol.shtrih_attrs = new ShtrihAttributes*[symbol.rowNumber];
symbol.shtrihNumbers = new int[symbol.rowNumber];

for(Ns = info_STR.XminRastr; Ns <= info_STR.XmaxRastr; Ns++)
 {
   ShtrihFile->GetString(ShtrihString, Ns);
   //��������� ������, ���� ����
   if (ShtrihFile->ErrorCode)
    {
      if (ShtrihString.Stroka != NULL)
       {
         delete []ShtrihString.Stroka; ShtrihString.Stroka = NULL;
       }
      delete ShtrihFile; ShtrihFile = NULL;
      return;
    }

   // ��������� �������
   int idx = Ns - info_STR.XminRastr; //���������� X
   //������� ������ ���������� � ������� � idx
   symbol.shtrih_attrs[idx] = new ShtrihAttributes[ShtrihString.Length];
   symbol.shtrihNumbers[idx] =  ShtrihString.Length;

   //������������� ������ ����� � ������ � idx
   for (int k = 0; k < ShtrihString.Length; k++)
    {
      symbol.shtrih_attrs[idx][k].yn = ShtrihString.Stroka[k].yn;
      symbol.shtrih_attrs[idx][k].yk = ShtrihString.Stroka[k].yk;
      symbol.shtrih_attrs[idx][k].N_p = -1;
      symbol.shtrih_attrs[idx][k].Ksw_p = 0;
      symbol.shtrih_attrs[idx][k].N_s = -1;
      symbol.shtrih_attrs[idx][k].Ksw_s = 0;
      symbol.shtrih_attrs[idx][k].isBegin = false;
      symbol.shtrih_attrs[idx][k].isEnd = false;
      symbol.shtrih_attrs[idx][k].isR = false;
      symbol.shtrih_attrs[idx][k].isS = false;
      symbol.shtrih_attrs[idx][k].isRS = false;
      symbol.shtrih_attrs[idx][k].isSeparate = false;
      //������������� ���������� �� �������� - ��� (���)
      symbol.shtrih_attrs[idx][k].isAfterRS = false;
      symbol.shtrih_attrs[idx][k].isClustered = false;
      symbol.shtrih_attrs[idx][k].M = 0;
    }
  }
  //end of for by columns

}
//---------------------------------------------------------------------------
void AttributesToSwStr(SymbolAttributes* InSymbol)
{
SymbolAttributes& symbol = *InSymbol;
for (int idx=0; idx<symbol.rowNumber; idx++)
  if(idx)  //����� ������� ������ � ���������� (����� ������)
   SwStr(symbol.shtrih_attrs[idx-1],symbol.shtrihNumbers[idx-1],
        symbol.shtrih_attrs[idx],symbol.shtrihNumbers[idx]);
}
//---------------------------------------------------------------------------
void SwStrToStrTags(SymbolAttributes* InSymbol)
{
SymbolAttributes& symbol = *InSymbol;
for (int i=0; i < symbol.rowNumber; i++)
 for (int j=0; j < symbol.shtrihNumbers[i]; j++)
  {
    ShtrihAttributes& cur_str = symbol.shtrih_attrs[i][j];
    // ������������� �����
    if (cur_str.Ksw_p == 0 && cur_str.Ksw_s == 0)
     { cur_str.isSeparate = true; symbol.isNumber++; continue; }
    if (cur_str.Ksw_p == 0 && cur_str.Ksw_s == 1)
     { cur_str.isBegin = true; symbol.nsNumber++; continue; }
    if (cur_str.Ksw_p == 1 && cur_str.Ksw_s == 0)
     { cur_str.isEnd = true; symbol.ksNumber++; continue; }
    if (cur_str.Ksw_p > 1)
     {
       if (cur_str.Ksw_s > 1) // ����� ������� � �����������
        { cur_str.isRS = cur_str.isR = cur_str.isS = true; symbol.rsNumber++; symbol.ssNumber++; }
       else
        { cur_str.isS = true; symbol.ssNumber++; }// ����� ������ ����� �������
       continue;
     }
    if (cur_str.Ksw_s > 1)
     { cur_str.isR = true; symbol.rsNumber++; continue; }

  }

//����� ����� �������/�����������
for (int i=0; i < symbol.rowNumber; i++)
 for (int j=0; j < symbol.shtrihNumbers[i]; j++)
  if (symbol.shtrih_attrs[i][j].isR || symbol.shtrih_attrs[i][j].isS)
   if (i < symbol.rowNumber - 1) //�� ��������� ������
    for (int k = symbol.shtrih_attrs[i][j].N_s;
        k < symbol.shtrih_attrs[i][j].N_s+symbol.shtrih_attrs[i][j].Ksw_s; k++)
     symbol.shtrih_attrs[i+1][k].isAfterRS = true;
//end
}
//---------------------------------------------------------------------------

void StrTagsToProObjects(SymbolAttributes* InSymbol)
{
SymbolAttributes& symbol = *InSymbol;

int clusterIdx = 0;     //������� ������ ��������

ShtrihCoord start(-1, -1), end(-1,-1); //������ ������/���������� ��� (��� �� �����������)

for (int i=0; i<symbol.rowNumber; i++)
 {
   for (int j=0; j<symbol.shtrihNumbers[i]; j++)
    {
      if (!symbol.shtrih_attrs[i][j].isClustered)
       {
         if (symbol.shtrih_attrs[i][j].isBegin || symbol.shtrih_attrs[i][j].isAfterRS)
          {
            clusterIdx++;

            start.row = i;
            start.col = j;

            int x=i, y=j;

            while (x < symbol.rowNumber && y >= 0 && y<symbol.shtrihNumbers[x])
             {
             //����� ��� ������������ � ������, ���� ����� ��������
               if (symbol.shtrih_attrs[x][y].isEnd)
                {
                  symbol.shtrih_attrs[x][y].isClustered = true;
                  symbol.shtrih_attrs[x][y].M = clusterIdx;
                  end.row = x;
                  end.col = y; 

                  symbol.proStart.push_back(start);
                  symbol.proEnd.push_back(end);
                  start.row = start.col = -1;
                  end.row = end.col = -1;
                  break;
                }
               if (symbol.shtrih_attrs[x][y].isR ||
                symbol.shtrih_attrs[x][y].isS)
                {
                  end.row = x;
                  end.col = y;
                  if (end.row == start.row) //����������� ���
                   {
                     clusterIdx--;
                     start.row = start.col = -1;
                     end.row = end.col = -1;
                     break;
                   }

                  symbol.proStart.push_back(start);
                  symbol.proEnd.push_back(end);
                  start.row = start.col = -1;
                  end.row = end.col = -1;
                  break;
                }
                
               symbol.shtrih_attrs[x][y].isClustered = true;
               symbol.shtrih_attrs[x][y].M = clusterIdx;
               //������� � ���������� ������ �������
               //���������
               //������� ������� ����� ������������������ ������ � ��. �������
               //������ ����� ��� ��������� � ��. �������
               y = symbol.shtrih_attrs[x][y].N_s;
               x++;

             }
          }//����� ���������������� ������ ���

       }
    }
 }
symbol.proNumber = clusterIdx;         
}
//---------------------------------------------------------------------------

void ProObjectGetStatistics(SymbolAttributes* InSymbol)
{
SymbolAttributes& symbol = *InSymbol;

symbol.pros.resize(symbol.proNumber);
for (int i=0; i < symbol.proNumber; i++)
 symbol.pros[i] = new ProAttributes();

int ProId;

for (int i=0; i<symbol.rowNumber; i++)
 {
   for (int j=0; j<symbol.shtrihNumbers[i]; j++)
    {
      ProId = symbol.shtrih_attrs[i][j].M;
      if (ProId > 0)
       {
         symbol.pros[ProId-1]->shtrihNumbers++;
         symbol.pros[ProId-1]->pixelSquare += symbol.shtrih_attrs[i][j].yk -
                                 symbol.shtrih_attrs[i][j].yn + 1;

         if (symbol.pros[ProId-1]->YMin > symbol.shtrih_attrs[i][j].yn)
           symbol.pros[ProId-1]->YMin = symbol.shtrih_attrs[i][j].yn;
         if (symbol.pros[ProId-1]->YMax < symbol.shtrih_attrs[i][j].yk)
           symbol.pros[ProId-1]->YMax = symbol.shtrih_attrs[i][j].yk;
       }

    }
 }

for (int i=0; i< symbol.proNumber; i++)
 {
   //startWith, XMin
   int x = symbol.proStart[i].row;
   int y = symbol.proStart[i].col;
   symbol.pros[i]->XMin = x;

   if (symbol.shtrih_attrs[x][y].isBegin)
    symbol.pros[i]->startWith = 1;
   else if (symbol.shtrih_attrs[x][y].isAfterRS)
    {
      y = symbol.shtrih_attrs[x][y].N_p;  //Ksw_p = 1 !!!
      x = x-1;
      if (symbol.shtrih_attrs[x][y].isS)
       symbol.pros[i]->startWith = 3;
      if (symbol.shtrih_attrs[x][y].isR)
       symbol.pros[i]->startWith = 2;
      //������ ��� ����� ������ �� �����������
      symbol.proStart[i].row = x;
      symbol.proStart[i].col = y;
    }
   //endWith, XMax
   x = symbol.proEnd[i].row;
   y = symbol.proEnd[i].col;
   symbol.pros[i]->XMax = x;

   if (symbol.shtrih_attrs[x][y].isEnd)
    symbol.pros[i]->endWith = 1;
   else if (symbol.shtrih_attrs[x][y].isR)
    symbol.pros[i]->endWith = 2;
   else if (symbol.shtrih_attrs[x][y].isS)
    symbol.pros[i]->endWith = 3;

   if (symbol.pros[i]->endWith > 1)
    symbol.pros[i]->XMax = x-1;
   //width, height
   symbol.pros[i]->width = symbol.pros[i]->XMax - symbol.pros[i]->XMin + 1;
   symbol.pros[i]->height = symbol.pros[i]->YMax - symbol.pros[i]->YMin + 1;
   //DelimiterLength
   if (symbol.pros[i]->startWith == 2)
    {
      int yn = symbol.shtrih_attrs[ symbol.proStart[i].row ]
                                  [ symbol.proStart[i].col ].yn;
      int yk = symbol.shtrih_attrs[ symbol.proStart[i].row ]
                                  [ symbol.proStart[i].col ].yk;
      symbol.pros[i]->DelimiterLength = yk - yn + 1;
    }
   if (symbol.pros[i]->endWith == 3)
    {
      int yn = symbol.shtrih_attrs[ symbol.proEnd[i].row ]
                                  [ symbol.proEnd[i].col ].yn;
      int yk = symbol.shtrih_attrs[ symbol.proEnd[i].row ]
                                  [ symbol.proEnd[i].col ].yk;
      if (yk - yn + 1 > symbol.pros[i]->DelimiterLength)
        symbol.pros[i]->DelimiterLength = yk - yn + 1;
    }
 } //end of for (i=0, ProNumber)


}


//---------------------------------------------------------------------------
void SymbolToAttributes_debug(SymbolAttributes* testedSymbol)
{
SymbolToAttributes_debug(testedSymbol, 0);
}
//---------------------------------------------------------------------------
void SymbolToAttributes_debug(SymbolAttributes* testedSymbol, int startX)
{
SymbolAttributes* symbol = testedSymbol;
AnsiString message = "";
for (int i = startX; i < symbol->rowNumber; i++)
 {
   message += "Column(x)�" + IntToStr(i) + "\n";

   for (int j=0; j < symbol->shtrihNumbers[i]; j++)
    {
      ShtrihAttributes& cur_shtrih =symbol->shtrih_attrs[i][j];
      message += "[" + IntToStr(cur_shtrih.yn) + ";"
                + IntToStr(cur_shtrih.yk) + "]";
      message += " sw_p = " + IntToStr(cur_shtrih.Ksw_p) + " from "
                + IntToStr(cur_shtrih.N_p) + ";";
      message += " sw_s = " + IntToStr(cur_shtrih.Ksw_s) + " from "
                + IntToStr(cur_shtrih.N_s) + ";";
      message += "\n";
    }
 }

ShowMessage(message);
}
//---------------------------------------------------------------------------
void AttributesToSwStr_debug(SymbolAttributes* testedSymbol)
{
AttributesToSwStr_debug(testedSymbol, 0);
}
//---------------------------------------------------------------------------
void AttributesToSwStr_debug(SymbolAttributes* testedSymbol, int startX)
{
SymbolAttributes* symbol = testedSymbol;
AnsiString message = "";
for (int i = startX; i < symbol->rowNumber; i++)
 {
   message += "Column(x)�" + IntToStr(i) + "\n";

   for (int j=0; j < symbol->shtrihNumbers[i]; j++)
    {
      ShtrihAttributes& cur_shtrih =symbol->shtrih_attrs[i][j];
      message += "[" + IntToStr(cur_shtrih.yn) + ";"
                + IntToStr(cur_shtrih.yk) + "]";
      message += " sw_p = " + IntToStr(cur_shtrih.Ksw_p) + " from "
                + IntToStr(cur_shtrih.N_p) + ";";
      message += " sw_s = " + IntToStr(cur_shtrih.Ksw_s) + " from "
                + IntToStr(cur_shtrih.N_s) + ";";
      message += "\n";
    }
 }

ShowMessage(message);
}
//---------------------------------------------------------------------------
void SwStrToStrTags_debug(SymbolAttributes* testedSymbol)
{
SwStrToStrTags_debug(testedSymbol, 0);
}

//---------------------------------------------------------------------------

void SwStrToStrTags_debug(SymbolAttributes* testedSymbol, int advanced)
{
SymbolAttributes* symbol = testedSymbol;
String message = "";
message += "������� ������ " + IntToStr(symbol->nsNumber) + "\n";
if (advanced & 1)
 for (int i=0; i<symbol->rowNumber; i++)
  for (int j=0; j<symbol->shtrihNumbers[i]; j++)
   if (symbol->shtrih_attrs[i][j].isBegin)
    message += IntToStr(i) + ", ["
                + IntToStr(symbol->shtrih_attrs[i][j].yn) + ";"
                + IntToStr(symbol->shtrih_attrs[i][j].yk) + "]" + "\n";

message += "������� ����� " + IntToStr(symbol->ksNumber) + "\n";
if (advanced & 2)
  for (int i=0; i<symbol->rowNumber; i++)
   for (int j=0; j<symbol->shtrihNumbers[i]; j++)
    if (symbol->shtrih_attrs[i][j].isEnd)
     message += IntToStr(i) + ", ["
                + IntToStr(symbol->shtrih_attrs[i][j].yn) + ";"
                + IntToStr(symbol->shtrih_attrs[i][j].yk) + "]" + "\n";

message += "������� ������� " + IntToStr(symbol->ssNumber) + "\n";
if (advanced & 4)
  for (int i=0; i<symbol->rowNumber; i++)
   for (int j=0; j<symbol->shtrihNumbers[i]; j++)
    if (symbol->shtrih_attrs[i][j].isS)
     message += IntToStr(i) + ", ["
                + IntToStr(symbol->shtrih_attrs[i][j].yn) + ";"
                + IntToStr(symbol->shtrih_attrs[i][j].yk) + "]" + "\n";

message += "������� ����������� " + IntToStr(symbol->rsNumber) + "\n";
if (advanced & 8)
  for (int i=0; i<symbol->rowNumber; i++)
   for (int j=0; j<symbol->shtrihNumbers[i]; j++)
    if (symbol->shtrih_attrs[i][j].isR)
     message += IntToStr(i) + ", ["
                + IntToStr(symbol->shtrih_attrs[i][j].yn) + ";"
                + IntToStr(symbol->shtrih_attrs[i][j].yk) + "]" + "\n";

if (advanced & 16)
 {
   message += "��������� ������ ����� �������/�����������: \n";
   for (int i=0; i<symbol->rowNumber; i++)
    for (int j=0; j<symbol->shtrihNumbers[i]; j++)
     if (symbol->shtrih_attrs[i][j].isAfterRS)
      message += IntToStr(i) + ", ["
                + IntToStr(symbol->shtrih_attrs[i][j].yn) + ";"
                + IntToStr(symbol->shtrih_attrs[i][j].yk) + "]" + "\n";
 }

ShowMessage(message);
}

//---------------------------------------------------------------------------
void StrTagsToProObjects_debug(SymbolAttributes* testedSymbol)
{
SymbolAttributes* symbol = testedSymbol;
String message = "";

message += "����� ������� ��������� ��������:\n" + IntToStr(symbol->proNumber);
ShowMessage(message);
}

//---------------------------------------------------------------------------
void ProObjectGetStatistics_debug(SymbolAttributes* testedSymbol)
{
SymbolAttributes* symbol = testedSymbol;
String message = "";
for (int i=0; i<symbol->proNumber; i++)
 {
   message += "��� ������ �"+IntToStr(i+1)+":\n";
   message += "����� ������� "+IntToStr(symbol->pros[i]->shtrihNumbers)+
                ", ����� ������� "+FloatToStr(symbol->pros[i]->pixelSquare)
                +" ����.\n";
   message += "������ ���������� � ";
   switch (symbol->pros[i]->startWith)
    {
      case 1: message += "������ ������"; break;
      case 2: message += "������ �����������"; break;
      case 3: message += "������ �������"; break;
    }
   message += "\n";
      message += "������ �������������";
   switch (symbol->pros[i]->endWith)
    {
      case 1: message += "������� �����"; break;
      case 2: message += "������� �����������"; break;
      case 3: message += "������� �������"; break;
    }
   message += "\n";

   message += "����� �������: ["+IntToStr(symbol->pros[i]->XMin)
                +","+IntToStr(symbol->pros[i]->XMax)
                +"]x["+IntToStr(symbol->pros[i]->YMin)
                +","+IntToStr(symbol->pros[i]->YMax) + "]\n";
 }
ShowMessage(message);
}

