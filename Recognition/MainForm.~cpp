//---------------------------------------------------------------------------
#define NO_WIN32_LEAN_AND_MEAN
#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "SettingForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "JPEG.hpp"
//---------------------------------------------------------------------------
#include "libs\convertlib.h"
#include "libs\shtrihlib.h"
#include "libs\charprocesslib.h"
#include "libs\charpriznaklib.h"
#include "deskew.h"
//---------------------------------------------------------------------------
#include <vector>
#include <queue>
#include <stack>

#include <windows.h>
#include <shlobj.h>
#include <stdio.h>
#include <stdlib.h>



#include <segment.h>
TMainWindow *MainWindow;

std::vector<TRect> vt;
std::vector<TPoint> start;
int index = 1;
int selindex = -1;

//---------------------------------------------------------------------------
__fastcall TMainWindow::TMainWindow(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainWindow::OpenButtonClick(TObject *Sender)
{
index = 1;
selindex = -1;

vt.clear();
start.clear();
ContourList->Items->Clear();
//
if (OpenPictureFileDialog->Execute())
Image1->Picture->LoadFromFile(OpenPictureFileDialog->FileName);

SegmentButton->Enabled = true;
}

//---------------------------------------------------------------------------

void SegmentContour(int& minX, int& minY, int& maxX, int& maxY)
{
	//запоминаем стартовую точку
	start.push_back(TPoint(minX, minY));

	BFS(minX, minY, maxX, maxY);

	MainWindow->ContourList->Items->Add("Contour№"+IntToStr(index)+
		" x="+IntToStr(minX)+"y="+IntToStr(minY)+"x="+IntToStr(maxX)+"y="+IntToStr(maxY));

	vt.push_back(TRect(minX-1, minY-1, maxX+1, maxY+1));
	index++;
}
//---------------------------------------------------------------------------

void RestoreColor(TColor oldColor, TColor newColor)
{
	TImage* img = MainWindow->Image1;
	for (int i=0; i<img->Width; i++)
		for (int j=0; j<img->Height; j++)
			if (img->Canvas->Pixels[i][j] == oldColor)
				img->Canvas->Pixels[i][j] = newColor;
}

//---------------------------------------------------------------------------

void SortContourList()
{
	int index = 0;  //индекс текущей обрабатываемой позиции
	TPoint tempPoint;
	TRect tempRect;
	int ymin_index;
	while (index < start.size())
	{
		ymin_index = index;
		//находим индекс самого верхнего контура
		for (int i=index; i<start.size(); i++)
		{
			tempPoint = start[i];
			if (tempPoint.y < start[ymin_index].y)
				ymin_index = i;
		}
		tempRect = vt[index]; vt[index] = vt[ymin_index]; vt[ymin_index] = tempRect;
		tempPoint = start[index]; start[index] = start[ymin_index]; start[ymin_index] = tempPoint;
		int indexUp = index+1;
		int strTop = vt[index].Top;
		int strBottom = vt[index].Bottom;
		//присоединяем к нему контуры в одной с ним строке

		for (int i=indexUp; i < vt.size(); i++)
		{
			if (vt[i].Top > strBottom) continue;
			if (strTop > vt[i].Bottom) continue;
			//иначе есть пересечение
			int ymin = max(strTop, vt[i].Top);
			int ymax = min(strBottom, vt[i].Bottom);
			float InterSize = ymax - ymin + 1;
			float height = vt[i].Bottom - vt[i].Top + 1;
			if (InterSize / height > 0.3)
			{
				tempRect = vt[i]; vt[i] = vt[indexUp]; vt[indexUp] = tempRect;
				tempPoint = start[i]; start[i] = start[indexUp]; start[indexUp] = tempPoint;
				strTop = min(strTop, vt[indexUp].Top);
				strBottom = max(strBottom, vt[indexUp].Bottom);
				indexUp++;
			}
		}
		//сортировка в строке
		for (int i=index; i<indexUp; i++)
			for (int j=i; j<indexUp; j++)
				if (vt[i].Left > vt[j].Left)
				{
					tempRect = vt[i]; vt[i] = vt[j]; vt[j] = tempRect;
					tempPoint = start[i]; start[i] = start[j]; start[j] = tempPoint;
				}

				index = indexUp;
	}//end of while
}
//---------------------------------------------------------------------------

void __fastcall TMainWindow::SegmentButtonClick(TObject *Sender)
{
	int ulx, uly, drx, dry;

	ContourList->Items->Clear();

	Image1->Picture->Bitmap->PixelFormat = pf24bit;
	//
	setColors(clBlack, clYellow);
	SetImage(MainWindow->Image1);
	//
	for (int j=0; j<Image1->Height; j++)
	{
		for (int i=0; i<Image1->Width; i++)
		{
			if (Image1->Canvas->Pixels[i][j] == clBlack)
			{
				ulx = drx = i;
				uly = dry = j;
				//Процедура сегментации меняет черные пиксели на желтые
				SegmentContour(ulx, uly, drx, dry);
				//ContourList->Repaint();
			}
		}
	}

	RestoreColor(clYellow, clBlack); //обратная замена введенного
	// желтого цвета на черный
	//Сортировка списка контуров
	SortContourList();
	ContourList->Items->Clear();
	for (int i=0; i<vt.size(); i++)
		ContourList->Items->Add("Contour№"+IntToStr(i+1)+
		" x="+IntToStr(vt[i].Left)+"y="+IntToStr(vt[i].Top)
		+"x="+IntToStr(vt[i].Right)+"y="+IntToStr(vt[i].Bottom));
}
//---------------------------------------------------------------------------

void __fastcall TMainWindow::SaveButtonClick(TObject *Sender)
{
	if (SavePictureFileDialog->Execute())
	{
		Image1->Picture->SaveToFile(SavePictureFileDialog->FileName);
	}
}


//---------------------------------------------------------------------------
void SegmentListClick()
{
	TImage* Image1 = MainWindow->Image1;

	//чистим старый контур, если есть (с красного на черный)
	if (selindex >= 0)
	{
		setColors(clRed, clBlack);
		DFS(start[selindex].x, start[selindex].y);
	}
	//чистка закончена
	//ставим активным выбранный контур
	selindex = MainWindow->ContourList->ItemIndex;

	//красим новый объект (с черного на красный)
	setColors(clBlack, clRed);
	DFS(start[selindex].x, start[selindex].y);

	//отрисовываем объект в окне символа
	int minX = vt[selindex].Left + 1;
	int maxX = vt[selindex].Right - 1;
	int minY = vt[selindex].Top + 1;
	int maxY = vt[selindex].Bottom - 1;
	TRect copy(minX, minY, maxX, maxY);
	//фикс из-за особенностей copyRect
	copy.Right++; copy.Bottom++;

	TImage* SymbolImage = MainWindow->SymbolImage;
	SymbolImage->Picture->Bitmap->Width = copy.Width();
	SymbolImage->Picture->Bitmap->Height = copy.Height();
	//чистка
	SymbolImage->Canvas->Brush->Color = clWhite;
	SymbolImage->Canvas->FillRect( TRect(0,0,copy.Width(), copy.Height()) );

	for (int i=minX; i<=maxX; i++)
		for (int j=minY; j<=maxY; j++)
			if (Image1->Canvas->Pixels[i][j] == clRed)
				SymbolImage->Canvas->Pixels[i-minX][j-minY] = clBlack;

}
//---------------------------------------------------------------------------
void __fastcall TMainWindow::ContourListClick(TObject *Sender)
{
	SegmentListClick();
}

//---------------------------------------------------------------------------
void charpriznaki_filter(SymbolAttributes* symbol, TImage* SymbolImage)
{
	std::vector<TPoint> & points = GetInnerArea();

	//удаление точек ( x > width, y > height)
	for (int i=0; i<points.size(); i++)
	{
		TPoint p = points[i];
		if (p.x > SymbolImage->Width - 1
			|| p.y > SymbolImage->Height - 1)
		{
			//ShowMessage("удаляем проверочную точку ["+IntToStr(points[i].x)
			//          +";"+IntToStr(points[i].y)+"]");
			points.erase(points.begin()+i);
			i--;
		}
	}
	//
	TPoint point;
	SetImage(SymbolImage);
	setColors(clWhite, clYellow);
	for (int i=0; i<points.size(); i++)
	{
		point = points[i];
		DFS4(point.x, point.y);
		//удаление лишних точек
		for (int j=i+1; j<points.size(); j++)
			if (SymbolImage->Canvas->Pixels[points[j].x][points[j].y] == clYellow)
			{
				//ShowMessage("стираем лишнюю проверочную точку ["+IntToStr(points[j].x)
				//           +";"+IntToStr(points[j].y)+"]");
				points.erase(points.begin()+j);
				j--;
			}
			// проверка границ
			bool flag = true;      //true - все хорошо, пока внутренняя область
			//верх и низ
			for (int k = 0; k < SymbolImage->Width; k++)
			{
				if (SymbolImage->Canvas->Pixels[k][0] == clYellow)
					flag = false;
				if (SymbolImage->Canvas->Pixels[k][SymbolImage->Height-1] == clYellow)
					flag = false;
				if (!flag) break;
			}
			//право/лево
			if (flag)
				for (int k = 0; k < SymbolImage->Height; k++)
				{
					if (SymbolImage->Canvas->Pixels[0][k] == clYellow)
						flag = false;
					if (SymbolImage->Canvas->Pixels[SymbolImage->Width-1][k] == clYellow)
						flag = false;
					if (!flag) break;
				}

				if (!flag)
				{
					//ShowMessage("удаляем проверочную точку ["+IntToStr(points[i].x)
					//            +";"+IntToStr(points[i].y)+"]");
					//возврат на место внешних областей
					setColors(clYellow, clWhite);
					DFS(points[i].x, points[i].y);
					setColors(clWhite, clYellow);
					//
					points.erase(points.begin()+i);
					i--;
				}
	}

	//ShowMessage("всего точек внутренних областей "+IntToStr(points.size()) );
	//возврат на место внутренних областей
	setColors(clYellow, clWhite);
	for (int i=0; i<points.size(); i++)
		DFS4(points[i].x, points[i].y);
	SetImage(MainWindow->Image1);
}
//---------------------------------------------------------------------------

SymbolAttributes* SharedSymbol;
void __fastcall TMainWindow::ProRsoTestButtonClick(TObject *Sender)
{
	String InFileName = "";
	String OutFileName = GetCurrentDir() + "\\TempShtrih.str";
	Convert2(SymbolImage->Picture->Bitmap, InFileName, OutFileName);
	//SymbolImage->Picture->SaveToFile(OutFileName + ".jpg");

	SymbolAttributes* symbol = new SymbolAttributes();
	//
	symbol->symbolWidth = SymbolImage->Width;
	symbol->symbolHeight = SymbolImage->Height;
	//
	SymbolToAttributes(OutFileName.c_str(), symbol);
	AttributesToSwStr(symbol);
	//SymbolToAttributes_debug(symbol, 28);
	SwStrToStrTags(symbol);
	//SwStrToStrTags_debug(symbol, 4+8+16);
	StrTagsToProObjects(symbol);
	//StrTagsToProObjects_debug(symbol);
	ProObjectGetStatistics(symbol);
	//ProObjectGetStatistics_debug(symbol);

	FindAllInnerAreas(symbol);
	FindAllInnerAreas_debug(symbol);

	charpriznaki_filter(symbol, SymbolImage);
	std::vector<TPoint> & points = GetInnerArea();

	//РАСПОЗНАВАНИЕ
	if (points.size() == 2)
		ShowMessage("это может быть Ф или В");
	if (points.size() == 1)
		if ((float)SymbolImage->Width / (float)SymbolImage->Height > 1.1)
			ShowMessage("Я думаю, что это Ю или ю");
		else ShowMessage("Я не знаю");
		//РАСПОЗНАНО
		PriznakiClear();

		//разрисовка ПРО
		for (int count=1; count <= symbol->proNumber; count++)
		{
			int color = random(256*256*256)+10000;
			SymbolImage->Canvas->Pen->Color = color;

			for (int i=0; i<symbol->rowNumber; i++)
				for (int j=0; j<symbol->shtrihNumbers[i]; j++)
					if (symbol->shtrih_attrs[i][j].M == count)
					{
						SymbolImage->Canvas->MoveTo(i, symbol->shtrih_attrs[i][j].yn - symbol->YMin);
						SymbolImage->Canvas->LineTo(i, symbol->shtrih_attrs[i][j].yk - symbol->YMin+1);
					}
		}

		SetImage(MainWindow->Image1);
		delete symbol;
		closeLibrary();
		DeleteFile(OutFileName);
		//SharedSymbol = symbol;
		//Transform1Button->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainWindow::SaveSymbolButtonClick(TObject *Sender)
{
	if (SavePictureFileDialog->Execute())
	{
		SymbolImage->Picture->SaveToFile(SavePictureFileDialog->FileName);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainWindow::ProButtonClick(TObject *Sender)
{
	RichEdit1->Lines->Clear();

	Image1->Picture->SaveToFile(ExtractFileDir(Application->ExeName)
		+"\\Result\\original.bmp");

	String OutFileName = GetCurrentDir() + "\\TempShtrih.str";

	for (int t=0; t<ContourList->Items->Count; t++)
	{
		selindex = t;
		TRect copy(vt[selindex].Left+1, vt[selindex].Top+1, vt[selindex].Right-1, vt[selindex].Bottom-1);
		//фикс из-за особенностей copyRect
		copy.Right++; copy.Bottom++;
		SymbolImage->Picture->Bitmap->Width = copy.Width();
		SymbolImage->Picture->Bitmap->Height = copy.Height();

		SymbolImage->Canvas->CopyRect(TRect(0,0,SymbolImage->Width+1, SymbolImage->Height+1), Image1->Canvas, copy );

		Convert2(SymbolImage->Picture->Bitmap, "", OutFileName);

		SymbolAttributes* symbol = new SymbolAttributes();
		SymbolToAttributes(OutFileName.c_str(), symbol);
		AttributesToSwStr(symbol);
		SwStrToStrTags(symbol);
		//SwStrToStrTags_debug(symbol, 4+8+16);
		StrTagsToProObjects(symbol);
		//StrTagsToProObjects_debug(symbol);
		ProObjectGetStatistics(symbol);

		//разрисовка ПРО
		for (int count=1; count <= symbol->proNumber; count++)
		{
			int color = random(256*256*256)+10000;
			SymbolImage->Canvas->Pen->Color = color;

			for (int i=0; i<symbol->rowNumber; i++)
				for (int j=0; j<symbol->shtrihNumbers[i]; j++)
					if (symbol->shtrih_attrs[i][j].M == count)
					{
						SymbolImage->Canvas->MoveTo(i, symbol->shtrih_attrs[i][j].yn - symbol->YMin);
						SymbolImage->Canvas->LineTo(i, symbol->shtrih_attrs[i][j].yk - symbol->YMin+1);
					}
		}

		Image1->Canvas->CopyRect(copy, SymbolImage->Canvas, TRect(0,0,SymbolImage->Width + 1, SymbolImage->Height + 1));

		RichEdit1->Lines->Add(ContourList->Items->operator [](selindex)+":");
		RichEdit1->Lines->Add("Изолированых штрихов: "+IntToStr(symbol->isNumber));
		RichEdit1->Lines->Add("Штрихов начала: "+IntToStr(symbol->nsNumber));
		RichEdit1->Lines->Add("Штрихов конца: "+IntToStr(symbol->ksNumber));
		RichEdit1->Lines->Add("Штрихов слияния: "+IntToStr(symbol->ssNumber));
		RichEdit1->Lines->Add("Штрихов расщепления: "+IntToStr(symbol->rsNumber));
		RichEdit1->Lines->Add("Простых растровых объектов: "+IntToStr(symbol->proNumber));
		RichEdit1->Lines->Add("--------------------------------");

		closeLibrary();
		DeleteFile(OutFileName);
		delete symbol;
	}

	Image1->Picture->SaveToFile(ExtractFileDir(Application->ExeName)
		+"\\Result\\pro.bmp");
}
//---------------------------------------------------------------------------

void __fastcall TMainWindow::SaveTextButtonClick(TObject *Sender)
{
	Memo1->Lines = RichEdit1->Lines;

	if (SaveFileDialog->Execute() )
		Memo1->Lines->SaveToFile(SaveFileDialog->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TMainWindow::AnimationButtonClick(TObject *Sender)
{
	String str = "";
	for (int i=0; i<ContourList->Items->Count; i++)
	{
		ContourList->ItemIndex = i;
		ContourListClick(NULL);
		str = IntToStr(i);
		while (str.Length() < 3) str = "0" + str;
		Image1->Picture->SaveToFile("file"+str+".bmp");
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainWindow::Transform1ButtonClick(TObject *Sender)
{
	SymbolAttributes* symbol = SharedSymbol;
	String OutFileName = GetCurrentDir() + "\\TempShtrih.str";

	Transform1(symbol);
	Transform1_debug(symbol);

	//чистка лишних объектов ПРО
	SymbolImage->Canvas->Pen->Color = clWhite;

	for (int i=0; i<symbol->rowNumber; i++)
		for (int j=0; j<symbol->shtrihNumbers[i]; j++)
		{
			int ProIndex = symbol->shtrih_attrs[i][j].M;
			ProIndex--;                 //приводим к индексу массива
			if (ProIndex < 0) continue; //если штрих не классифицирован, то пропускаем
			if (!symbol->pros[ProIndex]->ToDelete) continue;

			SymbolImage->Canvas->MoveTo(i, symbol->shtrih_attrs[i][j].yn - symbol->YMin);
			SymbolImage->Canvas->LineTo(i, symbol->shtrih_attrs[i][j].yk - symbol->YMin+1);
		}

		delete symbol;
		closeLibrary();
		DeleteFile(OutFileName);

		Transform1Button->Enabled = false;
}

//---------------------------------------------------------------------------

void __fastcall TMainWindow::Transform2ButtonClick(TObject *Sender)
{
	//ПРЕОБРАЗОВАНИЕ №2
	String InFileName = "";
	String OutFileName = GetCurrentDir() + "\\TempShtrih.str";

	Convert2(SymbolImage->Picture->Bitmap, InFileName, OutFileName);

	SymbolAttributes* symbol = new SymbolAttributes();
	//
	symbol->symbolWidth = SymbolImage->Width;
	symbol->symbolHeight = SymbolImage->Height;
	//
	SymbolToAttributes(OutFileName.c_str(), symbol);
	AttributesToSwStr(symbol);
	SwStrToStrTags(symbol);

	Transform2(symbol);

	AttributesToSwStr(symbol);
	SwStrToStrTags(symbol);
	StrTagsToProObjects(symbol);
	ProObjectGetStatistics(symbol);

	ShowMessage("Преобразование №2: Дорисовка линий");
	SymbolImage->Canvas->Pen->Color = clBlack;
	vector<int> & lines = GetRedrawLines();
	for (int t=0; t < lines.size(); t++)
	{
		int i = lines[t];
		SymbolImage->Canvas->MoveTo(i, symbol->shtrih_attrs[i][0].yn - symbol->YMin);
		SymbolImage->Canvas->LineTo(i, symbol->shtrih_attrs[i][0].yk - symbol->YMin+1);
	}
	lines.clear();

	//разрисовка ПРО
	for (int count=1; count <= symbol->proNumber; count++)
	{
		int color = random(256*256*256)+10000;
		SymbolImage->Canvas->Pen->Color = color;

		for (int i=0; i<symbol->rowNumber; i++)
			for (int j=0; j<symbol->shtrihNumbers[i]; j++)
				if (symbol->shtrih_attrs[i][j].M == count)
				{
					SymbolImage->Canvas->MoveTo(i, symbol->shtrih_attrs[i][j].yn - symbol->YMin);
					SymbolImage->Canvas->LineTo(i, symbol->shtrih_attrs[i][j].yk - symbol->YMin+1);
				}
	}

	closeLibrary();
	DeleteFile(OutFileName);

}

//---------------------------------------------------------------------------

void __fastcall TMainWindow::BlackButtonClick(TObject *Sender)
{

	//перевод обратно в черно-белое
	for (int i=0; i < SymbolImage->Width; i++)
		for (int j=0; j < SymbolImage->Height; j++)
			if (SymbolImage->Canvas->Pixels[i][j] != clWhite)
				SymbolImage->Canvas->Pixels[i][j] = clBlack;
}
//---------------------------------------------------------------------------


void __fastcall TMainWindow::FormClose(TObject *Sender,
	TCloseAction &Action)
{
	closeLibrary(); //обязательно удаляем объект открытого штрихового файла
}
//---------------------------------------------------------------------------

void __fastcall TMainWindow::CustomButtonClick(TObject *Sender)
{
	AnsiString str;
	AnsiString file = ExtractFileName(OpenPictureFileDialog->FileName);

	RichEdit1->Lines->Clear();

	switch (RadioGroup1->ItemIndex)
	{
	case 0: RichEdit1->Lines->Add("Название;Ширина;Высота;Ширина/Высота;Файл"); break;
	case 1: RichEdit1->Lines->Add("Название;Штр.Нач.;Штр.Конца;Штр.Сл.;Штр.Расщ;Число ПРО;Файл");
		break;
	case 2: RichEdit1->Lines->Add("Название;Площ.Внутр.Обл.;Площ.буквы;S(обл.)/S(буквы);Файл");
	case 3: RichEdit1->Lines->Add("Название;%заполненности;Файл");
		break;
	}

	String OutFileName = GetCurrentDir() + "\\TempShtrih.str";

	for (int t=0; t<ContourList->Items->Count; t++)
	{
		ContourList->ItemIndex = t;
		ContourListClick(NULL);

		Convert2(SymbolImage->Picture->Bitmap, "", OutFileName);

		SymbolAttributes* symbol = new SymbolAttributes();
		SymbolToAttributes(OutFileName.c_str(), symbol);
		AttributesToSwStr(symbol);
		SwStrToStrTags(symbol);
		//SwStrToStrTags_debug(symbol, 4+8+16);
		StrTagsToProObjects(symbol);
		//StrTagsToProObjects_debug(symbol);
		ProObjectGetStatistics(symbol);

		/*//разрисовка ПРО
		for (int count=1; count <= symbol->proNumber; count++)
		{
		int color = random(256*256*256)+10000;
		SymbolImage->Canvas->Pen->Color = color;

		for (int i=0; i<symbol->rowNumber; i++)
		for (int j=0; j<symbol->shtrihNumbers[i]; j++)
		if (symbol->shtrih_attrs[i][j].M == count)
		{
		SymbolImage->Canvas->MoveTo(i, symbol->shtrih_attrs[i][j].yn - symbol->YMin);
		SymbolImage->Canvas->LineTo(i, symbol->shtrih_attrs[i][j].yk - symbol->YMin+1);
		}
		}
		*/

		switch (RadioGroup1->ItemIndex)
		{
		case 0:
			str = "";
			str += ContourList->Items->operator [](selindex)+";";
			str += IntToStr(SymbolImage->Width)+";"
				+IntToStr(SymbolImage->Height)+";"
				+ FloatToStr((float)SymbolImage->Width / (float)SymbolImage->Height)+";";
			str += file;
			RichEdit1->Lines->Add(str);
			break;

		case 1:
			{
				str = "";
				str += ContourList->Items->operator [](selindex)+";";
				str += IntToStr(symbol->nsNumber) + ";";
				str += IntToStr(symbol->ksNumber) + ";";
				str += IntToStr(symbol->ssNumber) + ";";
				str += IntToStr(symbol->rsNumber) + ";";
				str += IntToStr(symbol->proNumber)+ ";";
				str += file;
				RichEdit1->Lines->Add(str);
				break;

		case 2:
			FindAllInnerAreas(symbol);
			charpriznaki_filter(symbol, SymbolImage);
			std::vector<TPoint> & points = GetInnerArea();
			int xmin, xmax, ymin, ymax;
			int Ssymbol = SymbolImage->Width * SymbolImage->Height;
			int Sarea = 0;

			for (int k=0; k<points.size(); k++)
			{
				str = "";
				SetImage(SymbolImage);
				setColors(clWhite, clYellow);
				xmin = xmax = points[k].x;
				ymin = ymax = points[k].y;

				BFS(xmin, ymin, xmax, ymax);

				Sarea = 0;
				for (int i=xmin; i<=xmax; i++)
					for (int j=ymin; j<=ymax; j++)
						if (SymbolImage->Canvas->Pixels[i][j] == clYellow) Sarea++;

				setColors(clYellow, clWhite);
				BFS(points[k].x, points[k].y);

				str += "Contour№ "+IntToStr(t+1);
				str += "Area№ "+IntToStr(k)+";";
				str += IntToStr(Sarea)+";";
				str += IntToStr(Ssymbol)+";";
				str += FloatToStr((float)Sarea / (float) Ssymbol) + ";";
				str += file;
				SetImage(MainWindow->Image1);
				RichEdit1->Lines->Add(str);
			}
			}
			break;

		case 3:
			{
				int Ssymbol = SymbolImage->Width * SymbolImage->Height;
				int sumPix = 0;
				str = "";
				str += ContourList->Items->operator [](selindex)+";";
				sumPix = 0;
				for (int i=0; i<symbol->rowNumber; i++)
					for (int j=0; j<symbol->shtrihNumbers[i]; j++)
						if (symbol->shtrih_attrs[i][j].M == 0)
							sumPix += symbol->shtrih_attrs[i][j].yk - symbol->shtrih_attrs[i][j].yn + 1;
				for (int i=0; i<symbol->proNumber; i++)
					sumPix += symbol->pros[i]->pixelSquare;

				str += FloatToStr((float)sumPix / (float) Ssymbol ) + ";";
				str += file;
				RichEdit1->Lines->Add(str);
			}
			break;
		}

		closeLibrary();
		DeleteFile(OutFileName);
		delete symbol;
		PriznakiClear();
	}
	CustomButton->Enabled = false;
	CustomButton->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainWindow::MacroButtonClick(TObject *Sender)
{
	SegmentButtonClick(NULL);
	CustomButtonClick(NULL);
}
//---------------------------------------------------------------------------
void vRotateImage90(TImage* Image1)
{
	//функция поворачивает изображение Image1
	//и потом присваивает результат в Image1
	Graphics::TBitmap *pBitmap1 = NULL;
	pBitmap1 = new Graphics::TBitmap();
	//Определяем размеры повернутого изображения
	pBitmap1->Width = Image1->Picture->Bitmap->Height;
	pBitmap1->Height = Image1->Picture->Bitmap->Width;
	//Поворот на 90 градусов
	//Медленно по кубикам пикселям и по другому нельзя
	for(int y=pBitmap1->Height; y >= 0; y--)
		for(int x=0; x < pBitmap1->Width; x++)
		{
			pBitmap1->Canvas->Pixels[x][y]
			= Image1->Canvas->Pixels[y][Image1->Height-1 - x];
		}

		//pBitmap1->SaveToFile("a.bmp");
		Image1->Picture->Bitmap->Assign(pBitmap1);

		delete pBitmap1;
}
//---------------------------------------------------------------------------

void __fastcall TMainWindow::RecognButtonClick(TObject *Sender)
{
        char f[MAX_PATH];
        char filename[MAX_PATH]="";
        SHGetSpecialFolderPath(NULL,f,CSIDL_PERSONAL,false);
        strcat(f,filename);
        RichEdit1->Lines->Add(f);
        //return;
        // Ориентация
        if (SettingWindow->OrientBox->Checked)
         {

           if (orient(Image1) == 1)
            {
              RichEdit1->Lines->Add("поворачиваем изображение на 90 градусов");
              RichEdit1->Refresh();
              vRotateImage90(Image1);
              Image1->Refresh();
            }
         }
         
        //1 поворот
        if (SettingWindow->DeskewBox->Checked)
         {
           RichEdit1->Lines->Add("Проверка угла наклона...");
           RichEdit1->Refresh();
           gmseDeskew* sk = new gmseDeskew(Image1->Picture->Bitmap);
           double skewangle = sk->GetSkewAngle();
           RichEdit1->Lines->Add("угол наклона равен "+FloatToStr(skewangle) +" градусов");
           RichEdit1->Refresh();

           if (abs(skewangle) > 2)
            {
              Graphics::TBitmap* pic = new Graphics::TBitmap();
              vRotate(-skewangle, Image1->Picture->Bitmap, pic);
              //Image1->Picture->Bitmap = pic;
              Image1->Picture->Assign(pic);
              Image1->Repaint();
              RichEdit1->Lines->Add("изображение выровнено");
              RichEdit1->Refresh();
            }
           else
            {
              RichEdit1->Lines->Add("поворот не требуется");
              RichEdit1->Refresh();
            }
         }

        RichEdit1->Lines->Add("\nсегментация текста...");
        RichEdit1->Refresh();
        SegmentButtonClick(NULL);
        RichEdit1->Lines->Add("сегментация завершена");
        RichEdit1->Refresh();

	SymbolAttributes* symbol;
	String OutFileName = String(f) + "\\TempShtrih.str";

	String otvet = "";
	String str = "";
        char* symbols = new char[vt.size()];

	for (int t=0; t<ContourList->Items->Count; t++)
	{
		ContourList->ItemIndex = t;
		ContourListClick(NULL);

		Convert2(SymbolImage->Picture->Bitmap, "", OutFileName);

		symbol = new SymbolAttributes();
		//
		symbol->symbolWidth = SymbolImage->Width;
		symbol->symbolHeight = SymbolImage->Height;
		//
		SymbolToAttributes(OutFileName.c_str(), symbol);
		AttributesToSwStr(symbol);
		SwStrToStrTags(symbol);
		StrTagsToProObjects(symbol);
		ProObjectGetStatistics(symbol);

		//распознавание
		//1. Внутренние области
		FindAllInnerAreas(symbol);
		charpriznaki_filter(symbol, SymbolImage);
		std::vector<TPoint> & points = GetInnerArea();

		int AreaCount = points.size();

		//2. Аспект
		float aspect = (float)SymbolImage->Width / (float)SymbolImage->Height;

		//3. % заполненности
		int Ssymbol = SymbolImage->Width * SymbolImage->Height;
		int sumPix = 0;
		for (int i=0; i<symbol->rowNumber; i++)
			for (int j=0; j<symbol->shtrihNumbers[i]; j++)
				if (symbol->shtrih_attrs[i][j].M == 0)
					sumPix += symbol->shtrih_attrs[i][j].yk - symbol->shtrih_attrs[i][j].yn + 1;
		for (int i=0; i<symbol->proNumber; i++)
			sumPix += symbol->pros[i]->pixelSquare;

		//4. Количество вертикальных ПРО
		int VerticalProCount = 0;
		int AverageShtrihLength;

		str = "";

		for (int i=0; i<symbol->proNumber; i++)
		{
			// защита от ошибки
			if (symbol->pros[i]->shtrihNumbers == 0) continue;
			// считаем среднюю длину штриха
			AverageShtrihLength = symbol->pros[i]->pixelSquare /
				symbol->pros[i]->shtrihNumbers;
			if (AverageShtrihLength > 0.7 * symbol->symbolHeight)
				VerticalProCount++;
		}

		float fillPercent = (float)sumPix / (float) Ssymbol;

		if (AreaCount == 0)
		{ //str = "ЦцУуКкЕеНнГгШшЩщЗзХхIПпЛлЖжЭэЧчСсМмИиТт";
			if (aspect >= 0 && aspect <= 0.36)
			{ //str = "1,\,Ы_I"
				int k = symbol->rsNumber + symbol->ssNumber;
				switch (k)
				{
				case 0:
					str = "\\";
					break;
				case 1:
					str = "1";
					break;
				case 2:
					str = "I";
                                        if (t > 0)
                                        {
                                         if (symbols[t-1]  == 'ь')
					  { symbols[t-1] = '\0'; symbols[t] = 'ы'; str = "ы"; }
					 if (symbols[t-1] == 'Ь')
					  { symbols[t-1] = '\0'; symbols[t] = 'Ы'; str = "Ы"; };
                                        }
					break;
				}
			}
			if (aspect > 0.36 && aspect <= 0.52)
			{ // str = "/, Ы_I, ы_I"
				int k = symbol->rsNumber + symbol->ssNumber;
				switch (k)
				{
				case 0:
					str = "/";
					break;
				case 2:
					str = "I";
					if (t > 0)
                                        {
                                         if (symbols[t-1]  == 'ь')
					  { symbols[t-1] = '\0'; symbols[t] = 'ы'; str = "ы"; }
					 if (symbols[t-1] == 'Ь')
					  { symbols[t-1] = '\0'; symbols[t] = 'Ы'; str = "Ы"; };
                                        }
					break;
				}
			}
			if (aspect > 0.52 && aspect <= 0.65)
			{ //str = "2357,З"
				if (symbol->rsNumber == 0)
				{ //str = "7,"
					if (fillPercent < 0.3)
						str = "7";
					else
						str = ",";
				}
				else
				{ //str = 235З"
					int k = symbol->rsNumber + symbol->ssNumber;

					ShtrihAttributes* sShtrih = NULL;
					ShtrihAttributes* rShtrih = NULL;

					switch (k)
					{
					case 2:
						// str = "25"
                                                if (symbol->rsNumber == 0 || symbol->ssNumber == 0) break; 
						for (int i=0; i< symbol->rowNumber; i++)
							for (int j=0; j <symbol->shtrihNumbers[i]; j++)
							{
								ShtrihAttributes& cur_str = symbol->shtrih_attrs[i][j];
								if (cur_str.isR)
									rShtrih = &symbol->shtrih_attrs[i][j];
								if (cur_str.isS)
									sShtrih = &symbol->shtrih_attrs[i][j];
							}
							if (rShtrih->yn + rShtrih->yk < sShtrih->yn + sShtrih->yk)
								str = "5";
							else
								str = "2";
							break;

					case 3:
						// str = "3З"
						if (aspect < 0.6)
							str = "3";
						else
							str = "З";
						break;
					}
				}
			}
			if (aspect > 0.65 && aspect <= 0.87)
			{ // str = "ГгЕ Ё_Е зсСТуЦцЧчЭэ" + "2"
				if (VerticalProCount == 1)
				{ // str = "ГгЕ Ё_Е ТЧч"
					int ProId = 0;
					for (int i=0; i<symbol->proNumber; i++)
					{
						// защита от ошибки
						if (symbol->pros[i]->shtrihNumbers == 0) continue;
						// считаем среднюю длину штриха
						AverageShtrihLength = symbol->pros[i]->pixelSquare /
							symbol->pros[i]->shtrihNumbers;
						if (AverageShtrihLength > 0.7 * symbol->symbolHeight)
						{ ProId = i; break; }
					}

					if (symbol->proStart[ProId].row > symbol->symbolWidth / 2)
					{ // str = "Чч"
                                                str = "Ч";
       					}
					else
					{ // str = "ГгЕ Ё_Е Т"
						// закрываем библиотеку
						closeLibrary();
						DeleteFile(OutFileName);
						delete symbol;
						PriznakiClear();

						// поворачиваем изображение в контуре
						vRotateImage90(SymbolImage);

						// заносим его в штриховой файл
						Convert2(SymbolImage->Picture->Bitmap, "", OutFileName);
						symbol = new SymbolAttributes();
						SymbolToAttributes(OutFileName.c_str(), symbol);
						AttributesToSwStr(symbol);
						SwStrToStrTags(symbol);
						StrTagsToProObjects(symbol);
						ProObjectGetStatistics(symbol);

						if (symbol->ssNumber == 1)
						{ //str = "Гг Т
							// правило - ищем этот штрих слияния
							// и смотрим, есть ли у него в середине
							// пристыкованный ПРО объект
							int x=-1, y=-1;

							for (int i=0; i<symbol->rowNumber; i++)
								for (int j=0; j<symbol->shtrihNumbers[i]; j++)
									if (symbol->shtrih_attrs[i][j].isS)
									{ x = i; y = j; break; }

									ShtrihAttributes& sShtrih = symbol->shtrih_attrs[x][y];
									int centerY = (sShtrih.yn + sShtrih.yk)/2;
									if (x < 1)
									{ // ОШИБКА. негде взять предыдущий штрих
										closeLibrary();
										DeleteFile(OutFileName);
										delete symbol;
										otvet += "{ошибка}";
										continue;
									}

									bool center = false;
									for (int j = 0; j < symbol->shtrihNumbers[x-1]; j++)
										if (symbol->shtrih_attrs[x-1][j].yn <= centerY
											&& symbol->shtrih_attrs[x-1][j].yk >= centerY)
										{ center = true; break; }

										if (center)
											str = "Т";
										else
										{
											// str = "Гг"
                                                                                        str = "Г";
                                                                                }
						}//end "Гг Т"
						else
							// str = "Е Ё_Е"
							str = "Е";
					}
				} // end "Гг Ё_Е ТЧч"
				else
				{ // str = "зсСуЦцЭэ" + "2"
					int k = symbol->rsNumber + symbol->ssNumber;
					switch (k)
					{
					case 4:
						// str  = "Цц"
                                                str = "Ц";
                                                break;
       					case 3:
						// str = "зу"
						if (fillPercent < 0.26)
							str = "у";
						else
							str = "з";
                                                break;
					case 2:
						// str = "2" + "Сс"
                                                if (symbol->ssNumber == 0)
                                                 str = "С";
                                                else
						 str = "2";
						break;
					case 1:
						// str = "СсЭэ"
						if (symbol->ssNumber == 0)
						{ // Нет штрихов слияния - это "Сс"
                                                        str = "С";
                                                }
						if (symbol->rsNumber == 0)
						{ // Нет штрихов расщепления - это "Ээ"
                                                        str = "Э";
                                                }
						break;
					} // end of switch
				}
			} //end aspect 0.65-0.87
			if (aspect > 0.87 && aspect <= 1.14)
			{ // str = ". Ё_* ё_* Ии Й_И й_и Кк Лл Нн Пп т У Хх ц Чч Щ"
				if (fillPercent > 0.45)
				{ // str  = ". Ё_* ё_*"
					str = ".";
				}
				else
				{ // str = "Ии Й_И й_и Кк Лл Нн Пп т У Хх ц Чч Щ"
					int k = symbol->rsNumber + symbol->ssNumber;
					int i_s = -1, i_r = -1;
					switch (VerticalProCount)
					{
					case 0:
						// str = "У Хх"

						if (k <= 3)
							str = "У";
						else
							str = "Х";
                                                        break;
					case 1:
						// str = "Кк Лл т Чч"
						if (symbol->ssNumber == 1)
						{ // str = "Кк т Чч"
							// закрываем библиотеку
							closeLibrary();
							DeleteFile(OutFileName);
							delete symbol;
							PriznakiClear();

							// поворачиваем изображение в контуре
							vRotateImage90(SymbolImage);

							// заносим его в штриховой файл
							Convert2(SymbolImage->Picture->Bitmap, "", OutFileName);
							symbol = new SymbolAttributes();
							SymbolToAttributes(OutFileName.c_str(), symbol);
							AttributesToSwStr(symbol);
							SwStrToStrTags(symbol);
							StrTagsToProObjects(symbol);
							ProObjectGetStatistics(symbol);
							k = symbol->rsNumber + symbol->ssNumber;

							if (k > 2)
							{ // str = "Кк"
								str = "К";
							}
							else
							{ // str = "Т Чч"
								if (symbol->rsNumber == 0)
								{ // str = "т"
									str = "т";
								}
								else
								{ // str = "Чч"
									str = "Ч";
								}
							}
						} // end "Кк Т Чч"
						else
						{ // str = "Лл"
							str = "Л";
						}
						break;
					case 2:
						// str = "Ии Й_И й_и Нн Пп ц"
						// закрываем библиотеку
						closeLibrary();
						DeleteFile(OutFileName);
						delete symbol;
						PriznakiClear();

						// поворачиваем изображение в контуре
						vRotateImage90(SymbolImage);

						// заносим его в штриховой файл
						Convert2(SymbolImage->Picture->Bitmap, "", OutFileName);
						symbol = new SymbolAttributes();
						SymbolToAttributes(OutFileName.c_str(), symbol);
						AttributesToSwStr(symbol);
						SwStrToStrTags(symbol);
						StrTagsToProObjects(symbol);
						ProObjectGetStatistics(symbol);
						k = symbol->rsNumber + symbol->ssNumber;

						if (symbol->ssNumber == 0)
						{ // str = "ц"
							str = "ц";
							break; //case
						}
						if (symbol->rsNumber == 0)
						{ // str = "Пп"
							str = "П";
							break; //case
						}
						//str = "Й_И й_и Ии Нн"
						// признак - если штрих слияния идёт перед
						// штрихом расщепления то это Нн, иначе это Ии
						//int i_s = -1, i_r = -1;
						for (int i=0; i<symbol->rowNumber; i++)
							for (int j=0; j<symbol->shtrihNumbers[i]; j++)
							{
								if (symbol->shtrih_attrs[i][j].isR)
									i_r = i;
								if (symbol->shtrih_attrs[i][j].isS)
									i_s = i;
							}

							if (i_s < i_r)
							{ // str = "Нн"
								str = "Н";
							}
							else
							{ // str = "Ии Й_И й_и"
								str = "И";
							}
							break;
					case 3:
						// // str = "Щ"
						str = "Щ";
						break;
					}
				}
			} // end aspect 0.87-1.14
			if (aspect > 1.14 && aspect <= 1.31)
			{ // str = "ЖМмщ"
				switch (VerticalProCount)
				{
				case 1:
					str = "Ж";
					break;
				case 2:
					str = "М";
					break;
				case 3:
					str = "щ";
					break;
				}
			}
			if (aspect > 1.31 && aspect <= 1.47)
			{ // str = "жШ"
				switch (VerticalProCount)
				{
				case 1:
					str = "ж";
					break;
				case 3:
					str = "Ш";
					break;
				}
			}
			if (aspect > 1.47 && aspect <= 1.61)
			{ // str = "ш"
				str = "ш";
			}
			if (aspect > 1.61)
				// str = "Й_~ й_~"
				str = "~";
		}

		if (AreaCount == 1)
		{ //str = "0469ЪъАаеРрОоДдЯяЬьБбЮю";
			int Ssymbol = symbol->symbolHeight * symbol->symbolWidth;
			int Sarea = 0;

			std::vector<TPoint> & points = GetInnerArea();
			int xmin, xmax, ymin, ymax;

			xmin = xmax = points[0].x;
			ymin = ymax = points[0].y;

			SetImage(SymbolImage);
			setColors(clWhite, clYellow);

			BFS(xmin, ymin, xmax, ymax);

			for (int i=xmin; i<=xmax; i++)
				for (int j=ymin; j<=ymax; j++)
					if (SymbolImage->Canvas->Pixels[i][j] == clYellow) Sarea++;

			//возврат на место
			setColors(clYellow, clWhite);
			BFS(points[0].x, points[0].y);

			SetImage(MainWindow->Image1);

			float AreaPart = (float) Sarea / (float)Ssymbol;

			if (aspect > 0 && aspect <= 0.66)
			{ // str = "0469б"
				if (symbol->rsNumber >= 2)
				{ // str = "6б"
					// у буквы б 1й штрих расщепления м/у ~ и о выше
					// 2го штриха расщепления у области о
					ShtrihAttributes* s1, *s2;
					s1 = s2 = NULL;
					for (int i=0; i < symbol->rowNumber; i++)
						for (int j=0; j < symbol->shtrihNumbers[i]; j++)
						{
							if (symbol->shtrih_attrs[i][j].isR)
							{
								if (s1 == NULL)
									s1 = &symbol->shtrih_attrs[i][j];
								else
									s2 = &symbol->shtrih_attrs[i][j];

								if (s2 != NULL) break;
							}
						}
						if (s1->yn < s2->yn)
							str = "б";
						else
							str = "6";
				}
				else if (symbol->ssNumber >= 2)
					str = "9";
				else
				{ // str = "04"


					if (AreaPart < 0.2)
						str = "4";
					else
						str = "0";
				}
			}

			if (aspect > 0.66 && aspect <= 0.71)
				// str = "р"
				str = "р";

			if (aspect > 0.71 && aspect <= 0.89)
			{ // str = "аБДде ё_е Р ы_ь Ьь Оо"
				int k;
				switch (VerticalProCount)
				{
				case 0:
					// str = "ае Оо"

					if (AreaPart >= 0.14 && AreaPart <= 0.16)
						str = "а";
					if (AreaPart >= 0.1 && AreaPart <= 0.13)
						str = "е";
					if (AreaPart >= 0.36 && AreaPart <= 0.43)
						str = "о";
					if (AreaPart >= 0.48 && AreaPart <= 0.52)
						str = "О";
					break;
				case 1:
					// str = "БДд Р ы_ь ь"
					if (AreaPart >= 0.2)
					{
						str = "Д";
					}
					else
					{ // str = "Б Р Ьь"
						// закрываем библиотеку
						closeLibrary();
						DeleteFile(OutFileName);
						delete symbol;
						PriznakiClear();

						// поворачиваем изображение в контуре
						vRotateImage90(SymbolImage);

						// заносим его в штриховой файл
						Convert2(SymbolImage->Picture->Bitmap, "", OutFileName);
						symbol = new SymbolAttributes();
						SymbolToAttributes(OutFileName.c_str(), symbol);
						AttributesToSwStr(symbol);
						SwStrToStrTags(symbol);
						StrTagsToProObjects(symbol);
						ProObjectGetStatistics(symbol);
						//
						symbol->symbolWidth = SymbolImage->Picture->Width;
						symbol->symbolHeight = SymbolImage->Picture->Height;
						//
						k = symbol->rsNumber + symbol->ssNumber;
						if (k > 2)
							str = "Б";
						else
						{
							int i_r=-1, i_s=-1;
							for (int i=0; i < symbol->rowNumber; i++)
								for (int j=0; j < symbol->shtrihNumbers[i]; j++)
								{
									if (symbol->shtrih_attrs[i][j].isR)
										i_r = i;
									if (symbol->shtrih_attrs[i][j].isS)
										i_s = i;
								}
								// у буквы Р штрих слияния ближе к концу
								//у Ь штрих расщепления ближе к началу
								if (i_r < symbol->symbolWidth / 3)
                                                                        str = "Ь";
								if (i_s > (symbol->symbolWidth*2)/3)
                                                                        str = "Р";
						}
					}
					break;
				} // end switch
			} // end aspect 0.71-0.89
			if (aspect > 0.89 && aspect <= 0.98)
			{ // str = "Оо ы_ь ь ЪЯя"
				int k;

				if (AreaPart >= 0.36 && AreaPart <= 0.42)
					str = "о";
				else if (AreaPart >= 0.48 && AreaPart <= 0.52)
					str = "О";
				else
				{ // str  = "ьЪЯя"
					// закрываем библиотеку
					closeLibrary();
					DeleteFile(OutFileName);
					delete symbol;
					PriznakiClear();

					// поворачиваем изображение в контуре
					vRotateImage90(SymbolImage);

					// заносим его в штриховой файл
					Convert2(SymbolImage->Picture->Bitmap, "", OutFileName);
					symbol = new SymbolAttributes();
					SymbolToAttributes(OutFileName.c_str(), symbol);
					AttributesToSwStr(symbol);
					SwStrToStrTags(symbol);
					StrTagsToProObjects(symbol);
					ProObjectGetStatistics(symbol);

					k = symbol->rsNumber + symbol->ssNumber;
					if (k == 2)
						str = "Ь";
					else
					{ // k >= 3
						int x = -1, y = -1;
						for (int i=0; i<symbol->rowNumber; i++)
							for (int j=0; j<symbol->shtrihNumbers[i]; j++)
								if (symbol->shtrih_attrs[i][j].isR ||
									symbol->shtrih_attrs[i][j].isS)
								{ x = i, y=j; break; }

                                                                // у Я первый штрих будет слиянием, у Ъ - расщеплением
								if (symbol->shtrih_attrs[x][y].isS)
								{ // str = "Яя"
									str = "Я";
								}
								else
									str = "Ъ";
					}
				}
			} // end aspect 0.89-0.98

			if (aspect > 0.98 && aspect <= 1.05)
			{ // str = "АъЯ" + "Ъ"
				if (AreaPart <= 0.08)
					str = "А";
				else
				{ // У ъ первый будет штрих слияния, у Я - штрих расщепления
					int x, y;
					for (int i=0; i<symbol->rowNumber; i++)
						for (int j=0; j<symbol->shtrihNumbers[i]; j++)
							if (symbol->shtrih_attrs[i][j].isR ||
								symbol->shtrih_attrs[i][j].isS)
							{ x = i, y=j; break; }

							if (symbol->shtrih_attrs[x][y].isR)
								str = "Я";
							else
                                                                str = "Ъ";
				}
			}

			if (aspect > 1.05)
				str = "Ю";
		}

		if (AreaCount == 2)
		{ // str = "8ВвФф"
			if (aspect >= 0 && aspect <= 0.6)
				str = "8";
			if (aspect > 0.6 && aspect <= 0.65)
				str = "ф";
			if (aspect > 0.65 && aspect <= 0.95)
				str = "В";
			if (aspect > 0.95)
				str = "Ф";
		}

		//ShowMessage(str);
                if (str == "")
                 symbols[t] = '\0';
                else
                symbols[t] = str[1];
                
		closeLibrary();
		DeleteFile(OutFileName);
		delete symbol;
		PriznakiClear();


	} // конец цикла распознавания


        for (int i=0; i<vt.size(); i++)
        {
          if  (symbols[i] == 'Е' || symbols[i] == 'е')
           {
             int dot_count = 0;
             int i1 = -1, i2 = -1;
             int l = vt[i].left, r = vt[i].right, t = vt[i].top, b = vt[i].bottom;
             int w = vt[i].Width(), h= vt[i].Height();
             for (int j=0; j<vt.size(); j++)
              {
                if (vt[j].Right < l - w/2) continue;
                if (vt[j].Left > r + w/2) continue;
                if (vt[j].Bottom < t - h/2) continue;
                if (vt[j].Top > b + h/2) continue;
                // объект в границах
                if (symbols[j] == '.')
                 {
                   switch (dot_count)
                    {
                      case 0: i1 = j; break;
                      case 1: i2 = j; break;
                    }
                   dot_count++;
                 }
              }
           if (dot_count >= 2)
            {
              symbols[i1] = symbols[i2] = '\0';
              if (symbols[i] == 'Е') symbols[i] = 'Ё';
              if (symbols[i] == 'е') symbols[i] = 'ё';
            }
          }
          if (symbols[i] == 'И' || symbols[i] == 'и')
           {
             int l = vt[i].left, r = vt[i].right, t = vt[i].top, b = vt[i].bottom;
             int w = vt[i].Width(), h= vt[i].Height();
             for (int j=0; j<vt.size(); j++)
              {
                if (vt[j].Right < l - w/2) continue;
                if (vt[j].Left > r + w/2) continue;
                if (vt[j].Bottom < t - h/2) continue;
                if (vt[j].Top > b + h/2) continue;
                if (symbols[j] == '~')
                 { symbols[i] = 'Й'; symbols[j] = '\0'; break; }
              }
           }
        }

for (int i=0; i<vt.size(); i++)
if (symbols[i] != '\0')
otvet += symbols[i];

//чистка
if (selindex >= 0)
{
setColors(clRed, clBlack);
SetImage(MainWindow->Image1);
BFS(start[selindex].x, start[selindex].y);
setColors(clBlack, clRed);
}

RichEdit1->Lines->Add("\nРезультат:");
RichEdit1->Lines->Add(otvet);
}
//---------------------------------------------------------------------------


void __fastcall TMainWindow::SettingsMenuItemClick(TObject *Sender)
{
SettingWindow->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainWindow::OpenMenuItemClick(TObject *Sender)
{
OpenButtonClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TMainWindow::Button1Click(TObject *Sender)
{
Image1->Canvas->Brush->Style = bsClear;
Image1->Canvas->Pen->Color = clBlue;
for (int i=0; i<vt.size(); i++)
Image1->Canvas->Rectangle(vt[i].Left, vt[i].Top, vt[i].Right+1, vt[i].Bottom+1);
Image1->Picture->SaveToFile("1.bmp");
/*SymbolImage->Picture->Bitmap->Width += 2;
SymbolImage->Picture->Bitmap->Height += 2;
TPixelFormat TempPixel = SymbolImage->Picture->Bitmap->PixelFormat;
SymbolImage->Picture->Bitmap->PixelFormat = pf32bit;
for (int i=SymbolImage->Width-1; i>=0; i--)
 for (int j=SymbolImage->Height-1; j>=0; j--)
  SymbolImage->Canvas->Pixels[i+1][j+1] = SymbolImage->Canvas->Pixels[i][j];

for (int i=0; i<SymbolImage->Width; i++)
{
 SymbolImage->Canvas->Pixels[i][0] = clWhite;
 SymbolImage->Canvas->Pixels[i][SymbolImage->Height-1] = clWhite;
}

for (int j=0; j<SymbolImage->Height; j++)
{
 SymbolImage->Canvas->Pixels[0][j] = clWhite;
 SymbolImage->Canvas->Pixels[SymbolImage->Width-1][j] = clWhite;
}
 */

}
//---------------------------------------------------------------------------

