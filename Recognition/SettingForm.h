//---------------------------------------------------------------------------

#ifndef SettingFormH
#define SettingFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TSettingWindow : public TForm
{
__published:	// IDE-managed Components
        TCheckBox *DeskewBox;
        TCheckBox *OrientBox;
        TButton *okButton;
        TLabel *Label1;
        void __fastcall okButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TSettingWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSettingWindow *SettingWindow;
//---------------------------------------------------------------------------
#endif
