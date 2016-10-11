//---------------------------------------------------------------------------
#pragma hdrstop
#include "SYSyncItemOperation.h"
//---------------------------------------------------------------------------
SYSyncItemOperation::SYSyncItemOperation(int id, int delay)
{
	this->ID = id;
        this->Delay = delay;
}

SYSyncItemOperation::~SYSyncItemOperation()
{

}

void SYSyncItemOperation::Main(void)
{
    wchar_t wszBuf[256];
    memset(wszBuf, 0, sizeof(wszBuf));

    wsprintf(wszBuf, L"ID=%d Dleay=%d\n", this->ID, this->Delay);
    OutputDebugString(wszBuf);
}

