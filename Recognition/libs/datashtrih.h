#ifndef __DATASHTRIH_H
#define __DATASHTRIH_H

#if !defined(__WINDOWS_H)
#include <windows.h>
#endif

#if !defined(__VCL_H)
#include <vcl.h>
#endif

#if !defined(__STAT_H)
#include <sys\stat.h>
#endif

#if !defined(__MATH_H)
#include <math.h>
#endif

#if !defined(__IO_H)
#include <io.h>
#endif

#if !defined(__FCNTL_H)
#include <fcntl.h>
#endif

#if !defined(__STRIHG_H)
#include <string.h>
#endif

#if !defined(__CONIO_H)
#include <conio.h>
#endif

#if !defined(__STDIO_H)
#include <stdio.h>
#endif

#if !defined(__DIR_H)
#include <dir.h>
#endif

#if !defined(__LIMITS_H)
#include <limits.h>
#endif

//#pragma option push
#pragma option -a1

//  Режим работы
#define  REGWRITE     1    //режим создания штрих-файла
#define  REGREAD      2    //режим чтения штрих-файла
#define  REGUPDATE    3    //режим изменения метки штрих-файла

//  Байтовый размер рабочего буфера под метрику штрихов
#define  SIZETMPBUFER   327680
#define  SIZETMPBUFMIN   65536

//  Байтовый размер рабочего буфера под текстовые переменные
#define  MAXTXT      100
//  Форматы файла штрихов (действует только при создании штрих-файла)
#define NOSHTRIH_FORMAT  0 //Невозможно автоматическое определение формата
#define SHTRIH_FORMAT_1  1 //1 базовый штрих-формат(метка файла и метрика
                           //целые знаковые двухбайтовые величины.)
#define SHTRIH_FORMAT_2  2 //2 базовый штрих-формат(метка файла и метрика
                           //целые беззнаковые двухбайтовые величины.)
#define SHTRIH_FORMAT_3  3 //1 дополнительный штрих-формат(метка файла -
                           //целые знаковые двухбайтовые величины, метрика -
                           //целые беззнаковые однобайтовые величины.)
#define SHTRIH_FORMAT_4  4 //2 дополнительный штрих-формат(метка файла -
                           //целые беззнаковые двухбайтовые величины, метрика -
                           //целые знаковые четырехбайтовые величины
#define SHTRIH_FORMAT_5  5 //3 дополнительный штрих-формат(метка файла и метрика
                           //целые знаковые четырехбайтовые величины.)

//  Флаги форматов штрих-файла(1-ая позиция метки штрих-файла)
#define BASESTRFORMAT     3
#define ADD1STRFORMAT   321
#define ADD2STRFORMAT   324
#define ADD3STRFORMAT   344

//  Тип штрихов(12-ая позиция метки штрих-файла)
#define OLDTYPESTR     1  //Штрихи с УВГИ 8002/8093 в режиме "Штрих"
#define NEWTYPESTR     2  //Штрихи с УВГИ 8093 в режиме "Штрих М" или
                          //с УВГИ 8094/8094М
#define USRTYPESTR     3  //Штрихи, дополнительных форматов

//  Тип привязки штрихов(13-ая позиция метки штрих-файла)
#define PRIVMNK            0  //по МНК
#define PRIVFOURCORNER     1  //по 4 углам
#define PRIVGREEDSQUARE    2  //по сетке квадратов

//  Длина блока метрики в словах(35-ая позиция метки штрих-файла)
#define PAGESIZE        3072

//  Максимальные размеры штриховых матриц для различных форматов
#define MAXSHTRIH1      32760     //Для 1 формата по числу строк и по числу пикселей в строке
#define MAXSHTRIH2      65520     //Для 2 формата по числу строк и по числу пикселей в строке
#define MAXXSHTRIH3     65520     //Для 3 формата по числу строк
#define MAXYSHTRIH3       250     //Для 3 формата по числу пикселей в строке
#define MAXSHTRIH4   LONG_MAX-10  //Для 4 и 5  форматов по числу строк и по числу пикселей в строке
//  Шаг дискретизации ( размер пикселя по осям в мм) по умолчанию
#define HPIX            0.03
//  Информация об открытом файле штрихов
typedef struct
{
   bool  FlagInfo;           //флаг заполненности структуры
   char  NameFile[MAXPATH];  //полное имя открытого файла
   char  Regim;              //Режим открытия файла
   long  FormatFile;         //Формат файла штрихов
   long  TypeShtrih;         //Тип штрихов
   long  TypePrivShtrih;     //Тип привязки штрихов
   long  XminRastr;          //Координаты
   long  XmaxRastr;          //углов
   long  YminRastr;          //растровой
   long  YmaxRastr;          //области
   long  XminInf;            //Координаты
   long  XmaxInf;            //углов
   long  YminInf;            //информационной
   long  YmaxInf;            //области
   float Hx_Pix;             //Размер пикселя по оси OX
   float Hy_Pix;             //Размер пикселя по оси OY
   long  CountPage;          //Количество страниц(блоков) метрики
   long  LengthLastPage;     //Длина занятой части последней страницы(блока) метрики
   long  LengthPage;         //Размер страницы(блока) метрики
   long  Null_X;             //Смещение привязки координаты по оси OX в ед. растра
   long  Null_Y;             //Смещение привязки координаты по оси OY в ед. растра
   long  PRK[8];             //Пересчитанные растровые координаты крестов
   long  RK[8];              //Растровые координаты крестов
   double TK[8];             //Теоретические координаты крестов (в 0.1 мм)
   long  CoShtrihStrokaMax;  //Мах. число штрихов в строке
   long  CoShtrihFile;       //Общее число штрихов в файле
   long  CoNullStroka;       //Общее число пустых строк в файле
}INFO_STR;

typedef struct
{
   union{unsigned char xn; unsigned char yn;};
   union{unsigned char xk; unsigned char yk;};
}SHTRIH_1;

typedef struct
{
   union{short xn; short yn;};
   union{short xk; short yk;};
}SHTRIH_2;

typedef struct
{
   union{unsigned short xn; unsigned short yn;};
   union{unsigned short xk; unsigned short yk;};
}SHTRIH_2U;

typedef struct
{
   union{long xn; long yn;};
   union{long xk; long yk;};
}SHTRIH_4;

/*
unsigned char *PtrString1;
short *PtrString2;
unsigned short *PtrString2U;
long *PtrString4;

SHTRIH_1  *String1Byte;
SHTRIH_2  *String2Byte;
SHTRIH_2U *String2UByte;
SHTRIH_4  *String4Byte;
*/
typedef struct
{
  int Length;
  SHTRIH_1 *Stroka;
}STROKA_1;

typedef struct
{
  int Length;
  SHTRIH_2 *Stroka;
}STROKA_2;

typedef struct
{
  int Length;
  SHTRIH_2U *Stroka;
}STROKA_2U;

typedef struct
{
  int Length;
  SHTRIH_4 *Stroka;
}STROKA_4;

typedef struct
{
  int Length;
  void *Stroka;
}STROKA;
//STROKA stroka;
typedef struct   //структура для параметров последовательного чтения строк
{
  long Beg;           //начальный номер строки
  long End;           //конечный номер строки
  long Tek;           //текущий номер строки
  long MyOffsetT;     //смещение до начальной строки
  long MyOffsetS;     //смещение до конечной строки
  long kbrAll;        //общее количество байт для чтения всех строк
  long kblM;          //кол-во блоков, размером SizeBuffer байт для чтения метрики
  long ostM;          //остаток в последнем блоке
  long nblM;          //номер текущего блока
  unsigned int i_rd;  //рабочая переменная
  unsigned int ne_rd; //рабочая переменная
}InitNextSS;

typedef struct
{
  long KWordFile;    //количество (1, 2, или 4)-байтовых слов в формируемом штрих-файле
  long SizeBlokFile; //длина блока записи метрики файла в(1, 2, или 4)-байтовых словах
  long SizeFile;     //длина файла в блоках, байтовый размер к-рого равен байтовому размеру метки данного файла
  unsigned int ke;
  unsigned int KeBufMx;
  long KblWr;        //число библиотечных блоков записи метрики
  long NstrTek;      //номер текущей записываемой строки
}WRITE_SHTRIH_FILE;

union ShortToLong
{
   long Lp;
   short Sp[2];
};
union NameToMetka2
{
   short Z[7];
   char  Text[14];
};

union NameToMetka4
{
   short Z[7];
   char  Text[28];
};

#pragma option -a4

#endif







