//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "SYSyncOperationQueue.h"
#include "SYSyncItemOperation.h"
SYSyncOperationQueue *g_queue = new SYSyncOperationQueue();
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
    	g_queue->Start();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	g_queue->Clean();
	for (int i = 0; i < 100; i++)
        {
            SYSyncItemOperation *operation = new SYSyncItemOperation(i, i);
            g_queue->AddOperation((SYOperation *)operation);
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
 	//g_queue->Stop();
        for (int i = 40; i < 100; i++) {
          g_queue->CleanWithID(i);
        }
}
//---------------------------------------------------------------------------

