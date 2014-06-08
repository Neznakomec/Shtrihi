#ifndef __SHTRIHLIB_H
#define __SHTRIHLIB_H

#if !defined(__DATASHTRIH_H)
#include "datashtrih.h"
#endif


class SHTRIH
{
private:
  char drive[MAXDRIVE];
  char dir[MAXDIR];
  char file[MAXFILE];
  char ext[MAXEXT];
  char NameFile[MAXPATH];
  char NameKatalog[MAXPATH];
  char tmptxt[MAXTXT];
//  char  *TmpBufer;
  char  REGIM;
  ShortToLong Ustl;
  char  *Metrika1Byte;
  short *Metrika2Byte;
  unsigned short *Metrika2UByte;
  long  *Metrika4Byte;
  void  *TmpMetka;
  short SMetka_Old[256],SMetka_New[256];
  unsigned short USMetka_Old[256],USMetka_New[256];
  long  LMetka_Old[256],LMetka_New[256];
  int   i,j;
  long  SizeBuffer,kbMet,kblM,ostM,nblM,ne;
  long  sh_tmp,sh_max,null_str;
  int   nui;   //номер устройства на котором открыт файл штрихов
  int   nuk;   //номер устройства на котором открыт файл каталога строк
  int   done;
  bool  Flag_Zapret,Flag_PrtMessageError;
  unsigned char  C_XminInf,C_XmaxInf,C_YminInf,C_YmaxInf;
  short          S_XminInf,S_XmaxInf,S_YminInf,S_YmaxInf;
  unsigned short U_XminInf,U_XmaxInf,U_YminInf,U_YmaxInf;
  long           L_XminInf,L_XmaxInf,L_YminInf,L_YmaxInf;

  unsigned char *PtrString1;
  short *PtrString2;
  unsigned short *PtrString2U;
  long *PtrString4;

  SHTRIH_1  *String1Byte;
  SHTRIH_2  *String2Byte;
  SHTRIH_2U *String2UByte;
  SHTRIH_4  *String4Byte;


  INFO_STR info_str;
  InitNextSS InitNextSS; //структура для параметров последовательного чтения строк
  WRITE_SHTRIH_FILE WrShtrih; //структура, содержащая информацию о записываемом штрих-файле
  NameToMetka2  Name2;   //имя файла при 2х-байтовой метке
  NameToMetka4  Name4;   //имя файла при 4х-байтовой метке


  void  GetInfo(void);
  bool  WriteMetka(void *Mas);
  bool  ReadMetka(void *Mas);
  void  CreatKatalog(void);
  char  DetectTypeShtrih(void);
  bool  rdblock(void *block,long &Nbl, long Kbl, long Ost, unsigned int &ke_block);
  bool  wrblock(void *block,unsigned int ke_block);
  bool  RewindMetrika(void);
  int   GetString(void *Mas);
  int   GetStringAllFormat(long *Mas);
  void  EndWriteFile(void);
  void  WriteRegion();
  bool  CheckStroka(void *Mas, long Ns, int &LenStr);
  void  PrintErrorMessage();

  void _PutXmin(long T);
  void _PutXmax(long T);
  void _PutYmin(long T);
  void _PutYmax(long T);
  void _PutInf_Xmin(long T);
  void _PutInf_Xmax(long T);
  void _PutInf_Ymin(long T);
  void _PutInf_Ymax(long T);
  void  InitVariable(void);


public:

  int ErrorCode;
  SHTRIH();
  SHTRIH(long Size);
  ~SHTRIH();
//SHTRIHEXTERNFUNC  void SHTRIHEXPORTFUNC InitStr(char *Name,char regim,char ShtrihFormat);
  void InitStr(char *Name,char regim,char ShtrihFormat=NOSHTRIH_FORMAT);
//Автоматическое определение формата файла штрихов
  bool DeterminationFormatFile(char Ff=NOSHTRIH_FORMAT);
//возвращает информацию об открытом файле
  bool GetInfoStr(INFO_STR &info);
//**********************************************************
// Функции для работы с меткой файла в режиме ЧТЕНИЯ
//**********************************************************
//возвращает значение позиции Np (1<= Np <= 256)метки
  long GetPos(short Np);
//возвращает формат файла (1 позиция метки)
  long GetTypeFile(void);
//возвращает картографическое имя док-та
  void GetName(char *NameDoc, int &ks);
//возвращает номер части листа
  long GetNumberPaper(void);
//возвращает тип штрихов
  long GetTypeShtrih(void);
//возвращает тип привязки штрихов
  long GetTypePrivShtrih(void);
//возвращает цену ед. растра в 0.1 мм
  long GetRastrUnit(void);
//возвращает минимум по оси ОХ растра
  long GetXmin(void);
//возвращает максимум по оси ОХ растра
  long GetXmax(void);
//возвращает минимум по оси ОY растра
  long GetYmin(void);
//возвращает максимум по оси ОY растра
  long GetYmax(void);
//возвращает шаг дискретизации по оси Ox(20 позиция)
  float GetPixX(void);
//возвращает шаг дискретизации по оси Oy(22 позиция)
  float GetPixY(void);
//возвращает число страниц (блоков) метрики файла в словах (33 позиция)
  long GetCountPage(void);
//возвращает длину занятой части последней страницы в словах (34 позиция)
  long GetLengthLastPage(void);
//возвращает длину страницы в словах (35 позиция)
  long GetLengthPage(void);
//возвращает минимум по оси ОХ информационной области документа (51 позиция)
  long GetInf_Xmin(void);
//возвращает максимум по оси ОХ информационной области документа (52 позиция)
  long GetInf_Xmax(void);
//возвращает минимум по оси ОY информационной области документа (53 позиция)
  long GetInf_Ymin(void);
//возвращает максимум по оси ОХ информационной области документа (54 позиция)
  long GetInf_Ymax(void);
/*
//возвращает размер рамки информационной области по оси ОХ (60 позиция)
     long GetInf_Dx(void);
//возвращает размер рамки информационной области по оси ОY (61 позиция)
     long GetInf_Dy(void);
*/
//возвращает указатель на массив, содержащий смещение привязки координаты
  void GetBegin_List(long *Mas);
//возвращает указатель на массив из 8 целочисленных элементов, содержащий
//растровые координаты привязочных "крестов"
  void GetRastr_Krest(long *Mas);
// возвращает указатель на массив из 8 элементов, содержащий
// растровые координаты пересчитанных привязочных "крестов"
  void GetConvrRastr_Krest(long *Mas);
//возвращает указатель на массив из 8 вещественных элементов, содержащий
//теоретические координаты привязочных "крестов" в дискретах по 0.1 мм
  void GetTeor_Krest(double* Mas);

//****************************************************************************
// Функции чтения строки (или последовательного чтения строк) из штрих-файла
//****************************************************************************

// Чтение строки с номером N
  int GetString(void *Mas, long N);
  int GetStringAllFormat(long *Mas, long N);
  void GetStringAllFormat(STROKA_4 &stroka, long N);

  void GetString(STROKA_2 &stroka, long N);
  void GetString(STROKA_2U &stroka, long N);
  void GetString(STROKA_1 &stroka, long N);
  void GetString(STROKA_4 &stroka, long N);
// Инициализация последовательного чтения строк штрихов
  void InitGetNextSS(long Beg,long End);
// Функции последовательного чтения строк штрих-файла
  void GetNextString(STROKA_2 &stroka);
  void GetNextString(STROKA_2U &stroka);
  void GetNextString(STROKA_1 &stroka);
  void GetNextString(STROKA_4 &stroka);

  void GetNextStringAllFormat(STROKA_4 &stroka);


//**********************************************************
//  Функции для работы с меткой штрих-файла в режиме ЗАПИСИ
//**********************************************************

//Функции копирования метки
  void CopyMetka(void *Metka);
  void CopyMetka(SHTRIH &Src);
  void CopyMetka(SHTRIH *Src);
//устанавливает значение позиции Np (1<= Np <= 256)метки
  void PutPos(short Np, long T);
  void PutPos(short Np, short T);
  void PutPos(short Np, unsigned short T);
//устанавливает тип файла (1 позиция метки)
  void PutTypeFile(long T);
//устанавливает картографическое имя док-та (2-8 позиции метки)
  void PutName(char *NameDoc);
//устанавливает номер части листа (9-позиция метки)
  void PutNumberPaper(long T);
//устанавливает тип штрихов
  void PutTypeShtrih(long T);
//устанавливает тип привязки штрихов
  void PutTypePrivShtrih(long T);
//устанавливает  цену ед. растра в 0.1 мм (14 позиция метки)
  void PutRastrUnit(long T);
//устанавливает минимум по оси ОХ растра (16 позиция)
  void PutXmin(long T);
//устанавливает максимум по оси ОХ растра (17 позиция)
  void PutXmax(long T);
//устанавливает минимум по оси ОY растра (18 позиция)
  void PutYmin(long T);
//устанавливает максимум по оси ОY растра (19 позиция)
  void PutYmax(long T);
//устанавливает шаг дискретизации по оси Ox(20 позиция)
  void PutPixX(float Hpix);
//устанавливает шаг дискретизации по оси Oy(22 позиция)
  void PutPixY(float Hpix);
//устанавливает число страниц (блоков) метрики файла в словах (33 позиция)
  void PutCountPage(long T);
//устанавливает длину занятой части последней страницы в словах (34 позиция)
  void PutLengthLastPage(long T);
//устанавливает длину страницы в словах (35 позиция)
  void PutLengthPage(long T);
//устанавливает минимум по оси ОХ информационной области документа (51 позиция)
  void PutInf_Xmin(long T);
//устанавливает максимум по оси ОХ информационной области документа (52 позиция)
  void PutInf_Xmax(long T);
//устанавливает минимум по оси ОY информационной области документа (53 позиция)
  void PutInf_Ymin(long T);
//устанавливает максимум по оси ОХ информационной области документа (54 позиция)
  void PutInf_Ymax(long T);
/*
//устанавливает размер рамки информационной области по оси ОХ (60 позиция)
     void PutInf_Dx(long T);
//устанавливает размер рамки информационной области по оси ОY (61 позиция)
     void PutInf_Dy(long T);
*/
//устанавливает растровые координаты ЮЗ угла листа (70 - 71 позиции)
  void PutBegin_List(void *);
//устанавливает растровые координаты привязочных "крестов" (86-93 позиции)
  void PutRastr_Krest(void *);
//записывает массив из 8 элементов, содержащий
//растровые координаты пересчитанных привязочных "крестов"
  void PutConvrRastr_Krest(void *);
//устанавливает теоретические координаты привязочных "крестов"
//в дискретах по 0.1 мм (94-101 - теоретич. координаты; 102-109 - мантисса * 10000)
  void PutTeor_Krest(double *);

  void PutString(void *Mas, int LenStroka);
  void PutString(STROKA_2 &stroka);
  void PutString(STROKA_2U &stroka);
  void PutString(STROKA_1 &stroka);
  void PutString(STROKA_4 &stroka);
  void PutStringAllFormat(STROKA_4 &stroka);
// Заполнение метки файла по данным структуры INFO_STR
  bool PutInfoStr(INFO_STR &info);
// Копирует некоторые поля из структуры src в структуру dest
  bool CopyInfoStr(INFO_STR &dest,INFO_STR &src);
};
#endif







