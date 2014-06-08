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

//  ����� ������
#define  REGWRITE     1    //����� �������� �����-�����
#define  REGREAD      2    //����� ������ �����-�����
#define  REGUPDATE    3    //����� ��������� ����� �����-�����

//  �������� ������ �������� ������ ��� ������� �������
#define  SIZETMPBUFER   327680
#define  SIZETMPBUFMIN   65536

//  �������� ������ �������� ������ ��� ��������� ����������
#define  MAXTXT      100
//  ������� ����� ������� (��������� ������ ��� �������� �����-�����)
#define NOSHTRIH_FORMAT  0 //���������� �������������� ����������� �������
#define SHTRIH_FORMAT_1  1 //1 ������� �����-������(����� ����� � �������
                           //����� �������� ������������ ��������.)
#define SHTRIH_FORMAT_2  2 //2 ������� �����-������(����� ����� � �������
                           //����� ����������� ������������ ��������.)
#define SHTRIH_FORMAT_3  3 //1 �������������� �����-������(����� ����� -
                           //����� �������� ������������ ��������, ������� -
                           //����� ����������� ������������ ��������.)
#define SHTRIH_FORMAT_4  4 //2 �������������� �����-������(����� ����� -
                           //����� ����������� ������������ ��������, ������� -
                           //����� �������� ��������������� ��������
#define SHTRIH_FORMAT_5  5 //3 �������������� �����-������(����� ����� � �������
                           //����� �������� ��������������� ��������.)

//  ����� �������� �����-�����(1-�� ������� ����� �����-�����)
#define BASESTRFORMAT     3
#define ADD1STRFORMAT   321
#define ADD2STRFORMAT   324
#define ADD3STRFORMAT   344

//  ��� �������(12-�� ������� ����� �����-�����)
#define OLDTYPESTR     1  //������ � ���� 8002/8093 � ������ "�����"
#define NEWTYPESTR     2  //������ � ���� 8093 � ������ "����� �" ���
                          //� ���� 8094/8094�
#define USRTYPESTR     3  //������, �������������� ��������

//  ��� �������� �������(13-�� ������� ����� �����-�����)
#define PRIVMNK            0  //�� ���
#define PRIVFOURCORNER     1  //�� 4 �����
#define PRIVGREEDSQUARE    2  //�� ����� ���������

//  ����� ����� ������� � ������(35-�� ������� ����� �����-�����)
#define PAGESIZE        3072

//  ������������ ������� ��������� ������ ��� ��������� ��������
#define MAXSHTRIH1      32760     //��� 1 ������� �� ����� ����� � �� ����� �������� � ������
#define MAXSHTRIH2      65520     //��� 2 ������� �� ����� ����� � �� ����� �������� � ������
#define MAXXSHTRIH3     65520     //��� 3 ������� �� ����� �����
#define MAXYSHTRIH3       250     //��� 3 ������� �� ����� �������� � ������
#define MAXSHTRIH4   LONG_MAX-10  //��� 4 � 5  �������� �� ����� ����� � �� ����� �������� � ������
//  ��� ������������� ( ������ ������� �� ���� � ��) �� ���������
#define HPIX            0.03
//  ���������� �� �������� ����� �������
typedef struct
{
   bool  FlagInfo;           //���� ������������� ���������
   char  NameFile[MAXPATH];  //������ ��� ��������� �����
   char  Regim;              //����� �������� �����
   long  FormatFile;         //������ ����� �������
   long  TypeShtrih;         //��� �������
   long  TypePrivShtrih;     //��� �������� �������
   long  XminRastr;          //����������
   long  XmaxRastr;          //�����
   long  YminRastr;          //���������
   long  YmaxRastr;          //�������
   long  XminInf;            //����������
   long  XmaxInf;            //�����
   long  YminInf;            //��������������
   long  YmaxInf;            //�������
   float Hx_Pix;             //������ ������� �� ��� OX
   float Hy_Pix;             //������ ������� �� ��� OY
   long  CountPage;          //���������� �������(������) �������
   long  LengthLastPage;     //����� ������� ����� ��������� ��������(�����) �������
   long  LengthPage;         //������ ��������(�����) �������
   long  Null_X;             //�������� �������� ���������� �� ��� OX � ��. ������
   long  Null_Y;             //�������� �������� ���������� �� ��� OY � ��. ������
   long  PRK[8];             //������������� ��������� ���������� �������
   long  RK[8];              //��������� ���������� �������
   double TK[8];             //������������� ���������� ������� (� 0.1 ��)
   long  CoShtrihStrokaMax;  //���. ����� ������� � ������
   long  CoShtrihFile;       //����� ����� ������� � �����
   long  CoNullStroka;       //����� ����� ������ ����� � �����
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
typedef struct   //��������� ��� ���������� ����������������� ������ �����
{
  long Beg;           //��������� ����� ������
  long End;           //�������� ����� ������
  long Tek;           //������� ����� ������
  long MyOffsetT;     //�������� �� ��������� ������
  long MyOffsetS;     //�������� �� �������� ������
  long kbrAll;        //����� ���������� ���� ��� ������ ���� �����
  long kblM;          //���-�� ������, �������� SizeBuffer ���� ��� ������ �������
  long ostM;          //������� � ��������� �����
  long nblM;          //����� �������� �����
  unsigned int i_rd;  //������� ����������
  unsigned int ne_rd; //������� ����������
}InitNextSS;

typedef struct
{
  long KWordFile;    //���������� (1, 2, ��� 4)-�������� ���� � ����������� �����-�����
  long SizeBlokFile; //����� ����� ������ ������� ����� �(1, 2, ��� 4)-�������� ������
  long SizeFile;     //����� ����� � ������, �������� ������ �-���� ����� ��������� ������� ����� ������� �����
  unsigned int ke;
  unsigned int KeBufMx;
  long KblWr;        //����� ������������ ������ ������ �������
  long NstrTek;      //����� ������� ������������ ������
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







