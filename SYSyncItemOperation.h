//---------------------------------------------------------------------------

#ifndef SYSyncItemOperationH
#define SYSyncItemOperationH
#include "SYSyncOperationQueue.h"
//---------------------------------------------------------------------------
class SYSyncItemOperation : public SYOperation
{
public:
  	SYSyncItemOperation(int id, int delay);
    	~SYSyncItemOperation();
    	void Main(void);
private:

};
#endif

