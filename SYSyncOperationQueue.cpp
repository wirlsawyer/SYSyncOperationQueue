//---------------------------------------------------------------------------
#pragma hdrstop
#include "SYSyncOperationQueue.h"

//---------------------------------------------------------------------------
SYSyncOperationQueue::SYSyncOperationQueue()
: TThread(true)
{
    InitializeCriticalSection(&m_hMutex);
    m_pCurOperation = NULL;
    m_pVecQueue   = new std::vector<SYOperation*>;
    m_RunMaxCount = 0;
    flag_Start    = false;
    flag_Doing    = false;
    this->Resume();
}

__fastcall SYSyncOperationQueue::~SYSyncOperationQueue()
{
	this->Stop();
        m_pCurOperation = NULL;

	if (m_pVecQueue)
	{
		//clear
		while(!m_pVecQueue->empty())
		{
			delete m_pVecQueue->back();
			m_pVecQueue->pop_back();
		}
		delete m_pVecQueue;
	}
        this->Terminate();
}

void __fastcall SYSyncOperationQueue::Sync()
{
       m_pCurOperation->Main();
}

void __fastcall SYSyncOperationQueue::Execute(void)
{

	while (true)
	{
        	//EnterCriticalSection( &m_hMutex );
    	        if (this->flag_Start && this->flag_Doing == false)
                {
                        flag_Doing = true;
                 	m_pCurOperation = this->GetFirstItem();

    			if (m_pCurOperation == NULL)
        		{
                             flag_Doing = false;
    			}else{
                             DelayWithMilliSecond(m_pCurOperation->Delay);
                	     Synchronize(Sync);
           		     delete m_pCurOperation;
                   	     m_pCurOperation = NULL;

        		}
                }
                flag_Doing = false;
                //LeaveCriticalSection( &m_hMutex );
                DelayWithMilliSecond(10);
    	}//end while
}


void SYSyncOperationQueue::Start(int count)
{
        //EnterCriticalSection( &m_hMutex );
	m_RunMaxCount = count;
        this->flag_Start = true;
        //LeaveCriticalSection( &m_hMutex );

}

void SYSyncOperationQueue::Stop(void)
{
	//EnterCriticalSection( &m_hMutex );
	flag_Start = false;
        //LeaveCriticalSection( &m_hMutex );
}

void SYSyncOperationQueue::Clean(void)
{
        //EnterCriticalSection( &m_hMutex );
	flag_Start = false;
        while(flag_Doing)
        {
        	DelayWithMilliSecond(10);
        }
        //clear
   	while(!m_pVecQueue->empty())
   	{
   		delete m_pVecQueue->back();
   		m_pVecQueue->pop_back();
   	}

        this->flag_Start = true;
        //LeaveCriticalSection( &m_hMutex );
}

void SYSyncOperationQueue::CleanWithID(int ID)
{
	flag_Start = false;
        while(flag_Doing)
        {
        	DelayWithMilliSecond(10);
        }

        //clear
        std::vector<SYOperation *>::iterator iter = m_pVecQueue->begin();
    	while (iter != m_pVecQueue->end())   
        {
        	SYOperation *oper = *iter;
                if (oper->ID == ID) {
                   m_pVecQueue->erase(iter);
                   delete oper;
                } else {
                   ++iter;
                }
        }

        this->flag_Start = true;
}

void SYSyncOperationQueue::AddOperation(SYOperation *item)
{
	//EnterCriticalSection( &m_hMutex );
 	m_pVecQueue->push_back(item);
        //LeaveCriticalSection( &m_hMutex );
}

SYOperation *SYSyncOperationQueue::GetFirstItem(void)
{
        //EnterCriticalSection( &m_hMutex );
	if (m_pVecQueue->empty()) return NULL;
    	SYOperation *pResult;
   	pResult = m_pVecQueue->at(0);
	m_pVecQueue->erase(m_pVecQueue->begin());
        //LeaveCriticalSection( &m_hMutex );
    	return pResult;
}

void __fastcall SYSyncOperationQueue::DelayWithMilliSecond(unsigned int ms)
{
    DWORD dwBeginTime = GetTickCount();
    while(true)
    {
    	DWORD dwCurTime = GetTickCount();
    	if((dwCurTime - dwBeginTime) > ms)
    	{
    		break;
    	}
    	//Dovenets
    	MSG msg;
    	while (PeekMessage( & msg, NULL,  0 ,  0 , PM_REMOVE))
    	{
    		TranslateMessage( & msg);
    		DispatchMessage( & msg);
    	}
    }
}


