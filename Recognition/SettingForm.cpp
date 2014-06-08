//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SettingForm.h"
#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSettingWindow *SettingWindow;
//---------------------------------------------------------------------------
__fastcall TSettingWindow::TSettingWindow(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSettingWindow::okButtonClick(TObject *Sender)
{
SettingWindow->Close();
}
//---------------------------------------------------------------------------

