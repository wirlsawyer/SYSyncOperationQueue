//---------------------------------------------------------------------------

#ifndef SYSyncOperationQueueH
#define SYSyncOperationQueueH
#include <vcl.h>
#include <vector>
//---------------------------------------------------------------------------
class SYOperation
{
public:
	SYOperation(){Delay = 0;}
	virtual	void Main() = 0;

	__property int ID = { read = m_ID, write = m_ID };
        __property unsigned int Delay = { read = m_Delay, write = m_Delay };
private:
        int m_ID;
        unsigned int m_Delay;
};

//---------------------------------------------------------------------------
class SYSyncOperationQueue : public TThread
{
public:
     SYSyncOperationQueue();
     __fastcall ~SYSyncOperationQueue(void);
     void Start(int count=1);
     void Stop(void);
     void Clean(void);
     void CleanWithID(int ID);
     void AddOperation(SYOperation *item);
private:
     virtual void __fastcall Execute(void);
     void __fastcall Sync(void);
     SYOperation *GetFirstItem(void);
     void __fastcall DelayWithMilliSecond(unsigned int ms);
private:
    CRITICAL_SECTION  m_hMutex;
    std::vector<SYOperation*>* m_pVecQueue;
    int		m_RunMaxCount;
    SYOperation *m_pCurOperation;
public:
    bool	flag_Start;
    bool	flag_Doing;
	
};
#endif

