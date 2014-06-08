//---------------------------------------------------------------------------

#ifndef charprocesslibH
#define charprocesslibH

#include <iostream>
#include <vector>
#include "libs\shtrihlib.h"
//---------------------------------------------------------------------------
//�������� ���������� ������
struct ShtrihAttributes
{
   long yn;
   long yk;    // ���������� ������
   long N_p;
   long Ksw_p; // ����� � ���-�� ������� ������� �����
   long N_s;
   long Ksw_s; // ����� � ���-�� ������� ������� ������
   bool isBegin;        // ������ ���������� �������
   bool isEnd;          // ����� ���������� �������
   bool isR;            // ����������� ��������� ��������
   bool isS;            // ������� ��������� ��������
   bool isRS;           // ������� � �����������
   bool isSeparate;     // ������������� �����

   bool isAfterRS;      // ����� ����� �������/�����������

   bool isClustered;    // ����� �� ����� � ��������
   int M;               // ����������������� ����� - ����� ��������
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
    long shtrihNumbers;    //���������� �������
    int pixelSquare;       //������� (����� ��������)

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
    int DelimiterLength;        //����� ������-����������� (����. �� 2-�)
    //��� �����������
    //
    //0 - �� ����������
    //1 - ������� ������
    //2 - ������� �����������
    //3 - ������� �������
    // ( ��� startWith ����� �������/�����������
    // ��������� ��� ����� �����������)
    int startWith;
    //��� �����������
    //
    //0 - �� ����������
    //1 - ������� �����
    //2 - ������� �����������
    //3 - ������� �������
    // (��� endWith ����� �������/�����������
    // ��������� ��� ����� �������)
    int endWith;

    //������ ����, ����� �� ������� ���� ������ �� �������� �����������
    bool ToDelete;
};

//�������� ��������������� �������
struct SymbolAttributes
{
   int rowNumber;
   int* shtrihNumbers;
   ShtrihAttributes** shtrih_attrs;

   int isNumber; // ���������� ������������� �������
   int nsNumber; //���������� ������� ������
   std::vector<ShtrihCoord> nShtrih;
   int ksNumber; //���������� ������� �����
   std::vector<ShtrihCoord> kShtrih;
   int rsNumber; //���������� ������� �����������
   std::vector<ShtrihCoord> rShtrih;
   int ssNumber; //���������� ������� �������
   std::vector<ShtrihCoord> sShtrih;

   int proNumber;
   std::vector<ProAttributes*> pros;
   //������ ����� (��� �����������)
   //� ������ ������(��� �����������) ���
   //
   //(������� � ������� shtrih_attrs)
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

   int XMin;  //�������������� �� ���������� �����
   int YMin;  //����� ��� ��������� ����������� �� Canvas (MoveTo,LineTo)

   int symbolWidth;     //�����/������ �������
   int symbolHeight;    //������� �� Image->Width, Image->Height ��������
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
