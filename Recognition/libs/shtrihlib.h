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
  int   nui;   //����� ���������� �� ������� ������ ���� �������
  int   nuk;   //����� ���������� �� ������� ������ ���� �������� �����
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
  InitNextSS InitNextSS; //��������� ��� ���������� ����������������� ������ �����
  WRITE_SHTRIH_FILE WrShtrih; //���������, ���������� ���������� � ������������ �����-�����
  NameToMetka2  Name2;   //��� ����� ��� 2�-�������� �����
  NameToMetka4  Name4;   //��� ����� ��� 4�-�������� �����


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
//�������������� ����������� ������� ����� �������
  bool DeterminationFormatFile(char Ff=NOSHTRIH_FORMAT);
//���������� ���������� �� �������� �����
  bool GetInfoStr(INFO_STR &info);
//**********************************************************
// ������� ��� ������ � ������ ����� � ������ ������
//**********************************************************
//���������� �������� ������� Np (1<= Np <= 256)�����
  long GetPos(short Np);
//���������� ������ ����� (1 ������� �����)
  long GetTypeFile(void);
//���������� ���������������� ��� ���-��
  void GetName(char *NameDoc, int &ks);
//���������� ����� ����� �����
  long GetNumberPaper(void);
//���������� ��� �������
  long GetTypeShtrih(void);
//���������� ��� �������� �������
  long GetTypePrivShtrih(void);
//���������� ���� ��. ������ � 0.1 ��
  long GetRastrUnit(void);
//���������� ������� �� ��� �� ������
  long GetXmin(void);
//���������� �������� �� ��� �� ������
  long GetXmax(void);
//���������� ������� �� ��� �Y ������
  long GetYmin(void);
//���������� �������� �� ��� �Y ������
  long GetYmax(void);
//���������� ��� ������������� �� ��� Ox(20 �������)
  float GetPixX(void);
//���������� ��� ������������� �� ��� Oy(22 �������)
  float GetPixY(void);
//���������� ����� ������� (������) ������� ����� � ������ (33 �������)
  long GetCountPage(void);
//���������� ����� ������� ����� ��������� �������� � ������ (34 �������)
  long GetLengthLastPage(void);
//���������� ����� �������� � ������ (35 �������)
  long GetLengthPage(void);
//���������� ������� �� ��� �� �������������� ������� ��������� (51 �������)
  long GetInf_Xmin(void);
//���������� �������� �� ��� �� �������������� ������� ��������� (52 �������)
  long GetInf_Xmax(void);
//���������� ������� �� ��� �Y �������������� ������� ��������� (53 �������)
  long GetInf_Ymin(void);
//���������� �������� �� ��� �� �������������� ������� ��������� (54 �������)
  long GetInf_Ymax(void);
/*
//���������� ������ ����� �������������� ������� �� ��� �� (60 �������)
     long GetInf_Dx(void);
//���������� ������ ����� �������������� ������� �� ��� �Y (61 �������)
     long GetInf_Dy(void);
*/
//���������� ��������� �� ������, ���������� �������� �������� ����������
  void GetBegin_List(long *Mas);
//���������� ��������� �� ������ �� 8 ������������� ���������, ����������
//��������� ���������� ����������� "�������"
  void GetRastr_Krest(long *Mas);
// ���������� ��������� �� ������ �� 8 ���������, ����������
// ��������� ���������� ������������� ����������� "�������"
  void GetConvrRastr_Krest(long *Mas);
//���������� ��������� �� ������ �� 8 ������������ ���������, ����������
//������������� ���������� ����������� "�������" � ��������� �� 0.1 ��
  void GetTeor_Krest(double* Mas);

//****************************************************************************
// ������� ������ ������ (��� ����������������� ������ �����) �� �����-�����
//****************************************************************************

// ������ ������ � ������� N
  int GetString(void *Mas, long N);
  int GetStringAllFormat(long *Mas, long N);
  void GetStringAllFormat(STROKA_4 &stroka, long N);

  void GetString(STROKA_2 &stroka, long N);
  void GetString(STROKA_2U &stroka, long N);
  void GetString(STROKA_1 &stroka, long N);
  void GetString(STROKA_4 &stroka, long N);
// ������������� ����������������� ������ ����� �������
  void InitGetNextSS(long Beg,long End);
// ������� ����������������� ������ ����� �����-�����
  void GetNextString(STROKA_2 &stroka);
  void GetNextString(STROKA_2U &stroka);
  void GetNextString(STROKA_1 &stroka);
  void GetNextString(STROKA_4 &stroka);

  void GetNextStringAllFormat(STROKA_4 &stroka);


//**********************************************************
//  ������� ��� ������ � ������ �����-����� � ������ ������
//**********************************************************

//������� ����������� �����
  void CopyMetka(void *Metka);
  void CopyMetka(SHTRIH &Src);
  void CopyMetka(SHTRIH *Src);
//������������� �������� ������� Np (1<= Np <= 256)�����
  void PutPos(short Np, long T);
  void PutPos(short Np, short T);
  void PutPos(short Np, unsigned short T);
//������������� ��� ����� (1 ������� �����)
  void PutTypeFile(long T);
//������������� ���������������� ��� ���-�� (2-8 ������� �����)
  void PutName(char *NameDoc);
//������������� ����� ����� ����� (9-������� �����)
  void PutNumberPaper(long T);
//������������� ��� �������
  void PutTypeShtrih(long T);
//������������� ��� �������� �������
  void PutTypePrivShtrih(long T);
//�������������  ���� ��. ������ � 0.1 �� (14 ������� �����)
  void PutRastrUnit(long T);
//������������� ������� �� ��� �� ������ (16 �������)
  void PutXmin(long T);
//������������� �������� �� ��� �� ������ (17 �������)
  void PutXmax(long T);
//������������� ������� �� ��� �Y ������ (18 �������)
  void PutYmin(long T);
//������������� �������� �� ��� �Y ������ (19 �������)
  void PutYmax(long T);
//������������� ��� ������������� �� ��� Ox(20 �������)
  void PutPixX(float Hpix);
//������������� ��� ������������� �� ��� Oy(22 �������)
  void PutPixY(float Hpix);
//������������� ����� ������� (������) ������� ����� � ������ (33 �������)
  void PutCountPage(long T);
//������������� ����� ������� ����� ��������� �������� � ������ (34 �������)
  void PutLengthLastPage(long T);
//������������� ����� �������� � ������ (35 �������)
  void PutLengthPage(long T);
//������������� ������� �� ��� �� �������������� ������� ��������� (51 �������)
  void PutInf_Xmin(long T);
//������������� �������� �� ��� �� �������������� ������� ��������� (52 �������)
  void PutInf_Xmax(long T);
//������������� ������� �� ��� �Y �������������� ������� ��������� (53 �������)
  void PutInf_Ymin(long T);
//������������� �������� �� ��� �� �������������� ������� ��������� (54 �������)
  void PutInf_Ymax(long T);
/*
//������������� ������ ����� �������������� ������� �� ��� �� (60 �������)
     void PutInf_Dx(long T);
//������������� ������ ����� �������������� ������� �� ��� �Y (61 �������)
     void PutInf_Dy(long T);
*/
//������������� ��������� ���������� �� ���� ����� (70 - 71 �������)
  void PutBegin_List(void *);
//������������� ��������� ���������� ����������� "�������" (86-93 �������)
  void PutRastr_Krest(void *);
//���������� ������ �� 8 ���������, ����������
//��������� ���������� ������������� ����������� "�������"
  void PutConvrRastr_Krest(void *);
//������������� ������������� ���������� ����������� "�������"
//� ��������� �� 0.1 �� (94-101 - ��������. ����������; 102-109 - �������� * 10000)
  void PutTeor_Krest(double *);

  void PutString(void *Mas, int LenStroka);
  void PutString(STROKA_2 &stroka);
  void PutString(STROKA_2U &stroka);
  void PutString(STROKA_1 &stroka);
  void PutString(STROKA_4 &stroka);
  void PutStringAllFormat(STROKA_4 &stroka);
// ���������� ����� ����� �� ������ ��������� INFO_STR
  bool PutInfoStr(INFO_STR &info);
// �������� ��������� ���� �� ��������� src � ��������� dest
  bool CopyInfoStr(INFO_STR &dest,INFO_STR &src);
};
#endif







